uniform sampler2D texture;
uniform float time;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	float test =  sin(time);

    // multiply it by the color
    gl_FragColor = vec4(1.000,0.833,0.224,0.0) * pixel;
}