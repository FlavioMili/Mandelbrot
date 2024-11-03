#version 120

uniform float zoom;
uniform vec2 offset;
uniform int maxIter;

void main() {
    vec2 z = vec2(0.0);
    vec2 c = ((gl_FragCoord.xy - vec2(400.0, 300.0)) / vec2(300.0)) / zoom + offset;
    
    int i;
    float smoothVal = 0.0;
    
    for (i = 0; i < maxIter && dot(z,z) <= 4.0; i++) {
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;
        z = vec2(x, y);
    }
    
    if (i < maxIter) {
        // Smooth iteration count for better coloring
        float log_zn = log(dot(z,z)) / 2.0;
        float nu = log(log_zn / log(2.0)) / log(2.0);
        smoothVal = float(i) + 1.0 - nu;
    }
    
    // Normalize and create cyclic color value
    float colorVal = smoothVal / float(maxIter);
    colorVal = sqrt(colorVal); // Adjust contrast
    
     vec3 color = vec3(
         0.5 + 0.5 * cos(colorVal * 6.28318),
         0.5 + 0.5 * sin(colorVal * 6.28318),
         0.5 + 0.5 * cos(colorVal * 6.28318 + 2.094)
     );
    
    // Inside set coloring
    if (i == maxIter) {
        color = vec3(0.1, 0.2, 0.4); 
    }
    
    gl_FragColor = vec4(color, 1.0);
}
