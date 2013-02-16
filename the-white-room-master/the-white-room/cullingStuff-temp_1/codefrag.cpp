#include "VFCull.h"


int main() {
   Matrix4x4 *vpMatrix;  //clipping planes in world space
   Matrix4x4 *wvpMatrix; //clipping planes in object/model space
   Matrix4x4 *pMatrix;   // clipping planes in view space
   Plane p_planes[6];     //holds 6 Planes
   Point *pt;
   
   //get 4x4 of modelview matrix
   //start with identity and multiply by modelview?
   
   ExtractPlanesGL(&p_planes, vpMatrix, true); 
   
   //pt = object's representative point
   if(Cull(p_planes, pt)) {   
       //dont draw
   }
   else {
       //draw
   }

}