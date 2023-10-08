#pragma once
#include "math2801.h"

class Uniforms;

/// Contains information about the virtual camera.
class Camera{
  public:
    
    /// Horizontal field of view, in radians
    float fov_h;

    /// Vertical field of view, in radians
    float fov_v;
    
    /// Near clip distance. Must be positive.
    float hither;
    
    /// Far clip distance. Must be greater than hither.
    float yon;
    
    /// The projection matrix.
    math2801::mat4 projMatrix;
    
    /// The view matrix.
    math2801::mat4 viewMatrix;
    
    /// Combination of viewMatrix * projMatrix.
    math2801::mat4 viewProjMatrix;
    
    /// The eye location.
    math2801::vec3 eye;
    
    /// Unit vector to the viewer's right.
    math2801::vec3 right;
    
    /// Unit vector pointing upwards from the viewer's point of view.
    math2801::vec3 up;
    
    /// Unit vector pointing in the viewer's look direction.
    math2801::vec3 look;
    
    
    /// Create a camera.
    /// @param eye The eye location
    /// @param coi The center of interest
    /// @param up Approximate up vector
    /// @param fov The field of view, in radians
    /// @param aspectRatio Window aspect ratio, as width/height
    /// @param hither The near clip distance
    /// @param yon The far clip distance
    Camera( math2801::vec3 eye,
            math2801::vec3 coi,
            math2801::vec3 up,
            float fov,
            float aspectRatio,
            float hither,
            float yon
    );
    
    /// Recompute the projection matrix (projMatrix) and viewProjMatrix.
    void updateProjMatrix();

    /// Recompute the view matrix and viewProjMatrix.
    void updateViewMatrix();
    
    /// Set the uniforms associated with the camera.
    /// @param uniforms The Uniforms object to use
    void setUniforms(Uniforms* uniforms, std::string prefix);
    
    /// Set the camera parameters to look at a given location and call updateViewMatrix.
    /// @param eye The eye location
    /// @param coi The center of interest
    /// @param up Approximate up vector
    void lookAt(math2801::vec3 eye,
                math2801::vec3 coi,
                math2801::vec3 up);
           
    /// Strafe the camera.
    /// @param deltaRight Distance to move along the right vector.
    /// @param deltaUp Distance to move along the up vector.
    /// @param deltaLook Distance to move along the look vector.
    void strafe(float deltaRight, float deltaUp, float deltaLook);

    /// Strafe the camera but do not change the y value of eye.
    /// @param deltaRight Distance to move along the right vector.
    /// @param deltaUp Distance to move along the up vector.
    /// @param deltaLook Distance to move along the look vector.
    void strafeNoUpDown(float deltaRight, float deltaUp, float deltaLook);
    
    /// Turn the camera around the 'up' axis.
    /// @param angle Angle, in radians.
    void turn(float angle);

    /// tilt the camera around the 'right' axis.
    /// @param angle Angle, in radians.
    void tilt(float angle);
};
