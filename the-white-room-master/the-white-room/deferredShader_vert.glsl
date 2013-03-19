attribute vec3 aPosition;
attribute vec2 aTexCoord;

varying vec2 vTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uModelMatrix;
//uniform mat4 uViewMatrix;
uniform mat4 uNormalMatrix;

void main( void )
{
    vec4 vPosition;
    vPosition = uModelMatrix * vec4(aPosition, 1.0);
    //vPosition = uViewMatrix * vPosition;

	gl_Position = vPosition;//uProjMatrix * vPosition;//vec4(aPosition, 1.0);
	vTexCoord = aTexCoord;//gl_FragCoord[0].xy;
        //vTexCoord = (vPosition.xy) / 2.0;//aTexCoord; //

    //gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}
