uniform float uShininess;
uniform float uSpecStrength;
uniform vec3 uLightColor;
uniform vec3 uCamTrans;
uniform vec3 uAmbColor;
uniform vec3 uSpecColor;
uniform vec3 uDiffColor;
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
  vec3 specL = cross(uSpecColor, uLightColor);
  //vec3 specL = uSpecColor * uLightColor;
  vec3 V;
  V = normalize(uCamTrans - vThePosition);
      vec3 R = 
        2.0 * max(dot(normalize(vNormal), normalize(vLightDir)), 0.0) * 
        normalize(vNormal) - normalize(vLightDir);


      float VdotR = clamp(
        pow(max(dot(normalize(R), normalize(V)), 0.0), uShininess), 0.0, 1.0);
      /*specL.x *= VdotR;
      specL.y *= VdotR;
      specL.z *= VdotR;*/
      
    if (uUseTex != 0) {
        texColor = vec4(texture2D(uTexUnit, vTexCoord));
        tColor = vec3(texture2D(uTexUnit, vTexCoord));
    }
      
      specL *= VdotR;// * uLightColor.rgb;// * uSpecStrength;
      //specL *= uSpecStrength;
  //}

  vec3 diffL = uDiffColor;
  float NdotL = max(dot(normalize(vNormal), normalize(vLightDir)), 0.0);
  diffL *= NdotL * uLightColor;

  vec3 ambL = uAmbColor * uLightColor + vec3(.1, .1, .1) * uAmbColor;

  vec3 finColor = (diffL * 0.7 + specL * 0.7) /
    (1 + lDist * lDist * 0.0007) + ambL * 0.85;
  gl_FragColor = vec4(finColor.r, finColor.g, finColor.b, 1.0);

  //testing if this variable is even being set
  if (uUseTex != 0) {
    gl_FragColor = texColor;
  }

    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
