#version 330 core

in vec2 Uv; // UV coordinates from vertex shader (0..1)
out vec4 FragColor;

// Uniforms
uniform vec4 u_bg_color;
uniform vec4 u_border_color;
uniform bool u_bordered;
uniform bool u_visible;
uniform float u_border_radius; // in normalized [0..0.5] units
uniform int u_border_size;     // in pixels
uniform vec2 u_resolution;     // screen or framebuffer resolution

float sdRoundedRect(vec2 p, vec2 size, float radius) {
    vec2 d = abs(p) - size + vec2(radius);
    return length(max(d, 0.0)) - radius;
}

void main() {
    if(!u_visible) {
        discard;
    }
    // Center UV around (0,0)
    vec2 centered = Uv - 0.5;

    // Size in UV space (half-size = 0.5)
    vec2 halfSize = vec2(0.5);

    // Radius as fraction of UV size
    float radius = u_border_radius * 0.5;

    // Signed distance in UV space
    float dist = sdRoundedRect(centered, halfSize - vec2(radius), radius);

    float border_thickness = u_border_size / min(u_resolution.x, u_resolution.y);

    if (u_bordered) {
        if (dist < 0.0 && dist >= -border_thickness)
            FragColor = u_border_color;
        else if (dist < -border_thickness)
            FragColor = u_bg_color;
        else
            discard;
    } else {
        if (dist <= 0.0)
            FragColor = u_bg_color;
        else
            discard;
    }
}
