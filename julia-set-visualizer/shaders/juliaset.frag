#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec3 mandelbrot(vec2 c) {
    vec2 z = vec2(0.0);
    float iter = 0.0;
    const float max_iter = 1000.0;
    for (float i = 0.0; i < max_iter; i++) {
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;

        if (length(z) > 2.0) break;

        iter++;
    }
    float f = iter/max_iter;

    return vec3(f, f, f );
}

vec3 julia(vec2 uv, vec2 c) {
    float escapeRadius = 2.0;
    vec2 z = uv;
    float iter = 0.0;
    const float max_iter = 1000.0;
    for (float i = 0.0; i < max_iter; i++) {
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
        if (length(z) > escapeRadius) {
            // If current radius is bigger than escape radius, this is an escape point
            return vec3(iter / max_iter, 0.0, 0.0);
        }
    }

    return vec3(0.0);
}

void main(){
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (gl_FragCoord.xy - 0.5 * u_resolution.xy) /u_resolution.y;
    uv *= 4.0;
    vec3 color = vec3(0.0);

    // Draw mandelbrot in background
    color += mandelbrot(uv) * 0.2;

	// Get coordinates of mouse normalized to screen
    vec2 mouse = u_mouse.xy / u_resolution.xy;
    color += julia(uv, mouse);

    gl_FragColor = vec4(color, 1.0);
}