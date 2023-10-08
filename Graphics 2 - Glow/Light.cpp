#include "Light.h"
#include "gltf.h"
#include <sstream>
#include "consoleoutput.h"
#include "Uniforms.h"
#include "math2801.h"

using namespace math2801;

Light::Light(std::string name_, vec3 position_, bool positional_,
            vec3 direction_, float cosInnerSpotAngle_,
            float cosOuterSpotAngle_, vec3 color_,
            float intensity_)
{
    this->name=name_;
    this->position = position_;
    this->positional = positional_;
    this->direction = direction_;
    this->cosInnerSpotAngle = cosInnerSpotAngle_;
    this->cosOuterSpotAngle = cosOuterSpotAngle_;
    this->color = color_;
    this->intensity = intensity_;
}

Light::operator std::string()
{
    std::ostringstream oss;
    oss << "[Light:  " <<
        this->name << ": " <<
        "pos=" << this->position << 
        " positional=" << this->positional <<
        " direction=" << this->direction <<  
        " cosines=" << this->cosInnerSpotAngle << "," << this->cosOuterSpotAngle <<
        " color=" << this->color <<
        " intensity=" << this->intensity;
    return oss.str();
}

LightCollection::LightCollection(const gltf::GLTFScene& scene, int maxLights)
{
    for(const auto& L : scene.lights){
        this->lightPositionAndDirectionalFlag.push_back(
            vec4( L.position[0], L.position[1], L.position[2], L.position[3] )
        );
        this->lightColorAndIntensity.push_back( 
            vec4(L.color[0], L.color[1], L.color[2], L.intensity )
        );
        this->cosSpotAngles.push_back( 
            vec4(L.cosInnerAngle,L.cosOuterAngle,0,0)
        );
        this->spotDirection.push_back( 
            vec4( L.direction[0], L.direction[1], L.direction[2], 0.0 )
        );
    }
    
    if( (int)this->lightPositionAndDirectionalFlag.size() > maxLights ){
        warn("Scene has more than",maxLights,"lights; truncating");
        this->lightPositionAndDirectionalFlag.resize(maxLights);
        this->lightColorAndIntensity.resize(maxLights);
        this->cosSpotAngles.resize(maxLights);
        this->spotDirection.resize(maxLights);
    } else {
        while((int)lightPositionAndDirectionalFlag.size() < maxLights ){
            this->lightPositionAndDirectionalFlag.push_back(vec4(0,0,0,1));
            this->lightColorAndIntensity.push_back(vec4(0,0,0,0));
            this->cosSpotAngles.push_back(vec4(0,0,0,0));
            this->spotDirection.push_back(vec4(0,0,1,0));
        }
    }
}
 
void LightCollection::setUniforms(Uniforms* uniforms)
{
    uniforms->set("lightPositionAndDirectionalFlag",this->lightPositionAndDirectionalFlag);
    uniforms->set("lightColorAndIntensity", this->lightColorAndIntensity);
    uniforms->set("cosSpotAngles", this->cosSpotAngles);
    uniforms->set("spotDirection", this->spotDirection);
    uniforms->set("attenuation", vec3(300,0.0,0.30));
}

