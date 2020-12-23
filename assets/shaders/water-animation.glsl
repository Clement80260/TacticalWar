#ifdef GL_ES
precision mediump float;
#endif

#define M_PI 3.1415926535897932384626433832795

uniform sampler2D texture;
uniform float u_time;
uniform float u_widthFactor;
uniform float u_textureHeight;


//varying vec4 v_color;
//varying vec2 v_texCoords;

void main() {

	float umin = 9.0 / 138.0;
	float umax = 126.0 / 138.0;
	float intervalLength = umax - umin;

    float textureFactor = 656.0 / u_textureHeight; // Texture factor is to handle different texture size (to apply the same distortion
                                                   // on any texture size).

    vec2 yDistort = vec2(0, 0);
	
	if(gl_TexCoord[0].x > umin && gl_TexCoord[0].x < umax)
	{
		yDistort = vec2(0, sin((((gl_TexCoord[0].x - umin) * (1.0 / intervalLength)) * 4.0 * M_PI) + (u_time * 3.0)) * 0.003 * textureFactor);
	}
    vec2 newCoords = gl_TexCoord[0].xy;
    newCoords += yDistort;
    vec4 finalColor = texture2D(texture, newCoords);
    finalColor *= gl_Color;
    gl_FragColor = finalColor;
}