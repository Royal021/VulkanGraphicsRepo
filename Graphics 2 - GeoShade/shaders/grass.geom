#version 450 core
#extension GL_GOOGLE_include_directive : enable
#include "pushconstants.txt"
#include "uniforms.txt"

layout(triangles) in;
layout(triangle_strip,max_vertices=23) out;

layout(location=0) in vec2 texcoord[];
layout(location=1) in vec3 normal[];
layout(location=2) in vec3 worldPos[];
layout(location=3) in vec2 tangent[];
layout(location=4) in vec4 texcoord2[];

layout(location=0) out vec2 g_texcoord;
layout(location=1) out vec2 g_texcoord2;
layout(location=2) out vec3 g_normal;
layout(location=3) out vec3 g_worldPos;
layout(location=4) out vec4 g_tangent;

void outputFace( vec3 p1,  vec3 p2,  vec3 p3,  vec3 p4,
                 vec4 p1s, vec4 p2s, vec4 p3s, vec4 p4s,
                 vec3 fn, vec2 tc){

    gl_Position = p1s;      g_normal = fn;
    g_worldPos = p1;        g_texcoord = tc;
    g_texcoord2 = vec2(0);  g_tangent = vec4(0);
    EmitVertex();
    gl_Position = p2s;      g_normal = fn;
    g_worldPos = p2;        g_texcoord = tc;
    g_texcoord2 = vec2(0);  g_tangent = vec4(0);
    EmitVertex();
    gl_Position = p4s;      g_normal = fn;
    g_worldPos = p4;        g_texcoord = tc;
    g_texcoord2 = vec2(0);  g_tangent = vec4(0);
    EmitVertex();
    gl_Position = p3s;      g_normal = fn;
    g_worldPos = p3;        g_texcoord = tc;
    g_texcoord2 = vec2(0);  g_tangent = vec4(0);
    EmitVertex();
    EndPrimitive();
}

void main(){

    for(int i=0;i<3;++i){
        g_texcoord = texcoord[i];
        g_texcoord2 = texcoord2[i];
        g_normal = normal[i];
        g_worldPos = worldPos[i];
        g_tangent = tangent[i];
        gl_Position = vec4(g_worldPos,1.0) * viewProjMatrix;
        EmitVertex();
    }
    EndPrimitive();

    vec3 p = (worldPos[0] + worldPos[1] + worldPos[2] ) / 3;
    vec3 N = (normal[0] + normal[1] + normal[2] ) / 3;
    N = (vec4(N,0.0)*worldMatrix).xyz;
    vec2 t = (texcoord[0] + texcoord[1] + texcoord[2] ) / 3;

    vec3 T = (tangent[0].xyz + tangent[1].xyz + tangent[2].xyz ) / 3;
    N = normalize(N);
    T = T - dot(T,N)*N;
    T = normalize(T);
    vec3 B = cross(T,N);

    vec3 a = p - shaftWidth * T + shaftDepth * B;
    vec3 b = p - shaftWidth * T - shaftDepth * B;
    vec3 c = p + shaftWidth * T - shaftDepth * B;
    vec3 d = p + shaftWidth * T + shaftDepth * B;

    vec3 ah = a + shaftHeight * N;
    vec3 bh = b + shaftHeight * N;
    vec3 ch = c + shaftHeight * N;
    vec3 dh = d + shaftHeight * N;

    vec4 as = vec4(a,1.0) * viewProjMatrix;
    vec4 bs = vec4(b,1.0) * viewProjMatrix;
    vec4 cs = vec4(c,1.0) * viewProjMatrix;
    vec4 ds = vec4(d,1.0) * viewProjMatrix;
    vec4 ahs = vec4(ah,1.0) * viewProjMatrix;
    vec4 bhs = vec4(bh,1.0) * viewProjMatrix;
    vec4 chs = vec4(ch,1.0) * viewProjMatrix;
    vec4 dhs = vec4(dh,1.0) * viewProjMatrix;
}