#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(triangles, fractional_even_spacing) in;

//, fractional_even_spacing

layout(location=0) in vec2 texcoord[];
layout(location=1) in vec2 texcoord2[];
layout(location=2) in vec3 normal[];
layout(location=3) in vec3 worldpos[];
layout(location=4) in vec4 tangent[];

layout(location=0) out vec2 t_texcoord;
layout(location=1) out vec2 t_texcoord2;
layout(location=2) out vec3 t_normal;
layout(location=3) out vec3 t_worldpos;
layout(location=4) out vec4 t_tangent;

vec4 barycentric(vec4 p, vec4 q, vec4 r){
    return  gl_TessCoord[0] * p +
            gl_TessCoord[1] * q +
            gl_TessCoord[2] * r;
}

vec3 barycentric(vec3 p, vec3 q, vec3 r){
    return  gl_TessCoord[0] * p +
            gl_TessCoord[1] * q +
            gl_TessCoord[2] * r;
}

vec2 barycentric(vec2 p, vec2 q, vec2 r){
    return  gl_TessCoord[0] * p +
            gl_TessCoord[1] * q +
            gl_TessCoord[2] * r;
}

vec3 project( vec3 v, vec3 n, vec3 p ){
    //project p to plane defined by point v and normal n
    vec4 planeEquation = vec4(n, -dot(v,n) );
    float pdistance = dot( vec4(p,1),planeEquation );
    return p - pdistance * n;
}

void main(){

    //p1 = point on unrefined surface
    vec3 p1 = barycentric(
        worldpos[0], worldpos[1], worldpos[2]
    );
    //pr{1,2,3} = p1 projected to vertex planes
    vec3 pr1 = project( worldpos[0], normal[0], p1 );
    vec3 pr2 = project( worldpos[1], normal[1], p1 );
    vec3 pr3 = project( worldpos[2], normal[2], p1 );
    //average position
    vec3 p1a = barycentric( pr1,pr2,pr3 );
    //three-quarter/one-quarter mix
    float a=0.75;
    p1 = mix(p1,p1a,a);     //p1=(1.0-a)*p1 + a * p1a;
    t_worldpos = p1;
    gl_Position = vec4(t_worldpos,1.0) * viewProjMatrix;


    t_texcoord = barycentric(
        texcoord[0], texcoord[1], texcoord[2]
    );
    t_texcoord2 = barycentric(
        texcoord2[0], texcoord2[1], texcoord2[2]
    );
    t_normal = barycentric(
        normal[0], normal[1], normal[2]
    );
    t_worldpos = barycentric(
        worldpos[0], worldpos[1], worldpos[2]
    );
    t_tangent = barycentric(
        tangent[0], tangent[1], tangent[2]
    );
   
}