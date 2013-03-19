attribute vec3 aPosition;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

uniform mat4 uLightProjMatrix;
uniform mat4 uLightViewMatrix;

uniform vec3 uLightPos;
uniform vec4 uLightColor;  // code value for planar shadows

void main() {
    vec4 vPosition;
   
  //shadow mapping
  if(vec3(uLightColor) == vec3(1.0, 0.0, 1.0)) {

     // First model transforms 
     vPosition = uModelMatrix * vec4(aPosition, 1.0);
     vPosition = uLightViewMatrix * vPosition;
     gl_Position = uLightProjMatrix * vPosition;
      
  }
  else { //planar shadows
 

  /* First model transforms */
  vPosition = uModelMatrix * vec4(aPosition, 1.0);
  float shadowX, shadowY, shadowZ;
  vec3 wall = vec3(uLightColor);
  
    // wall limits = 30
  if(wall == vec3(0.0, 0.0, 0.0)) {   // floor shadow
     shadowY = -8.25f;
  
     shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
     shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
  }
  else if(wall == vec3(1.0, 0.0, 0.0)) {  // fireplace wall
      shadowZ = -29.95;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.z - uLightPos.z)) * shadowZ;
      shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
  }
  else if(wall == vec3(0.0, 1.0, 0.0)) {  // door wall
      shadowZ = 29.95;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.z - uLightPos.z)) * shadowZ;
      shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
  }
  else if(wall == vec3(0.0, 0.0, 1.0)) {  // bookcase wall
      shadowX = -29.96;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.x - uLightPos.x)) * shadowX;
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
  }
  else if(wall == vec3(1.0, 1.0, 1.0)) {  // radio wall
      shadowX = 29.96;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.x - uLightPos.x)) * shadowX;
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
  }
  else if(wall == vec3(1.0, 1.0, 0.0)) {  // plants cast shadow on table
     shadowY = -3.47f;
  
     shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
     shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
     
     // ignore if shadow falls off table
     if(shadowZ > 25.0)
         shadowZ = 25.0;
  }
  else if(wall == vec3(0.0, 1.0, 1.0)) {  // radio casts shadow on table
      shadowY = -3.75;
      
      shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
      
      // if shadow falls off table
      if(shadowX > 29.39)
          shadowX = 29.39;
  }
  
  vPosition.x = shadowX;
  vPosition.y = shadowY;
  vPosition.z = shadowZ;
  
  vPosition = uViewMatrix * vPosition;
  gl_Position = uProjMatrix * vPosition;

  }  //end of planar shadows
}
