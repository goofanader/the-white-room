attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

varying vec3 normals;
varying vec4 position;
varying vec2 vTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uNormalMatrix;
uniform mat4 uProjMatrix;

void main()
{
    vec4 vPosition;
    vPosition = uModelMatrix * vec4(aPosition, 1.0);
    vPosition = uViewMatrix * vPosition;
    position = vPosition;

    normals = normalize(uNormalMatrix * vec4(aNormal, 1.0)).xyz;

    vTexCoord = aTexCoord;
    gl_Position = uProjMatrix * vPosition;
    //gl_TexCoord[0]	= gl_MultiTexCoord0;
    //normals			= normalize(worldRotationInverse * gl_NormalMatrix * gl_Normal);
    //position		= gl_ModelViewMatrix * gl_Vertex;
    //gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}