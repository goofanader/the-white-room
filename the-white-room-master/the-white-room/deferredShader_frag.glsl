uniform sampler2D tDiffuse; 
uniform sampler2D tPosition;
uniform sampler2D tNormals;
uniform vec3 uCamTrans;
uniform vec4 uLightColor;
uniform vec3 uLightPos;

void main( void )
{
	vec4 image = texture2D( tDiffuse, gl_TexCoord[0].xy );
	vec4 position = texture2D( tPosition, gl_TexCoord[0].xy );
	vec4 normal = texture2D( tNormals, gl_TexCoord[0].xy );
	
	//vec3 light = vec3(50,100,50); //hardcoded, change this.
	vec3 lightDir = uLightPos - position.xyz ;
	
	normal = normalize(normal);
	lightDir = normalize(lightDir);
	
	vec3 eyeDir = normalize(uCamTrans-position.xyz);
	vec3 vHalfVector = normalize(lightDir.xyz+eyeDir);
	
	//gl_FragColor = max(dot(normal.xyz,lightDir),0) * image + pow(max(dot(normal.xyz,vHalfVector),0.0), 100) * 1.5;
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
