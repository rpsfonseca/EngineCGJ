#version 330
 
// Texture coords of occlusion image
in vec2 inoutTexCoord;
out vec4 outColor;
uniform vec2 lightScreenPos;

// Array of textures: 0 - occlusion scene, 1 - normal scene 
uniform sampler2DArray tex;


layout( shared ) uniform ShaftsParams
{
    int samples;
	float exposure;
	float decay;
	float density;
	float weight;
};

void main(void)
{
	outColor = vec4(0);
	vec2 textCoo = inoutTexCoord.xy;
	vec2 deltaTextCoord = textCoo - lightScreenPos;
 	deltaTextCoord *= 1.0 /  float(samples) * density;
 	
	float illuminationDecay = 1.0;

	// Evaluate the summation of shadows from occlusion texture
	for(int i=0; i < samples ; i++)
  	{
		textCoo -= deltaTextCoord;
		vec4 colorSample  = texture(tex, vec3( clamp(textCoo,0,1), 0 ) );
			
		colorSample  *= illuminationDecay * weight;
		outColor += colorSample;
		illuminationDecay *= decay;
 	}

	outColor *= exposure;

	outColor += texture( tex, vec3( inoutTexCoord, 1 ) );
	outColor *= 0.5;

	outColor = outColor;
}