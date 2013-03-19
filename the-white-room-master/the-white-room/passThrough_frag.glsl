varying vec4		position;
varying vec3		normals;
varying vec2 vTexCoord;
uniform sampler2D	uTexUnit;
uniform int uUseTex;

void main( void )
{
    if (uUseTex != 0) {
	gl_FragData[0] = vec4(1.0, 1.0, 1.0, 0.0); //white colorvec4(texture2D(uTexUnit, vTexCoord.st).rgb, 1.0);
    } else {
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 0.0); //white color
    }
	gl_FragData[1] = vec4(1.0, 1.0, 1.0, 1.0);//vec4(position.xyz,0.0);
	gl_FragData[2] = vec4(1.0, 1.0, 1.0, 1.0);//vec4(normals.xyz,0.0);
}