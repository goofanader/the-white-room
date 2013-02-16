uniform float uShininess;
uniform float uSpecStrength;
uniform vec3 uLightColor;
uniform vec3 uCamTrans;
uniform vec3 uColor;

varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vThePosition;

void main() {
    //gl_FragColor = vec4(uColor, 1.0);
  vec3 specL = uColor;
  vec3 V;
  V.x = uCamTrans.x - vThePosition.x; //Camera at (0, 0, 0)?
  V.y = uCamTrans.y - vThePosition.y;
  V.z = uCamTrans.z - vThePosition.z;
  V = normalize(V);
  /*if (dot(vNormal, vLightDir) < 0.0)
    specL = vec3(0.0);
  else {*/
      vec3 R = -vLightDir + 2.0 * max(dot(vNormal, vLightDir), 0.0) * vNormal;
      //vec3 R = -vLightDir + 2.0 * dot(vNormal, vLightDir) * vNormal;
      //R = normalize(R);
      float VdotR = max(pow(dot(V, R), uShininess), 0.0);
      specL.x *= VdotR;
      specL.y *= VdotR;
      specL.z *= VdotR;
      specL.x *= uLightColor.x;
      specL.y *= uLightColor.y;
      specL.z *= uLightColor.z;
      specL *= uSpecStrength;
  //}

  vec3 diffL = uColor;
  float NdotL = max(dot(vNormal, vLightDir), 0.0);
  diffL.x *= NdotL;
  diffL.y *= NdotL;
  diffL.z *= NdotL;
  diffL.x *= uLightColor.x;
  diffL.y *= uLightColor.y;
  diffL.z *= uLightColor.z;

  vec3 ambL = uColor;
  ambL.x *= 0.1 * uColor.x * uLightColor.x;
  ambL.y *= 0.1 * uColor.y * uLightColor.y;
  ambL.z *= 0.1 * uColor.z * uLightColor.z;

  ambL = vec3(0.5, 0.5, 0.5);
  vec3 finColor = diffL + specL + ambL;
  //vec3 finColor = uLightColor;
  gl_FragColor = vec4(finColor.r, finColor.g, finColor.b, 1.0);

    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0,0.0, 0.0, 1.0);
    }
}
