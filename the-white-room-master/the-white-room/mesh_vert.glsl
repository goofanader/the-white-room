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

varying vec3 vNormal;
varying vec3 normals;
varying vec3 vLightDir;
varying vec3 vThePosition;
varying vec2 vTexCoord;
varying float lDist;

//items for shadow mapping
//uniform mat4 uLightProjMatrix;
//uniform mat4 uLightViewMatrix;
//varying vec4 ShadowCoord;
const mat4 bias = mat4(0.5, 0.0, 0.0, 0.0,
                       0.0, 0.5, 0.0, 0.0,
                       0.0, 0.0, 0.5, 0.0,
                       0.5, 0.5, 0.5, 1.0);

void main() {
  vec4 vPosition;

  vTexCoord = aTexCoord;

  /* First model transforms */
  vPosition = uModelMatrix * vec4(aPosition, 1.0);
  vThePosition = vPosition.xyz;
  lDist = length(-vThePosition + uLightPos);
  normals = aNormal;
  vLightDir = uLightPos - vThePosition;
  vNormal = normalize(uNormalMatrix * vec4(normals, 1.0)).xyz;

  vPosition = uViewMatrix * vPosition;
  gl_Position = uProjMatrix * vPosition;
  if (uTime < 6.0) 
    gl_Position += 1.0/uTime - 1.0/6.0;
  
  //ShadowCoord = bias * uLightProjMatrix * uLightViewMatrix * uModelMatrix * vec4(aVertex, 1.0);
}
