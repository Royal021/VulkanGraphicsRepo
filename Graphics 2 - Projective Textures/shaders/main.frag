#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(location=0) in vec2 texcoord;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 worldPos;
layout(location=3) in vec4 tangent;
layout(location=4) in vec2 texcoord2;

layout(location=0) out vec4 color;

layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT) uniform sampler texSampler;
layout(set=0,binding=BASE_TEXTURE_SLOT) uniform texture2DArray baseColorTexture;
layout(set=0,binding=EMISSIVE_TEXTURE_SLOT) uniform texture2DArray emissiveTexture;
layout(set=0,binding=NORMAL_TEXTURE_SLOT) uniform texture2DArray normalTexture;
layout(set=0,binding=METALLICROUGHNESS_TEXTURE_SLOT) uniform texture2DArray metallicRoughnessTexture;
layout(set=0,binding=ENVMAP_TEXTURE_SLOT) uniform textureCube environmentMap;

layout(set=0,binding=PROJECTED_TEXTURE_SLOT) uniform texture2DArray projectedTexture;

#define AMBIENT_ABOVE vec3(0.3,0.3,0.3)
#define AMBIENT_BELOW vec3(0.1,0.1,0.1)
#define PI 3.14159265358979323

// c=Base object color
// i=index of light
// N=Normal
// V=Vector to viewer
// dp = diffuse percentage (output)
// sp = specular percentage (output)


//metallic blue, roughness green
float MF = (texture( sampler2DArray(metallicRoughnessTexture, texSampler),
                    vec3(texcoord2,animationFrame) ).b) * metallicFactor;

float RF = (texture( sampler2DArray(metallicRoughnessTexture, texSampler),
                    vec3(texcoord2,animationFrame) ).g) * roughnessFactor;



vec3 schlickFresnel(vec3 F0, float cos_theta_VH, float metallicity){
    vec3 one_minus_F0 = vec3(1.0)-F0;
    return F0 + one_minus_F0 * pow(1.0 - cos_theta_VH,5.0);
}

vec3 schlickDiffuse(
        vec3 F,             //from schlickFresnel()
        float cos_theta_VH,
        float mu,           //metallicity
        vec3 baseColor,     //from texture
        float cos_theta_NL )
{
    vec3 d = mix( 0.96*baseColor , vec3(0), mu );
    d = d/PI;
    return cos_theta_NL * ( vec3(1.0)-F) * d ;
}

vec3 schlickSpecular(
    vec3 F,         //from schlickFresnel()
    float cos_theta_VH, float cos_theta_NH,
    vec3 baseColor,     //from texture
    float cos_theta_NL, float cos_theta_NV,
    float rho,      //roughness
    float mu        //metallicity
){
    float rho2 = rho*rho;
    float disc1 = max(0.0,
            rho2 + (1.0-rho2) * cos_theta_NV * cos_theta_NV );
    float disc2 = max(0.0,
            rho2 + (1.0-rho2) * cos_theta_NL * cos_theta_NL );
    float denom = max(0.0001,
            cos_theta_NL * sqrt( disc1 ) +
            cos_theta_NV * sqrt( disc2 )
    );
    float Vis = 1.0 / (2.0 * denom );
    float tmp = rho / (1.0 + cos_theta_NH*cos_theta_NH * (rho2-1.0) );
    float D = 1.0/PI * tmp*tmp;
    return cos_theta_NL * F * Vis * D;
}

// c=Base object color
// i=index of light
// N=Normal
// V=Vector to viewer
// dp = diffuse percentage (output)
// sp = specular percentage (output)
void computeLightContribution(vec3 c, int i, vec3 N, vec3 V, out vec3 diffuse, out vec3 specular)
{
    vec3 lightPosition = lightPositionAndDirectionalFlag[i].xyz;
    float positional = lightPositionAndDirectionalFlag[i].w;
    vec3 spotDir = spotDirection[i].xyz;
    float cosSpotInnerAngle = cosSpotAngles[i].x;
    float cosSpotOuterAngle = cosSpotAngles[i].y;
    vec3 lightColor = lightColorAndIntensity[i].xyz;
    float intensity = lightColorAndIntensity[i].w;
    
    vec3 L = lightPosition - worldPos*positional;
    float D = length(L);
    L /= D;
    
    //LambertDiffuse
    //float dp = dot(N,L);
    //dp = clamp(dp,0.0,1.0);
    
    //Phong
    //vec3 R = reflect(-L,N);
    //float sp = sign(dp) * dot(V,R);
    //sp = clamp(sp,0.0,1.0);
    //sp = pow(sp,16.0);
    
    //schlick compute first line outside loop
    vec3 Fzero = mix( vec3(0.04), c, MF );
    vec3 H = normalize(L + V);
    float costhetaNH = clamp(dot(N,H),0.0,1.0);
    float costhetaNL = clamp(dot(N,L),0.0,1.0);
    float costhetaVH = clamp(dot(V,H),0.0,1.0);
    float costhetaNV = clamp(dot(N,V),0.0,1.0);
    vec3 F = schlickFresnel(Fzero, costhetaVH, MF );
    vec3 dp = schlickDiffuse(F, costhetaVH, MF, c, costhetaNL);
    vec3 sp = schlickSpecular(F, costhetaVH, costhetaNH, c, costhetaNL, costhetaNV, RF,MF);

    float A = 1.0/(attenuation[0] + D*(attenuation[1] + D*attenuation[2]));
    A = clamp(A,0.0,1.0);
    
    dp *= A;
    sp *= A;
    
    float spotdot = dot(-L,spotDir);
    float SA = smoothstep( cosSpotOuterAngle, cosSpotInnerAngle, spotdot );
    
    dp *= SA;
    sp *= SA;

    diffuse = dp * c * intensity * lightColor;
    specular = sp * intensity * lightColor;
    
}
   
vec3 doBumpMapping(vec3 b, vec3 N)
{
    if( tangent.w == 0.0 )
        return N;

    N = normalize(N);

    vec3 T = tangent.xyz;
    T = T - dot(T, N) * N;
    T = normalize(T);
    vec3 B = cross( N, T);
    B = B * tangent.w;
    vec3 beta = 2.0 * (b - vec3(0.5));
    beta.xy = normalFactor * beta.xy;
    N = beta * mat3(T.x, B.x, N.x, T.y, B.y, N.y, T.z, B.z, N.z);

    
    return N;       //bump mapped normal
}

vec3 getProjColor(vec3 p, vec3 N){
    
    float t = -(dot( projTexPlane.xyz,p) + projTexPlane.w) / (dot( projTexPlane.xyz,projTexLightDir));
    vec3 pprime = p + t * projTexLightDir;
    vec3 w = pprime - projTexCorner;
    float u = dot(w,projTexEastVector)/projTexSize.x;
    float v = dot(w,projTexSouthVector)/projTexSize.y;

    u = clamp(u,0.0,1.0);
    v = clamp(v,0.0,1.0);
    vec4 projColor = texture(sampler2DArray(projectedTexture, texSampler),vec3(u,v,0.0));
    if( dot(N,projTexLightDir) < 0.0 ){
    return vec3(0,0,0);
}
    float projPct = clamp(dot(N,projTexLightDir),0.0,1.0);
    return projPct * projColor.rgb;
   }



void main(){
     
    vec4 c = texture( sampler2DArray(baseColorTexture,texSampler),
                      vec3(texcoord,animationFrame) );
    c = c * baseColorFactor;
    
    vec3 b = texture( sampler2DArray(normalTexture, texSampler),
                    vec3(texcoord2,animationFrame) ).xyz;


    vec3 N = normal;
    N = doBumpMapping(b.xyz, N);

    N = (vec4(N,0.0) * worldMatrix).xyz;
    N = normalize(N);

    float mappedY = 0.5 * (N.y+1.0);
    vec3 ambient = mix( AMBIENT_BELOW, AMBIENT_ABOVE, mappedY );
    
    vec3 V = normalize(eyePos-worldPos);

    //reflected view vector
    vec3 reflectedView = reflect(-V,N);

    //reflection color
    vec3 reflColor = texture(
    samplerCube(environmentMap, texSampler),
    reflectedView,
    RF*8.0).rgb;
    
    vec3 totaldp = vec3(0.0);
    vec3 totalsp = vec3(0.0);
    
    for(int i=0;i<MAX_LIGHTS;++i){
        vec3 dp;
        vec3 sp;
        computeLightContribution(c.rgb,i,N,V,dp,sp);
        
        totaldp += dp;
        totalsp += sp;
    }
    
    c.rgb = c.rgb * (ambient + totaldp) + totalsp;
    c.rgb = clamp(c.rgb, vec3(0.0), vec3(1.0) );
    vec4 e = texture( sampler2DArray(emissiveTexture,texSampler),
                      vec3(texcoord,0.0) );

    c.rgb += e.rgb * emissiveFactor.rgb;

    //add reflection color
    c.rgb += pow(1.0-RF,4.0) * MF * reflColor;

    
    vec3 p = worldPos;

   
   c.rgb += getProjColor( p, N) * 0.80;
   
    ////
    //the get color
    /////
       //// do the loop

    float stepSize = 0.05;
    float remaining = distance(eyePos,p);
    vec3 delta = stepSize * V;
    vec3 total = vec3(0.0);

    int numSteps = int(remaining / stepSize);

    for(int i=0;i<numSteps;++i)
        {
    //set "normal" to the light direction
    //so we get full light contribution here
            
            total += getProjColor( p, projTexLightDir);
            p += delta;
        }
    total *= 1.0/numSteps;

    c.rgb += 0.75 * total;
   

    color = c;
}
