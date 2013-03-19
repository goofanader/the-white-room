uniform vec4 uLightColor; //used in planar shadows

void main() {
    if(vec3(uLightColor) == vec3(1.0, 0.0, 1.0)) {
      //depth written automatically (shadow mapping)
    }
    else { // planar shadow
        
       gl_FragColor = vec4(0.1, 0.1, 0.1, 1.0);

       vec4 fogColor = vec4(0.2, 0.2, 0.2, 1.0);
       const float LOG2 = 1.442695;
       float fogDensity = gl_Fog.density * 0.4;
       float z = 1.0 - (gl_FragCoord.z / gl_FragCoord.w) / 10.0;
       float fogFactor = exp2( -fogDensity * fogDensity * z *  z *  LOG2 );
       fogFactor = clamp(fogFactor, 0.0, 1.0);

       gl_FragColor = mix(fogColor, gl_FragColor, fogFactor);
    }  // end planar shadow
}
