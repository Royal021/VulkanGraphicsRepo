#pragma once
#include "math2801.h"
#include <string>

class Uniforms;

namespace gltf{
    class GLTFScene;
};

///Information about one light.
class Light{
  public:
  
    //Name of light
    std::string name;
    
    /// position in space (positional) or direction to the light (if directional)
    math2801::vec3 position;
    
    /// True if positional; false if directional (sun).
    bool positional;
    
    /// Direction (for spotlight)
    math2801::vec3 direction;
    
    /// Cosine of angle where light starts to fade out (for spotlight; use -1 if not a spotlight)
    float cosInnerSpotAngle;
    
    /// Cosine of angle where light has faded out (for spotlight; use -1 if not a spotlight)
    float cosOuterSpotAngle;
    
    /// Color of light (RGB, 0...1)
    math2801::vec3 color;
    
    /// Intensity of light
    float intensity;
    
    /// Create light.
    /// @param name Name of light
    /// @param position Location in space (positional) or direction to the light (directional)
    /// @param positional True if positional; false if directional (sun).
    /// @param cosInnerSpotAngle Cosine of angle where light starts to fade out (for spotlight; use -1 if not a spotlight)
    /// @param cosOuterSpotAngle Cosine of angle where light has faded out (for spotlight; use -1 if not a spotlight)
    /// @param color Color of light (RGB, 0...1)
    /// intensity Intensity of light
    Light(std::string name, math2801::vec3 position, bool positional,
            math2801::vec3 direction, float cosInnerSpotAngle,
            float cosOuterSpotAngle, math2801::vec3 color,
            float intensity);
            
    /// For debugging: Return readable representation of light
    /// @return String description of light's parameters
    operator std::string();
    
};

/// A collection of several lights
class LightCollection{
  public:
  
    /// Parse GLTF data and retrieve information on lights
    /// @param scene The scene to pars
    /// @param maxLights Maximum number of lights. If the scene
    ///         has more than this number of lights, the excess
    ///         will be discarded and a warning is printed.
    ///         If the scene has fewer than this number of lights,
    ///         additional lights with a color of (0,0,0) and
    ///         an intensity of 0 are created.
    LightCollection(const gltf::GLTFScene& scene, int maxLights);
    
    /// Set the light uniforms
    void setUniforms(Uniforms* uniforms);
    
    /// xyz = light position; w=1 for positional, 0 for directional
    std::vector<math2801::vec4> lightPositionAndDirectionalFlag;
    
    /// xyz = light color (0...1); w=intensity
    std::vector<math2801::vec4> lightColorAndIntensity;
    
    /// xy = inner and outer spotlight angles
    std::vector<math2801::vec4> cosSpotAngles;
    
    /// xyz= spotlight direction
    std::vector<math2801::vec4> spotDirection;
};

