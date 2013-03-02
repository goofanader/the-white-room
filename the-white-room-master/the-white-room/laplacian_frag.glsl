uniform float uShininess;
uniform float uSpecStrength;
uniform vec4 uLightColor;
uniform vec3 uCamTrans;
uniform vec4 uAmbColor;
uniform vec4 uSpecColor;
uniform vec4 uDiffColor;
//uniform int uUseTex;
//uniform sampler2D uTexUnit;
uniform sampler2D uSmokeUnit;

varying vec3 normals;

varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vThePosition;
//varying vec2 vTexCoord;
varying float lDist;

#define KERNEL_SIZE 9
float kernel[KERNEL_SIZE];
float gaussKernel[KERNEL_SIZE];
vec2 offset[KERNEL_SIZE];

void main() {
    float width = 1024.0;
    float height = 1024.0;

    float step_w = 1.0 / width;
    float step_h = 1.0 / height;

    int i = 0;
    vec4 sum = vec4(0.0);
    vec4 gaussSum = vec4(0.0);

    offset[0] = vec2(-step_w, -step_h);
    offset[1] = vec2(0.0, -step_h);
    offset[2] = vec2(step_w, -step_h);

    offset[3] = vec2(-step_w, 0.0);
    offset[4] = vec2(0.0, 0.0);
    offset[5] = vec2(step_w, 0.0);

    offset[6] = vec2(-step_w, step_h);
    offset[7] = vec2(0.0, step_h);
    offset[8] = vec2(step_w, step_h);

    kernel[0] = -1.0;
    kernel[1] = -1.0;
    kernel[2] = -1.0;

    kernel[3] = -1.0;
    kernel[4] = 8.0;
    kernel[5] = -1.0;

    kernel[6] = -1.0;
    kernel[7] = -1.0;
    kernel[8] = -1.0;

    //Gaussian Blur Kernel
    gaussKernel[0] = 1.0 / 16.0;
    gaussKernel[1] = 2.0 / 16.0;
    gaussKernel[2] = 1.0 / 16.0;

    gaussKernel[3] = 2.0 / 16.0;
    gaussKernel[4] = 4.0 / 16.0;
    gaussKernel[5] = 2.0 / 16.0;

    gaussKernel[6] = 1.0 / 16.0;
    gaussKernel[7] = 2.0 / 16.0;
    gaussKernel[8] = 1.0 / 16.0;

    //if (vTexCoord.s < .5) {
        for (i = 0; i < KERNEL_SIZE; i++) {
            vec4 temp = vec4(vNormal, 1.0) + vec4(offset[i], 0.0, 0.0);//texture2D(uTexUnit, vTexCoord.st + offset[i]);
            sum += (temp * kernel[i]);// - (temp * gaussKernel[i] / 10.5);
            gaussSum += temp * gaussKernel[i];
        }

        float alpha = uAmbColor.a * vNormal.x;
        gl_FragColor = uAmbColor;//vec4(uAmbColor.rgb, alpha);
    //}
    //else {
        sum = vec4(normals, 1.0);

        //gl_FragColor = vec4(normalize(vec3(uAmbColor + uDiffColor + uSpecColor)), 1.0);//texture2D(uTexUnit, vTexCoord.xy);
    //}
}
