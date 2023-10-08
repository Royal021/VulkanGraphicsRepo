#include "Camera.h"
#include "Uniforms.h"
#include <cmath>

Camera::Camera( math2801::vec3 eye_,
        math2801::vec3 coi,
        math2801::vec3 up_,
        float fov,
        float aspectRatio,
        float hither_,
        float yon_
){
    this->fov_h = math2801::radians(fov);
    this->fov_v = aspectRatio*this->fov_h;
    this->hither=hither_;
    this->yon=yon_;
    this->updateProjMatrix();
    this->lookAt(eye_,coi,up_);
}

void Camera::updateProjMatrix()
{
    float d_h = 1/std::tan(this->fov_h);
    float d_v = 1/std::tan(this->fov_v);
    
    this->projMatrix = math2801::mat4(
       d_h,     0,      0,      0,
       0,       -d_v,   0,      0,
       0,       0,      this->yon/(this->hither-this->yon),      -1,
       0,       0,      (this->hither*this->yon)/(this->hither-this->yon),      0
    );
}

void Camera::lookAt(
        math2801::vec3 eye_,
        math2801::vec3 coi,
        math2801::vec3 up_
){
    this->eye = eye_;
    this->look = math2801::normalize(coi-this->eye);
    this->right = math2801::normalize(cross(this->look,up_));
    this->up = math2801::cross(this->right,this->look);
    this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    this->viewMatrix = math2801::mat4(
        this->right.x, this->up.x, -this->look.x, 0,
        this->right.y, this->up.y, -this->look.y, 0,
        this->right.z, this->up.z, -this->look.z, 0,
        -dot(this->eye,this->right), -dot(this->eye,this->up), dot(this->eye,this->look), 1
    );
    this->viewProjMatrix = this->viewMatrix*this->projMatrix;
}

void Camera::setUniforms(Uniforms* uniforms)
{
    uniforms->set("viewMatrix",this->viewMatrix);
    uniforms->set("viewProjMatrix",this->viewProjMatrix);
    uniforms->set("projMatrix",this->projMatrix);
    uniforms->set("eyePos",this->eye);
}

void Camera::strafe(float deltaRight, float deltaUp, float deltaLook)
{
    this->eye = this->eye + deltaRight*this->right + deltaUp*this->up + deltaLook*this->look;
    this->updateViewMatrix();
}

void Camera::strafeNoUpDown(float deltaRight, float deltaUp, float deltaLook)
{
    math2801::vec3 delta = deltaRight * this->right + deltaUp * this->up + deltaLook * this->look;
    delta.y = 0;
    this->eye = this->eye + delta;
    this->updateViewMatrix();
}
    
void Camera::turn(float angle)
{
    math2801::mat3 M = math2801::axisRotation3x3( math2801::vec3(0,1,0), angle );
    this->look = this->look * M;
    this->right = this->right * M;
    this->up = this->up * M;
    this->updateViewMatrix();
}

void Camera::tilt(float angle)
{
    math2801::mat3 M = math2801::axisRotation3x3( this->right, angle );
    this->look = this->look * M;
    this->up = this->up * M;
    this->updateViewMatrix();
}
