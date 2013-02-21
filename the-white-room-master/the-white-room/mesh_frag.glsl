uniform float uShininess;
uniform float uSpecStrength;
uniform vec4 uLightColor;
uniform vec3 uCamTrans;
uniform vec4 uAmbColor;
uniform vec4 uSpecColor;
uniform vec4 uDiffColor;
uniform int uUseTex;
uniform sampler2D uTexUnit;

varying vec3 normals;

varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vThePosition;
varying vec2 vTexCoord;
varying float lDist;

void main() {
    //gl_FragColor = vec4(uColor, 1.0);
  
  vec4 texColor;
  vec3 tColor;
  vec3 nNormal = normalize(vNormal);
  vec3 nLightDir = normalize(vLightDir);
  float NDotL = max(dot(nNormal, nLightDir), 0.0);

if (uUseTex != 0) {
        texColor = vec4(texture2D(uTexUnit, vTexCoord));
        tColor = vec3(texture2D(uTexUnit, vTexCoord));
    }

vec3 specL;
    if (NDotL > 0.0) {
  specL = uSpecColor.rgb;
  if (uUseTex != 0) {
    specL = texColor.xyz;
  }
  //vec3 specL = uSpecColor * uLightColor;
  vec3 V;
  V = normalize(uCamTrans - vThePosition);
      vec3 R = 2.0 * NDotL * nNormal - nLightDir;

      float VdotR = clamp(
        pow(max(dot(R, V), 0.0), uShininess), 0.0, 1.0);
      /*specL.x *= VdotR;
      specL.y *= VdotR;
      specL.z *= VdotR;*/
      
          
      specL *= VdotR;// * uLightColor.rgb;// * uSpecStrength;
      //specL *= uSpecStrength;
  //
}
else specL = vec3(0.0);

  vec3 diffL = uDiffColor.rgb;
  if (uUseTex != 0) {
    diffL = texColor.xyz;
  }
  diffL *= NDotL * uLightColor.rgb;

  vec3 ambL = uAmbColor.rgb * uLightColor.rgb + vec3(.1, .1, .1) * uAmbColor.rgb;
  if (uUseTex != 0) {
    ambL = texColor.xyz * uLightColor.rgb / 3.0 + vec3(.1, .1, .1) * texColor.xyz;
  }

  vec3 finColor = (diffL * 0.7 + specL * 0.7) /
    (.7 + lDist * 0.01 + lDist * lDist * 0.001) + ambL * 0.65;
  gl_FragColor = vec4(finColor.r, finColor.g, finColor.b, 1.0);


    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
