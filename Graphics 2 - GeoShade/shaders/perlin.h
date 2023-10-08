
//This header can be used from GLSL or C++


// xoshiro algorithm from https://prng.di.unimi.it/xoroshiro64starstar.c
// It has this copyright notice:
// Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
// To the extent possible under law, the author has dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
// See <http://creativecommons.org/publicdomain/zero/1.0/>.




//pick one of these to choose a PRNG
#define USE_XOSHIRO
//#define USE_PCG
//#define USE_PCGnD

#ifdef __cplusplus

#include <cstdint>
#include <cmath>
#include "math2801.h"

typedef std::uint32_t uint;
using math2801::vec2;
using math2801::vec3;
using math2801::vec4;
using math2801::uvec2;
using math2801::uvec3;
using math2801::uvec4;
using math2801::dot;

float floor(float x){
    return (float)std::floor(x);
}

float ceil(float x){
    return (float)std::ceil(x);
}

float fract(float x){
    return float(x-int(x));
}

float smoothstep(float a, float b, float c)
{
    if(c < a)
        return 0;
    if(c > b)
        return 1;
    float t = (c-a)/(b-a);
    return 3*t*t - 2*t*t*t;
}

float mix(float a, float b, float c)
{
    return a + c * (b-a);
}


math2801::vec3 mix(math2801::vec3 a, math2801::vec3 b, float c)
{
    return a + c * (b-a);
}

#endif


float uintToFloat(uint val){
    //floats only hold 24 bits of precision
    //CPU doesn't care, but GPU will give artifacts
    //if we try to use all 32 bits
    return float(val>>8) / float(0xffffff);
}

uint rotateLeft(uint val, uint places)
{
    uint tmp = val << places;
    uint tmp2 = val >> (uint(32)-places);
    return tmp | tmp2;
}

#ifdef USE_XOSHIRO


uint state0;
uint state1;

uint xoshiro64()
{
    uint s0 = state0;
    uint s1 = state1;
    uint res = s0 * uint(0x9e3779bb);
    s1 = s0 ^ s1;
    state0 = rotateLeft(s0,uint(26));
    state0 ^= s1;
    state0 ^= s1<<9;
    state1 = rotateLeft(s1,uint(13));
    return res;
}


void seed(uint s0){
    state0=s0;
    state1=42;
    xoshiro64();
    xoshiro64();
}

void seed(uvec2 s){
    state0=s.x;
    state1=s.y;
    xoshiro64();
    xoshiro64();
}

void seed(uvec3 s){
    state0=s.x;
    state1=s.y;
    state0 ^= s.z>>13;
    state1 ^= s.z<<13;
    xoshiro64();
    xoshiro64();
}

void seed(uvec4 s){
    state0=s.x;
    state1=s.y;
    state0 ^= s.z>>13;
    state1 ^= s.z<<13;
    state0 ^= s.w>>12;
    state1 ^= s.w<<12;
    xoshiro64();
    xoshiro64();
}

float Random(){
    return uintToFloat( xoshiro64() );
}

#endif

#ifdef USE_PCG

uint state0;

uint pcg( )
{
    state0 *= uint(747796405);
    state0 += uint(2891336453);
    uint tmp1 = state0>>28;
    tmp1 += uint(4);
    tmp1 = state0 >> tmp1;
    state0 ^= tmp1;
    state0 *= uint(277803737);
    state0 ^= (state0 >> 22);
    return state0;
}


void seed(uint s0){
    state0 = s0;
}

void seed(uvec2 s){
    state0 = s.x ^ rotateLeft(s.y,uint(13) );
}

void seed(uvec3 s){
    state0 = s.x ^ rotateLeft(s.y,uint(13) ) ^ rotateLeft(s.z,uint(17));
}

void seed(uvec4 s){
    state0 = s.x ^ rotateLeft(s.y,uint(13) ) ^ rotateLeft(s.z,uint(17)) ^ rotateLeft(s.w,uint(23));
}

float Random(){
    return uintToFloat( pcg() );
}

#endif

#ifdef USE_PCGnD

uvec4 state;

//ref: Mark Jarzynski, Mac Olano. Hash Functions for GPU Rendering.
//https://jcgt.org/published/0009/03/02/
uvec3 pcg3d()
{
    state.x *= uint(1664525);
    state.y *= uint(1664525);
    state.z *= uint(1664525);
    state.x += uint(1013904223);
    state.y += uint(1013904223);
    state.z += uint(1013904223);
    state.x += state.y*state.z;
    state.y += state.z*state.x;
    state.z += state.x*state.y;
    state.x ^= state.x>>16;
    state.y ^= state.y>>16;
    state.z ^= state.z>>16;
    state.x += state.y*state.z;
    state.y += state.z*state.x;
    state.z += state.x*state.y;
    return uvec3(state.x,state.y,state.z);
}

//ref: Mark Jarzynski, Mac Olano. Hash Functions for GPU Rendering.
//https://jcgt.org/published/0009/03/02/
uvec4 pcg4d()
{
    state.x *= uint(1664525);
    state.y *= uint(1664525);
    state.z *= uint(1664525);
    state.w *= uint(1664525);
    state.x += uint(1013904223);
    state.y += uint(1013904223);
    state.z += uint(1013904223);
    state.w += uint(1013904223);
    state.x += state.y*state.w;
    state.y += state.z*state.x;
    state.z += state.x*state.y;
    state.w += state.y*state.z;
    state.x ^= state.x>>16;
    state.y ^= state.y>>16;
    state.z ^= state.z>>16;
    state.w ^= state.w>>16;
    state.x += state.y*state.w;
    state.y += state.z*state.x;
    state.z += state.x*state.y;
    state.w += state.y*state.z;
    return state;
}


void seed(uint s){
    state.x=s;
    state.y=state.z=state.w=uint(0);
}

void seed(uvec2 s){
    state.x = s.x;
    state.y = s.y;
    state.z=state.w=uint(0);
}

void seed(uvec3 s){
    state.x=s.x;
    state.y=s.y;
    state.z=s.z;
    state.w = uint(0);
}

void seed(uvec4 s){
    state=s;
}

float Random(float v)
{
    seed(uint(int(v)));
    uvec3 r = pcg3d();
    return uintToFloat(r.x);
}

vec2 Random(vec2 v)
{
    seed( uvec3( uint(int(v.x)), uint(int(v.y)), uint(1) ) );
    uvec3 r = pcg3d();
    return vec2(uintToFloat(r.x), uintToFloat(r.y));
}

vec3 Random(vec3 v)
{
    seed( uvec3( uint(int(v.x)), uint(int(v.y)), uint(int(v.z)) ) );
    uvec3 r = pcg3d();
    return vec3(uintToFloat(r.x), uintToFloat(r.y), uintToFloat(r.z));
}


vec4 Random(vec4 v)
{
    seed( uvec4( uint(int(v.x)), uint(int(v.y)), uint(int(v.z)), uint(int(v.w)) ) );
    uvec4 r = pcg4d();
    return vec4(uintToFloat(r.x), uintToFloat(r.y), uintToFloat(r.z), uintToFloat(r.w));
}

#endif


#if defined USE_XOSHIRO  || defined USE_PCG
//returns 0 or 1
float Random(float v)
{
    seed(uint(int(v)));
    return float(Random()<0.5);    //0 or 1
}

//returns randomized vector with each
//component in range [0,1]
vec2 Random(vec2 v)
{
    //can't go from int->float directly if negative
    seed(uvec2(uint(int(v.x)),uint(int(v.y))));
    return vec2(Random(),Random());
}

//returns randomized vector with each
//component in range [0,1]
vec3 Random(vec3 v)
{
    seed(uvec3(uint(int(v.x)),uint(int(v.y)),uint(int(v.z))));
    return vec3(Random(), Random(), Random() );
}

//returns randomized vector with each
//component in range [0,1]
vec4 Random(vec4 v)
{
    seed(uvec4(uint(int(v.x)),uint(int(v.y)),uint(int(v.z)),uint(int(v.w))));
    return vec4(Random(), Random(), Random(), Random() );
}


#endif

float gradient(float v1){
    float v = Random(v1);
    v = v - float(0.5);      //-0.5 or 0.5
    return v*float(2.0);      //-1 or 1
}

vec2 gradient(vec2 v)
{
    vec2 r = Random(v);
    r = r - vec2(0.5,0.5);
    r = normalize(r);
    return r;
}

vec3 gradient(vec3 v1)
{
    vec3 r = Random(v1);
    r -= vec3(0.5);
    r = normalize(r);
    return r;
}

vec4 gradient(vec4 v1){
    vec4 r = Random(v1);
    r -= vec4(0.5);
    r = normalize(r);
    return r;
}

float noise(float p){
    float q[2];
    q[0] = floor(p);
    q[1] = ceil(p);
    float d[2];
    for(int i=0;i<2;++i){
        float g = gradient(q[i]);
        float v = p-q[i];
        d[i] = g*v;
    }
    float t = fract(p);
    t = smoothstep(0.0, 1.0, t);
    float n =  mix( d[0], d[1], t );
    return n;
}

//returns value in -1...1 range
float noise(vec2 p)
{
    float x=p.x;
    float y=p.y;

    vec2 q[4];
    q[0] = vec2(floor(x), ceil(y));
    q[1] = vec2(ceil(x), ceil(y));
    q[2] = vec2(floor(x), floor(y));
    q[3] = vec2(ceil(x), floor(y));

    float d[4];
    for(int i=0;i<4;++i){
        vec2 g = gradient(q[i]);
        vec2 v = p-q[i];
        d[i] = dot(g, v);
    }

    float t = fract(x);
    t = smoothstep(0.0, 1.0, t);
    float a[2];
    a[0] =  mix( d[0], d[1], t );
    a[1] =  mix( d[2], d[3], t );
    t = fract(y);
    t = smoothstep(0.0, 1.0, t);
    float n = mix(a[1], a[0], t );
    return n;
}

float noise(vec3 p){
    float x = p.x; float y = p.y; float z = p.z; float t;
    vec3 q[8];  float d[8];  float a[4]; float b[2];
    q[0] = vec3(floor(x), ceil(y), floor(z));
    q[1] = vec3(ceil(x), ceil(y), floor(z));
    q[2] = vec3(floor(x), floor(y), floor(z));
    q[3] = vec3(ceil(x), floor(y), floor(z));
    q[4] = vec3(floor(x), ceil(y), ceil(z));
    q[5] = vec3(ceil(x), ceil(y), ceil(z));
    q[6] = vec3(floor(x), floor(y), ceil(z));
    q[7] = vec3(ceil(x), floor(y), ceil(z));
    for(int i=0;i<8;++i){
        vec3 g = gradient(q[i]);
        d[i] = dot(g, p-q[i]);
    }
    t = smoothstep(0.0, 1.0, fract(p.x));
    a[0] = mix( d[0], d[1], t ); a[1] = mix( d[2], d[3], t );
    a[2] = mix( d[4], d[5], t ); a[3] = mix( d[6], d[7], t );
    t = smoothstep(0.0, 1.0, fract(p.y));
    b[0] = mix( a[1], a[0], t ); b[1] = mix( a[3], a[2], t );
    t = smoothstep(0.0, 1.0, fract(p.z) );
    return mix(b[0], b[1], t );
}



float noise(vec4 p){
    float x = p.x; float y = p.y; float z = p.z; float w = p.w;
    float t;
    vec4 q[16];
    float d[16];
    float a[8];
    float b[4];
    float c[2];

    q[0] = vec4(floor(x), ceil(y), floor(z), floor(w));
    q[1] = vec4(ceil(x), ceil(y), floor(z), floor(w));
    q[2] = vec4(floor(x), floor(y), floor(z), floor(w));
    q[3] = vec4(ceil(x), floor(y), floor(z), floor(w));
    q[4] = vec4(floor(x), ceil(y), ceil(z), floor(w));
    q[5] = vec4(ceil(x), ceil(y), ceil(z), floor(w));
    q[6] = vec4(floor(x), floor(y), ceil(z), floor(w));
    q[7] = vec4(ceil(x), floor(y), ceil(z), floor(w));
    q[8] = vec4(floor(x), ceil(y), floor(z), ceil(w));
    q[9] = vec4(ceil(x), ceil(y), floor(z), ceil(w));
    q[10] = vec4(floor(x), floor(y), floor(z), ceil(w));
    q[11] = vec4(ceil(x), floor(y), floor(z), ceil(w));
    q[12] = vec4(floor(x), ceil(y), ceil(z), ceil(w));
    q[13] = vec4(ceil(x), ceil(y), ceil(z), ceil(w));
    q[14] = vec4(floor(x), floor(y), ceil(z), ceil(w));
    q[15] = vec4(ceil(x), floor(y), ceil(z), ceil(w));
    for(int i=0;i<16;++i){
        vec4 g = gradient(q[i]);
        d[i] = dot(g, p-q[i]);
    }
    t = smoothstep(0.0, 1.0, fract(p.x));
    a[0] = mix( d[0], d[1], t );
    a[1] = mix( d[2], d[3], t );
    a[2] = mix( d[4], d[5], t );
    a[3] = mix( d[6], d[7], t );
    a[4] = mix( d[8], d[9], t );
    a[5] = mix( d[10], d[11], t );
    a[6] = mix( d[12], d[13], t );
    a[7] = mix( d[14], d[15], t );
    t = smoothstep(0.0, 1.0, fract(p.y));
    b[0] = mix( a[1], a[0], t );
    b[1] = mix( a[3], a[2], t );
    b[2] = mix( a[5], a[4], t );
    b[3] = mix( a[7], a[6], t );
    t = smoothstep(0.0, 1.0, fract(p.z) );
    c[0] = mix( b[0], b[1], t );
    c[1] = mix( b[2], b[3], t );
    t = smoothstep(0.0, 1.0, fract(p.w) );
    return mix(c[0],c[1],t);
}
