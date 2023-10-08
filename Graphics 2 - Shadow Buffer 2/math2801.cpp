
// Generated from mk.py

//jh ssu fall 2019, fall 2020, fall 2022

// ~ Some of these functions (individually noted) are based on code from TDL.
// ~ The TDL copyright is as follows:
 
// ~ Copyright 2009, Google Inc.
// ~ All rights reserved.

// ~ Redistribution and use in source and binary forms, with or without
// ~ modification, are permitted provided that the following conditions are
// ~ met:

// ~ *  Redistributions of source code must retain the above copyright
// ~ notice, this list of conditions and the following disclaimer.
// ~ *  Redistributions in binary form must reproduce the above
// ~ copyright notice, this list of conditions and the following disclaimer
// ~ in the documentation and/or other materials provided with the
// ~ distribution.
// ~ *  Neither the name of Google Inc. nor the names of its
// ~ contributors may be used to endorse or promote products derived from
// ~ this software without specific prior written permission.

// ~ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ~ "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// ~ LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// ~ A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// ~ OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// ~ SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// ~ LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// ~ DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// ~ THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// ~ (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// ~ OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include "math2801.h"
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <random>

//disable warning for uninitialized member variables;
//this is spurious
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26495)
#endif


namespace math2801{
  
/// Convert any scalar type (float, double, int, unsigned) to T
template<typename T>
T anyScalarToType(const AnyScalar& s)
{
    if( std::holds_alternative<float>(s) )
        return (T)std::get<float>(s);
    else if( std::holds_alternative<double>(s) )
        return (T)std::get<double>(s);
    else if( std::holds_alternative<std::int32_t>(s) )
        return (T)std::get<std::int32_t>(s);
    else if( std::holds_alternative<std::uint32_t>(s) )
        return (T)std::get<std::uint32_t>(s);
    else{
        assert(0);
        throw std::runtime_error("internal error");
    }
}
vec2::vec2()
{
    this->x = float(0);
    this->y = float(0);
}
vec2::vec2(const vec2& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
}
vec2::vec2(const uvec2& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
}
vec2::vec2(const ivec2& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
}
vec2::vec2(const dvec2& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
}
/// Constructor
vec2::vec2( const AnyScalar& x_, const AnyScalar& y_ )
{
    this->x = anyScalarToType<float>(x_);
    this->y = anyScalarToType<float>(y_);
}
//no vec-scalar constructor for 2d vector
vec2::vec2(const AnyScalar& v)
{
    this->x = anyScalarToType<float>(v);
    this->y = this->x;
}
float vec2::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float vec2::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec2::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec2::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void vec2::operator=(const vec2& o)
{
    this->x = o.x;
    this->y = o.y;
}
void vec2::operator+=(const vec2& o)
{
    this->x += o.x;
    this->y += o.y;
}
void vec2::operator-=(const vec2& o)
{
    this->x -= o.x;
    this->y -= o.y;
}
void vec2::operator*=(const vec2& o)
{
    this->x *= o.x;
    this->y *= o.y;
}
void vec2::operator/=(const vec2& o)
{
    this->x /= o.x;
    this->y /= o.y;
}
    void vec2::operator*=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x *= tmp;
    this->y *= tmp;
}

    void vec2::operator/=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x /= tmp;
    this->y /= tmp;
}

vec2::operator std::string() const
{
    return std::string("vec2(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ')' ;
}
unsigned vec2::size() const
{
    return 2;
}
vec2 vec2::xy() const
{
    return vec2( x, y );
}
vec2 operator+(const vec2& arg1, const vec2& arg2)
{
    vec2 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    return rv;
}
vec2 operator-(const vec2& arg1, const vec2& arg2)
{
    vec2 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    return rv;
}
vec2 operator*(const vec2& arg1, const vec2& arg2)
{
    vec2 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    return rv;
}
vec2 operator/(const vec2& arg1, const vec2& arg2)
{
    vec2 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    return rv;
}
vec2 operator*( const vec2& v, float s)
{
    vec2 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    return rv;
}
vec2 operator*( float s, const vec2& v  )
{
     vec2 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    return rv;
}
vec2 operator/( const vec2& v, float s)
{
    vec2 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    return rv;
}
vec2 operator*( const vec2& v, double s)
{
    vec2 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    return rv;
}
vec2 operator*( double s, const vec2& v  )
{
     vec2 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    return rv;
}
vec2 operator/( const vec2& v, double s)
{
    vec2 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    return rv;
}
vec2 operator*( const vec2& v, std::int32_t s)
{
    vec2 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    return rv;
}
vec2 operator*( std::int32_t s, const vec2& v  )
{
     vec2 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    return rv;
}
vec2 operator/( const vec2& v, std::int32_t s)
{
    vec2 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    return rv;
}
vec2 operator*( const vec2& v, std::uint32_t s)
{
    vec2 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    return rv;
}
vec2 operator*( std::uint32_t s, const vec2& v  )
{
     vec2 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    return rv;
}
vec2 operator/( const vec2& v, std::uint32_t s)
{
    vec2 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    return rv;
}
bool operator<(const vec2& v1, const vec2& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    return false;   //v1==v2
}
bool operator>(const vec2& v1, const vec2& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    return false;   //v1==v2
}
bool operator<=(const vec2& v1, const vec2& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const vec2& v1, const vec2& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const vec2& v1, const vec2& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    return true;
}
bool operator!=(const vec2& v1, const vec2& v2)
{
    return !(v1==v2);
}
vec2 operator-(const vec2& v)
{
    vec2 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    return rv;
}
vec2 operator+(const vec2& v)
{
    return v;
}
float dot(const vec2& v1, const vec2& v2)
{
    return v1.x * v2.x+v1.y * v2.y;
}
float length(const vec2& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const vec2& v)
{
    o << "vec2(" << std::to_string(v.x) + ',' + std::to_string(v.y) << ")" ;
    return o;
}
//no cross product for non-3d vec
vec2 min(const vec2& v1, const vec2& v2)
{
    return vec2( (float) std::min(v1.x, v2.x),  (float) std::min(v1.y, v2.y));
}
vec2 max(const vec2& v1, const vec2& v2)
{
    return vec2( (float) std::max(v1.x, v2.x),  (float) std::max(v1.y, v2.y));
}

uvec2::uvec2()
{
    this->x = std::uint32_t(0);
    this->y = std::uint32_t(0);
}
uvec2::uvec2(const vec2& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
}
uvec2::uvec2(const uvec2& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
}
uvec2::uvec2(const ivec2& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
}
uvec2::uvec2(const dvec2& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
}
/// Constructor
uvec2::uvec2( const AnyScalar& x_, const AnyScalar& y_ )
{
    this->x = anyScalarToType<std::uint32_t>(x_);
    this->y = anyScalarToType<std::uint32_t>(y_);
}
//no vec-scalar constructor for 2d vector
uvec2::uvec2(const AnyScalar& v)
{
    this->x = anyScalarToType<std::uint32_t>(v);
    this->y = this->x;
}
std::uint32_t uvec2::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t uvec2::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec2::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec2::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void uvec2::operator=(const uvec2& o)
{
    this->x = o.x;
    this->y = o.y;
}
void uvec2::operator+=(const uvec2& o)
{
    this->x += o.x;
    this->y += o.y;
}
void uvec2::operator-=(const uvec2& o)
{
    this->x -= o.x;
    this->y -= o.y;
}
void uvec2::operator*=(const uvec2& o)
{
    this->x *= o.x;
    this->y *= o.y;
}
void uvec2::operator/=(const uvec2& o)
{
    this->x /= o.x;
    this->y /= o.y;
}
    void uvec2::operator*=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
}

    void uvec2::operator/=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
}

uvec2::operator std::string() const
{
    return std::string("vec2(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ')' ;
}
unsigned uvec2::size() const
{
    return 2;
}
uvec2 uvec2::xy() const
{
    return uvec2( x, y );
}
uvec2 operator+(const uvec2& arg1, const uvec2& arg2)
{
    uvec2 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    return rv;
}
uvec2 operator-(const uvec2& arg1, const uvec2& arg2)
{
    uvec2 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    return rv;
}
uvec2 operator*(const uvec2& arg1, const uvec2& arg2)
{
    uvec2 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    return rv;
}
uvec2 operator/(const uvec2& arg1, const uvec2& arg2)
{
    uvec2 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    return rv;
}
uvec2 operator*( const uvec2& v, float s)
{
    uvec2 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    return rv;
}
uvec2 operator*( float s, const uvec2& v  )
{
     uvec2 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    return rv;
}
uvec2 operator/( const uvec2& v, float s)
{
    uvec2 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    return rv;
}
uvec2 operator*( const uvec2& v, double s)
{
    uvec2 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    return rv;
}
uvec2 operator*( double s, const uvec2& v  )
{
     uvec2 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    return rv;
}
uvec2 operator/( const uvec2& v, double s)
{
    uvec2 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    return rv;
}
uvec2 operator*( const uvec2& v, std::int32_t s)
{
    uvec2 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    return rv;
}
uvec2 operator*( std::int32_t s, const uvec2& v  )
{
     uvec2 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    return rv;
}
uvec2 operator/( const uvec2& v, std::int32_t s)
{
    uvec2 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    return rv;
}
uvec2 operator*( const uvec2& v, std::uint32_t s)
{
    uvec2 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    return rv;
}
uvec2 operator*( std::uint32_t s, const uvec2& v  )
{
     uvec2 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    return rv;
}
uvec2 operator/( const uvec2& v, std::uint32_t s)
{
    uvec2 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    return rv;
}
bool operator<(const uvec2& v1, const uvec2& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    return false;   //v1==v2
}
bool operator>(const uvec2& v1, const uvec2& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    return false;   //v1==v2
}
bool operator<=(const uvec2& v1, const uvec2& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const uvec2& v1, const uvec2& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const uvec2& v1, const uvec2& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    return true;
}
bool operator!=(const uvec2& v1, const uvec2& v2)
{
    return !(v1==v2);
}
//no negation for unsigned vec type
uvec2 operator+(const uvec2& v)
{
    return v;
}
std::uint32_t dot(const uvec2& v1, const uvec2& v2)
{
    return v1.x * v2.x+v1.y * v2.y;
}
float length(const uvec2& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const uvec2& v)
{
    o << "uvec2(" << std::to_string(v.x) + ',' + std::to_string(v.y) << ")" ;
    return o;
}
//no cross product for non-3d vec
uvec2 min(const uvec2& v1, const uvec2& v2)
{
    return uvec2( (std::uint32_t) std::min(v1.x, v2.x),  (std::uint32_t) std::min(v1.y, v2.y));
}
uvec2 max(const uvec2& v1, const uvec2& v2)
{
    return uvec2( (std::uint32_t) std::max(v1.x, v2.x),  (std::uint32_t) std::max(v1.y, v2.y));
}

ivec2::ivec2()
{
    this->x = std::int32_t(0);
    this->y = std::int32_t(0);
}
ivec2::ivec2(const vec2& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
}
ivec2::ivec2(const uvec2& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
}
ivec2::ivec2(const ivec2& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
}
ivec2::ivec2(const dvec2& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
}
/// Constructor
ivec2::ivec2( const AnyScalar& x_, const AnyScalar& y_ )
{
    this->x = anyScalarToType<std::int32_t>(x_);
    this->y = anyScalarToType<std::int32_t>(y_);
}
//no vec-scalar constructor for 2d vector
ivec2::ivec2(const AnyScalar& v)
{
    this->x = anyScalarToType<std::int32_t>(v);
    this->y = this->x;
}
std::int32_t ivec2::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t ivec2::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec2::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec2::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void ivec2::operator=(const ivec2& o)
{
    this->x = o.x;
    this->y = o.y;
}
void ivec2::operator+=(const ivec2& o)
{
    this->x += o.x;
    this->y += o.y;
}
void ivec2::operator-=(const ivec2& o)
{
    this->x -= o.x;
    this->y -= o.y;
}
void ivec2::operator*=(const ivec2& o)
{
    this->x *= o.x;
    this->y *= o.y;
}
void ivec2::operator/=(const ivec2& o)
{
    this->x /= o.x;
    this->y /= o.y;
}
    void ivec2::operator*=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
}

    void ivec2::operator/=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
}

ivec2::operator std::string() const
{
    return std::string("vec2(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ')' ;
}
unsigned ivec2::size() const
{
    return 2;
}
ivec2 ivec2::xy() const
{
    return ivec2( x, y );
}
ivec2 operator+(const ivec2& arg1, const ivec2& arg2)
{
    ivec2 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    return rv;
}
ivec2 operator-(const ivec2& arg1, const ivec2& arg2)
{
    ivec2 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    return rv;
}
ivec2 operator*(const ivec2& arg1, const ivec2& arg2)
{
    ivec2 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    return rv;
}
ivec2 operator/(const ivec2& arg1, const ivec2& arg2)
{
    ivec2 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    return rv;
}
ivec2 operator*( const ivec2& v, float s)
{
    ivec2 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    return rv;
}
ivec2 operator*( float s, const ivec2& v  )
{
     ivec2 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    return rv;
}
ivec2 operator/( const ivec2& v, float s)
{
    ivec2 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    return rv;
}
ivec2 operator*( const ivec2& v, double s)
{
    ivec2 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    return rv;
}
ivec2 operator*( double s, const ivec2& v  )
{
     ivec2 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    return rv;
}
ivec2 operator/( const ivec2& v, double s)
{
    ivec2 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    return rv;
}
ivec2 operator*( const ivec2& v, std::int32_t s)
{
    ivec2 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    return rv;
}
ivec2 operator*( std::int32_t s, const ivec2& v  )
{
     ivec2 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    return rv;
}
ivec2 operator/( const ivec2& v, std::int32_t s)
{
    ivec2 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    return rv;
}
ivec2 operator*( const ivec2& v, std::uint32_t s)
{
    ivec2 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    return rv;
}
ivec2 operator*( std::uint32_t s, const ivec2& v  )
{
     ivec2 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    return rv;
}
ivec2 operator/( const ivec2& v, std::uint32_t s)
{
    ivec2 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    return rv;
}
bool operator<(const ivec2& v1, const ivec2& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    return false;   //v1==v2
}
bool operator>(const ivec2& v1, const ivec2& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    return false;   //v1==v2
}
bool operator<=(const ivec2& v1, const ivec2& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const ivec2& v1, const ivec2& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const ivec2& v1, const ivec2& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    return true;
}
bool operator!=(const ivec2& v1, const ivec2& v2)
{
    return !(v1==v2);
}
ivec2 operator-(const ivec2& v)
{
    ivec2 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    return rv;
}
ivec2 operator+(const ivec2& v)
{
    return v;
}
std::int32_t dot(const ivec2& v1, const ivec2& v2)
{
    return v1.x * v2.x+v1.y * v2.y;
}
float length(const ivec2& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const ivec2& v)
{
    o << "ivec2(" << std::to_string(v.x) + ',' + std::to_string(v.y) << ")" ;
    return o;
}
//no cross product for non-3d vec
ivec2 min(const ivec2& v1, const ivec2& v2)
{
    return ivec2( (std::int32_t) std::min(v1.x, v2.x),  (std::int32_t) std::min(v1.y, v2.y));
}
ivec2 max(const ivec2& v1, const ivec2& v2)
{
    return ivec2( (std::int32_t) std::max(v1.x, v2.x),  (std::int32_t) std::max(v1.y, v2.y));
}

dvec2::dvec2()
{
    this->x = double(0);
    this->y = double(0);
}
dvec2::dvec2(const vec2& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
}
dvec2::dvec2(const uvec2& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
}
dvec2::dvec2(const ivec2& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
}
dvec2::dvec2(const dvec2& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
}
/// Constructor
dvec2::dvec2( const AnyScalar& x_, const AnyScalar& y_ )
{
    this->x = anyScalarToType<double>(x_);
    this->y = anyScalarToType<double>(y_);
}
//no vec-scalar constructor for 2d vector
dvec2::dvec2(const AnyScalar& v)
{
    this->x = anyScalarToType<double>(v);
    this->y = this->x;
}
double dvec2::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double dvec2::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec2::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec2::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void dvec2::operator=(const dvec2& o)
{
    this->x = o.x;
    this->y = o.y;
}
void dvec2::operator+=(const dvec2& o)
{
    this->x += o.x;
    this->y += o.y;
}
void dvec2::operator-=(const dvec2& o)
{
    this->x -= o.x;
    this->y -= o.y;
}
void dvec2::operator*=(const dvec2& o)
{
    this->x *= o.x;
    this->y *= o.y;
}
void dvec2::operator/=(const dvec2& o)
{
    this->x /= o.x;
    this->y /= o.y;
}
    void dvec2::operator*=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x *= tmp;
    this->y *= tmp;
}

    void dvec2::operator/=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x /= tmp;
    this->y /= tmp;
}

dvec2::operator std::string() const
{
    return std::string("vec2(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ')' ;
}
unsigned dvec2::size() const
{
    return 2;
}
dvec2 dvec2::xy() const
{
    return dvec2( x, y );
}
dvec2 operator+(const dvec2& arg1, const dvec2& arg2)
{
    dvec2 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    return rv;
}
dvec2 operator-(const dvec2& arg1, const dvec2& arg2)
{
    dvec2 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    return rv;
}
dvec2 operator*(const dvec2& arg1, const dvec2& arg2)
{
    dvec2 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    return rv;
}
dvec2 operator/(const dvec2& arg1, const dvec2& arg2)
{
    dvec2 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    return rv;
}
dvec2 operator*( const dvec2& v, float s)
{
    dvec2 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    return rv;
}
dvec2 operator*( float s, const dvec2& v  )
{
     dvec2 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    return rv;
}
dvec2 operator/( const dvec2& v, float s)
{
    dvec2 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    return rv;
}
dvec2 operator*( const dvec2& v, double s)
{
    dvec2 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    return rv;
}
dvec2 operator*( double s, const dvec2& v  )
{
     dvec2 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    return rv;
}
dvec2 operator/( const dvec2& v, double s)
{
    dvec2 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    return rv;
}
dvec2 operator*( const dvec2& v, std::int32_t s)
{
    dvec2 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    return rv;
}
dvec2 operator*( std::int32_t s, const dvec2& v  )
{
     dvec2 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    return rv;
}
dvec2 operator/( const dvec2& v, std::int32_t s)
{
    dvec2 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    return rv;
}
dvec2 operator*( const dvec2& v, std::uint32_t s)
{
    dvec2 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    return rv;
}
dvec2 operator*( std::uint32_t s, const dvec2& v  )
{
     dvec2 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    return rv;
}
dvec2 operator/( const dvec2& v, std::uint32_t s)
{
    dvec2 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    return rv;
}
bool operator<(const dvec2& v1, const dvec2& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    return false;   //v1==v2
}
bool operator>(const dvec2& v1, const dvec2& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    return false;   //v1==v2
}
bool operator<=(const dvec2& v1, const dvec2& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const dvec2& v1, const dvec2& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const dvec2& v1, const dvec2& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    return true;
}
bool operator!=(const dvec2& v1, const dvec2& v2)
{
    return !(v1==v2);
}
dvec2 operator-(const dvec2& v)
{
    dvec2 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    return rv;
}
dvec2 operator+(const dvec2& v)
{
    return v;
}
double dot(const dvec2& v1, const dvec2& v2)
{
    return v1.x * v2.x+v1.y * v2.y;
}
float length(const dvec2& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const dvec2& v)
{
    o << "dvec2(" << std::to_string(v.x) + ',' + std::to_string(v.y) << ")" ;
    return o;
}
//no cross product for non-3d vec
dvec2 min(const dvec2& v1, const dvec2& v2)
{
    return dvec2( (double) std::min(v1.x, v2.x),  (double) std::min(v1.y, v2.y));
}
dvec2 max(const dvec2& v1, const dvec2& v2)
{
    return dvec2( (double) std::max(v1.x, v2.x),  (double) std::max(v1.y, v2.y));
}

vec3::vec3()
{
    this->x = float(0);
    this->y = float(0);
    this->z = float(0);
}
vec3::vec3(const vec3& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
}
vec3::vec3(const uvec3& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
}
vec3::vec3(const ivec3& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
}
vec3::vec3(const dvec3& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
}
/// Constructor
vec3::vec3( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_ )
{
    this->x = anyScalarToType<float>(x_);
    this->y = anyScalarToType<float>(y_);
    this->z = anyScalarToType<float>(z_);
}
vec3::vec3(const vec2& v, const AnyScalar& z_) :
    vec3::vec3(v.x, v.y, z_)
{}
vec3::vec3(const AnyScalar& v)
{
    this->x = anyScalarToType<float>(v);
    this->y = this->x;
    this->z = this->x;
}
float vec3::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float vec3::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec3::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec3::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void vec3::operator=(const vec3& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
}
void vec3::operator+=(const vec3& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
}
void vec3::operator-=(const vec3& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
}
void vec3::operator*=(const vec3& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
}
void vec3::operator/=(const vec3& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
}
    void vec3::operator*=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
}

    void vec3::operator/=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
}

vec3::operator std::string() const
{
    return std::string("vec3(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ')' ;
}
unsigned vec3::size() const
{
    return 3;
}
vec2 vec3::xy() const
{
    return vec2( x, y );
}
vec3 vec3::xyz() const
{
    return vec3( x, y, z );
}
vec3 operator+(const vec3& arg1, const vec3& arg2)
{
    vec3 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    return rv;
}
vec3 operator-(const vec3& arg1, const vec3& arg2)
{
    vec3 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    return rv;
}
vec3 operator*(const vec3& arg1, const vec3& arg2)
{
    vec3 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    return rv;
}
vec3 operator/(const vec3& arg1, const vec3& arg2)
{
    vec3 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    return rv;
}
vec3 operator*( const vec3& v, float s)
{
    vec3 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    return rv;
}
vec3 operator*( float s, const vec3& v  )
{
     vec3 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    return rv;
}
vec3 operator/( const vec3& v, float s)
{
    vec3 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    return rv;
}
vec3 operator*( const vec3& v, double s)
{
    vec3 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    return rv;
}
vec3 operator*( double s, const vec3& v  )
{
     vec3 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    return rv;
}
vec3 operator/( const vec3& v, double s)
{
    vec3 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    return rv;
}
vec3 operator*( const vec3& v, std::int32_t s)
{
    vec3 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    return rv;
}
vec3 operator*( std::int32_t s, const vec3& v  )
{
     vec3 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    return rv;
}
vec3 operator/( const vec3& v, std::int32_t s)
{
    vec3 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    return rv;
}
vec3 operator*( const vec3& v, std::uint32_t s)
{
    vec3 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    return rv;
}
vec3 operator*( std::uint32_t s, const vec3& v  )
{
     vec3 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    return rv;
}
vec3 operator/( const vec3& v, std::uint32_t s)
{
    vec3 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    return rv;
}
bool operator<(const vec3& v1, const vec3& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    return false;   //v1==v2
}
bool operator>(const vec3& v1, const vec3& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    return false;   //v1==v2
}
bool operator<=(const vec3& v1, const vec3& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const vec3& v1, const vec3& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const vec3& v1, const vec3& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    return true;
}
bool operator!=(const vec3& v1, const vec3& v2)
{
    return !(v1==v2);
}
vec3 operator-(const vec3& v)
{
    vec3 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    return rv;
}
vec3 operator+(const vec3& v)
{
    return v;
}
float dot(const vec3& v1, const vec3& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z;
}
float length(const vec3& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const vec3& v)
{
    o << "vec3(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) << ")" ;
    return o;
}
vec3 cross(const vec3& v, const vec3& w)
{
    return vec3(
       v.y*w.z - w.y*v.z,
       w.x*v.z - v.x*w.z,
       v.x*w.y - w.x*v.y
    );
}
vec3 min(const vec3& v1, const vec3& v2)
{
    return vec3( (float) std::min(v1.x, v2.x),  (float) std::min(v1.y, v2.y),  (float) std::min(v1.z, v2.z));
}
vec3 max(const vec3& v1, const vec3& v2)
{
    return vec3( (float) std::max(v1.x, v2.x),  (float) std::max(v1.y, v2.y),  (float) std::max(v1.z, v2.z));
}

uvec3::uvec3()
{
    this->x = std::uint32_t(0);
    this->y = std::uint32_t(0);
    this->z = std::uint32_t(0);
}
uvec3::uvec3(const vec3& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
}
uvec3::uvec3(const uvec3& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
}
uvec3::uvec3(const ivec3& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
}
uvec3::uvec3(const dvec3& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
}
/// Constructor
uvec3::uvec3( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_ )
{
    this->x = anyScalarToType<std::uint32_t>(x_);
    this->y = anyScalarToType<std::uint32_t>(y_);
    this->z = anyScalarToType<std::uint32_t>(z_);
}
uvec3::uvec3(const uvec2& v, const AnyScalar& z_) :
    uvec3::uvec3(v.x, v.y, z_)
{}
uvec3::uvec3(const AnyScalar& v)
{
    this->x = anyScalarToType<std::uint32_t>(v);
    this->y = this->x;
    this->z = this->x;
}
std::uint32_t uvec3::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t uvec3::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec3::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec3::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void uvec3::operator=(const uvec3& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
}
void uvec3::operator+=(const uvec3& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
}
void uvec3::operator-=(const uvec3& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
}
void uvec3::operator*=(const uvec3& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
}
void uvec3::operator/=(const uvec3& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
}
    void uvec3::operator*=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
}

    void uvec3::operator/=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
}

uvec3::operator std::string() const
{
    return std::string("vec3(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ')' ;
}
unsigned uvec3::size() const
{
    return 3;
}
uvec2 uvec3::xy() const
{
    return uvec2( x, y );
}
uvec3 uvec3::xyz() const
{
    return uvec3( x, y, z );
}
uvec3 operator+(const uvec3& arg1, const uvec3& arg2)
{
    uvec3 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    return rv;
}
uvec3 operator-(const uvec3& arg1, const uvec3& arg2)
{
    uvec3 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    return rv;
}
uvec3 operator*(const uvec3& arg1, const uvec3& arg2)
{
    uvec3 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    return rv;
}
uvec3 operator/(const uvec3& arg1, const uvec3& arg2)
{
    uvec3 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    return rv;
}
uvec3 operator*( const uvec3& v, float s)
{
    uvec3 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    return rv;
}
uvec3 operator*( float s, const uvec3& v  )
{
     uvec3 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    return rv;
}
uvec3 operator/( const uvec3& v, float s)
{
    uvec3 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    return rv;
}
uvec3 operator*( const uvec3& v, double s)
{
    uvec3 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    return rv;
}
uvec3 operator*( double s, const uvec3& v  )
{
     uvec3 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    return rv;
}
uvec3 operator/( const uvec3& v, double s)
{
    uvec3 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    return rv;
}
uvec3 operator*( const uvec3& v, std::int32_t s)
{
    uvec3 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    return rv;
}
uvec3 operator*( std::int32_t s, const uvec3& v  )
{
     uvec3 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    return rv;
}
uvec3 operator/( const uvec3& v, std::int32_t s)
{
    uvec3 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    return rv;
}
uvec3 operator*( const uvec3& v, std::uint32_t s)
{
    uvec3 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    return rv;
}
uvec3 operator*( std::uint32_t s, const uvec3& v  )
{
     uvec3 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    return rv;
}
uvec3 operator/( const uvec3& v, std::uint32_t s)
{
    uvec3 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    return rv;
}
bool operator<(const uvec3& v1, const uvec3& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    return false;   //v1==v2
}
bool operator>(const uvec3& v1, const uvec3& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    return false;   //v1==v2
}
bool operator<=(const uvec3& v1, const uvec3& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const uvec3& v1, const uvec3& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const uvec3& v1, const uvec3& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    return true;
}
bool operator!=(const uvec3& v1, const uvec3& v2)
{
    return !(v1==v2);
}
//no negation for unsigned vec type
uvec3 operator+(const uvec3& v)
{
    return v;
}
std::uint32_t dot(const uvec3& v1, const uvec3& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z;
}
float length(const uvec3& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const uvec3& v)
{
    o << "uvec3(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) << ")" ;
    return o;
}
uvec3 cross(const uvec3& v, const uvec3& w)
{
    return uvec3(
       v.y*w.z - w.y*v.z,
       w.x*v.z - v.x*w.z,
       v.x*w.y - w.x*v.y
    );
}
uvec3 min(const uvec3& v1, const uvec3& v2)
{
    return uvec3( (std::uint32_t) std::min(v1.x, v2.x),  (std::uint32_t) std::min(v1.y, v2.y),  (std::uint32_t) std::min(v1.z, v2.z));
}
uvec3 max(const uvec3& v1, const uvec3& v2)
{
    return uvec3( (std::uint32_t) std::max(v1.x, v2.x),  (std::uint32_t) std::max(v1.y, v2.y),  (std::uint32_t) std::max(v1.z, v2.z));
}

ivec3::ivec3()
{
    this->x = std::int32_t(0);
    this->y = std::int32_t(0);
    this->z = std::int32_t(0);
}
ivec3::ivec3(const vec3& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
}
ivec3::ivec3(const uvec3& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
}
ivec3::ivec3(const ivec3& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
}
ivec3::ivec3(const dvec3& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
}
/// Constructor
ivec3::ivec3( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_ )
{
    this->x = anyScalarToType<std::int32_t>(x_);
    this->y = anyScalarToType<std::int32_t>(y_);
    this->z = anyScalarToType<std::int32_t>(z_);
}
ivec3::ivec3(const ivec2& v, const AnyScalar& z_) :
    ivec3::ivec3(v.x, v.y, z_)
{}
ivec3::ivec3(const AnyScalar& v)
{
    this->x = anyScalarToType<std::int32_t>(v);
    this->y = this->x;
    this->z = this->x;
}
std::int32_t ivec3::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t ivec3::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec3::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec3::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void ivec3::operator=(const ivec3& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
}
void ivec3::operator+=(const ivec3& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
}
void ivec3::operator-=(const ivec3& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
}
void ivec3::operator*=(const ivec3& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
}
void ivec3::operator/=(const ivec3& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
}
    void ivec3::operator*=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
}

    void ivec3::operator/=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
}

ivec3::operator std::string() const
{
    return std::string("vec3(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ')' ;
}
unsigned ivec3::size() const
{
    return 3;
}
ivec2 ivec3::xy() const
{
    return ivec2( x, y );
}
ivec3 ivec3::xyz() const
{
    return ivec3( x, y, z );
}
ivec3 operator+(const ivec3& arg1, const ivec3& arg2)
{
    ivec3 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    return rv;
}
ivec3 operator-(const ivec3& arg1, const ivec3& arg2)
{
    ivec3 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    return rv;
}
ivec3 operator*(const ivec3& arg1, const ivec3& arg2)
{
    ivec3 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    return rv;
}
ivec3 operator/(const ivec3& arg1, const ivec3& arg2)
{
    ivec3 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    return rv;
}
ivec3 operator*( const ivec3& v, float s)
{
    ivec3 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    return rv;
}
ivec3 operator*( float s, const ivec3& v  )
{
     ivec3 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    return rv;
}
ivec3 operator/( const ivec3& v, float s)
{
    ivec3 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    return rv;
}
ivec3 operator*( const ivec3& v, double s)
{
    ivec3 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    return rv;
}
ivec3 operator*( double s, const ivec3& v  )
{
     ivec3 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    return rv;
}
ivec3 operator/( const ivec3& v, double s)
{
    ivec3 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    return rv;
}
ivec3 operator*( const ivec3& v, std::int32_t s)
{
    ivec3 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    return rv;
}
ivec3 operator*( std::int32_t s, const ivec3& v  )
{
     ivec3 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    return rv;
}
ivec3 operator/( const ivec3& v, std::int32_t s)
{
    ivec3 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    return rv;
}
ivec3 operator*( const ivec3& v, std::uint32_t s)
{
    ivec3 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    return rv;
}
ivec3 operator*( std::uint32_t s, const ivec3& v  )
{
     ivec3 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    return rv;
}
ivec3 operator/( const ivec3& v, std::uint32_t s)
{
    ivec3 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    return rv;
}
bool operator<(const ivec3& v1, const ivec3& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    return false;   //v1==v2
}
bool operator>(const ivec3& v1, const ivec3& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    return false;   //v1==v2
}
bool operator<=(const ivec3& v1, const ivec3& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const ivec3& v1, const ivec3& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const ivec3& v1, const ivec3& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    return true;
}
bool operator!=(const ivec3& v1, const ivec3& v2)
{
    return !(v1==v2);
}
ivec3 operator-(const ivec3& v)
{
    ivec3 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    return rv;
}
ivec3 operator+(const ivec3& v)
{
    return v;
}
std::int32_t dot(const ivec3& v1, const ivec3& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z;
}
float length(const ivec3& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const ivec3& v)
{
    o << "ivec3(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) << ")" ;
    return o;
}
ivec3 cross(const ivec3& v, const ivec3& w)
{
    return ivec3(
       v.y*w.z - w.y*v.z,
       w.x*v.z - v.x*w.z,
       v.x*w.y - w.x*v.y
    );
}
ivec3 min(const ivec3& v1, const ivec3& v2)
{
    return ivec3( (std::int32_t) std::min(v1.x, v2.x),  (std::int32_t) std::min(v1.y, v2.y),  (std::int32_t) std::min(v1.z, v2.z));
}
ivec3 max(const ivec3& v1, const ivec3& v2)
{
    return ivec3( (std::int32_t) std::max(v1.x, v2.x),  (std::int32_t) std::max(v1.y, v2.y),  (std::int32_t) std::max(v1.z, v2.z));
}

dvec3::dvec3()
{
    this->x = double(0);
    this->y = double(0);
    this->z = double(0);
}
dvec3::dvec3(const vec3& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
}
dvec3::dvec3(const uvec3& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
}
dvec3::dvec3(const ivec3& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
}
dvec3::dvec3(const dvec3& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
}
/// Constructor
dvec3::dvec3( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_ )
{
    this->x = anyScalarToType<double>(x_);
    this->y = anyScalarToType<double>(y_);
    this->z = anyScalarToType<double>(z_);
}
dvec3::dvec3(const dvec2& v, const AnyScalar& z_) :
    dvec3::dvec3(v.x, v.y, z_)
{}
dvec3::dvec3(const AnyScalar& v)
{
    this->x = anyScalarToType<double>(v);
    this->y = this->x;
    this->z = this->x;
}
double dvec3::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double dvec3::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec3::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec3::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void dvec3::operator=(const dvec3& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
}
void dvec3::operator+=(const dvec3& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
}
void dvec3::operator-=(const dvec3& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
}
void dvec3::operator*=(const dvec3& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
}
void dvec3::operator/=(const dvec3& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
}
    void dvec3::operator*=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
}

    void dvec3::operator/=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
}

dvec3::operator std::string() const
{
    return std::string("vec3(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ')' ;
}
unsigned dvec3::size() const
{
    return 3;
}
dvec2 dvec3::xy() const
{
    return dvec2( x, y );
}
dvec3 dvec3::xyz() const
{
    return dvec3( x, y, z );
}
dvec3 operator+(const dvec3& arg1, const dvec3& arg2)
{
    dvec3 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    return rv;
}
dvec3 operator-(const dvec3& arg1, const dvec3& arg2)
{
    dvec3 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    return rv;
}
dvec3 operator*(const dvec3& arg1, const dvec3& arg2)
{
    dvec3 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    return rv;
}
dvec3 operator/(const dvec3& arg1, const dvec3& arg2)
{
    dvec3 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    return rv;
}
dvec3 operator*( const dvec3& v, float s)
{
    dvec3 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    return rv;
}
dvec3 operator*( float s, const dvec3& v  )
{
     dvec3 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    return rv;
}
dvec3 operator/( const dvec3& v, float s)
{
    dvec3 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    return rv;
}
dvec3 operator*( const dvec3& v, double s)
{
    dvec3 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    return rv;
}
dvec3 operator*( double s, const dvec3& v  )
{
     dvec3 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    return rv;
}
dvec3 operator/( const dvec3& v, double s)
{
    dvec3 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    return rv;
}
dvec3 operator*( const dvec3& v, std::int32_t s)
{
    dvec3 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    return rv;
}
dvec3 operator*( std::int32_t s, const dvec3& v  )
{
     dvec3 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    return rv;
}
dvec3 operator/( const dvec3& v, std::int32_t s)
{
    dvec3 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    return rv;
}
dvec3 operator*( const dvec3& v, std::uint32_t s)
{
    dvec3 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    return rv;
}
dvec3 operator*( std::uint32_t s, const dvec3& v  )
{
     dvec3 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    return rv;
}
dvec3 operator/( const dvec3& v, std::uint32_t s)
{
    dvec3 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    return rv;
}
bool operator<(const dvec3& v1, const dvec3& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    return false;   //v1==v2
}
bool operator>(const dvec3& v1, const dvec3& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    return false;   //v1==v2
}
bool operator<=(const dvec3& v1, const dvec3& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const dvec3& v1, const dvec3& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const dvec3& v1, const dvec3& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    return true;
}
bool operator!=(const dvec3& v1, const dvec3& v2)
{
    return !(v1==v2);
}
dvec3 operator-(const dvec3& v)
{
    dvec3 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    return rv;
}
dvec3 operator+(const dvec3& v)
{
    return v;
}
double dot(const dvec3& v1, const dvec3& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z;
}
float length(const dvec3& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const dvec3& v)
{
    o << "dvec3(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) << ")" ;
    return o;
}
dvec3 cross(const dvec3& v, const dvec3& w)
{
    return dvec3(
       v.y*w.z - w.y*v.z,
       w.x*v.z - v.x*w.z,
       v.x*w.y - w.x*v.y
    );
}
dvec3 min(const dvec3& v1, const dvec3& v2)
{
    return dvec3( (double) std::min(v1.x, v2.x),  (double) std::min(v1.y, v2.y),  (double) std::min(v1.z, v2.z));
}
dvec3 max(const dvec3& v1, const dvec3& v2)
{
    return dvec3( (double) std::max(v1.x, v2.x),  (double) std::max(v1.y, v2.y),  (double) std::max(v1.z, v2.z));
}

vec4::vec4()
{
    this->x = float(0);
    this->y = float(0);
    this->z = float(0);
    this->w = float(0);
}
vec4::vec4(const vec4& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
    this->w = float( v.w );
}
vec4::vec4(const uvec4& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
    this->w = float( v.w );
}
vec4::vec4(const ivec4& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
    this->w = float( v.w );
}
vec4::vec4(const dvec4& v)
{
    this->x = float( v.x );
    this->y = float( v.y );
    this->z = float( v.z );
    this->w = float( v.w );
}
/// Constructor
vec4::vec4( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_ )
{
    this->x = anyScalarToType<float>(x_);
    this->y = anyScalarToType<float>(y_);
    this->z = anyScalarToType<float>(z_);
    this->w = anyScalarToType<float>(w_);
}
vec4::vec4(const vec2& v, const AnyScalar& z_, const AnyScalar& w_) :
    vec4::vec4(v.x, v.y, z_, w_)
{}
vec4::vec4(const vec3& v, const AnyScalar& w_) :
    vec4::vec4(v.x, v.y, v.z, w_)
{}
vec4::vec4(const AnyScalar& v)
{
    this->x = anyScalarToType<float>(v);
    this->y = this->x;
    this->z = this->x;
    this->w = this->x;
}
float vec4::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float vec4::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec4::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
float& vec4::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void vec4::operator=(const vec4& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
    this->w = o.w;
}
void vec4::operator+=(const vec4& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    this->w += o.w;
}
void vec4::operator-=(const vec4& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
    this->w -= o.w;
}
void vec4::operator*=(const vec4& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
    this->w *= o.w;
}
void vec4::operator/=(const vec4& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
    this->w /= o.w;
}
    void vec4::operator*=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
    this->w *= tmp;
}

    void vec4::operator/=(const AnyScalar& s)
{
    float tmp = anyScalarToType<float>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
    this->w /= tmp;
}

vec4::operator std::string() const
{
    return std::string("vec4(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ',' + std::to_string(this->w) + ')' ;
}
unsigned vec4::size() const
{
    return 4;
}
vec2 vec4::xy() const
{
    return vec2( x, y );
}
vec3 vec4::xyz() const
{
    return vec3( x, y, z );
}
vec4 vec4::xyzw() const
{
    return vec4( x, y, z, w );
}
vec4 operator+(const vec4& arg1, const vec4& arg2)
{
    vec4 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    rv.w = arg1.w + arg2.w;
    return rv;
}
vec4 operator-(const vec4& arg1, const vec4& arg2)
{
    vec4 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    rv.w = arg1.w - arg2.w;
    return rv;
}
vec4 operator*(const vec4& arg1, const vec4& arg2)
{
    vec4 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    rv.w = arg1.w * arg2.w;
    return rv;
}
vec4 operator/(const vec4& arg1, const vec4& arg2)
{
    vec4 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    rv.w = arg1.w / arg2.w;
    return rv;
}
vec4 operator*( const vec4& v, float s)
{
    vec4 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    rv.w = v.w * (float)s;
    return rv;
}
vec4 operator*( float s, const vec4& v  )
{
     vec4 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    rv.w = (float)s * v.w ;
    return rv;
}
vec4 operator/( const vec4& v, float s)
{
    vec4 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    rv.w = v.w / (float)s;
    return rv;
}
vec4 operator*( const vec4& v, double s)
{
    vec4 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    rv.w = v.w * (float)s;
    return rv;
}
vec4 operator*( double s, const vec4& v  )
{
     vec4 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    rv.w = (float)s * v.w ;
    return rv;
}
vec4 operator/( const vec4& v, double s)
{
    vec4 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    rv.w = v.w / (float)s;
    return rv;
}
vec4 operator*( const vec4& v, std::int32_t s)
{
    vec4 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    rv.w = v.w * (float)s;
    return rv;
}
vec4 operator*( std::int32_t s, const vec4& v  )
{
     vec4 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    rv.w = (float)s * v.w ;
    return rv;
}
vec4 operator/( const vec4& v, std::int32_t s)
{
    vec4 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    rv.w = v.w / (float)s;
    return rv;
}
vec4 operator*( const vec4& v, std::uint32_t s)
{
    vec4 rv;
    rv.x = v.x * (float)s;
    rv.y = v.y * (float)s;
    rv.z = v.z * (float)s;
    rv.w = v.w * (float)s;
    return rv;
}
vec4 operator*( std::uint32_t s, const vec4& v  )
{
     vec4 rv;
    rv.x = (float)s * v.x ;
    rv.y = (float)s * v.y ;
    rv.z = (float)s * v.z ;
    rv.w = (float)s * v.w ;
    return rv;
}
vec4 operator/( const vec4& v, std::uint32_t s)
{
    vec4 rv;
    rv.x = v.x / (float)s;
    rv.y = v.y / (float)s;
    rv.z = v.z / (float)s;
    rv.w = v.w / (float)s;
    return rv;
}
bool operator<(const vec4& v1, const vec4& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    if(v1.w < v2.w)
        return true;
    if(v1.w > v2.w)
        return false;
    return false;   //v1==v2
}
bool operator>(const vec4& v1, const vec4& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    if(v1.w > v2.w)
        return true;
    if(v1.w < v2.w)
        return false;
    return false;   //v1==v2
}
bool operator<=(const vec4& v1, const vec4& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const vec4& v1, const vec4& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const vec4& v1, const vec4& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    if(v1.w != v2.w)
        return false;
    return true;
}
bool operator!=(const vec4& v1, const vec4& v2)
{
    return !(v1==v2);
}
vec4 operator-(const vec4& v)
{
    vec4 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    rv.w = -(v.w);
    return rv;
}
vec4 operator+(const vec4& v)
{
    return v;
}
float dot(const vec4& v1, const vec4& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z+v1.w * v2.w;
}
float length(const vec4& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const vec4& v)
{
    o << "vec4(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) + ',' + std::to_string(v.w) << ")" ;
    return o;
}
//no cross product for non-3d vec
vec4 min(const vec4& v1, const vec4& v2)
{
    return vec4( (float) std::min(v1.x, v2.x),  (float) std::min(v1.y, v2.y),  (float) std::min(v1.z, v2.z),  (float) std::min(v1.w, v2.w));
}
vec4 max(const vec4& v1, const vec4& v2)
{
    return vec4( (float) std::max(v1.x, v2.x),  (float) std::max(v1.y, v2.y),  (float) std::max(v1.z, v2.z),  (float) std::max(v1.w, v2.w));
}

uvec4::uvec4()
{
    this->x = std::uint32_t(0);
    this->y = std::uint32_t(0);
    this->z = std::uint32_t(0);
    this->w = std::uint32_t(0);
}
uvec4::uvec4(const vec4& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
    this->w = std::uint32_t( v.w );
}
uvec4::uvec4(const uvec4& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
    this->w = std::uint32_t( v.w );
}
uvec4::uvec4(const ivec4& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
    this->w = std::uint32_t( v.w );
}
uvec4::uvec4(const dvec4& v)
{
    this->x = std::uint32_t( v.x );
    this->y = std::uint32_t( v.y );
    this->z = std::uint32_t( v.z );
    this->w = std::uint32_t( v.w );
}
/// Constructor
uvec4::uvec4( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_ )
{
    this->x = anyScalarToType<std::uint32_t>(x_);
    this->y = anyScalarToType<std::uint32_t>(y_);
    this->z = anyScalarToType<std::uint32_t>(z_);
    this->w = anyScalarToType<std::uint32_t>(w_);
}
uvec4::uvec4(const uvec2& v, const AnyScalar& z_, const AnyScalar& w_) :
    uvec4::uvec4(v.x, v.y, z_, w_)
{}
uvec4::uvec4(const uvec3& v, const AnyScalar& w_) :
    uvec4::uvec4(v.x, v.y, v.z, w_)
{}
uvec4::uvec4(const AnyScalar& v)
{
    this->x = anyScalarToType<std::uint32_t>(v);
    this->y = this->x;
    this->z = this->x;
    this->w = this->x;
}
std::uint32_t uvec4::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t uvec4::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec4::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::uint32_t& uvec4::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void uvec4::operator=(const uvec4& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
    this->w = o.w;
}
void uvec4::operator+=(const uvec4& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    this->w += o.w;
}
void uvec4::operator-=(const uvec4& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
    this->w -= o.w;
}
void uvec4::operator*=(const uvec4& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
    this->w *= o.w;
}
void uvec4::operator/=(const uvec4& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
    this->w /= o.w;
}
    void uvec4::operator*=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
    this->w *= tmp;
}

    void uvec4::operator/=(const AnyScalar& s)
{
    std::uint32_t tmp = anyScalarToType<std::uint32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
    this->w /= tmp;
}

uvec4::operator std::string() const
{
    return std::string("vec4(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ',' + std::to_string(this->w) + ')' ;
}
unsigned uvec4::size() const
{
    return 4;
}
uvec2 uvec4::xy() const
{
    return uvec2( x, y );
}
uvec3 uvec4::xyz() const
{
    return uvec3( x, y, z );
}
uvec4 uvec4::xyzw() const
{
    return uvec4( x, y, z, w );
}
uvec4 operator+(const uvec4& arg1, const uvec4& arg2)
{
    uvec4 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    rv.w = arg1.w + arg2.w;
    return rv;
}
uvec4 operator-(const uvec4& arg1, const uvec4& arg2)
{
    uvec4 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    rv.w = arg1.w - arg2.w;
    return rv;
}
uvec4 operator*(const uvec4& arg1, const uvec4& arg2)
{
    uvec4 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    rv.w = arg1.w * arg2.w;
    return rv;
}
uvec4 operator/(const uvec4& arg1, const uvec4& arg2)
{
    uvec4 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    rv.w = arg1.w / arg2.w;
    return rv;
}
uvec4 operator*( const uvec4& v, float s)
{
    uvec4 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    rv.w = v.w * (std::uint32_t)s;
    return rv;
}
uvec4 operator*( float s, const uvec4& v  )
{
     uvec4 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    rv.w = (std::uint32_t)s * v.w ;
    return rv;
}
uvec4 operator/( const uvec4& v, float s)
{
    uvec4 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    rv.w = v.w / (std::uint32_t)s;
    return rv;
}
uvec4 operator*( const uvec4& v, double s)
{
    uvec4 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    rv.w = v.w * (std::uint32_t)s;
    return rv;
}
uvec4 operator*( double s, const uvec4& v  )
{
     uvec4 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    rv.w = (std::uint32_t)s * v.w ;
    return rv;
}
uvec4 operator/( const uvec4& v, double s)
{
    uvec4 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    rv.w = v.w / (std::uint32_t)s;
    return rv;
}
uvec4 operator*( const uvec4& v, std::int32_t s)
{
    uvec4 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    rv.w = v.w * (std::uint32_t)s;
    return rv;
}
uvec4 operator*( std::int32_t s, const uvec4& v  )
{
     uvec4 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    rv.w = (std::uint32_t)s * v.w ;
    return rv;
}
uvec4 operator/( const uvec4& v, std::int32_t s)
{
    uvec4 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    rv.w = v.w / (std::uint32_t)s;
    return rv;
}
uvec4 operator*( const uvec4& v, std::uint32_t s)
{
    uvec4 rv;
    rv.x = v.x * (std::uint32_t)s;
    rv.y = v.y * (std::uint32_t)s;
    rv.z = v.z * (std::uint32_t)s;
    rv.w = v.w * (std::uint32_t)s;
    return rv;
}
uvec4 operator*( std::uint32_t s, const uvec4& v  )
{
     uvec4 rv;
    rv.x = (std::uint32_t)s * v.x ;
    rv.y = (std::uint32_t)s * v.y ;
    rv.z = (std::uint32_t)s * v.z ;
    rv.w = (std::uint32_t)s * v.w ;
    return rv;
}
uvec4 operator/( const uvec4& v, std::uint32_t s)
{
    uvec4 rv;
    rv.x = v.x / (std::uint32_t)s;
    rv.y = v.y / (std::uint32_t)s;
    rv.z = v.z / (std::uint32_t)s;
    rv.w = v.w / (std::uint32_t)s;
    return rv;
}
bool operator<(const uvec4& v1, const uvec4& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    if(v1.w < v2.w)
        return true;
    if(v1.w > v2.w)
        return false;
    return false;   //v1==v2
}
bool operator>(const uvec4& v1, const uvec4& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    if(v1.w > v2.w)
        return true;
    if(v1.w < v2.w)
        return false;
    return false;   //v1==v2
}
bool operator<=(const uvec4& v1, const uvec4& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const uvec4& v1, const uvec4& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const uvec4& v1, const uvec4& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    if(v1.w != v2.w)
        return false;
    return true;
}
bool operator!=(const uvec4& v1, const uvec4& v2)
{
    return !(v1==v2);
}
//no negation for unsigned vec type
uvec4 operator+(const uvec4& v)
{
    return v;
}
std::uint32_t dot(const uvec4& v1, const uvec4& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z+v1.w * v2.w;
}
float length(const uvec4& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const uvec4& v)
{
    o << "uvec4(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) + ',' + std::to_string(v.w) << ")" ;
    return o;
}
//no cross product for non-3d vec
uvec4 min(const uvec4& v1, const uvec4& v2)
{
    return uvec4( (std::uint32_t) std::min(v1.x, v2.x),  (std::uint32_t) std::min(v1.y, v2.y),  (std::uint32_t) std::min(v1.z, v2.z),  (std::uint32_t) std::min(v1.w, v2.w));
}
uvec4 max(const uvec4& v1, const uvec4& v2)
{
    return uvec4( (std::uint32_t) std::max(v1.x, v2.x),  (std::uint32_t) std::max(v1.y, v2.y),  (std::uint32_t) std::max(v1.z, v2.z),  (std::uint32_t) std::max(v1.w, v2.w));
}

ivec4::ivec4()
{
    this->x = std::int32_t(0);
    this->y = std::int32_t(0);
    this->z = std::int32_t(0);
    this->w = std::int32_t(0);
}
ivec4::ivec4(const vec4& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
    this->w = std::int32_t( v.w );
}
ivec4::ivec4(const uvec4& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
    this->w = std::int32_t( v.w );
}
ivec4::ivec4(const ivec4& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
    this->w = std::int32_t( v.w );
}
ivec4::ivec4(const dvec4& v)
{
    this->x = std::int32_t( v.x );
    this->y = std::int32_t( v.y );
    this->z = std::int32_t( v.z );
    this->w = std::int32_t( v.w );
}
/// Constructor
ivec4::ivec4( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_ )
{
    this->x = anyScalarToType<std::int32_t>(x_);
    this->y = anyScalarToType<std::int32_t>(y_);
    this->z = anyScalarToType<std::int32_t>(z_);
    this->w = anyScalarToType<std::int32_t>(w_);
}
ivec4::ivec4(const ivec2& v, const AnyScalar& z_, const AnyScalar& w_) :
    ivec4::ivec4(v.x, v.y, z_, w_)
{}
ivec4::ivec4(const ivec3& v, const AnyScalar& w_) :
    ivec4::ivec4(v.x, v.y, v.z, w_)
{}
ivec4::ivec4(const AnyScalar& v)
{
    this->x = anyScalarToType<std::int32_t>(v);
    this->y = this->x;
    this->z = this->x;
    this->w = this->x;
}
std::int32_t ivec4::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t ivec4::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec4::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
std::int32_t& ivec4::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void ivec4::operator=(const ivec4& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
    this->w = o.w;
}
void ivec4::operator+=(const ivec4& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    this->w += o.w;
}
void ivec4::operator-=(const ivec4& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
    this->w -= o.w;
}
void ivec4::operator*=(const ivec4& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
    this->w *= o.w;
}
void ivec4::operator/=(const ivec4& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
    this->w /= o.w;
}
    void ivec4::operator*=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
    this->w *= tmp;
}

    void ivec4::operator/=(const AnyScalar& s)
{
    std::int32_t tmp = anyScalarToType<std::int32_t>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
    this->w /= tmp;
}

ivec4::operator std::string() const
{
    return std::string("vec4(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ',' + std::to_string(this->w) + ')' ;
}
unsigned ivec4::size() const
{
    return 4;
}
ivec2 ivec4::xy() const
{
    return ivec2( x, y );
}
ivec3 ivec4::xyz() const
{
    return ivec3( x, y, z );
}
ivec4 ivec4::xyzw() const
{
    return ivec4( x, y, z, w );
}
ivec4 operator+(const ivec4& arg1, const ivec4& arg2)
{
    ivec4 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    rv.w = arg1.w + arg2.w;
    return rv;
}
ivec4 operator-(const ivec4& arg1, const ivec4& arg2)
{
    ivec4 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    rv.w = arg1.w - arg2.w;
    return rv;
}
ivec4 operator*(const ivec4& arg1, const ivec4& arg2)
{
    ivec4 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    rv.w = arg1.w * arg2.w;
    return rv;
}
ivec4 operator/(const ivec4& arg1, const ivec4& arg2)
{
    ivec4 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    rv.w = arg1.w / arg2.w;
    return rv;
}
ivec4 operator*( const ivec4& v, float s)
{
    ivec4 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    rv.w = v.w * (std::int32_t)s;
    return rv;
}
ivec4 operator*( float s, const ivec4& v  )
{
     ivec4 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    rv.w = (std::int32_t)s * v.w ;
    return rv;
}
ivec4 operator/( const ivec4& v, float s)
{
    ivec4 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    rv.w = v.w / (std::int32_t)s;
    return rv;
}
ivec4 operator*( const ivec4& v, double s)
{
    ivec4 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    rv.w = v.w * (std::int32_t)s;
    return rv;
}
ivec4 operator*( double s, const ivec4& v  )
{
     ivec4 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    rv.w = (std::int32_t)s * v.w ;
    return rv;
}
ivec4 operator/( const ivec4& v, double s)
{
    ivec4 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    rv.w = v.w / (std::int32_t)s;
    return rv;
}
ivec4 operator*( const ivec4& v, std::int32_t s)
{
    ivec4 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    rv.w = v.w * (std::int32_t)s;
    return rv;
}
ivec4 operator*( std::int32_t s, const ivec4& v  )
{
     ivec4 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    rv.w = (std::int32_t)s * v.w ;
    return rv;
}
ivec4 operator/( const ivec4& v, std::int32_t s)
{
    ivec4 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    rv.w = v.w / (std::int32_t)s;
    return rv;
}
ivec4 operator*( const ivec4& v, std::uint32_t s)
{
    ivec4 rv;
    rv.x = v.x * (std::int32_t)s;
    rv.y = v.y * (std::int32_t)s;
    rv.z = v.z * (std::int32_t)s;
    rv.w = v.w * (std::int32_t)s;
    return rv;
}
ivec4 operator*( std::uint32_t s, const ivec4& v  )
{
     ivec4 rv;
    rv.x = (std::int32_t)s * v.x ;
    rv.y = (std::int32_t)s * v.y ;
    rv.z = (std::int32_t)s * v.z ;
    rv.w = (std::int32_t)s * v.w ;
    return rv;
}
ivec4 operator/( const ivec4& v, std::uint32_t s)
{
    ivec4 rv;
    rv.x = v.x / (std::int32_t)s;
    rv.y = v.y / (std::int32_t)s;
    rv.z = v.z / (std::int32_t)s;
    rv.w = v.w / (std::int32_t)s;
    return rv;
}
bool operator<(const ivec4& v1, const ivec4& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    if(v1.w < v2.w)
        return true;
    if(v1.w > v2.w)
        return false;
    return false;   //v1==v2
}
bool operator>(const ivec4& v1, const ivec4& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    if(v1.w > v2.w)
        return true;
    if(v1.w < v2.w)
        return false;
    return false;   //v1==v2
}
bool operator<=(const ivec4& v1, const ivec4& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const ivec4& v1, const ivec4& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const ivec4& v1, const ivec4& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    if(v1.w != v2.w)
        return false;
    return true;
}
bool operator!=(const ivec4& v1, const ivec4& v2)
{
    return !(v1==v2);
}
ivec4 operator-(const ivec4& v)
{
    ivec4 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    rv.w = -(v.w);
    return rv;
}
ivec4 operator+(const ivec4& v)
{
    return v;
}
std::int32_t dot(const ivec4& v1, const ivec4& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z+v1.w * v2.w;
}
float length(const ivec4& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const ivec4& v)
{
    o << "ivec4(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) + ',' + std::to_string(v.w) << ")" ;
    return o;
}
//no cross product for non-3d vec
ivec4 min(const ivec4& v1, const ivec4& v2)
{
    return ivec4( (std::int32_t) std::min(v1.x, v2.x),  (std::int32_t) std::min(v1.y, v2.y),  (std::int32_t) std::min(v1.z, v2.z),  (std::int32_t) std::min(v1.w, v2.w));
}
ivec4 max(const ivec4& v1, const ivec4& v2)
{
    return ivec4( (std::int32_t) std::max(v1.x, v2.x),  (std::int32_t) std::max(v1.y, v2.y),  (std::int32_t) std::max(v1.z, v2.z),  (std::int32_t) std::max(v1.w, v2.w));
}

dvec4::dvec4()
{
    this->x = double(0);
    this->y = double(0);
    this->z = double(0);
    this->w = double(0);
}
dvec4::dvec4(const vec4& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
    this->w = double( v.w );
}
dvec4::dvec4(const uvec4& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
    this->w = double( v.w );
}
dvec4::dvec4(const ivec4& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
    this->w = double( v.w );
}
dvec4::dvec4(const dvec4& v)
{
    this->x = double( v.x );
    this->y = double( v.y );
    this->z = double( v.z );
    this->w = double( v.w );
}
/// Constructor
dvec4::dvec4( const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_ )
{
    this->x = anyScalarToType<double>(x_);
    this->y = anyScalarToType<double>(y_);
    this->z = anyScalarToType<double>(z_);
    this->w = anyScalarToType<double>(w_);
}
dvec4::dvec4(const dvec2& v, const AnyScalar& z_, const AnyScalar& w_) :
    dvec4::dvec4(v.x, v.y, z_, w_)
{}
dvec4::dvec4(const dvec3& v, const AnyScalar& w_) :
    dvec4::dvec4(v.x, v.y, v.z, w_)
{}
dvec4::dvec4(const AnyScalar& v)
{
    this->x = anyScalarToType<double>(v);
    this->y = this->x;
    this->z = this->x;
    this->w = this->x;
}
double dvec4::operator[](unsigned idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double dvec4::operator[](int idx) const
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec4::operator[](unsigned idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
double& dvec4::operator[](int idx)
{
    switch(idx){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::runtime_error("Bad index ("+std::to_string(idx)+")");
    }
}
void dvec4::operator=(const dvec4& o)
{
    this->x = o.x;
    this->y = o.y;
    this->z = o.z;
    this->w = o.w;
}
void dvec4::operator+=(const dvec4& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    this->w += o.w;
}
void dvec4::operator-=(const dvec4& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
    this->w -= o.w;
}
void dvec4::operator*=(const dvec4& o)
{
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
    this->w *= o.w;
}
void dvec4::operator/=(const dvec4& o)
{
    this->x /= o.x;
    this->y /= o.y;
    this->z /= o.z;
    this->w /= o.w;
}
    void dvec4::operator*=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x *= tmp;
    this->y *= tmp;
    this->z *= tmp;
    this->w *= tmp;
}

    void dvec4::operator/=(const AnyScalar& s)
{
    double tmp = anyScalarToType<double>(s);
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
    this->w /= tmp;
}

dvec4::operator std::string() const
{
    return std::string("vec4(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ',' + std::to_string(this->z) + ',' + std::to_string(this->w) + ')' ;
}
unsigned dvec4::size() const
{
    return 4;
}
dvec2 dvec4::xy() const
{
    return dvec2( x, y );
}
dvec3 dvec4::xyz() const
{
    return dvec3( x, y, z );
}
dvec4 dvec4::xyzw() const
{
    return dvec4( x, y, z, w );
}
dvec4 operator+(const dvec4& arg1, const dvec4& arg2)
{
    dvec4 rv;
    rv.x = arg1.x + arg2.x;
    rv.y = arg1.y + arg2.y;
    rv.z = arg1.z + arg2.z;
    rv.w = arg1.w + arg2.w;
    return rv;
}
dvec4 operator-(const dvec4& arg1, const dvec4& arg2)
{
    dvec4 rv;
    rv.x = arg1.x - arg2.x;
    rv.y = arg1.y - arg2.y;
    rv.z = arg1.z - arg2.z;
    rv.w = arg1.w - arg2.w;
    return rv;
}
dvec4 operator*(const dvec4& arg1, const dvec4& arg2)
{
    dvec4 rv;
    rv.x = arg1.x * arg2.x;
    rv.y = arg1.y * arg2.y;
    rv.z = arg1.z * arg2.z;
    rv.w = arg1.w * arg2.w;
    return rv;
}
dvec4 operator/(const dvec4& arg1, const dvec4& arg2)
{
    dvec4 rv;
    rv.x = arg1.x / arg2.x;
    rv.y = arg1.y / arg2.y;
    rv.z = arg1.z / arg2.z;
    rv.w = arg1.w / arg2.w;
    return rv;
}
dvec4 operator*( const dvec4& v, float s)
{
    dvec4 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    rv.w = v.w * (double)s;
    return rv;
}
dvec4 operator*( float s, const dvec4& v  )
{
     dvec4 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    rv.w = (double)s * v.w ;
    return rv;
}
dvec4 operator/( const dvec4& v, float s)
{
    dvec4 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    rv.w = v.w / (double)s;
    return rv;
}
dvec4 operator*( const dvec4& v, double s)
{
    dvec4 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    rv.w = v.w * (double)s;
    return rv;
}
dvec4 operator*( double s, const dvec4& v  )
{
     dvec4 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    rv.w = (double)s * v.w ;
    return rv;
}
dvec4 operator/( const dvec4& v, double s)
{
    dvec4 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    rv.w = v.w / (double)s;
    return rv;
}
dvec4 operator*( const dvec4& v, std::int32_t s)
{
    dvec4 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    rv.w = v.w * (double)s;
    return rv;
}
dvec4 operator*( std::int32_t s, const dvec4& v  )
{
     dvec4 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    rv.w = (double)s * v.w ;
    return rv;
}
dvec4 operator/( const dvec4& v, std::int32_t s)
{
    dvec4 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    rv.w = v.w / (double)s;
    return rv;
}
dvec4 operator*( const dvec4& v, std::uint32_t s)
{
    dvec4 rv;
    rv.x = v.x * (double)s;
    rv.y = v.y * (double)s;
    rv.z = v.z * (double)s;
    rv.w = v.w * (double)s;
    return rv;
}
dvec4 operator*( std::uint32_t s, const dvec4& v  )
{
     dvec4 rv;
    rv.x = (double)s * v.x ;
    rv.y = (double)s * v.y ;
    rv.z = (double)s * v.z ;
    rv.w = (double)s * v.w ;
    return rv;
}
dvec4 operator/( const dvec4& v, std::uint32_t s)
{
    dvec4 rv;
    rv.x = v.x / (double)s;
    rv.y = v.y / (double)s;
    rv.z = v.z / (double)s;
    rv.w = v.w / (double)s;
    return rv;
}
bool operator<(const dvec4& v1, const dvec4& v2)
{
    if(v1.x < v2.x)
        return true;
    if(v1.x > v2.x)
        return false;
    if(v1.y < v2.y)
        return true;
    if(v1.y > v2.y)
        return false;
    if(v1.z < v2.z)
        return true;
    if(v1.z > v2.z)
        return false;
    if(v1.w < v2.w)
        return true;
    if(v1.w > v2.w)
        return false;
    return false;   //v1==v2
}
bool operator>(const dvec4& v1, const dvec4& v2)
{
    if(v1.x > v2.x)
        return true;
    if(v1.x < v2.x)
        return false;
    if(v1.y > v2.y)
        return true;
    if(v1.y < v2.y)
        return false;
    if(v1.z > v2.z)
        return true;
    if(v1.z < v2.z)
        return false;
    if(v1.w > v2.w)
        return true;
    if(v1.w < v2.w)
        return false;
    return false;   //v1==v2
}
bool operator<=(const dvec4& v1, const dvec4& v2)
{
    return (v1==v2) || (v1 < v2);
}
bool operator>=(const dvec4& v1, const dvec4& v2)
{
    return (v1==v2) || (v1 > v2);
}
bool operator==(const dvec4& v1, const dvec4& v2)
{
    if(v1.x != v2.x)
        return false;
    if(v1.y != v2.y)
        return false;
    if(v1.z != v2.z)
        return false;
    if(v1.w != v2.w)
        return false;
    return true;
}
bool operator!=(const dvec4& v1, const dvec4& v2)
{
    return !(v1==v2);
}
dvec4 operator-(const dvec4& v)
{
    dvec4 rv;
    rv.x = -(v.x);
    rv.y = -(v.y);
    rv.z = -(v.z);
    rv.w = -(v.w);
    return rv;
}
dvec4 operator+(const dvec4& v)
{
    return v;
}
double dot(const dvec4& v1, const dvec4& v2)
{
    return v1.x * v2.x+v1.y * v2.y+v1.z * v2.z+v1.w * v2.w;
}
float length(const dvec4& v)
{
    return (float)std::sqrt(dot(v,v));
}
std::ostream& operator<<(std::ostream& o, const dvec4& v)
{
    o << "dvec4(" << std::to_string(v.x) + ',' + std::to_string(v.y) + ',' + std::to_string(v.z) + ',' + std::to_string(v.w) << ")" ;
    return o;
}
//no cross product for non-3d vec
dvec4 min(const dvec4& v1, const dvec4& v2)
{
    return dvec4( (double) std::min(v1.x, v2.x),  (double) std::min(v1.y, v2.y),  (double) std::min(v1.z, v2.z),  (double) std::min(v1.w, v2.w));
}
dvec4 max(const dvec4& v1, const dvec4& v2)
{
    return dvec4( (double) std::max(v1.x, v2.x),  (double) std::max(v1.y, v2.y),  (double) std::max(v1.z, v2.z),  (double) std::max(v1.w, v2.w));
}

mat2:: RowProxy::RowProxy( mat2* m_, int r_) : m(m_), r(r_) {}
mat2::CRowProxy::CRowProxy(const mat2* m_, int r_) : m(m_), r(r_) {}
mat2:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat2::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat2::RowProxy mat2::operator[](unsigned idx)
{
    if( idx >= 2 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
mat2::CRowProxy mat2::operator[](unsigned idx) const
{
    if( idx >= 2 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
float& mat2::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
float mat2::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
mat2 mat2::identity()
{
    return mat2(
        1.0f, 0.0f,
        0.0f, 1.0f
    );
}
mat2::mat2()
{
    this->_M[0][0] = (float) 0;
    this->_M[0][1] = (float) 0;
    this->_M[1][0] = (float) 0;
    this->_M[1][1] = (float) 0;
}
mat2::mat2(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m10, const AnyScalar& m11)
{
    this->_M[0][0] = anyScalarToType<float>(m00);
    this->_M[0][1] = anyScalarToType<float>(m01);
    this->_M[1][0] = anyScalarToType<float>(m10);
    this->_M[1][1] = anyScalarToType<float>(m11);
}
float mat2::operator()(unsigned r, unsigned c) const
{
    if(r < 2 && c < 2 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
float& mat2::operator()(unsigned r, unsigned c) 
{
    if(r < 2 && c < 2 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<float> mat2::data() const
{    std::vector<float> rv(4);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[1][0];
    rv[3] = this->_M[1][1];
    return rv;
}
mat2::operator std::string() const
{    std::ostringstream o;
    o << "mat2(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << std::endl;
    return o.str();
}
//matrix binary operations
mat2 operator+(const mat2& m1, const mat2& m2)
{
    mat2 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    return rv;
}
mat2 operator-(const mat2& m1, const mat2& m2)
{
    mat2 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    return rv;
}
//matrix equality
bool operator==(const mat2& m1, const mat2& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const mat2& m1, const mat2& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
mat2 operator*(const mat2& m1, const mat2& m2)
{
    mat2 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    return rv;
}
//matrix-vector multiply
vec2 operator*(const mat2& m, const vec2& v)
{
    vec2 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    return rv;
}
//vector-matrix multiply
vec2 operator*(const vec2& v, const mat2& m)
{
    vec2 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    return rv;
}
//matrix-scalar operations
mat2 operator*(const mat2& m, float s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    return rv;
}
mat2 operator*(const mat2& m, double s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    return rv;
}
mat2 operator*(const mat2& m, std::int32_t s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    return rv;
}
mat2 operator*(const mat2& m, std::uint32_t s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    return rv;
}
mat2 operator/(const mat2& m, float s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    return rv;
}
mat2 operator/(const mat2& m, double s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    return rv;
}
mat2 operator/(const mat2& m, std::int32_t s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    return rv;
}
mat2 operator/(const mat2& m, std::uint32_t s)
{
    mat2 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    return rv;
}
//scalar-matrix operations
mat2 operator*(float s, const mat2& m)
{
    mat2 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    return rv;
}
mat2 operator*(double s, const mat2& m)
{
    mat2 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    return rv;
}
mat2 operator*(std::int32_t s, const mat2& m)
{
    mat2 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    return rv;
}
mat2 operator*(std::uint32_t s, const mat2& m)
{
    mat2 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    return rv;
}
//unary matrix operations
mat2 operator+(const mat2& m)
{
    return (float(+1)) * m;
}
mat2 operator-(const mat2& m)
{
    return (float(-1)) * m;
}
//matrix transpose
mat2 transpose(const mat2& m)
{
    mat2 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const mat2& m)
{    o << "mat2(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << std::endl;
    return o;
}

dmat2:: RowProxy::RowProxy( dmat2* m_, int r_) : m(m_), r(r_) {}
dmat2::CRowProxy::CRowProxy(const dmat2* m_, int r_) : m(m_), r(r_) {}
dmat2:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat2::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat2::RowProxy dmat2::operator[](unsigned idx)
{
    if( idx >= 2 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
dmat2::CRowProxy dmat2::operator[](unsigned idx) const
{
    if( idx >= 2 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
double& dmat2::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
double dmat2::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
dmat2 dmat2::identity()
{
    return dmat2(
        1.0f, 0.0f,
        0.0f, 1.0f
    );
}
dmat2::dmat2()
{
    this->_M[0][0] = (double) 0;
    this->_M[0][1] = (double) 0;
    this->_M[1][0] = (double) 0;
    this->_M[1][1] = (double) 0;
}
dmat2::dmat2(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m10, const AnyScalar& m11)
{
    this->_M[0][0] = anyScalarToType<double>(m00);
    this->_M[0][1] = anyScalarToType<double>(m01);
    this->_M[1][0] = anyScalarToType<double>(m10);
    this->_M[1][1] = anyScalarToType<double>(m11);
}
double dmat2::operator()(unsigned r, unsigned c) const
{
    if(r < 2 && c < 2 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
double& dmat2::operator()(unsigned r, unsigned c) 
{
    if(r < 2 && c < 2 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<double> dmat2::data() const
{    std::vector<double> rv(4);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[1][0];
    rv[3] = this->_M[1][1];
    return rv;
}
dmat2::operator std::string() const
{    std::ostringstream o;
    o << "dmat2(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << std::endl;
    return o.str();
}
//matrix binary operations
dmat2 operator+(const dmat2& m1, const dmat2& m2)
{
    dmat2 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    return rv;
}
dmat2 operator-(const dmat2& m1, const dmat2& m2)
{
    dmat2 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    return rv;
}
//matrix equality
bool operator==(const dmat2& m1, const dmat2& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const dmat2& m1, const dmat2& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
dmat2 operator*(const dmat2& m1, const dmat2& m2)
{
    dmat2 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    return rv;
}
//matrix-vector multiply
dvec2 operator*(const dmat2& m, const dvec2& v)
{
    dvec2 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    return rv;
}
//vector-matrix multiply
dvec2 operator*(const dvec2& v, const dmat2& m)
{
    dvec2 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    return rv;
}
//matrix-scalar operations
dmat2 operator*(const dmat2& m, float s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    return rv;
}
dmat2 operator*(const dmat2& m, double s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    return rv;
}
dmat2 operator*(const dmat2& m, std::int32_t s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    return rv;
}
dmat2 operator*(const dmat2& m, std::uint32_t s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    return rv;
}
dmat2 operator/(const dmat2& m, float s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    return rv;
}
dmat2 operator/(const dmat2& m, double s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    return rv;
}
dmat2 operator/(const dmat2& m, std::int32_t s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    return rv;
}
dmat2 operator/(const dmat2& m, std::uint32_t s)
{
    dmat2 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    return rv;
}
//scalar-matrix operations
dmat2 operator*(float s, const dmat2& m)
{
    dmat2 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    return rv;
}
dmat2 operator*(double s, const dmat2& m)
{
    dmat2 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    return rv;
}
dmat2 operator*(std::int32_t s, const dmat2& m)
{
    dmat2 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    return rv;
}
dmat2 operator*(std::uint32_t s, const dmat2& m)
{
    dmat2 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    return rv;
}
//unary matrix operations
dmat2 operator+(const dmat2& m)
{
    return (double(+1)) * m;
}
dmat2 operator-(const dmat2& m)
{
    return (double(-1)) * m;
}
//matrix transpose
dmat2 transpose(const dmat2& m)
{
    dmat2 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const dmat2& m)
{    o << "dmat2(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << std::endl;
    return o;
}

mat3:: RowProxy::RowProxy( mat3* m_, int r_) : m(m_), r(r_) {}
mat3::CRowProxy::CRowProxy(const mat3* m_, int r_) : m(m_), r(r_) {}
mat3:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat3::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat3::RowProxy mat3::operator[](unsigned idx)
{
    if( idx >= 3 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
mat3::CRowProxy mat3::operator[](unsigned idx) const
{
    if( idx >= 3 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
float& mat3::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
float mat3::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
mat3 mat3::identity()
{
    return mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}
mat3::mat3()
{
    this->_M[0][0] = (float) 0;
    this->_M[0][1] = (float) 0;
    this->_M[0][2] = (float) 0;
    this->_M[1][0] = (float) 0;
    this->_M[1][1] = (float) 0;
    this->_M[1][2] = (float) 0;
    this->_M[2][0] = (float) 0;
    this->_M[2][1] = (float) 0;
    this->_M[2][2] = (float) 0;
}
mat3::mat3(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22)
{
    this->_M[0][0] = anyScalarToType<float>(m00);
    this->_M[0][1] = anyScalarToType<float>(m01);
    this->_M[0][2] = anyScalarToType<float>(m02);
    this->_M[1][0] = anyScalarToType<float>(m10);
    this->_M[1][1] = anyScalarToType<float>(m11);
    this->_M[1][2] = anyScalarToType<float>(m12);
    this->_M[2][0] = anyScalarToType<float>(m20);
    this->_M[2][1] = anyScalarToType<float>(m21);
    this->_M[2][2] = anyScalarToType<float>(m22);
}
float mat3::operator()(unsigned r, unsigned c) const
{
    if(r < 3 && c < 3 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
float& mat3::operator()(unsigned r, unsigned c) 
{
    if(r < 3 && c < 3 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<float> mat3::data() const
{    std::vector<float> rv(9);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[0][2];
    rv[3] = this->_M[1][0];
    rv[4] = this->_M[1][1];
    rv[5] = this->_M[1][2];
    rv[6] = this->_M[2][0];
    rv[7] = this->_M[2][1];
    rv[8] = this->_M[2][2];
    return rv;
}
mat3::operator std::string() const
{    std::ostringstream o;
    o << "mat3(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << ' ';
    o << this->_M[0][2] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << ' ';
    o << this->_M[1][2] << std::endl;
    o << this->_M[2][0] << ' ';
    o << this->_M[2][1] << ' ';
    o << this->_M[2][2] << std::endl;
    return o.str();
}
//matrix binary operations
mat3 operator+(const mat3& m1, const mat3& m2)
{
    mat3 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] + m2._M[0][2];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] + m2._M[1][2];
    rv._M[2][0] = m1._M[2][0] + m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] + m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] + m2._M[2][2];
    return rv;
}
mat3 operator-(const mat3& m1, const mat3& m2)
{
    mat3 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] - m2._M[0][2];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] - m2._M[1][2];
    rv._M[2][0] = m1._M[2][0] - m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] - m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] - m2._M[2][2];
    return rv;
}
//matrix equality
bool operator==(const mat3& m1, const mat3& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[0][2] != m2._M[0][2] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    if(m1._M[1][2] != m2._M[1][2] ) return false;
    if(m1._M[2][0] != m2._M[2][0] ) return false;
    if(m1._M[2][1] != m2._M[2][1] ) return false;
    if(m1._M[2][2] != m2._M[2][2] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const mat3& m1, const mat3& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
mat3 operator*(const mat3& m1, const mat3& m2)
{
    mat3 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][0] += m1._M[0][2] * m2._M[2][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[0][1] += m1._M[0][2] * m2._M[2][1];
    rv._M[0][2] += m1._M[0][0] * m2._M[0][2];
    rv._M[0][2] += m1._M[0][1] * m2._M[1][2];
    rv._M[0][2] += m1._M[0][2] * m2._M[2][2];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][0] += m1._M[1][2] * m2._M[2][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    rv._M[1][1] += m1._M[1][2] * m2._M[2][1];
    rv._M[1][2] += m1._M[1][0] * m2._M[0][2];
    rv._M[1][2] += m1._M[1][1] * m2._M[1][2];
    rv._M[1][2] += m1._M[1][2] * m2._M[2][2];
    rv._M[2][0] += m1._M[2][0] * m2._M[0][0];
    rv._M[2][0] += m1._M[2][1] * m2._M[1][0];
    rv._M[2][0] += m1._M[2][2] * m2._M[2][0];
    rv._M[2][1] += m1._M[2][0] * m2._M[0][1];
    rv._M[2][1] += m1._M[2][1] * m2._M[1][1];
    rv._M[2][1] += m1._M[2][2] * m2._M[2][1];
    rv._M[2][2] += m1._M[2][0] * m2._M[0][2];
    rv._M[2][2] += m1._M[2][1] * m2._M[1][2];
    rv._M[2][2] += m1._M[2][2] * m2._M[2][2];
    return rv;
}
//matrix-vector multiply
vec3 operator*(const mat3& m, const vec3& v)
{
    vec3 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.x += m._M[0][2] * v.z;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    rv.y += m._M[1][2] * v.z;
    rv.z += m._M[2][0] * v.x;
    rv.z += m._M[2][1] * v.y;
    rv.z += m._M[2][2] * v.z;
    return rv;
}
//vector-matrix multiply
vec3 operator*(const vec3& v, const mat3& m)
{
    vec3 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.x += v.z * m._M[2][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    rv.y += v.z * m._M[2][1];
    rv.z += v.x * m._M[0][2];
    rv.z += v.y * m._M[1][2];
    rv.z += v.z * m._M[2][2];
    return rv;
}
//matrix-scalar operations
mat3 operator*(const mat3& m, float s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    return rv;
}
mat3 operator*(const mat3& m, double s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    return rv;
}
mat3 operator*(const mat3& m, std::int32_t s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    return rv;
}
mat3 operator*(const mat3& m, std::uint32_t s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    return rv;
}
mat3 operator/(const mat3& m, float s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    return rv;
}
mat3 operator/(const mat3& m, double s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    return rv;
}
mat3 operator/(const mat3& m, std::int32_t s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    return rv;
}
mat3 operator/(const mat3& m, std::uint32_t s)
{
    mat3 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    return rv;
}
//scalar-matrix operations
mat3 operator*(float s, const mat3& m)
{
    mat3 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    return rv;
}
mat3 operator*(double s, const mat3& m)
{
    mat3 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    return rv;
}
mat3 operator*(std::int32_t s, const mat3& m)
{
    mat3 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    return rv;
}
mat3 operator*(std::uint32_t s, const mat3& m)
{
    mat3 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    return rv;
}
//unary matrix operations
mat3 operator+(const mat3& m)
{
    return (float(+1)) * m;
}
mat3 operator-(const mat3& m)
{
    return (float(-1)) * m;
}
//matrix transpose
mat3 transpose(const mat3& m)
{
    mat3 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[0][2] = m._M[2][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    rv._M[1][2] = m._M[2][1];
    rv._M[2][0] = m._M[0][2];
    rv._M[2][1] = m._M[1][2];
    rv._M[2][2] = m._M[2][2];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const mat3& m)
{    o << "mat3(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << ' ';
    o << m._M[0][2] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << ' ';
    o << m._M[1][2] << std::endl;
    o << m._M[2][0] << ' ';
    o << m._M[2][1] << ' ';
    o << m._M[2][2] << std::endl;
    return o;
}

dmat3:: RowProxy::RowProxy( dmat3* m_, int r_) : m(m_), r(r_) {}
dmat3::CRowProxy::CRowProxy(const dmat3* m_, int r_) : m(m_), r(r_) {}
dmat3:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat3::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat3::RowProxy dmat3::operator[](unsigned idx)
{
    if( idx >= 3 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
dmat3::CRowProxy dmat3::operator[](unsigned idx) const
{
    if( idx >= 3 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
double& dmat3::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
double dmat3::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
dmat3 dmat3::identity()
{
    return dmat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}
dmat3::dmat3()
{
    this->_M[0][0] = (double) 0;
    this->_M[0][1] = (double) 0;
    this->_M[0][2] = (double) 0;
    this->_M[1][0] = (double) 0;
    this->_M[1][1] = (double) 0;
    this->_M[1][2] = (double) 0;
    this->_M[2][0] = (double) 0;
    this->_M[2][1] = (double) 0;
    this->_M[2][2] = (double) 0;
}
dmat3::dmat3(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22)
{
    this->_M[0][0] = anyScalarToType<double>(m00);
    this->_M[0][1] = anyScalarToType<double>(m01);
    this->_M[0][2] = anyScalarToType<double>(m02);
    this->_M[1][0] = anyScalarToType<double>(m10);
    this->_M[1][1] = anyScalarToType<double>(m11);
    this->_M[1][2] = anyScalarToType<double>(m12);
    this->_M[2][0] = anyScalarToType<double>(m20);
    this->_M[2][1] = anyScalarToType<double>(m21);
    this->_M[2][2] = anyScalarToType<double>(m22);
}
double dmat3::operator()(unsigned r, unsigned c) const
{
    if(r < 3 && c < 3 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
double& dmat3::operator()(unsigned r, unsigned c) 
{
    if(r < 3 && c < 3 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<double> dmat3::data() const
{    std::vector<double> rv(9);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[0][2];
    rv[3] = this->_M[1][0];
    rv[4] = this->_M[1][1];
    rv[5] = this->_M[1][2];
    rv[6] = this->_M[2][0];
    rv[7] = this->_M[2][1];
    rv[8] = this->_M[2][2];
    return rv;
}
dmat3::operator std::string() const
{    std::ostringstream o;
    o << "dmat3(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << ' ';
    o << this->_M[0][2] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << ' ';
    o << this->_M[1][2] << std::endl;
    o << this->_M[2][0] << ' ';
    o << this->_M[2][1] << ' ';
    o << this->_M[2][2] << std::endl;
    return o.str();
}
//matrix binary operations
dmat3 operator+(const dmat3& m1, const dmat3& m2)
{
    dmat3 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] + m2._M[0][2];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] + m2._M[1][2];
    rv._M[2][0] = m1._M[2][0] + m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] + m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] + m2._M[2][2];
    return rv;
}
dmat3 operator-(const dmat3& m1, const dmat3& m2)
{
    dmat3 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] - m2._M[0][2];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] - m2._M[1][2];
    rv._M[2][0] = m1._M[2][0] - m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] - m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] - m2._M[2][2];
    return rv;
}
//matrix equality
bool operator==(const dmat3& m1, const dmat3& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[0][2] != m2._M[0][2] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    if(m1._M[1][2] != m2._M[1][2] ) return false;
    if(m1._M[2][0] != m2._M[2][0] ) return false;
    if(m1._M[2][1] != m2._M[2][1] ) return false;
    if(m1._M[2][2] != m2._M[2][2] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const dmat3& m1, const dmat3& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
dmat3 operator*(const dmat3& m1, const dmat3& m2)
{
    dmat3 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][0] += m1._M[0][2] * m2._M[2][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[0][1] += m1._M[0][2] * m2._M[2][1];
    rv._M[0][2] += m1._M[0][0] * m2._M[0][2];
    rv._M[0][2] += m1._M[0][1] * m2._M[1][2];
    rv._M[0][2] += m1._M[0][2] * m2._M[2][2];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][0] += m1._M[1][2] * m2._M[2][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    rv._M[1][1] += m1._M[1][2] * m2._M[2][1];
    rv._M[1][2] += m1._M[1][0] * m2._M[0][2];
    rv._M[1][2] += m1._M[1][1] * m2._M[1][2];
    rv._M[1][2] += m1._M[1][2] * m2._M[2][2];
    rv._M[2][0] += m1._M[2][0] * m2._M[0][0];
    rv._M[2][0] += m1._M[2][1] * m2._M[1][0];
    rv._M[2][0] += m1._M[2][2] * m2._M[2][0];
    rv._M[2][1] += m1._M[2][0] * m2._M[0][1];
    rv._M[2][1] += m1._M[2][1] * m2._M[1][1];
    rv._M[2][1] += m1._M[2][2] * m2._M[2][1];
    rv._M[2][2] += m1._M[2][0] * m2._M[0][2];
    rv._M[2][2] += m1._M[2][1] * m2._M[1][2];
    rv._M[2][2] += m1._M[2][2] * m2._M[2][2];
    return rv;
}
//matrix-vector multiply
dvec3 operator*(const dmat3& m, const dvec3& v)
{
    dvec3 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.x += m._M[0][2] * v.z;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    rv.y += m._M[1][2] * v.z;
    rv.z += m._M[2][0] * v.x;
    rv.z += m._M[2][1] * v.y;
    rv.z += m._M[2][2] * v.z;
    return rv;
}
//vector-matrix multiply
dvec3 operator*(const dvec3& v, const dmat3& m)
{
    dvec3 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.x += v.z * m._M[2][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    rv.y += v.z * m._M[2][1];
    rv.z += v.x * m._M[0][2];
    rv.z += v.y * m._M[1][2];
    rv.z += v.z * m._M[2][2];
    return rv;
}
//matrix-scalar operations
dmat3 operator*(const dmat3& m, float s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    return rv;
}
dmat3 operator*(const dmat3& m, double s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    return rv;
}
dmat3 operator*(const dmat3& m, std::int32_t s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    return rv;
}
dmat3 operator*(const dmat3& m, std::uint32_t s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    return rv;
}
dmat3 operator/(const dmat3& m, float s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    return rv;
}
dmat3 operator/(const dmat3& m, double s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    return rv;
}
dmat3 operator/(const dmat3& m, std::int32_t s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    return rv;
}
dmat3 operator/(const dmat3& m, std::uint32_t s)
{
    dmat3 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    return rv;
}
//scalar-matrix operations
dmat3 operator*(float s, const dmat3& m)
{
    dmat3 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    return rv;
}
dmat3 operator*(double s, const dmat3& m)
{
    dmat3 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    return rv;
}
dmat3 operator*(std::int32_t s, const dmat3& m)
{
    dmat3 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    return rv;
}
dmat3 operator*(std::uint32_t s, const dmat3& m)
{
    dmat3 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    return rv;
}
//unary matrix operations
dmat3 operator+(const dmat3& m)
{
    return (double(+1)) * m;
}
dmat3 operator-(const dmat3& m)
{
    return (double(-1)) * m;
}
//matrix transpose
dmat3 transpose(const dmat3& m)
{
    dmat3 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[0][2] = m._M[2][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    rv._M[1][2] = m._M[2][1];
    rv._M[2][0] = m._M[0][2];
    rv._M[2][1] = m._M[1][2];
    rv._M[2][2] = m._M[2][2];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const dmat3& m)
{    o << "dmat3(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << ' ';
    o << m._M[0][2] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << ' ';
    o << m._M[1][2] << std::endl;
    o << m._M[2][0] << ' ';
    o << m._M[2][1] << ' ';
    o << m._M[2][2] << std::endl;
    return o;
}

mat4:: RowProxy::RowProxy( mat4* m_, int r_) : m(m_), r(r_) {}
mat4::CRowProxy::CRowProxy(const mat4* m_, int r_) : m(m_), r(r_) {}
mat4:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat4::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
mat4::RowProxy mat4::operator[](unsigned idx)
{
    if( idx >= 4 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
mat4::CRowProxy mat4::operator[](unsigned idx) const
{
    if( idx >= 4 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
float& mat4::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
float mat4::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
mat4 mat4::identity()
{
    return mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
mat4::mat4()
{
    this->_M[0][0] = (float) 0;
    this->_M[0][1] = (float) 0;
    this->_M[0][2] = (float) 0;
    this->_M[0][3] = (float) 0;
    this->_M[1][0] = (float) 0;
    this->_M[1][1] = (float) 0;
    this->_M[1][2] = (float) 0;
    this->_M[1][3] = (float) 0;
    this->_M[2][0] = (float) 0;
    this->_M[2][1] = (float) 0;
    this->_M[2][2] = (float) 0;
    this->_M[2][3] = (float) 0;
    this->_M[3][0] = (float) 0;
    this->_M[3][1] = (float) 0;
    this->_M[3][2] = (float) 0;
    this->_M[3][3] = (float) 0;
}
mat4::mat4(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m03, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m13, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22, const AnyScalar& m23, const AnyScalar& m30, const AnyScalar& m31, const AnyScalar& m32, const AnyScalar& m33)
{
    this->_M[0][0] = anyScalarToType<float>(m00);
    this->_M[0][1] = anyScalarToType<float>(m01);
    this->_M[0][2] = anyScalarToType<float>(m02);
    this->_M[0][3] = anyScalarToType<float>(m03);
    this->_M[1][0] = anyScalarToType<float>(m10);
    this->_M[1][1] = anyScalarToType<float>(m11);
    this->_M[1][2] = anyScalarToType<float>(m12);
    this->_M[1][3] = anyScalarToType<float>(m13);
    this->_M[2][0] = anyScalarToType<float>(m20);
    this->_M[2][1] = anyScalarToType<float>(m21);
    this->_M[2][2] = anyScalarToType<float>(m22);
    this->_M[2][3] = anyScalarToType<float>(m23);
    this->_M[3][0] = anyScalarToType<float>(m30);
    this->_M[3][1] = anyScalarToType<float>(m31);
    this->_M[3][2] = anyScalarToType<float>(m32);
    this->_M[3][3] = anyScalarToType<float>(m33);
}
float mat4::operator()(unsigned r, unsigned c) const
{
    if(r < 4 && c < 4 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
float& mat4::operator()(unsigned r, unsigned c) 
{
    if(r < 4 && c < 4 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<float> mat4::data() const
{    std::vector<float> rv(16);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[0][2];
    rv[3] = this->_M[0][3];
    rv[4] = this->_M[1][0];
    rv[5] = this->_M[1][1];
    rv[6] = this->_M[1][2];
    rv[7] = this->_M[1][3];
    rv[8] = this->_M[2][0];
    rv[9] = this->_M[2][1];
    rv[10] = this->_M[2][2];
    rv[11] = this->_M[2][3];
    rv[12] = this->_M[3][0];
    rv[13] = this->_M[3][1];
    rv[14] = this->_M[3][2];
    rv[15] = this->_M[3][3];
    return rv;
}
mat4::operator std::string() const
{    std::ostringstream o;
    o << "mat4(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << ' ';
    o << this->_M[0][2] << ' ';
    o << this->_M[0][3] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << ' ';
    o << this->_M[1][2] << ' ';
    o << this->_M[1][3] << std::endl;
    o << this->_M[2][0] << ' ';
    o << this->_M[2][1] << ' ';
    o << this->_M[2][2] << ' ';
    o << this->_M[2][3] << std::endl;
    o << this->_M[3][0] << ' ';
    o << this->_M[3][1] << ' ';
    o << this->_M[3][2] << ' ';
    o << this->_M[3][3] << std::endl;
    return o.str();
}
//matrix binary operations
mat4 operator+(const mat4& m1, const mat4& m2)
{
    mat4 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] + m2._M[0][2];
    rv._M[0][3] = m1._M[0][3] + m2._M[0][3];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] + m2._M[1][2];
    rv._M[1][3] = m1._M[1][3] + m2._M[1][3];
    rv._M[2][0] = m1._M[2][0] + m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] + m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] + m2._M[2][2];
    rv._M[2][3] = m1._M[2][3] + m2._M[2][3];
    rv._M[3][0] = m1._M[3][0] + m2._M[3][0];
    rv._M[3][1] = m1._M[3][1] + m2._M[3][1];
    rv._M[3][2] = m1._M[3][2] + m2._M[3][2];
    rv._M[3][3] = m1._M[3][3] + m2._M[3][3];
    return rv;
}
mat4 operator-(const mat4& m1, const mat4& m2)
{
    mat4 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] - m2._M[0][2];
    rv._M[0][3] = m1._M[0][3] - m2._M[0][3];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] - m2._M[1][2];
    rv._M[1][3] = m1._M[1][3] - m2._M[1][3];
    rv._M[2][0] = m1._M[2][0] - m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] - m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] - m2._M[2][2];
    rv._M[2][3] = m1._M[2][3] - m2._M[2][3];
    rv._M[3][0] = m1._M[3][0] - m2._M[3][0];
    rv._M[3][1] = m1._M[3][1] - m2._M[3][1];
    rv._M[3][2] = m1._M[3][2] - m2._M[3][2];
    rv._M[3][3] = m1._M[3][3] - m2._M[3][3];
    return rv;
}
//matrix equality
bool operator==(const mat4& m1, const mat4& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[0][2] != m2._M[0][2] ) return false;
    if(m1._M[0][3] != m2._M[0][3] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    if(m1._M[1][2] != m2._M[1][2] ) return false;
    if(m1._M[1][3] != m2._M[1][3] ) return false;
    if(m1._M[2][0] != m2._M[2][0] ) return false;
    if(m1._M[2][1] != m2._M[2][1] ) return false;
    if(m1._M[2][2] != m2._M[2][2] ) return false;
    if(m1._M[2][3] != m2._M[2][3] ) return false;
    if(m1._M[3][0] != m2._M[3][0] ) return false;
    if(m1._M[3][1] != m2._M[3][1] ) return false;
    if(m1._M[3][2] != m2._M[3][2] ) return false;
    if(m1._M[3][3] != m2._M[3][3] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const mat4& m1, const mat4& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
mat4 operator*(const mat4& m1, const mat4& m2)
{
    mat4 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][0] += m1._M[0][2] * m2._M[2][0];
    rv._M[0][0] += m1._M[0][3] * m2._M[3][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[0][1] += m1._M[0][2] * m2._M[2][1];
    rv._M[0][1] += m1._M[0][3] * m2._M[3][1];
    rv._M[0][2] += m1._M[0][0] * m2._M[0][2];
    rv._M[0][2] += m1._M[0][1] * m2._M[1][2];
    rv._M[0][2] += m1._M[0][2] * m2._M[2][2];
    rv._M[0][2] += m1._M[0][3] * m2._M[3][2];
    rv._M[0][3] += m1._M[0][0] * m2._M[0][3];
    rv._M[0][3] += m1._M[0][1] * m2._M[1][3];
    rv._M[0][3] += m1._M[0][2] * m2._M[2][3];
    rv._M[0][3] += m1._M[0][3] * m2._M[3][3];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][0] += m1._M[1][2] * m2._M[2][0];
    rv._M[1][0] += m1._M[1][3] * m2._M[3][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    rv._M[1][1] += m1._M[1][2] * m2._M[2][1];
    rv._M[1][1] += m1._M[1][3] * m2._M[3][1];
    rv._M[1][2] += m1._M[1][0] * m2._M[0][2];
    rv._M[1][2] += m1._M[1][1] * m2._M[1][2];
    rv._M[1][2] += m1._M[1][2] * m2._M[2][2];
    rv._M[1][2] += m1._M[1][3] * m2._M[3][2];
    rv._M[1][3] += m1._M[1][0] * m2._M[0][3];
    rv._M[1][3] += m1._M[1][1] * m2._M[1][3];
    rv._M[1][3] += m1._M[1][2] * m2._M[2][3];
    rv._M[1][3] += m1._M[1][3] * m2._M[3][3];
    rv._M[2][0] += m1._M[2][0] * m2._M[0][0];
    rv._M[2][0] += m1._M[2][1] * m2._M[1][0];
    rv._M[2][0] += m1._M[2][2] * m2._M[2][0];
    rv._M[2][0] += m1._M[2][3] * m2._M[3][0];
    rv._M[2][1] += m1._M[2][0] * m2._M[0][1];
    rv._M[2][1] += m1._M[2][1] * m2._M[1][1];
    rv._M[2][1] += m1._M[2][2] * m2._M[2][1];
    rv._M[2][1] += m1._M[2][3] * m2._M[3][1];
    rv._M[2][2] += m1._M[2][0] * m2._M[0][2];
    rv._M[2][2] += m1._M[2][1] * m2._M[1][2];
    rv._M[2][2] += m1._M[2][2] * m2._M[2][2];
    rv._M[2][2] += m1._M[2][3] * m2._M[3][2];
    rv._M[2][3] += m1._M[2][0] * m2._M[0][3];
    rv._M[2][3] += m1._M[2][1] * m2._M[1][3];
    rv._M[2][3] += m1._M[2][2] * m2._M[2][3];
    rv._M[2][3] += m1._M[2][3] * m2._M[3][3];
    rv._M[3][0] += m1._M[3][0] * m2._M[0][0];
    rv._M[3][0] += m1._M[3][1] * m2._M[1][0];
    rv._M[3][0] += m1._M[3][2] * m2._M[2][0];
    rv._M[3][0] += m1._M[3][3] * m2._M[3][0];
    rv._M[3][1] += m1._M[3][0] * m2._M[0][1];
    rv._M[3][1] += m1._M[3][1] * m2._M[1][1];
    rv._M[3][1] += m1._M[3][2] * m2._M[2][1];
    rv._M[3][1] += m1._M[3][3] * m2._M[3][1];
    rv._M[3][2] += m1._M[3][0] * m2._M[0][2];
    rv._M[3][2] += m1._M[3][1] * m2._M[1][2];
    rv._M[3][2] += m1._M[3][2] * m2._M[2][2];
    rv._M[3][2] += m1._M[3][3] * m2._M[3][2];
    rv._M[3][3] += m1._M[3][0] * m2._M[0][3];
    rv._M[3][3] += m1._M[3][1] * m2._M[1][3];
    rv._M[3][3] += m1._M[3][2] * m2._M[2][3];
    rv._M[3][3] += m1._M[3][3] * m2._M[3][3];
    return rv;
}
//matrix-vector multiply
vec4 operator*(const mat4& m, const vec4& v)
{
    vec4 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.x += m._M[0][2] * v.z;
    rv.x += m._M[0][3] * v.w;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    rv.y += m._M[1][2] * v.z;
    rv.y += m._M[1][3] * v.w;
    rv.z += m._M[2][0] * v.x;
    rv.z += m._M[2][1] * v.y;
    rv.z += m._M[2][2] * v.z;
    rv.z += m._M[2][3] * v.w;
    rv.w += m._M[3][0] * v.x;
    rv.w += m._M[3][1] * v.y;
    rv.w += m._M[3][2] * v.z;
    rv.w += m._M[3][3] * v.w;
    return rv;
}
//vector-matrix multiply
vec4 operator*(const vec4& v, const mat4& m)
{
    vec4 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.x += v.z * m._M[2][0];
    rv.x += v.w * m._M[3][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    rv.y += v.z * m._M[2][1];
    rv.y += v.w * m._M[3][1];
    rv.z += v.x * m._M[0][2];
    rv.z += v.y * m._M[1][2];
    rv.z += v.z * m._M[2][2];
    rv.z += v.w * m._M[3][2];
    rv.w += v.x * m._M[0][3];
    rv.w += v.y * m._M[1][3];
    rv.w += v.z * m._M[2][3];
    rv.w += v.w * m._M[3][3];
    return rv;
}
//matrix-scalar operations
mat4 operator*(const mat4& m, float s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[0][3] =  m._M[0][3] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[1][3] =  m._M[1][3] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    rv._M[2][3] =  m._M[2][3] * (float)s ;
    rv._M[3][0] =  m._M[3][0] * (float)s ;
    rv._M[3][1] =  m._M[3][1] * (float)s ;
    rv._M[3][2] =  m._M[3][2] * (float)s ;
    rv._M[3][3] =  m._M[3][3] * (float)s ;
    return rv;
}
mat4 operator*(const mat4& m, double s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[0][3] =  m._M[0][3] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[1][3] =  m._M[1][3] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    rv._M[2][3] =  m._M[2][3] * (float)s ;
    rv._M[3][0] =  m._M[3][0] * (float)s ;
    rv._M[3][1] =  m._M[3][1] * (float)s ;
    rv._M[3][2] =  m._M[3][2] * (float)s ;
    rv._M[3][3] =  m._M[3][3] * (float)s ;
    return rv;
}
mat4 operator*(const mat4& m, std::int32_t s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[0][3] =  m._M[0][3] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[1][3] =  m._M[1][3] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    rv._M[2][3] =  m._M[2][3] * (float)s ;
    rv._M[3][0] =  m._M[3][0] * (float)s ;
    rv._M[3][1] =  m._M[3][1] * (float)s ;
    rv._M[3][2] =  m._M[3][2] * (float)s ;
    rv._M[3][3] =  m._M[3][3] * (float)s ;
    return rv;
}
mat4 operator*(const mat4& m, std::uint32_t s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] * (float)s ;
    rv._M[0][1] =  m._M[0][1] * (float)s ;
    rv._M[0][2] =  m._M[0][2] * (float)s ;
    rv._M[0][3] =  m._M[0][3] * (float)s ;
    rv._M[1][0] =  m._M[1][0] * (float)s ;
    rv._M[1][1] =  m._M[1][1] * (float)s ;
    rv._M[1][2] =  m._M[1][2] * (float)s ;
    rv._M[1][3] =  m._M[1][3] * (float)s ;
    rv._M[2][0] =  m._M[2][0] * (float)s ;
    rv._M[2][1] =  m._M[2][1] * (float)s ;
    rv._M[2][2] =  m._M[2][2] * (float)s ;
    rv._M[2][3] =  m._M[2][3] * (float)s ;
    rv._M[3][0] =  m._M[3][0] * (float)s ;
    rv._M[3][1] =  m._M[3][1] * (float)s ;
    rv._M[3][2] =  m._M[3][2] * (float)s ;
    rv._M[3][3] =  m._M[3][3] * (float)s ;
    return rv;
}
mat4 operator/(const mat4& m, float s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[0][3] =  m._M[0][3] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[1][3] =  m._M[1][3] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    rv._M[2][3] =  m._M[2][3] / (float)s ;
    rv._M[3][0] =  m._M[3][0] / (float)s ;
    rv._M[3][1] =  m._M[3][1] / (float)s ;
    rv._M[3][2] =  m._M[3][2] / (float)s ;
    rv._M[3][3] =  m._M[3][3] / (float)s ;
    return rv;
}
mat4 operator/(const mat4& m, double s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[0][3] =  m._M[0][3] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[1][3] =  m._M[1][3] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    rv._M[2][3] =  m._M[2][3] / (float)s ;
    rv._M[3][0] =  m._M[3][0] / (float)s ;
    rv._M[3][1] =  m._M[3][1] / (float)s ;
    rv._M[3][2] =  m._M[3][2] / (float)s ;
    rv._M[3][3] =  m._M[3][3] / (float)s ;
    return rv;
}
mat4 operator/(const mat4& m, std::int32_t s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[0][3] =  m._M[0][3] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[1][3] =  m._M[1][3] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    rv._M[2][3] =  m._M[2][3] / (float)s ;
    rv._M[3][0] =  m._M[3][0] / (float)s ;
    rv._M[3][1] =  m._M[3][1] / (float)s ;
    rv._M[3][2] =  m._M[3][2] / (float)s ;
    rv._M[3][3] =  m._M[3][3] / (float)s ;
    return rv;
}
mat4 operator/(const mat4& m, std::uint32_t s)
{
    mat4 rv;
    rv._M[0][0] =  m._M[0][0] / (float)s ;
    rv._M[0][1] =  m._M[0][1] / (float)s ;
    rv._M[0][2] =  m._M[0][2] / (float)s ;
    rv._M[0][3] =  m._M[0][3] / (float)s ;
    rv._M[1][0] =  m._M[1][0] / (float)s ;
    rv._M[1][1] =  m._M[1][1] / (float)s ;
    rv._M[1][2] =  m._M[1][2] / (float)s ;
    rv._M[1][3] =  m._M[1][3] / (float)s ;
    rv._M[2][0] =  m._M[2][0] / (float)s ;
    rv._M[2][1] =  m._M[2][1] / (float)s ;
    rv._M[2][2] =  m._M[2][2] / (float)s ;
    rv._M[2][3] =  m._M[2][3] / (float)s ;
    rv._M[3][0] =  m._M[3][0] / (float)s ;
    rv._M[3][1] =  m._M[3][1] / (float)s ;
    rv._M[3][2] =  m._M[3][2] / (float)s ;
    rv._M[3][3] =  m._M[3][3] / (float)s ;
    return rv;
}
//scalar-matrix operations
mat4 operator*(float s, const mat4& m)
{
    mat4 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[0][3] =  (float)s * m._M[0][3]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[1][3] =  (float)s * m._M[1][3]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    rv._M[2][3] =  (float)s * m._M[2][3]  ;
    rv._M[3][0] =  (float)s * m._M[3][0]  ;
    rv._M[3][1] =  (float)s * m._M[3][1]  ;
    rv._M[3][2] =  (float)s * m._M[3][2]  ;
    rv._M[3][3] =  (float)s * m._M[3][3]  ;
    return rv;
}
mat4 operator*(double s, const mat4& m)
{
    mat4 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[0][3] =  (float)s * m._M[0][3]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[1][3] =  (float)s * m._M[1][3]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    rv._M[2][3] =  (float)s * m._M[2][3]  ;
    rv._M[3][0] =  (float)s * m._M[3][0]  ;
    rv._M[3][1] =  (float)s * m._M[3][1]  ;
    rv._M[3][2] =  (float)s * m._M[3][2]  ;
    rv._M[3][3] =  (float)s * m._M[3][3]  ;
    return rv;
}
mat4 operator*(std::int32_t s, const mat4& m)
{
    mat4 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[0][3] =  (float)s * m._M[0][3]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[1][3] =  (float)s * m._M[1][3]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    rv._M[2][3] =  (float)s * m._M[2][3]  ;
    rv._M[3][0] =  (float)s * m._M[3][0]  ;
    rv._M[3][1] =  (float)s * m._M[3][1]  ;
    rv._M[3][2] =  (float)s * m._M[3][2]  ;
    rv._M[3][3] =  (float)s * m._M[3][3]  ;
    return rv;
}
mat4 operator*(std::uint32_t s, const mat4& m)
{
    mat4 rv;
    rv._M[0][0] =  (float)s * m._M[0][0]  ;
    rv._M[0][1] =  (float)s * m._M[0][1]  ;
    rv._M[0][2] =  (float)s * m._M[0][2]  ;
    rv._M[0][3] =  (float)s * m._M[0][3]  ;
    rv._M[1][0] =  (float)s * m._M[1][0]  ;
    rv._M[1][1] =  (float)s * m._M[1][1]  ;
    rv._M[1][2] =  (float)s * m._M[1][2]  ;
    rv._M[1][3] =  (float)s * m._M[1][3]  ;
    rv._M[2][0] =  (float)s * m._M[2][0]  ;
    rv._M[2][1] =  (float)s * m._M[2][1]  ;
    rv._M[2][2] =  (float)s * m._M[2][2]  ;
    rv._M[2][3] =  (float)s * m._M[2][3]  ;
    rv._M[3][0] =  (float)s * m._M[3][0]  ;
    rv._M[3][1] =  (float)s * m._M[3][1]  ;
    rv._M[3][2] =  (float)s * m._M[3][2]  ;
    rv._M[3][3] =  (float)s * m._M[3][3]  ;
    return rv;
}
//unary matrix operations
mat4 operator+(const mat4& m)
{
    return (float(+1)) * m;
}
mat4 operator-(const mat4& m)
{
    return (float(-1)) * m;
}
//matrix transpose
mat4 transpose(const mat4& m)
{
    mat4 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[0][2] = m._M[2][0];
    rv._M[0][3] = m._M[3][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    rv._M[1][2] = m._M[2][1];
    rv._M[1][3] = m._M[3][1];
    rv._M[2][0] = m._M[0][2];
    rv._M[2][1] = m._M[1][2];
    rv._M[2][2] = m._M[2][2];
    rv._M[2][3] = m._M[3][2];
    rv._M[3][0] = m._M[0][3];
    rv._M[3][1] = m._M[1][3];
    rv._M[3][2] = m._M[2][3];
    rv._M[3][3] = m._M[3][3];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const mat4& m)
{    o << "mat4(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << ' ';
    o << m._M[0][2] << ' ';
    o << m._M[0][3] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << ' ';
    o << m._M[1][2] << ' ';
    o << m._M[1][3] << std::endl;
    o << m._M[2][0] << ' ';
    o << m._M[2][1] << ' ';
    o << m._M[2][2] << ' ';
    o << m._M[2][3] << std::endl;
    o << m._M[3][0] << ' ';
    o << m._M[3][1] << ' ';
    o << m._M[3][2] << ' ';
    o << m._M[3][3] << std::endl;
    return o;
}

dmat4:: RowProxy::RowProxy( dmat4* m_, int r_) : m(m_), r(r_) {}
dmat4::CRowProxy::CRowProxy(const dmat4* m_, int r_) : m(m_), r(r_) {}
dmat4:: RowProxy::RowProxy( RowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat4::CRowProxy::CRowProxy(CRowProxy&& R) noexcept : m(R.m), r(R.r) {}
dmat4::RowProxy dmat4::operator[](unsigned idx)
{
    if( idx >= 4 )
        throw std::runtime_error("Bad row value");
    return RowProxy(this,idx);
}
dmat4::CRowProxy dmat4::operator[](unsigned idx) const
{
    if( idx >= 4 )
        throw std::runtime_error("Bad row value");
    return CRowProxy(this,idx);
}
double& dmat4::RowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
double dmat4::CRowProxy::operator[](unsigned idx)
{
    return this->m->_M[this->r][idx];
}
dmat4 dmat4::identity()
{
    return dmat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
dmat4::dmat4()
{
    this->_M[0][0] = (double) 0;
    this->_M[0][1] = (double) 0;
    this->_M[0][2] = (double) 0;
    this->_M[0][3] = (double) 0;
    this->_M[1][0] = (double) 0;
    this->_M[1][1] = (double) 0;
    this->_M[1][2] = (double) 0;
    this->_M[1][3] = (double) 0;
    this->_M[2][0] = (double) 0;
    this->_M[2][1] = (double) 0;
    this->_M[2][2] = (double) 0;
    this->_M[2][3] = (double) 0;
    this->_M[3][0] = (double) 0;
    this->_M[3][1] = (double) 0;
    this->_M[3][2] = (double) 0;
    this->_M[3][3] = (double) 0;
}
dmat4::dmat4(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m03, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m13, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22, const AnyScalar& m23, const AnyScalar& m30, const AnyScalar& m31, const AnyScalar& m32, const AnyScalar& m33)
{
    this->_M[0][0] = anyScalarToType<double>(m00);
    this->_M[0][1] = anyScalarToType<double>(m01);
    this->_M[0][2] = anyScalarToType<double>(m02);
    this->_M[0][3] = anyScalarToType<double>(m03);
    this->_M[1][0] = anyScalarToType<double>(m10);
    this->_M[1][1] = anyScalarToType<double>(m11);
    this->_M[1][2] = anyScalarToType<double>(m12);
    this->_M[1][3] = anyScalarToType<double>(m13);
    this->_M[2][0] = anyScalarToType<double>(m20);
    this->_M[2][1] = anyScalarToType<double>(m21);
    this->_M[2][2] = anyScalarToType<double>(m22);
    this->_M[2][3] = anyScalarToType<double>(m23);
    this->_M[3][0] = anyScalarToType<double>(m30);
    this->_M[3][1] = anyScalarToType<double>(m31);
    this->_M[3][2] = anyScalarToType<double>(m32);
    this->_M[3][3] = anyScalarToType<double>(m33);
}
double dmat4::operator()(unsigned r, unsigned c) const
{
    if(r < 4 && c < 4 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
double& dmat4::operator()(unsigned r, unsigned c) 
{
    if(r < 4 && c < 4 )
        return this->_M[r][c];
    throw std::runtime_error("Matrix reference out of bounds");
}
    std::vector<double> dmat4::data() const
{    std::vector<double> rv(16);
    rv[0] = this->_M[0][0];
    rv[1] = this->_M[0][1];
    rv[2] = this->_M[0][2];
    rv[3] = this->_M[0][3];
    rv[4] = this->_M[1][0];
    rv[5] = this->_M[1][1];
    rv[6] = this->_M[1][2];
    rv[7] = this->_M[1][3];
    rv[8] = this->_M[2][0];
    rv[9] = this->_M[2][1];
    rv[10] = this->_M[2][2];
    rv[11] = this->_M[2][3];
    rv[12] = this->_M[3][0];
    rv[13] = this->_M[3][1];
    rv[14] = this->_M[3][2];
    rv[15] = this->_M[3][3];
    return rv;
}
dmat4::operator std::string() const
{    std::ostringstream o;
    o << "dmat4(" << std::endl;
    o << this->_M[0][0] << ' ';
    o << this->_M[0][1] << ' ';
    o << this->_M[0][2] << ' ';
    o << this->_M[0][3] << std::endl;
    o << this->_M[1][0] << ' ';
    o << this->_M[1][1] << ' ';
    o << this->_M[1][2] << ' ';
    o << this->_M[1][3] << std::endl;
    o << this->_M[2][0] << ' ';
    o << this->_M[2][1] << ' ';
    o << this->_M[2][2] << ' ';
    o << this->_M[2][3] << std::endl;
    o << this->_M[3][0] << ' ';
    o << this->_M[3][1] << ' ';
    o << this->_M[3][2] << ' ';
    o << this->_M[3][3] << std::endl;
    return o.str();
}
//matrix binary operations
dmat4 operator+(const dmat4& m1, const dmat4& m2)
{
    dmat4 rv;
    rv._M[0][0] = m1._M[0][0] + m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] + m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] + m2._M[0][2];
    rv._M[0][3] = m1._M[0][3] + m2._M[0][3];
    rv._M[1][0] = m1._M[1][0] + m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] + m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] + m2._M[1][2];
    rv._M[1][3] = m1._M[1][3] + m2._M[1][3];
    rv._M[2][0] = m1._M[2][0] + m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] + m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] + m2._M[2][2];
    rv._M[2][3] = m1._M[2][3] + m2._M[2][3];
    rv._M[3][0] = m1._M[3][0] + m2._M[3][0];
    rv._M[3][1] = m1._M[3][1] + m2._M[3][1];
    rv._M[3][2] = m1._M[3][2] + m2._M[3][2];
    rv._M[3][3] = m1._M[3][3] + m2._M[3][3];
    return rv;
}
dmat4 operator-(const dmat4& m1, const dmat4& m2)
{
    dmat4 rv;
    rv._M[0][0] = m1._M[0][0] - m2._M[0][0];
    rv._M[0][1] = m1._M[0][1] - m2._M[0][1];
    rv._M[0][2] = m1._M[0][2] - m2._M[0][2];
    rv._M[0][3] = m1._M[0][3] - m2._M[0][3];
    rv._M[1][0] = m1._M[1][0] - m2._M[1][0];
    rv._M[1][1] = m1._M[1][1] - m2._M[1][1];
    rv._M[1][2] = m1._M[1][2] - m2._M[1][2];
    rv._M[1][3] = m1._M[1][3] - m2._M[1][3];
    rv._M[2][0] = m1._M[2][0] - m2._M[2][0];
    rv._M[2][1] = m1._M[2][1] - m2._M[2][1];
    rv._M[2][2] = m1._M[2][2] - m2._M[2][2];
    rv._M[2][3] = m1._M[2][3] - m2._M[2][3];
    rv._M[3][0] = m1._M[3][0] - m2._M[3][0];
    rv._M[3][1] = m1._M[3][1] - m2._M[3][1];
    rv._M[3][2] = m1._M[3][2] - m2._M[3][2];
    rv._M[3][3] = m1._M[3][3] - m2._M[3][3];
    return rv;
}
//matrix equality
bool operator==(const dmat4& m1, const dmat4& m2)
{
    if(m1._M[0][0] != m2._M[0][0] ) return false;
    if(m1._M[0][1] != m2._M[0][1] ) return false;
    if(m1._M[0][2] != m2._M[0][2] ) return false;
    if(m1._M[0][3] != m2._M[0][3] ) return false;
    if(m1._M[1][0] != m2._M[1][0] ) return false;
    if(m1._M[1][1] != m2._M[1][1] ) return false;
    if(m1._M[1][2] != m2._M[1][2] ) return false;
    if(m1._M[1][3] != m2._M[1][3] ) return false;
    if(m1._M[2][0] != m2._M[2][0] ) return false;
    if(m1._M[2][1] != m2._M[2][1] ) return false;
    if(m1._M[2][2] != m2._M[2][2] ) return false;
    if(m1._M[2][3] != m2._M[2][3] ) return false;
    if(m1._M[3][0] != m2._M[3][0] ) return false;
    if(m1._M[3][1] != m2._M[3][1] ) return false;
    if(m1._M[3][2] != m2._M[3][2] ) return false;
    if(m1._M[3][3] != m2._M[3][3] ) return false;
    return true;
}
//matrix inequality
bool operator!=(const dmat4& m1, const dmat4& m2)
{
    return !(m1==m2);}
//matrix-matrix multiply
dmat4 operator*(const dmat4& m1, const dmat4& m2)
{
    dmat4 rv;
    rv._M[0][0] += m1._M[0][0] * m2._M[0][0];
    rv._M[0][0] += m1._M[0][1] * m2._M[1][0];
    rv._M[0][0] += m1._M[0][2] * m2._M[2][0];
    rv._M[0][0] += m1._M[0][3] * m2._M[3][0];
    rv._M[0][1] += m1._M[0][0] * m2._M[0][1];
    rv._M[0][1] += m1._M[0][1] * m2._M[1][1];
    rv._M[0][1] += m1._M[0][2] * m2._M[2][1];
    rv._M[0][1] += m1._M[0][3] * m2._M[3][1];
    rv._M[0][2] += m1._M[0][0] * m2._M[0][2];
    rv._M[0][2] += m1._M[0][1] * m2._M[1][2];
    rv._M[0][2] += m1._M[0][2] * m2._M[2][2];
    rv._M[0][2] += m1._M[0][3] * m2._M[3][2];
    rv._M[0][3] += m1._M[0][0] * m2._M[0][3];
    rv._M[0][3] += m1._M[0][1] * m2._M[1][3];
    rv._M[0][3] += m1._M[0][2] * m2._M[2][3];
    rv._M[0][3] += m1._M[0][3] * m2._M[3][3];
    rv._M[1][0] += m1._M[1][0] * m2._M[0][0];
    rv._M[1][0] += m1._M[1][1] * m2._M[1][0];
    rv._M[1][0] += m1._M[1][2] * m2._M[2][0];
    rv._M[1][0] += m1._M[1][3] * m2._M[3][0];
    rv._M[1][1] += m1._M[1][0] * m2._M[0][1];
    rv._M[1][1] += m1._M[1][1] * m2._M[1][1];
    rv._M[1][1] += m1._M[1][2] * m2._M[2][1];
    rv._M[1][1] += m1._M[1][3] * m2._M[3][1];
    rv._M[1][2] += m1._M[1][0] * m2._M[0][2];
    rv._M[1][2] += m1._M[1][1] * m2._M[1][2];
    rv._M[1][2] += m1._M[1][2] * m2._M[2][2];
    rv._M[1][2] += m1._M[1][3] * m2._M[3][2];
    rv._M[1][3] += m1._M[1][0] * m2._M[0][3];
    rv._M[1][3] += m1._M[1][1] * m2._M[1][3];
    rv._M[1][3] += m1._M[1][2] * m2._M[2][3];
    rv._M[1][3] += m1._M[1][3] * m2._M[3][3];
    rv._M[2][0] += m1._M[2][0] * m2._M[0][0];
    rv._M[2][0] += m1._M[2][1] * m2._M[1][0];
    rv._M[2][0] += m1._M[2][2] * m2._M[2][0];
    rv._M[2][0] += m1._M[2][3] * m2._M[3][0];
    rv._M[2][1] += m1._M[2][0] * m2._M[0][1];
    rv._M[2][1] += m1._M[2][1] * m2._M[1][1];
    rv._M[2][1] += m1._M[2][2] * m2._M[2][1];
    rv._M[2][1] += m1._M[2][3] * m2._M[3][1];
    rv._M[2][2] += m1._M[2][0] * m2._M[0][2];
    rv._M[2][2] += m1._M[2][1] * m2._M[1][2];
    rv._M[2][2] += m1._M[2][2] * m2._M[2][2];
    rv._M[2][2] += m1._M[2][3] * m2._M[3][2];
    rv._M[2][3] += m1._M[2][0] * m2._M[0][3];
    rv._M[2][3] += m1._M[2][1] * m2._M[1][3];
    rv._M[2][3] += m1._M[2][2] * m2._M[2][3];
    rv._M[2][3] += m1._M[2][3] * m2._M[3][3];
    rv._M[3][0] += m1._M[3][0] * m2._M[0][0];
    rv._M[3][0] += m1._M[3][1] * m2._M[1][0];
    rv._M[3][0] += m1._M[3][2] * m2._M[2][0];
    rv._M[3][0] += m1._M[3][3] * m2._M[3][0];
    rv._M[3][1] += m1._M[3][0] * m2._M[0][1];
    rv._M[3][1] += m1._M[3][1] * m2._M[1][1];
    rv._M[3][1] += m1._M[3][2] * m2._M[2][1];
    rv._M[3][1] += m1._M[3][3] * m2._M[3][1];
    rv._M[3][2] += m1._M[3][0] * m2._M[0][2];
    rv._M[3][2] += m1._M[3][1] * m2._M[1][2];
    rv._M[3][2] += m1._M[3][2] * m2._M[2][2];
    rv._M[3][2] += m1._M[3][3] * m2._M[3][2];
    rv._M[3][3] += m1._M[3][0] * m2._M[0][3];
    rv._M[3][3] += m1._M[3][1] * m2._M[1][3];
    rv._M[3][3] += m1._M[3][2] * m2._M[2][3];
    rv._M[3][3] += m1._M[3][3] * m2._M[3][3];
    return rv;
}
//matrix-vector multiply
dvec4 operator*(const dmat4& m, const dvec4& v)
{
    dvec4 rv;
    rv.x += m._M[0][0] * v.x;
    rv.x += m._M[0][1] * v.y;
    rv.x += m._M[0][2] * v.z;
    rv.x += m._M[0][3] * v.w;
    rv.y += m._M[1][0] * v.x;
    rv.y += m._M[1][1] * v.y;
    rv.y += m._M[1][2] * v.z;
    rv.y += m._M[1][3] * v.w;
    rv.z += m._M[2][0] * v.x;
    rv.z += m._M[2][1] * v.y;
    rv.z += m._M[2][2] * v.z;
    rv.z += m._M[2][3] * v.w;
    rv.w += m._M[3][0] * v.x;
    rv.w += m._M[3][1] * v.y;
    rv.w += m._M[3][2] * v.z;
    rv.w += m._M[3][3] * v.w;
    return rv;
}
//vector-matrix multiply
dvec4 operator*(const dvec4& v, const dmat4& m)
{
    dvec4 rv;
    rv.x += v.x * m._M[0][0];
    rv.x += v.y * m._M[1][0];
    rv.x += v.z * m._M[2][0];
    rv.x += v.w * m._M[3][0];
    rv.y += v.x * m._M[0][1];
    rv.y += v.y * m._M[1][1];
    rv.y += v.z * m._M[2][1];
    rv.y += v.w * m._M[3][1];
    rv.z += v.x * m._M[0][2];
    rv.z += v.y * m._M[1][2];
    rv.z += v.z * m._M[2][2];
    rv.z += v.w * m._M[3][2];
    rv.w += v.x * m._M[0][3];
    rv.w += v.y * m._M[1][3];
    rv.w += v.z * m._M[2][3];
    rv.w += v.w * m._M[3][3];
    return rv;
}
//matrix-scalar operations
dmat4 operator*(const dmat4& m, float s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[0][3] =  m._M[0][3] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[1][3] =  m._M[1][3] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    rv._M[2][3] =  m._M[2][3] * (double)s ;
    rv._M[3][0] =  m._M[3][0] * (double)s ;
    rv._M[3][1] =  m._M[3][1] * (double)s ;
    rv._M[3][2] =  m._M[3][2] * (double)s ;
    rv._M[3][3] =  m._M[3][3] * (double)s ;
    return rv;
}
dmat4 operator*(const dmat4& m, double s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[0][3] =  m._M[0][3] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[1][3] =  m._M[1][3] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    rv._M[2][3] =  m._M[2][3] * (double)s ;
    rv._M[3][0] =  m._M[3][0] * (double)s ;
    rv._M[3][1] =  m._M[3][1] * (double)s ;
    rv._M[3][2] =  m._M[3][2] * (double)s ;
    rv._M[3][3] =  m._M[3][3] * (double)s ;
    return rv;
}
dmat4 operator*(const dmat4& m, std::int32_t s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[0][3] =  m._M[0][3] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[1][3] =  m._M[1][3] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    rv._M[2][3] =  m._M[2][3] * (double)s ;
    rv._M[3][0] =  m._M[3][0] * (double)s ;
    rv._M[3][1] =  m._M[3][1] * (double)s ;
    rv._M[3][2] =  m._M[3][2] * (double)s ;
    rv._M[3][3] =  m._M[3][3] * (double)s ;
    return rv;
}
dmat4 operator*(const dmat4& m, std::uint32_t s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] * (double)s ;
    rv._M[0][1] =  m._M[0][1] * (double)s ;
    rv._M[0][2] =  m._M[0][2] * (double)s ;
    rv._M[0][3] =  m._M[0][3] * (double)s ;
    rv._M[1][0] =  m._M[1][0] * (double)s ;
    rv._M[1][1] =  m._M[1][1] * (double)s ;
    rv._M[1][2] =  m._M[1][2] * (double)s ;
    rv._M[1][3] =  m._M[1][3] * (double)s ;
    rv._M[2][0] =  m._M[2][0] * (double)s ;
    rv._M[2][1] =  m._M[2][1] * (double)s ;
    rv._M[2][2] =  m._M[2][2] * (double)s ;
    rv._M[2][3] =  m._M[2][3] * (double)s ;
    rv._M[3][0] =  m._M[3][0] * (double)s ;
    rv._M[3][1] =  m._M[3][1] * (double)s ;
    rv._M[3][2] =  m._M[3][2] * (double)s ;
    rv._M[3][3] =  m._M[3][3] * (double)s ;
    return rv;
}
dmat4 operator/(const dmat4& m, float s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[0][3] =  m._M[0][3] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[1][3] =  m._M[1][3] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    rv._M[2][3] =  m._M[2][3] / (double)s ;
    rv._M[3][0] =  m._M[3][0] / (double)s ;
    rv._M[3][1] =  m._M[3][1] / (double)s ;
    rv._M[3][2] =  m._M[3][2] / (double)s ;
    rv._M[3][3] =  m._M[3][3] / (double)s ;
    return rv;
}
dmat4 operator/(const dmat4& m, double s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[0][3] =  m._M[0][3] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[1][3] =  m._M[1][3] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    rv._M[2][3] =  m._M[2][3] / (double)s ;
    rv._M[3][0] =  m._M[3][0] / (double)s ;
    rv._M[3][1] =  m._M[3][1] / (double)s ;
    rv._M[3][2] =  m._M[3][2] / (double)s ;
    rv._M[3][3] =  m._M[3][3] / (double)s ;
    return rv;
}
dmat4 operator/(const dmat4& m, std::int32_t s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[0][3] =  m._M[0][3] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[1][3] =  m._M[1][3] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    rv._M[2][3] =  m._M[2][3] / (double)s ;
    rv._M[3][0] =  m._M[3][0] / (double)s ;
    rv._M[3][1] =  m._M[3][1] / (double)s ;
    rv._M[3][2] =  m._M[3][2] / (double)s ;
    rv._M[3][3] =  m._M[3][3] / (double)s ;
    return rv;
}
dmat4 operator/(const dmat4& m, std::uint32_t s)
{
    dmat4 rv;
    rv._M[0][0] =  m._M[0][0] / (double)s ;
    rv._M[0][1] =  m._M[0][1] / (double)s ;
    rv._M[0][2] =  m._M[0][2] / (double)s ;
    rv._M[0][3] =  m._M[0][3] / (double)s ;
    rv._M[1][0] =  m._M[1][0] / (double)s ;
    rv._M[1][1] =  m._M[1][1] / (double)s ;
    rv._M[1][2] =  m._M[1][2] / (double)s ;
    rv._M[1][3] =  m._M[1][3] / (double)s ;
    rv._M[2][0] =  m._M[2][0] / (double)s ;
    rv._M[2][1] =  m._M[2][1] / (double)s ;
    rv._M[2][2] =  m._M[2][2] / (double)s ;
    rv._M[2][3] =  m._M[2][3] / (double)s ;
    rv._M[3][0] =  m._M[3][0] / (double)s ;
    rv._M[3][1] =  m._M[3][1] / (double)s ;
    rv._M[3][2] =  m._M[3][2] / (double)s ;
    rv._M[3][3] =  m._M[3][3] / (double)s ;
    return rv;
}
//scalar-matrix operations
dmat4 operator*(float s, const dmat4& m)
{
    dmat4 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[0][3] =  (double)s * m._M[0][3]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[1][3] =  (double)s * m._M[1][3]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    rv._M[2][3] =  (double)s * m._M[2][3]  ;
    rv._M[3][0] =  (double)s * m._M[3][0]  ;
    rv._M[3][1] =  (double)s * m._M[3][1]  ;
    rv._M[3][2] =  (double)s * m._M[3][2]  ;
    rv._M[3][3] =  (double)s * m._M[3][3]  ;
    return rv;
}
dmat4 operator*(double s, const dmat4& m)
{
    dmat4 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[0][3] =  (double)s * m._M[0][3]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[1][3] =  (double)s * m._M[1][3]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    rv._M[2][3] =  (double)s * m._M[2][3]  ;
    rv._M[3][0] =  (double)s * m._M[3][0]  ;
    rv._M[3][1] =  (double)s * m._M[3][1]  ;
    rv._M[3][2] =  (double)s * m._M[3][2]  ;
    rv._M[3][3] =  (double)s * m._M[3][3]  ;
    return rv;
}
dmat4 operator*(std::int32_t s, const dmat4& m)
{
    dmat4 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[0][3] =  (double)s * m._M[0][3]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[1][3] =  (double)s * m._M[1][3]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    rv._M[2][3] =  (double)s * m._M[2][3]  ;
    rv._M[3][0] =  (double)s * m._M[3][0]  ;
    rv._M[3][1] =  (double)s * m._M[3][1]  ;
    rv._M[3][2] =  (double)s * m._M[3][2]  ;
    rv._M[3][3] =  (double)s * m._M[3][3]  ;
    return rv;
}
dmat4 operator*(std::uint32_t s, const dmat4& m)
{
    dmat4 rv;
    rv._M[0][0] =  (double)s * m._M[0][0]  ;
    rv._M[0][1] =  (double)s * m._M[0][1]  ;
    rv._M[0][2] =  (double)s * m._M[0][2]  ;
    rv._M[0][3] =  (double)s * m._M[0][3]  ;
    rv._M[1][0] =  (double)s * m._M[1][0]  ;
    rv._M[1][1] =  (double)s * m._M[1][1]  ;
    rv._M[1][2] =  (double)s * m._M[1][2]  ;
    rv._M[1][3] =  (double)s * m._M[1][3]  ;
    rv._M[2][0] =  (double)s * m._M[2][0]  ;
    rv._M[2][1] =  (double)s * m._M[2][1]  ;
    rv._M[2][2] =  (double)s * m._M[2][2]  ;
    rv._M[2][3] =  (double)s * m._M[2][3]  ;
    rv._M[3][0] =  (double)s * m._M[3][0]  ;
    rv._M[3][1] =  (double)s * m._M[3][1]  ;
    rv._M[3][2] =  (double)s * m._M[3][2]  ;
    rv._M[3][3] =  (double)s * m._M[3][3]  ;
    return rv;
}
//unary matrix operations
dmat4 operator+(const dmat4& m)
{
    return (double(+1)) * m;
}
dmat4 operator-(const dmat4& m)
{
    return (double(-1)) * m;
}
//matrix transpose
dmat4 transpose(const dmat4& m)
{
    dmat4 rv;
    rv._M[0][0] = m._M[0][0];
    rv._M[0][1] = m._M[1][0];
    rv._M[0][2] = m._M[2][0];
    rv._M[0][3] = m._M[3][0];
    rv._M[1][0] = m._M[0][1];
    rv._M[1][1] = m._M[1][1];
    rv._M[1][2] = m._M[2][1];
    rv._M[1][3] = m._M[3][1];
    rv._M[2][0] = m._M[0][2];
    rv._M[2][1] = m._M[1][2];
    rv._M[2][2] = m._M[2][2];
    rv._M[2][3] = m._M[3][2];
    rv._M[3][0] = m._M[0][3];
    rv._M[3][1] = m._M[1][3];
    rv._M[3][2] = m._M[2][3];
    rv._M[3][3] = m._M[3][3];
    return rv;
}
//matrix output
std::ostream& operator<<(std::ostream& o, const dmat4& m)
{    o << "dmat4(" << std::endl;
    o << m._M[0][0] << ' ';
    o << m._M[0][1] << ' ';
    o << m._M[0][2] << ' ';
    o << m._M[0][3] << std::endl;
    o << m._M[1][0] << ' ';
    o << m._M[1][1] << ' ';
    o << m._M[1][2] << ' ';
    o << m._M[1][3] << std::endl;
    o << m._M[2][0] << ' ';
    o << m._M[2][1] << ' ';
    o << m._M[2][2] << ' ';
    o << m._M[2][3] << std::endl;
    o << m._M[3][0] << ' ';
    o << m._M[3][1] << ' ';
    o << m._M[3][2] << ' ';
    o << m._M[3][3] << std::endl;
    return o;
}


inline mat3 upper3x3(const mat4& m){
    return mat3(
        m[0][0], m[0][1], m[0][2],
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2]);
}


//normalize is only defined for float vectors
vec2 normalize(const vec2& a){
    return 1.0f/length(a) * a;
}

vec3 normalize(const vec3& a){
    return 1.0f/length(a) * a;
}

vec4 normalize(const vec4& a){
    return 1.0f/length(a) * a;
}

dvec2 normalize(const dvec2& a){
    return 1.0f/length(a) * a;
}

dvec3 normalize(const dvec3& a){
    return 1.0f/length(a) * a;
}

dvec4 normalize(const dvec4& a){
    return 1.0f/length(a) * a;
}

mat4 translation(const vec3& t){
    //by jh
    return mat4( 1.0f, 0.0f, 0.0f, 0.0f, 
                 0.0f, 1.0f, 0.0f, 0.0f, 
                 0.0f, 0.0f, 1.0f, 0.0f, 
                 t[0], t[1], t[2], 1.0f);
}

mat4 translation(const AnyScalar& tx, const AnyScalar& ty, const AnyScalar& tz){
    //by jh
    return mat4( 1.0f, 0.0f, 0.0f, 0.0f, 
                 0.0f, 1.0f, 0.0f, 0.0f, 
                 0.0f, 0.0f, 1.0f, 0.0f, 
                 anyScalarToType<float>(tx),   anyScalarToType<float>(ty),   anyScalarToType<float>(tz),   1.0f);
}

mat3 translation2D(const vec2& t){
    //by jh
    return mat3( 1.0f, 0.0f, 0.0f, 
                 0.0f, 1.0f, 0.0f, 
                 t[0],t[1],1.0f);
}

mat3 translation2D(const AnyScalar& tx, const AnyScalar& ty){
    //by jh
    return mat3( 1.0f, 0.0f, 0.0f, 
                 0.0f, 1.0f, 0.0f, 
                 anyScalarToType<float>(tx), anyScalarToType<float>(ty), 1.0f);
}

mat4 scaling( const AnyScalar& sx, const AnyScalar& sy, const AnyScalar& sz ){
    //by jh
     return mat4(
        sx,   0.0f, 0.0f, 0.0f, 
        0.0f, sy,   0.0f, 0.0f, 
        0.0f, 0.0f, sz,   0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 scaling( vec3 s){
    //by jh
    return scaling(s.x,s.y,s.z);
}
  

mat3 scaling3x3( const AnyScalar& sx, const AnyScalar& sy, const AnyScalar& sz ){
    //by jh
    return upper3x3( scaling(sx,sy,sz) );
}

mat3 scaling2D( const AnyScalar&  sx, const AnyScalar& sy){
    //by jh
    return mat3(
        sx, 0.0f, 0.0f,
        0.0f, sy, 0.0f,
        0.0f, 0.0f, 1.0f);
}

//by jh
mat3 scaling2D( vec2 s ){
    return scaling2D(s.x,s.y);
}

mat4 quaternionToMat4(const vec4& q)
{
    //q should be unit quaternion
    float qx=q.x;
    float qy=q.y;
    float qz=q.z;
    float qw=q.w;
    
    float xx=qx*qx;
    float yy=qy*qy;
    float zz=qz*qz;
    float xy=qx*qy;
    float xz=qx*qz;
    float yz=qy*qz;
    float wx=qw*qx;
    float wy=qw*qy;
    float wz=qw*qz;
    
    //ref: Real Time Rendering, 4th ed., pg. 80
    mat4 M= mat4::identity() + 2*mat4(
        -(yy+zz),       xy-wz,      xz+wy,      0,
        xy+wz,          -(xx+zz),   yz-wx,      0,
        xz-wy,          yz+wx,      -(xx+yy),   0,
        0,              0,          0,          0
    );
    return transpose(M);
}

mat4 axisRotation(const vec3& axis, const AnyScalar& angle_)
{
    float angle = anyScalarToType<float>(angle_);
    //concept from Real Time Rendering, 4th ed., pg. 75
    float ax=std::abs(axis[0]);
    float ay=std::abs(axis[1]);
    float az=std::abs(axis[2]);
    vec3 a_;
    if(ax <= ay and ax <= az)
        a_ = vec3(0,-axis.z,axis.y);
    else if (ay <= ax and ay <= az)
        a_ = vec3(-axis.z,0,axis.x);
    else  
        a_ = vec3(-axis.y,axis.x,0); //#az is smallest
    a_ = normalize(a_);
    //cross product: a_ x axis
    vec3 c= vec3(
            a_[1]*axis[2] - axis[1]*a_[2],
            axis[0]*a_[2] - a_[0]*axis[2],
            a_[0]*axis[1] - axis[0]*a_[1]
    );
    c = normalize(c);
    
    //aligns a -> (0,0,1), a' -> (0,1,0), c -> (1,0,0)
    mat4 M = mat4(
        c[0], a_[0], axis[0], 0,
        c[1], a_[1], axis[1], 0,
        c[2], a_[2], axis[2], 0,
        0,0,0,1);
        
    float cs = std::cos(angle);
    float ss = std::sin(angle);
    //use z rotation matrix
    mat4 Rz = mat4(  cs,ss,0,0,
                -ss,cs,0,0,
                0,0,1,0,
                0,0,0,1);
    return M*Rz*transpose(M);
}

mat3 axisRotation3x3(vec3 axis, float angle)
{
    //concept from Real Time Rendering, 4th ed., pg. 75
    float ax=std::abs(axis[0]);
    float ay=std::abs(axis[1]);
    float az=std::abs(axis[2]);
    vec3 a_;
    if (ax <= ay and ax <= az)
        a_ = vec3(0,-axis.z,axis.y);
    else if (ay <= ax and ay <= az)
        a_ = vec3(-axis.z,0,axis.x);
    else
        a_ = vec3(-axis.y,axis.x,0);
    a_ = normalize(a_);
    vec3 c= vec3(
            a_[1]*axis[2] - axis[1]*a_[2],
            axis[0]*a_[2] - a_[0]*axis[2],
            a_[0]*axis[1] - axis[0]*a_[1]
    );
    c=normalize(c);
    //aligns a -> (0,0,1), a' -> (0,1,0), c -> (1,0,0)
    mat3 M = mat3(
        c[0], a_[0], axis[0],
        c[1], a_[1], axis[1],
        c[2], a_[2], axis[2]
    );
        
    float cs = std::cos(angle);
    float ss = std::sin(angle);
    //use z rotation matrix
    mat3 Rz = mat3(  cs,    ss, 0,
                    -ss,    cs, 0,
                    0,      0,  1
    );
    return M*Rz*transpose(M);
}


mat4 axisRotation(const vec4& axis, float angle){
    return axisRotation(axis.xyz(),angle);
}
  
namespace {

template<typename T>
T inverse2(const T& m){
    //Return matrix inverse. From TDL.
    auto d = 1.0f / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
    return T(d * m[1][1], -d * m[0][1], -d * m[1][0], d * m[0][0]);
}

};
   
mat2 inverse(const mat2& m){
    return inverse2(m);
}
  
dmat2 inverse(const dmat2& m){
    return inverse2(m);
}
 
namespace {
template<typename T>
T inverse3(const T& m){
    //Return matrix inverse. From TDL.
    auto t00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    auto t10 = m[0][1] * m[2][2] - m[0][2] * m[2][1];
    auto t20 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    auto d = 1.0f / (m[0][0] * t00 - m[1][0] * t10 + m[2][0] * t20);
    return T( d * t00, -d * t10, d * t20,
          -d * (m[1][0] * m[2][2] - m[1][2] * m[2][0]),
           d * (m[0][0] * m[2][2] - m[0][2] * m[2][0]),
          -d * (m[0][0] * m[1][2] - m[0][2] * m[1][0]),
           d * (m[1][0] * m[2][1] - m[1][1] * m[2][0]),
          -d * (m[0][0] * m[2][1] - m[0][1] * m[2][0]),
           d * (m[0][0] * m[1][1] - m[0][1] * m[1][0]) );
}
};

mat3 inverse(const mat3& m){
    return inverse3(m);
}
  
dmat3 inverse(const dmat3& m){
    return inverse3(m);
}
 
namespace{
template<typename T>
T inverse4(const T& m){
    //Return matrix inverse. From TDL.

    auto tmp_0 = m[2][2] * m[3][3];
    auto tmp_1 = m[3][2] * m[2][3];
    auto tmp_2 = m[1][2] * m[3][3];
    auto tmp_3 = m[3][2] * m[1][3];
    auto tmp_4 = m[1][2] * m[2][3];
    auto tmp_5 = m[2][2] * m[1][3];
    auto tmp_6 = m[0][2] * m[3][3];
    auto tmp_7 = m[3][2] * m[0][3];
    auto tmp_8 = m[0][2] * m[2][3];
    auto tmp_9 = m[2][2] * m[0][3];
    auto tmp_10 = m[0][2] * m[1][3];
    auto tmp_11 = m[1][2] * m[0][3];
    auto tmp_12 = m[2][0] * m[3][1];
    auto tmp_13 = m[3][0] * m[2][1];
    auto tmp_14 = m[1][0] * m[3][1];
    auto tmp_15 = m[3][0] * m[1][1];
    auto tmp_16 = m[1][0] * m[2][1];
    auto tmp_17 = m[2][0] * m[1][1];
    auto tmp_18 = m[0][0] * m[3][1];
    auto tmp_19 = m[3][0] * m[0][1];
    auto tmp_20 = m[0][0] * m[2][1];
    auto tmp_21 = m[2][0] * m[0][1];
    auto tmp_22 = m[0][0] * m[1][1];
    auto tmp_23 = m[1][0] * m[0][1];

    auto t0 = (tmp_0 * m[1][1] + tmp_3 * m[2][1] + tmp_4 * m[3][1]) -        (tmp_1 * m[1][1] + tmp_2 * m[2][1] + tmp_5 * m[3][1]);
    auto t1 = (tmp_1 * m[0][1] + tmp_6 * m[2][1] + tmp_9 * m[3][1]) -        (tmp_0 * m[0][1] + tmp_7 * m[2][1] + tmp_8 * m[3][1]);
    auto t2 = (tmp_2 * m[0][1] + tmp_7 * m[1][1] + tmp_10 * m[3][1]) -        (tmp_3 * m[0][1] + tmp_6 * m[1][1] + tmp_11 * m[3][1]);
    auto t3 = (tmp_5 * m[0][1] + tmp_8 * m[1][1] + tmp_11 * m[2][1]) -        (tmp_4 * m[0][1] + tmp_9 * m[1][1] + tmp_10 * m[2][1]);
    auto d = 1.0f / (m[0][0] * t0 + m[1][0] * t1 + m[2][0] * t2 + m[3][0] * t3);

    return T(d * t0, d * t1, d * t2, d * t3,
       d * ((tmp_1 * m[1][0] + tmp_2 * m[2][0] + tmp_5 * m[3][0]) -
          (tmp_0 * m[1][0] + tmp_3 * m[2][0] + tmp_4 * m[3][0])),
       d * ((tmp_0 * m[0][0] + tmp_7 * m[2][0] + tmp_8 * m[3][0]) -
          (tmp_1 * m[0][0] + tmp_6 * m[2][0] + tmp_9 * m[3][0])),
       d * ((tmp_3 * m[0][0] + tmp_6 * m[1][0] + tmp_11 * m[3][0]) -
          (tmp_2 * m[0][0] + tmp_7 * m[1][0] + tmp_10 * m[3][0])),
       d * ((tmp_4 * m[0][0] + tmp_9 * m[1][0] + tmp_10 * m[2][0]) -
          (tmp_5 * m[0][0] + tmp_8 * m[1][0] + tmp_11 * m[2][0])),
       d * ((tmp_12 * m[1][3] + tmp_15 * m[2][3] + tmp_16 * m[3][3]) -
          (tmp_13 * m[1][3] + tmp_14 * m[2][3] + tmp_17 * m[3][3])),
       d * ((tmp_13 * m[0][3] + tmp_18 * m[2][3] + tmp_21 * m[3][3]) -
          (tmp_12 * m[0][3] + tmp_19 * m[2][3] + tmp_20 * m[3][3])),
       d * ((tmp_14 * m[0][3] + tmp_19 * m[1][3] + tmp_22 * m[3][3]) -
          (tmp_15 * m[0][3] + tmp_18 * m[1][3] + tmp_23 * m[3][3])),
       d * ((tmp_17 * m[0][3] + tmp_20 * m[1][3] + tmp_23 * m[2][3]) -
          (tmp_16 * m[0][3] + tmp_21 * m[1][3] + tmp_22 * m[2][3])),
       d * ((tmp_14 * m[2][2] + tmp_17 * m[3][2] + tmp_13 * m[1][2]) -
          (tmp_16 * m[3][2] + tmp_12 * m[1][2] + tmp_15 * m[2][2])),
       d * ((tmp_20 * m[3][2] + tmp_12 * m[0][2] + tmp_19 * m[2][2]) -
          (tmp_18 * m[2][2] + tmp_21 * m[3][2] + tmp_13 * m[0][2])),
       d * ((tmp_18 * m[1][2] + tmp_23 * m[3][2] + tmp_15 * m[0][2]) -
          (tmp_22 * m[3][2] + tmp_14 * m[0][2] + tmp_19 * m[1][2])),
       d * ((tmp_22 * m[2][2] + tmp_16 * m[0][2] + tmp_21 * m[1][2]) -
          (tmp_20 * m[1][2] + tmp_23 * m[2][2] + tmp_17 * m[0][2])));
}
};

mat4 inverse(const mat4& m){
    return inverse4(m);
}
dmat4 inverse(const dmat4& m){
    return inverse4(m);
}

float radians(double deg){
    return float(deg)/180.0f * 3.14159265358979323f;
}
 
 
namespace {
    const double pi = 4.0 * std::atan(1.0);
    const double PI = 4.0 * std::atan(1.0);
}

float uniform( float min, float max){
    static std::minstd_rand R(12345);   //12345=seed
    std::uniform_real_distribution<float> D(min,max);
    float rv = D(R);
    return rv;
}

float uniform() {
    return uniform(0.0f, 1.0f) ;
}

int randrange( int min, int max){
    static std::minstd_rand R(54321);  //seed
    static std::uniform_real_distribution<float> D(0.0f, 1.0f);
    float t = D(R);
    int rv = (int)( float(min) + t * float(max-min));
    if( rv >= max )
        rv = max-1;
    return rv;
}
    
namespace {
template<typename vecT>
vecT reflect3( vecT incoming, vecT N){
    vecT V = -incoming;
    N = normalize(N);
    vecT Q = dot(V,N)*N;
    vecT A = Q-V;
    return V+A+A;
}
};

vec3 reflect(vec3 incoming, vec3 N){
    return reflect3(incoming,N);
}
dvec3 reflect(dvec3 incoming, dvec3 N){
    return reflect3(incoming,N);
}
 

static_assert(sizeof(vec2) == 8, "");
static_assert(sizeof(vec3) == 12, "");
static_assert(sizeof(vec4) == 16, "");
static_assert(sizeof(ivec2) == 8, "");
static_assert(sizeof(ivec3) == 12, "");
static_assert(sizeof(ivec4) == 16, "");
static_assert(sizeof(uvec2) == 8, "");
static_assert(sizeof(uvec3) == 12, "");
static_assert(sizeof(uvec4) == 16, "");
static_assert(sizeof(mat2) == 32, "");
static_assert(sizeof(mat3) == 48, "");
static_assert(sizeof(mat4) == 64, "");
static_assert(sizeof(dmat4) == 128, "");

};  //end namespace math2801

//re-enable disabled warnings
#ifdef _MSC_VER
#pragma warning(pop)
#endif
