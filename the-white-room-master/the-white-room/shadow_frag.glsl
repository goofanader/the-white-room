uniform float uShininess;
uniform float uSpecStrength;
uniform vec4 uLightColor;
uniform vec3 uCamTrans;
uniform vec4 uAmbColor;
uniform vec4 uSpecColor;
uniform vec4 uDiffColor;
uniform sampler2D uTexUnit, uTexUnit2;
uniform float uTime;

varying vec3 normals;

varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vThePosition;
varying vec2 vTexCoord;
varying float lDist;

//varying vec4 shadowCoord;
//uniform sampler2D shadowMap;

void main() {
      //gl_FragColor = vec4(uColor, 1.0);
  /*
  vec4 texColor;
  vec3 tColor;
  vec3 nNormal = normalize(vNormal);
  vec3 nLightDir = normalize(vLightDir);
  float NDotL = max(dot(nNormal, nLightDir), 0.0);


vec3 specL;
    if (NDotL > 0.0) {
  specL = uSpecColor.rgb;

  //vec3 specL = uSpecColor * uLightColor;
  vec3 V;
  V = normalize(uCamTrans - vThePosition);
      vec3 R = 2.0 * NDotL * nNormal - nLightDir;

      float VdotR = clamp(
        pow(max(dot(R, V), 0.0), uShininess), 0.0, 1.0);
      //specL.x *= VdotR;
      //specL.y *= VdotR;
      //specL.z *= VdotR;
      
          
      specL *= VdotR;// * uLightColor.rgb;// * uSpecStrength;
      //specL *= uSpecStrength;
  //
}
else specL = vec3(0.0);

  vec3 diffL = uDiffColor.rgb;

  diffL += ((sin(uTime) - 1.0) / 2.0);
  diffL *= NDotL * uLightColor.rgb;

  vec3 ambL = uAmbColor.rgb * uLightColor.rgb + vec3(.1, .1, .1) * uAmbColor.rgb;

  vec3 finColor =(diffL * 0.7 + specL * 0.7) /
    (.7 + lDist * 0.01 + lDist * lDist * 0.001) + ambL * 0.65;
    finColor += 3.8/uTime/uTime;
    
    
    //vec4 sc = shadowCoord / shadowCoord.w;
    //float epsilon = 0.0;  //increase to remove artifacts
    //float depth = texture2D(shadowMap, sc.xy).x;
    
    //if(depth + epsilon < sc.z) {
    //    finColor *= 0.3;
    //}
    
    finColor *= 0.1;
            
  gl_FragColor = vec4(
    finColor.r, 
    finColor.g, 
    finColor.b, uAmbColor.a);

    gl_FragColor.a = uAmbColor.a;

    if (gl_FragCoord.x >= 397.0 && gl_FragCoord.x <= 403.0 &&
        gl_FragCoord.y >= 297.0 && gl_FragCoord.y <= 303.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    */
    gl_FragColor = vec4(0.1, 0.1, 0.1, 1.0);

    vec4 fogColor = vec4(0.5, 0.5, 0.5, 1.0);
    const float LOG2 = 1.442695;
    float fogDensity = gl_Fog.density * 0.4;
    float z = 1.0 - (gl_FragCoord.z / gl_FragCoord.w) / 10.0;
    float fogFactor = exp2( -fogDensity * fogDensity * z *  z *  LOG2 );
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    gl_FragColor = mix(fogColor, gl_FragColor, fogFactor);
  
   //depth written automatically (shadow mapping)
}