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

void main() {
    //gl_FragColor = vec4(uColor, 1.0);
  
  vec4 texColor;
  vec3 tColor;
  vec3 specL = cross(uSpecColor, uLightColor);
  //vec3 specL = uSpecColor * uLightColor;
  vec3 V;
  V.x = uCamTrans.x - vThePosition.x; //Camera at (0, 0, 0)?
  V.y = uCamTrans.y - vThePosition.y;
  V.z = uCamTrans.z - vThePosition.z;
  V = normalize(V);
  /*if (dot(vNormal, vLightDir) < 0.0)
    specL = vec3(0.0);
  else {*/
      vec3 R = 2.0 * clamp(dot(vNormal, normalize(vLightDir/* - vThePosition*/)), 0.0, 1.0) * vNormal - vLightDir;
      //vec3 R = -vLightDir + 2.0 * dot(vNormal, vLightDir) * vNormal;
      //R = normalize(R);
      float VdotR = pow(clamp(dot(normalize(R), normalize(V)), 0.0, 1.0), uShininess);
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
  float NdotL = clamp(dot(normalize(vNormal), normalize(vLightDir/* - vThePosition*/)), 0.0, 1.0);
  diffL *= NdotL * uLightColor;

  vec3 ambL = uAmbColor * uLightColor + vec3(.1, .1, .1) * uAmbColor;

  //ambL = vec3(0.75, 0.75, 0.75);
  vec3 finColor = diffL + specL + ambL;
  //vec3 finColor = uLightColor;
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
