attribute vec3 aPosition;
attribute vec3 aVertex;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

uniform mat4 uTpProjMatrix;
uniform mat4 uTpViewMatrix;
uniform mat4 uTpModelMatrix;

uniform vec3 uLightPos;
uniform vec3 uLightColor;

varying vec3 vNormal;
varying vec3 normals;
varying vec3 vLightDir;
varying vec3 vThePosition;
varying vec2 vTexCoord;

void main() {
  vec4 vPosition;

  vTexCoord = aTexCoord;

  /* First model transforms */
  vPosition = uModelMatrix * vec4(aPosition, 1);
  vThePosition = vPosition.xyz;
  normals = aNormal;
  vLightDir = uLightPos - vec3(vPosition);
  vNormal = normalize(uNormalMatrix * vec4(normals, 1)).xyz;

  vPosition = uViewMatrix * vPosition;
  gl_Position = uProjMatrix * vPosition;
}
