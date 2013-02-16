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
  vec3 specL;
  vec3 V;
  V.x = uCamTrans.x - vThePosition.x; //Camera at (0, 0, 0)?
  V.y = uCamTrans.y - vThePosition.y;
  V.z = uCamTrans.z - vThePosition.z;
  V = normalize(V);
  /*if (dot(vNormal, vLightDir) < 0.0)
  else {*/
      vec3 R = -vLightDir + 2.0 * max(dot(normalize(vNormal), vLightDir), 0.0)* normalize(vNormal);
      //vec3 R = -vLightDir + 2.0 * dot(vNormal, vLightDir) * vNormal;
      //R = normalize(R);
      float VdotR = clamp(pow(dot(V, R), uShininess), 0.0, 1.0);
      specL = uColor * uSpecStrength * VdotR * uLightColor;
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

  ambL = vec3(0.75, 0.75, 0.75);
  vec3 finColor = diffL + specL + ambL;
  //vec3 finColor = uLightColor;
  gl_FragColor = vec4(finColor.r, finColor.g, finColor.b, 1.0);
  //vec3 finColor = diffL + ambL;
//  if (useNormalAsColor == 1)
    //gl_FragColor = vec4(vNormal, 1.0);
//  else
    //gl_FragColor = vec4(vLightDir, 1.0);
    //gl_FragColor = vec4(specL, 1.0);
    //gl_FragColor = vec4(ambL.xyz, 1.0);
    //gl_FragColor = vec4(uLightColor, 1.0);
    /*if (uLightColor.z > 1.0)// || uColor.z > 1.0 || uLightColor.z < 0.0 || uLightColor.z > 1.0)
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        gl_FragColor = vec4(0.0, 0.0, uLightColor.z * uColor.z, 1.0);*/


    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0,0.0, 0.0, 1.0);
    }
}
