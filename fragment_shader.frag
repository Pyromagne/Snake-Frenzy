#ifdef GL_ES
    precision mediump float;
#endif

uniform vec2 resolution;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;

void main()
{
    vec2 position = gl_FragCoord.xy / resolution;
    vec2 center = vec2(0.5, 0.5); // Center of the gradient

    // Calculate the distance from the center
    float distance = length(position - center);

    // Adjust the inner circle size
    float innerCircleSize = 0.6;

    // Smoothly interpolate colors based on distance
    vec3 color;
    color = mix(color1, color2, smoothstep(innerCircleSize - 0.2, innerCircleSize + 0.01, distance));

    // If outside the inner circle, interpolate to color3
    color = mix(color, color3, smoothstep(innerCircleSize + 0.02, 1.0, distance));

    gl_FragColor = vec4(color, 0.5);
}