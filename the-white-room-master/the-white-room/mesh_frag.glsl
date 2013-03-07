uniform float uShininess;
uniform float uSpecStrength;
uniform vec4 uLightColor;
uniform vec3 uCamTrans;
uniform vec4 uAmbColor;
uniform vec4 uSpecColor;
uniform vec4 uDiffColor;
uniform int uUseTex, uUseTex2;
uniform sampler2D uTexUnit, uTexUnit2;
uniform float uTime;

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
    }

if (uUseTex2 != 0) {
    float T = mod(uTime, 24);
    if (T >= 13.0 && T <= 22.0) {
        tColor = vec3(texture2D(uTexUnit2, vTexCoord)) * 
            (0.50*sin(6.2831853 * (T - 13.0) / 9.0) + 0.25);
        texColor = texColor - 
        (texColor - vec4(tColor, tColor.r)) *
        clamp((length(tColor) - 0.1)/(0.67735026 - 0.1), 0.0, 1.0);
    }
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
  diffL += ((sin(uTime) - 1.0) / 2.0);
  diffL *= NDotL * uLightColor.rgb;

  vec3 ambL = uAmbColor.rgb * uLightColor.rgb + vec3(.1, .1, .1) * uAmbColor.rgb;
  if (uUseTex != 0) {
    ambL = texColor.xyz * uLightColor.rgb / 3.0 + vec3(.1, .1, .1) * texColor.xyz;
  }

  vec3 finColor =(diffL * 0.7 + specL * 0.7) /
    (.7 + lDist * 0.01 + lDist * lDist * 0.001) + ambL * 0.65;
    finColor += 3.8/uTime/uTime;
  gl_FragColor = vec4(
    finColor.r, 
    finColor.g, 
    finColor.b, uUseTex2 != 0 ? texColor.a : uAmbColor.a);

    gl_FragColor.a = uAmbColor.a;

    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
