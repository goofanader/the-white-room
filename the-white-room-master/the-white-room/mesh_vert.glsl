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
uniform vec4 uLightColor;

uniform float uTime;

varying vec3 gNormal;
varying vec3 gnormals;
varying vec3 gLightDir;
varying vec3 gThePosition;
varying vec2 gTexCoord;
varying float gDist;

void main() {
  vec4 vPosition;

  gTexCoord = aTexCoord;

  /* First model transforms */
  vPosition = uModelMatrix * vec4(aPosition, 1.0);
  gThePosition = vPosition.xyz;
  gDist = length(-gThePosition + uLightPos);
  gnormals = aNormal;
  gLightDir = uLightPos - gThePosition;
  gNormal = normalize(uNormalMatrix * vec4(gnormals, 1.0)).xyz;

  vPosition = uViewMatrix * vPosition;
  gl_Position = uProjMatrix * vPosition;
  if (uTime < 6.0) 
    gl_Position += 1.0/uTime - 1.0/6.0;
}
