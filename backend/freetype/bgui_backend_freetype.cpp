#include <bgui_backend_freetype.hpp>
#include <unordered_map>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

static std::unordered_map<std::string, std::string> s_system_fonts;
static FT_Library s_ft;

void bkend::set_up_freetype() {
    if (FT_Init_FreeType(&s_ft)) {
        throw std::runtime_error("Error initializing Freetype.");
    }
    ft_search_system_fonts();
    ft_load_font("Noto Sans-Condensed", s_system_fonts["Noto Sans-Condensed"], bos::font_manager::m_default_resolution);
}

void bkend::shutdown_freetype() {
    FT_Done_FreeType(s_ft);
}

// Helper C++17 compatible ends_with
inline bool ends_with(const std::string &str, const std::string &suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// Scan system fonts
void bkend::ft_search_system_fonts() {
#ifdef _WIN32
    std::string folder = "C:\\Windows\\Fonts";
#else
    std::string folder = "/usr/share/fonts";
#endif

    for (const auto &entry : std::filesystem::recursive_directory_iterator(folder)) {
        if (!entry.is_regular_file()) continue;
        auto path = entry.path().string();
        if (!(ends_with(path, ".ttf") || ends_with(path, ".otf"))) continue;

        FT_Face face;
        if (!FT_New_Face(s_ft, path.c_str(), 0, &face)) {
            std::string family_name = face->family_name ? face->family_name : "(unknown)";
            std::string style = face->style_name ? face->style_name : "(unknown)";
            s_system_fonts[family_name + "-" + style] = path;
            FT_Done_Face(face);
        }
    }
}

bos::font& bkend::ft_load_font(const std::string &font_name, const std::string &font_path, unsigned int resolution) {
    auto &fmgr = bos::font_manager::instance();

    // Return cached font if exists
    if (fmgr.has_font(font_name) && fmgr.get_font(font_name).atlas.m_path == font_path)
        return fmgr.get_font(font_name);

    FT_Face face;
    if (FT_New_Face(s_ft, font_path.c_str(), 0, &face))
        throw std::runtime_error("Error loading font: " + font_name);

    FT_Set_Pixel_Sizes(face, 0u, resolution);

    bos::font _font{};
    _font.atlas.m_path = font_path;
    _font.atlas.m_use_red_channel = true;

    int padding = 2;
    int atlas_width = 0;
    int atlas_height = 0;
    int ascent = 0, descent = 0;

    // First pass: calculate atlas size
    for (unsigned int c = 32; c < 256; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "Missing glyph: " << c << "\n";
            continue;
        }
        ascent = std::max(ascent, face->glyph->bitmap_top);
        int desc = face->glyph->bitmap.rows - face->glyph->bitmap_top;
        descent = std::max(descent, desc);
        atlas_width += face->glyph->bitmap.width + padding;
    }
    atlas_height = ascent + descent;

    // Allocate buffer once
    _font.atlas.m_buffer.resize(atlas_width * atlas_height, 0);

    int xOffset = 0;
    for (unsigned int c = 32; c < 256; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;
        FT_Bitmap &bmp = face->glyph->bitmap;

        int yOffset = ascent - face->glyph->bitmap_top;

        // Copy bitmap to atlas buffer
        for (int row = 0; row < bmp.rows; row++) {
            for (int col = 0; col < bmp.width; col++) {
                int atlas_index = (yOffset + row) * atlas_width + (xOffset + col);
                int bmp_index = row * bmp.width + col;
                if (atlas_index < 0 || atlas_index >= (int)_font.atlas.m_buffer.size()) continue;
                _font.atlas.m_buffer[atlas_index] = bmp.buffer[bmp_index];
            }
        }

        // Store glyph info
        bos::character ch{};
        ch.size = { bmp.width, bmp.rows };
        ch.bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top };
        ch.advance = face->glyph->advance.x >> 6;

        // Compute UVs (normalized)
        float u0 = (float)xOffset / atlas_width;
        float u1 = (float)(xOffset + bmp.width) / atlas_width;
        float v0 = (float)yOffset / atlas_height;
        float v1 = (float)(yOffset + bmp.rows) / atlas_height;
        ch.uv_min = { u0, v0 };
        ch.uv_max = { u1, v1 };

        _font.chs.emplace(c, ch);
        xOffset += bmp.width + padding;
    }

    _font.atlas_size = { (float)atlas_width, (float)atlas_height };
    _font.ascent = face->size->metrics.ascender / 64.0f;
    _font.descent = std::abs(face->size->metrics.descender / 64.0f);
    _font.line_gap = (face->size->metrics.height / 64.0f) - (_font.ascent + _font.descent);

    fmgr.m_fonts.emplace(font_name, std::move(_font));
    FT_Done_Face(face);
    return fmgr.m_fonts[font_name];
}