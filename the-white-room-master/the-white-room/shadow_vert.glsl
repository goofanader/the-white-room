attribute vec3 aPosition;
attribute vec3 aVertex;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

uniform mat4 uLightProjMatrix;
uniform mat4 uLightViewMatrix;

uniform mat4 uTpProjMatrix;
uniform mat4 uTpViewMatrix;
uniform mat4 uTpModelMatrix;

uniform vec3 uLightPos;
uniform vec4 uLightColor;

uniform float uTime;

varying vec3 vNormal;
varying vec3 normals;
varying vec3 vLightDir;
varying vec3 vThePosition;
varying vec2 vTexCoord;
varying float lDist;


const mat4 bias = mat4(0.5, 0.0, 0.0, 0.0,
                       0.0, 0.5, 0.0, 0.0,
                       0.0, 0.0, 0.5, 0.0,
                       0.5, 0.5, 0.5, 1.0);

void main() {
    
    vec4 vPosition;

  /* First model transforms */
  vPosition = uModelMatrix * vec4(aPosition, 1.0);
  vThePosition = vPosition.xyz;
  lDist = length(-vThePosition + uLightPos);
  normals = aNormal;
  vLightDir = uLightPos - vThePosition;
  vNormal = normalize(uNormalMatrix * vec4(normals, 1.0)).xyz;

  float lightY = uLightPos.y + 8.25f;
  float objY = vPosition.y + 8.25f;
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
      shadowX = -29.5;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.x - uLightPos.x)) * shadowX;
      
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;

  }
  else if(wall == vec3(1.0, 1.0, 1.0)) {  // radio wall
      shadowX = 29.96;
      
      shadowY = uLightPos.y - ((uLightPos.y - vPosition.y) / (vPosition.x - uLightPos.x)) * shadowX;
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;

  }
  else if(wall == vec3(1.0, 1.0, 0.0)) {  // plants cast shadow on table
     shadowY = -3.1f;
  
     shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
     shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
     
     /*
     // ignore if shadow falls off table (collapse onto existing shadow??)
     vec2 center = vec2(0.0, 0.0);
     vec2 shadow = vec2(shadowX, shadowZ) - center; //shadow position - center of table;
     // distance from center of table
     float shadowlen = sqrt(shadow.x * shadow.x + shadow.y * shadow.y);
     
     if(shadowlen > 5.0) { // if shadow length > radius of table
         shadowX = center.x + 5.0;
         shadowZ = center.y +5.0;
     }
      * */
  }
  else if(wall == vec3(0.0, 1.0, 1.0)) {  // radio casts shadow on table
      shadowY = -3.75;
      
      shadowX = ((vPosition.x - uLightPos.x) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.x;
      shadowZ = ((vPosition.z - uLightPos.z) / (uLightPos.y - vPosition.y)) * (uLightPos.y - shadowY) + uLightPos.z;
      
      // if shadow falls off table
      if(shadowX > 29.5)
          shadowX = 29.5;
  }
  
  vPosition.x = shadowX;
  vPosition.y = shadowY;
  vPosition.z = shadowZ;
  
  vPosition = uViewMatrix * vPosition;
  gl_Position = uProjMatrix * vPosition;
  if (uTime < 6.0) 
    gl_Position += 1.0/uTime - 1.0/6.0;
  
  /** for shadow mapping  
  vec4 vPosition;

  // First model transforms 
  vPosition = uModelMatrix * vec4(aPosition, 1.0);
  vPosition = uLightViewMatrix * vPosition;
  gl_Position = uLightProjMatrix * vPosition;
  **/
}
