attribute vec3 aPosition;
uniform mat4 uProjMatrix;

void main( void )
{
	gl_Position = uProjMatrix * vec4(aPosition, 1.0);
	gl_TexCoord[0] = gl_MultiTexCoord0;

    //gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}
