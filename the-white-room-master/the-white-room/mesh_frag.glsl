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

// items for shadow mapping
// varying vec4 ShadowCoord;
// uniform sampler2D ShadowMap;

void main() {
    //gl_FragColor = vec4(uColor, 1.0);
    
  vec4 texColor;
  vec3 tColor;
  vec3 nNormal = normalize(vNormal);
  vec3 nLightDir = normalize(vLightDir);
  float NDotL = max(dot(nNormal, nLightDir), 0.0);

if (uUseTex != 0) {
    if (uUseTex == 2) {
        texColor = vec4(texture2D(uTexUnit, vTexCoord));
        //texColor.a = length(texColor);
    }
    else {
        texColor = vec4(texture2D(uTexUnit, vTexCoord));
    }
}


if (uUseTex2 != 0) {
    float T = mod(uTime, 24);
    if (T > 9.0 && T < 14.0) {
        tColor = vec3(texture2D(uTexUnit2, vTexCoord)) * 
            (0.50*sin(6.2831853 * (T - 9.0) / 6.0) + 0.5);
        texColor = texColor - 
        (texColor - vec4(tColor, 1.0)) *
        (length(tColor) - 0.0)/(length(vec3(1.0)) - 0.0);
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
  diffL += ((sin(uTime) - 1.0) / 4.0);
  diffL *= NDotL * uLightColor.rgb;

  vec3 ambL = uAmbColor.rgb * uLightColor.rgb + vec3(.1, .1, .1) * uAmbColor.rgb;
  if (uUseTex != 0) {
    ambL = texColor.xyz * uLightColor.rgb / 3.0 + vec3(.1, .1, .1) * texColor.xyz;
  }

  vec3 finColor =(diffL * 0.9 + specL * 0.7) /
    (.7 + lDist * 0.01 + lDist * lDist * 0.001) + ambL * 0.65;
    finColor += 3.8/uTime/uTime;
 
 /*
  float epsilon = 0.0; //increasing removes shadow artifacts
  vec4 shadowCoordPD = ShadowCoord / ShadowCoord.w;
  
  //ignores negative projection
  if(shadowCoordPD >= 0.0) {
      float shadow = texture2D(ShadowMap, shadowCoordPD.xy).x;
      
      if(shadow + epsilon < shadowCoordPD.z)
          finColor *= 0.5;
  }
   */
    
  gl_FragColor = vec4(
    finColor.r, 
    finColor.g, 
    finColor.b, uUseTex2 != 0 ? texColor.a : uAmbColor.a);

  
  vec4 fogColor = vec4(0.5, 0.5, 0.5, 1.0);
  const float LOG2 = 1.442695;
  float z = 1.0 - (gl_FragCoord.z / gl_FragCoord.w) / 10.0;
  float fogDensity = gl_Fog.density * 0.4;
  float fogFactor = exp2( -fogDensity * fogDensity * z *  z *  LOG2 );
  fogFactor = clamp(fogFactor, 0.0, 1.0);

  gl_FragColor = mix(fogColor, gl_FragColor, fogFactor);
  
  if (uUseTex != 2) gl_FragColor.a = uAmbColor.a;
    
    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
/*if (uUseTex == 2) {
    gl_FragColor = vec4(
        texColor.r, texColor.g, texColor.b,
        length(texColor));
}*/
if (uUseTex == 2) {
    gl_FragColor = vec4(
        texColor.r,
        texColor.g,
        texColor.b,
        texColor.a);
}

}
