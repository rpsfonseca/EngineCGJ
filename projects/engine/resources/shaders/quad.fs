#version 330 core

in vec3 exPosition;
out vec4 FragColor;

//-----------------------------------------------------------------------------
// Maths utils
//-----------------------------------------------------------------------------

const vec2 size = vec2(512,512);
const int samples = 64;

//const vec2 res = vec2(size.x,512);

const mat3 m = mat3( 0.00,  0.80,  0.60,
              -0.80,  0.36, -0.48,
              -0.60, -0.48,  0.64 );


float hash(float n)
{
    return fract(sin(n)*43758.5453);
}

float noise(vec3 x)
{
    vec3 p = floor(x); 
    vec3 f = fract(x);

    f = f*f*(3.0-2.0*f);//creates surrounding particles 

    float n = p.x + p.y*57.0 + 113.0*p.z;

    float res = mix(mix(mix( hash(n+  .0), hash(n+  1.),f.x),
                        mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
                    mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                        mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
    return res;
}

float fbm(vec3 p)
{
    float f;
    f  = 0.5000*noise( p ); p = m*p*2.02;
    f += 0.2500*noise( p ); p = m*p*2.03;
    f += 0.1250*noise( p );
    return f;
}


//-----------------------------------------------------------------------------
// Main functions
//-----------------------------------------------------------------------------
float scene(vec3 p)
{	
	return .001-length(p)*.07+fbm(p*.3);
	//vec3 r = vec3(1,1,1); 
	//eturn (length( p/r ) - 1.0) * min(min(r.x,r.y),r.z);
}

void main()
{
	vec2 q = exPosition.xy;// / iResolution.xy;
    vec2 v = q;
    //v.x *= iResolution.x/ iResolution.y;

	//#if 0
    //vec2 mo = -1.0 + 2.0*iMouse.xy / iResolution.xy;
    //#else
	vec2 mo = vec2(.1,cos(.25)*3.);
	//#endif

    // camera by iq
    vec3 org = 25.0*normalize(vec3(cos(2.75-3.0*mo.x), 0.7-1.0*(mo.y-1.0), sin(2.75-3.0*mo.x)));
	vec3 ta = vec3(0.0, 1.0, 0.0);
    vec3 ww = normalize( ta - org);
    vec3 uu = normalize(cross( vec3(0.0,1.0,0.0), ww ));
    vec3 vv = normalize(cross(ww,uu));
    vec3 dir = normalize( v.x*uu + v.y*vv + 1.5*ww );
	vec4 color=vec4(.0);
	
	
	
	const int nbSample = 64;
	const int nbSampleLight = 6;
	
	float zMax= 40.;
	float step= zMax/float(nbSample);
	float zMaxl= 20.;
	float stepl= zMaxl/float(nbSampleLight);
    vec3 p = org - vec3(0,3,0);
    float T = 1.;
    float absorption = 100.;
	vec3 sun_direction = normalize( vec3(1.,.0,.0) );
    
	for(int i=0; i<samples; i++)
	{
		float density = scene(p);
		if(density>0.)
		{
			float tmp = density / float(nbSample);
			T *= 1. -tmp * absorption;
			if( T <= 0.01)
				break;
				
				
			 //Light scattering
			float Tl = 1.0;
			for(int j=0; j<nbSampleLight; j++)
			{
				float densityLight = scene( p + normalize(sun_direction)*float(j)*stepl);
				if(densityLight>0.)
                	Tl *= 1. - densityLight * absorption/float(nbSample);
                if (Tl <= 0.01)
                    break;
			}
			
			//Add ambiant + light scattering color
			color += vec4(1.)*50.*tmp*T +  vec4(1.,.7,.4,1.)*80.*tmp*T*Tl;
		}
		p += dir*step;
	}    

	if(color.w < 0.15)
		discard;
	

    FragColor = color;
}