
#pragma once

// Generated from mk.py

//jh ssu fall 2019, fall 2020, fall 2022

#include <iostream>
#include <string>
#include <vector>
#include <variant>

namespace math2801 {

static const float pi = 3.14159265358979323f;

/// Any scalar type: float, double, int, unsigned
typedef std::variant<float,double,std::int32_t,std::uint32_t> AnyScalar;

class  vec2;
class uvec2;
class ivec2;
class dvec2;
class  vec3;
class uvec3;
class ivec3;
class dvec3;
class  vec4;
class uvec4;
class ivec4;
class dvec4;
class  mat2;
class dmat2;
class  mat3;
class dmat3;
class  mat4;
class dmat4;

/// A 2-dimensional vector with float components
class vec2 {
  public:
    float x;   ///< The x component
    float y;   ///< The y component
    /// Default constructor: Initialize to 0's
    vec2();
    /// Casting constructor
    /// @param v The vector to cast
    vec2(const vec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec2(const uvec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec2(const ivec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec2(const dvec2& v);
    /// @param x_,y_ Vector components
    vec2(const AnyScalar& x_, const AnyScalar& y_);
    //no vec-scalar constructor for 2d vector
    /// Initialize vec2's x,y to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit vec2(const AnyScalar& v);
    /// Get item from vec2
    /// @param idx Index (0...1)
    /// @return The vec2's x,y value
    float operator[](unsigned idx) const;
    /// Get item from vec2
    /// @param idx Index (0...1)
    /// @return The vec2's x,y value
    float operator[](int idx) const;
    /// Get item from vec2
    /// @param idx Index (0...1)
    /// @return The vec2's x,y value
    float& operator[](unsigned idx);
    /// Get item from vec2
    /// @param idx Index (0...1)
    /// @return The vec2's x,y value
    float& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const vec2& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const vec2& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const vec2& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const vec2& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const vec2& o);
    /// In-place multiplication operation: Computes vec2 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes vec2 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the vec2
    operator std::string() const;
    /// Vector size: Always returns 2.
    /// @return 2
    unsigned size() const;
    /// Return slice of a vec2
    /// @return The x,y components as a vec2
    vec2 xy() const;
};
/// Componentwise Addition operation
/// @param arg1 First vec2
/// @param arg2 Second vec2
/// @return arg1 + arg2
vec2 operator+(const vec2& arg1, const vec2& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First vec2
/// @param arg2 Second vec2
/// @return arg1 - arg2
vec2 operator-(const vec2& arg1, const vec2& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First vec2
/// @param arg2 Second vec2
/// @return arg1 * arg2
vec2 operator*(const vec2& arg1, const vec2& arg2);
/// Componentwise Division operation
/// @param arg1 First vec2
/// @param arg2 Second vec2
/// @return arg1 / arg2
vec2 operator/(const vec2& arg1, const vec2& arg2);
/// Compute vector multiplied by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v * s
vec2 operator*( const vec2& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec2
/// @return s * v
vec2 operator*( float s, const vec2& v  );
/// Compute vector divided by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v / s
vec2 operator/( const vec2& v, float s);
/// Compute vector multiplied by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v * s
vec2 operator*( const vec2& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec2
/// @return s * v
vec2 operator*( double s, const vec2& v  );
/// Compute vector divided by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v / s
vec2 operator/( const vec2& v, double s);
/// Compute vector multiplied by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v * s
vec2 operator*( const vec2& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec2
/// @return s * v
vec2 operator*( std::int32_t s, const vec2& v  );
/// Compute vector divided by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v / s
vec2 operator/( const vec2& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v * s
vec2 operator*( const vec2& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec2
/// @return s * v
vec2 operator*( std::uint32_t s, const vec2& v  );
/// Compute vector divided by scalar
/// @param v The vec2
/// @param s The scalar
/// @return v / s
vec2 operator/( const vec2& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y.
bool operator<(const vec2& v1, const vec2& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y.
bool operator>(const vec2& v1, const vec2& v2);
/// vec2 < operator.
/// @param v1 The first vec2
/// @param v2 The second vec2
/// @return true if v1<v2; false otherwise
bool operator<=(const vec2& v1, const vec2& v2);
/// vec2 > operator.
/// @param v1 The first vec2
/// @param v2 The second vec2
/// @return true if v1>v2; false otherwise
bool operator>=(const vec2& v1, const vec2& v2);
/// vec2 equality operator.
/// @param v1 The first vec2
/// @param v2 The second vec2
/// @return true if v1==v2; false otherwise
bool operator==(const vec2& v1, const vec2& v2);
/// vec2 inequality operator.
/// @param v1 The first vec2
/// @param v2 The second vec2
/// @return true if v1!=v2; false otherwise
bool operator!=(const vec2& v1, const vec2& v2);
/// vec2 negation
/// @param v The vec2 to negate
/// @return The negated vec2
vec2 operator-(const vec2& v);
/// Unary plus: This is basically a no-op.
/// @param v The vec2.
/// @return The vec2.
vec2 operator+(const vec2& v);
/// Vector dot product
/// @param v1 First vec2
/// @param v2 Second vec2
/// @return v1 (dot) v2
float dot(const vec2& v1, const vec2& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const vec2& v);
/// Stream extractor for outputting vec2.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const vec2& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First vec2
/// @param v2 Second vec2
/// @return vec2 where each component is the min of the corresponding components of v1 and v2
vec2 min(const vec2& v1, const vec2& v2);
/// Vector max operation (componentwise).
/// @param v1 First vec2
/// @param v2 Second vec2
/// @return vec2 where each component is the max of the corresponding components of v1 and v2
vec2 max(const vec2& v1, const vec2& v2);

/// A 2-dimensional vector with std::uint32_t components
class uvec2 {
  public:
    std::uint32_t x;   ///< The x component
    std::uint32_t y;   ///< The y component
    /// Default constructor: Initialize to 0's
    uvec2();
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec2(const vec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    uvec2(const uvec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec2(const ivec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec2(const dvec2& v);
    /// @param x_,y_ Vector components
    uvec2(const AnyScalar& x_, const AnyScalar& y_);
    //no vec-scalar constructor for 2d vector
    /// Initialize uvec2's x,y to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit uvec2(const AnyScalar& v);
    /// Get item from uvec2
    /// @param idx Index (0...1)
    /// @return The uvec2's x,y value
    std::uint32_t operator[](unsigned idx) const;
    /// Get item from uvec2
    /// @param idx Index (0...1)
    /// @return The uvec2's x,y value
    std::uint32_t operator[](int idx) const;
    /// Get item from uvec2
    /// @param idx Index (0...1)
    /// @return The uvec2's x,y value
    std::uint32_t& operator[](unsigned idx);
    /// Get item from uvec2
    /// @param idx Index (0...1)
    /// @return The uvec2's x,y value
    std::uint32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const uvec2& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const uvec2& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const uvec2& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const uvec2& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const uvec2& o);
    /// In-place multiplication operation: Computes uvec2 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes uvec2 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the uvec2
    operator std::string() const;
    /// Vector size: Always returns 2.
    /// @return 2
    unsigned size() const;
    /// Return slice of a uvec2
    /// @return The x,y components as a uvec2
    uvec2 xy() const;
};
/// Componentwise Addition operation
/// @param arg1 First uvec2
/// @param arg2 Second uvec2
/// @return arg1 + arg2
uvec2 operator+(const uvec2& arg1, const uvec2& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First uvec2
/// @param arg2 Second uvec2
/// @return arg1 - arg2
uvec2 operator-(const uvec2& arg1, const uvec2& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First uvec2
/// @param arg2 Second uvec2
/// @return arg1 * arg2
uvec2 operator*(const uvec2& arg1, const uvec2& arg2);
/// Componentwise Division operation
/// @param arg1 First uvec2
/// @param arg2 Second uvec2
/// @return arg1 / arg2
uvec2 operator/(const uvec2& arg1, const uvec2& arg2);
/// Compute vector multiplied by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v * s
uvec2 operator*( const uvec2& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec2
/// @return s * v
uvec2 operator*( float s, const uvec2& v  );
/// Compute vector divided by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v / s
uvec2 operator/( const uvec2& v, float s);
/// Compute vector multiplied by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v * s
uvec2 operator*( const uvec2& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec2
/// @return s * v
uvec2 operator*( double s, const uvec2& v  );
/// Compute vector divided by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v / s
uvec2 operator/( const uvec2& v, double s);
/// Compute vector multiplied by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v * s
uvec2 operator*( const uvec2& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec2
/// @return s * v
uvec2 operator*( std::int32_t s, const uvec2& v  );
/// Compute vector divided by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v / s
uvec2 operator/( const uvec2& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v * s
uvec2 operator*( const uvec2& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec2
/// @return s * v
uvec2 operator*( std::uint32_t s, const uvec2& v  );
/// Compute vector divided by scalar
/// @param v The uvec2
/// @param s The scalar
/// @return v / s
uvec2 operator/( const uvec2& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y.
bool operator<(const uvec2& v1, const uvec2& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y.
bool operator>(const uvec2& v1, const uvec2& v2);
/// uvec2 < operator.
/// @param v1 The first uvec2
/// @param v2 The second uvec2
/// @return true if v1<v2; false otherwise
bool operator<=(const uvec2& v1, const uvec2& v2);
/// uvec2 > operator.
/// @param v1 The first uvec2
/// @param v2 The second uvec2
/// @return true if v1>v2; false otherwise
bool operator>=(const uvec2& v1, const uvec2& v2);
/// uvec2 equality operator.
/// @param v1 The first uvec2
/// @param v2 The second uvec2
/// @return true if v1==v2; false otherwise
bool operator==(const uvec2& v1, const uvec2& v2);
/// uvec2 inequality operator.
/// @param v1 The first uvec2
/// @param v2 The second uvec2
/// @return true if v1!=v2; false otherwise
bool operator!=(const uvec2& v1, const uvec2& v2);
//no negation for unsigned vec type
/// Unary plus: This is basically a no-op.
/// @param v The uvec2.
/// @return The uvec2.
uvec2 operator+(const uvec2& v);
/// Vector dot product
/// @param v1 First uvec2
/// @param v2 Second uvec2
/// @return v1 (dot) v2
std::uint32_t dot(const uvec2& v1, const uvec2& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const uvec2& v);
/// Stream extractor for outputting uvec2.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const uvec2& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First uvec2
/// @param v2 Second uvec2
/// @return uvec2 where each component is the min of the corresponding components of v1 and v2
uvec2 min(const uvec2& v1, const uvec2& v2);
/// Vector max operation (componentwise).
/// @param v1 First uvec2
/// @param v2 Second uvec2
/// @return uvec2 where each component is the max of the corresponding components of v1 and v2
uvec2 max(const uvec2& v1, const uvec2& v2);

/// A 2-dimensional vector with std::int32_t components
class ivec2 {
  public:
    std::int32_t x;   ///< The x component
    std::int32_t y;   ///< The y component
    /// Default constructor: Initialize to 0's
    ivec2();
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec2(const vec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec2(const uvec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    ivec2(const ivec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec2(const dvec2& v);
    /// @param x_,y_ Vector components
    ivec2(const AnyScalar& x_, const AnyScalar& y_);
    //no vec-scalar constructor for 2d vector
    /// Initialize ivec2's x,y to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit ivec2(const AnyScalar& v);
    /// Get item from ivec2
    /// @param idx Index (0...1)
    /// @return The ivec2's x,y value
    std::int32_t operator[](unsigned idx) const;
    /// Get item from ivec2
    /// @param idx Index (0...1)
    /// @return The ivec2's x,y value
    std::int32_t operator[](int idx) const;
    /// Get item from ivec2
    /// @param idx Index (0...1)
    /// @return The ivec2's x,y value
    std::int32_t& operator[](unsigned idx);
    /// Get item from ivec2
    /// @param idx Index (0...1)
    /// @return The ivec2's x,y value
    std::int32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const ivec2& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const ivec2& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const ivec2& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const ivec2& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const ivec2& o);
    /// In-place multiplication operation: Computes ivec2 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes ivec2 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the ivec2
    operator std::string() const;
    /// Vector size: Always returns 2.
    /// @return 2
    unsigned size() const;
    /// Return slice of a ivec2
    /// @return The x,y components as a ivec2
    ivec2 xy() const;
};
/// Componentwise Addition operation
/// @param arg1 First ivec2
/// @param arg2 Second ivec2
/// @return arg1 + arg2
ivec2 operator+(const ivec2& arg1, const ivec2& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First ivec2
/// @param arg2 Second ivec2
/// @return arg1 - arg2
ivec2 operator-(const ivec2& arg1, const ivec2& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First ivec2
/// @param arg2 Second ivec2
/// @return arg1 * arg2
ivec2 operator*(const ivec2& arg1, const ivec2& arg2);
/// Componentwise Division operation
/// @param arg1 First ivec2
/// @param arg2 Second ivec2
/// @return arg1 / arg2
ivec2 operator/(const ivec2& arg1, const ivec2& arg2);
/// Compute vector multiplied by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v * s
ivec2 operator*( const ivec2& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec2
/// @return s * v
ivec2 operator*( float s, const ivec2& v  );
/// Compute vector divided by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v / s
ivec2 operator/( const ivec2& v, float s);
/// Compute vector multiplied by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v * s
ivec2 operator*( const ivec2& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec2
/// @return s * v
ivec2 operator*( double s, const ivec2& v  );
/// Compute vector divided by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v / s
ivec2 operator/( const ivec2& v, double s);
/// Compute vector multiplied by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v * s
ivec2 operator*( const ivec2& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec2
/// @return s * v
ivec2 operator*( std::int32_t s, const ivec2& v  );
/// Compute vector divided by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v / s
ivec2 operator/( const ivec2& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v * s
ivec2 operator*( const ivec2& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec2
/// @return s * v
ivec2 operator*( std::uint32_t s, const ivec2& v  );
/// Compute vector divided by scalar
/// @param v The ivec2
/// @param s The scalar
/// @return v / s
ivec2 operator/( const ivec2& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y.
bool operator<(const ivec2& v1, const ivec2& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y.
bool operator>(const ivec2& v1, const ivec2& v2);
/// ivec2 < operator.
/// @param v1 The first ivec2
/// @param v2 The second ivec2
/// @return true if v1<v2; false otherwise
bool operator<=(const ivec2& v1, const ivec2& v2);
/// ivec2 > operator.
/// @param v1 The first ivec2
/// @param v2 The second ivec2
/// @return true if v1>v2; false otherwise
bool operator>=(const ivec2& v1, const ivec2& v2);
/// ivec2 equality operator.
/// @param v1 The first ivec2
/// @param v2 The second ivec2
/// @return true if v1==v2; false otherwise
bool operator==(const ivec2& v1, const ivec2& v2);
/// ivec2 inequality operator.
/// @param v1 The first ivec2
/// @param v2 The second ivec2
/// @return true if v1!=v2; false otherwise
bool operator!=(const ivec2& v1, const ivec2& v2);
/// ivec2 negation
/// @param v The ivec2 to negate
/// @return The negated ivec2
ivec2 operator-(const ivec2& v);
/// Unary plus: This is basically a no-op.
/// @param v The ivec2.
/// @return The ivec2.
ivec2 operator+(const ivec2& v);
/// Vector dot product
/// @param v1 First ivec2
/// @param v2 Second ivec2
/// @return v1 (dot) v2
std::int32_t dot(const ivec2& v1, const ivec2& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const ivec2& v);
/// Stream extractor for outputting ivec2.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const ivec2& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First ivec2
/// @param v2 Second ivec2
/// @return ivec2 where each component is the min of the corresponding components of v1 and v2
ivec2 min(const ivec2& v1, const ivec2& v2);
/// Vector max operation (componentwise).
/// @param v1 First ivec2
/// @param v2 Second ivec2
/// @return ivec2 where each component is the max of the corresponding components of v1 and v2
ivec2 max(const ivec2& v1, const ivec2& v2);

/// A 2-dimensional vector with double components
class dvec2 {
  public:
    double x;   ///< The x component
    double y;   ///< The y component
    /// Default constructor: Initialize to 0's
    dvec2();
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec2(const vec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec2(const uvec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec2(const ivec2& v);
    /// Casting constructor
    /// @param v The vector to cast
    dvec2(const dvec2& v);
    /// @param x_,y_ Vector components
    dvec2(const AnyScalar& x_, const AnyScalar& y_);
    //no vec-scalar constructor for 2d vector
    /// Initialize dvec2's x,y to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit dvec2(const AnyScalar& v);
    /// Get item from dvec2
    /// @param idx Index (0...1)
    /// @return The dvec2's x,y value
    double operator[](unsigned idx) const;
    /// Get item from dvec2
    /// @param idx Index (0...1)
    /// @return The dvec2's x,y value
    double operator[](int idx) const;
    /// Get item from dvec2
    /// @param idx Index (0...1)
    /// @return The dvec2's x,y value
    double& operator[](unsigned idx);
    /// Get item from dvec2
    /// @param idx Index (0...1)
    /// @return The dvec2's x,y value
    double& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const dvec2& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const dvec2& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const dvec2& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const dvec2& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const dvec2& o);
    /// In-place multiplication operation: Computes dvec2 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes dvec2 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the dvec2
    operator std::string() const;
    /// Vector size: Always returns 2.
    /// @return 2
    unsigned size() const;
    /// Return slice of a dvec2
    /// @return The x,y components as a dvec2
    dvec2 xy() const;
};
/// Componentwise Addition operation
/// @param arg1 First dvec2
/// @param arg2 Second dvec2
/// @return arg1 + arg2
dvec2 operator+(const dvec2& arg1, const dvec2& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First dvec2
/// @param arg2 Second dvec2
/// @return arg1 - arg2
dvec2 operator-(const dvec2& arg1, const dvec2& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First dvec2
/// @param arg2 Second dvec2
/// @return arg1 * arg2
dvec2 operator*(const dvec2& arg1, const dvec2& arg2);
/// Componentwise Division operation
/// @param arg1 First dvec2
/// @param arg2 Second dvec2
/// @return arg1 / arg2
dvec2 operator/(const dvec2& arg1, const dvec2& arg2);
/// Compute vector multiplied by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v * s
dvec2 operator*( const dvec2& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec2
/// @return s * v
dvec2 operator*( float s, const dvec2& v  );
/// Compute vector divided by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v / s
dvec2 operator/( const dvec2& v, float s);
/// Compute vector multiplied by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v * s
dvec2 operator*( const dvec2& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec2
/// @return s * v
dvec2 operator*( double s, const dvec2& v  );
/// Compute vector divided by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v / s
dvec2 operator/( const dvec2& v, double s);
/// Compute vector multiplied by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v * s
dvec2 operator*( const dvec2& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec2
/// @return s * v
dvec2 operator*( std::int32_t s, const dvec2& v  );
/// Compute vector divided by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v / s
dvec2 operator/( const dvec2& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v * s
dvec2 operator*( const dvec2& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec2
/// @return s * v
dvec2 operator*( std::uint32_t s, const dvec2& v  );
/// Compute vector divided by scalar
/// @param v The dvec2
/// @param s The scalar
/// @return v / s
dvec2 operator/( const dvec2& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y.
bool operator<(const dvec2& v1, const dvec2& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y.
bool operator>(const dvec2& v1, const dvec2& v2);
/// dvec2 < operator.
/// @param v1 The first dvec2
/// @param v2 The second dvec2
/// @return true if v1<v2; false otherwise
bool operator<=(const dvec2& v1, const dvec2& v2);
/// dvec2 > operator.
/// @param v1 The first dvec2
/// @param v2 The second dvec2
/// @return true if v1>v2; false otherwise
bool operator>=(const dvec2& v1, const dvec2& v2);
/// dvec2 equality operator.
/// @param v1 The first dvec2
/// @param v2 The second dvec2
/// @return true if v1==v2; false otherwise
bool operator==(const dvec2& v1, const dvec2& v2);
/// dvec2 inequality operator.
/// @param v1 The first dvec2
/// @param v2 The second dvec2
/// @return true if v1!=v2; false otherwise
bool operator!=(const dvec2& v1, const dvec2& v2);
/// dvec2 negation
/// @param v The dvec2 to negate
/// @return The negated dvec2
dvec2 operator-(const dvec2& v);
/// Unary plus: This is basically a no-op.
/// @param v The dvec2.
/// @return The dvec2.
dvec2 operator+(const dvec2& v);
/// Vector dot product
/// @param v1 First dvec2
/// @param v2 Second dvec2
/// @return v1 (dot) v2
double dot(const dvec2& v1, const dvec2& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const dvec2& v);
/// Stream extractor for outputting dvec2.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const dvec2& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First dvec2
/// @param v2 Second dvec2
/// @return dvec2 where each component is the min of the corresponding components of v1 and v2
dvec2 min(const dvec2& v1, const dvec2& v2);
/// Vector max operation (componentwise).
/// @param v1 First dvec2
/// @param v2 Second dvec2
/// @return dvec2 where each component is the max of the corresponding components of v1 and v2
dvec2 max(const dvec2& v1, const dvec2& v2);

/// A 3-dimensional vector with float components
class vec3 {
  public:
    float x;   ///< The x component
    float y;   ///< The y component
    float z;   ///< The z component
    /// Default constructor: Initialize to 0's
    vec3();
    /// Casting constructor
    /// @param v The vector to cast
    vec3(const vec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec3(const uvec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec3(const ivec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec3(const dvec3& v);
    /// @param x_,y_,z_ Vector components
    vec3(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_);
    /// Create vec3
    /// @param v xy components of vec3
    /// @param z_ z_ component of vec3
    vec3(const vec2& v, const AnyScalar& z_);
    /// Initialize vec3's x,y,z to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit vec3(const AnyScalar& v);
    /// Get item from vec3
    /// @param idx Index (0...2)
    /// @return The vec3's x,y,z value
    float operator[](unsigned idx) const;
    /// Get item from vec3
    /// @param idx Index (0...2)
    /// @return The vec3's x,y,z value
    float operator[](int idx) const;
    /// Get item from vec3
    /// @param idx Index (0...2)
    /// @return The vec3's x,y,z value
    float& operator[](unsigned idx);
    /// Get item from vec3
    /// @param idx Index (0...2)
    /// @return The vec3's x,y,z value
    float& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const vec3& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const vec3& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const vec3& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const vec3& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const vec3& o);
    /// In-place multiplication operation: Computes vec3 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes vec3 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the vec3
    operator std::string() const;
    /// Vector size: Always returns 3.
    /// @return 3
    unsigned size() const;
    /// Return slice of a vec3
    /// @return The x,y components as a vec2
    vec2 xy() const;
    /// Return slice of a vec3
    /// @return The x,y,z components as a vec3
    vec3 xyz() const;
};
/// Componentwise Addition operation
/// @param arg1 First vec3
/// @param arg2 Second vec3
/// @return arg1 + arg2
vec3 operator+(const vec3& arg1, const vec3& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First vec3
/// @param arg2 Second vec3
/// @return arg1 - arg2
vec3 operator-(const vec3& arg1, const vec3& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First vec3
/// @param arg2 Second vec3
/// @return arg1 * arg2
vec3 operator*(const vec3& arg1, const vec3& arg2);
/// Componentwise Division operation
/// @param arg1 First vec3
/// @param arg2 Second vec3
/// @return arg1 / arg2
vec3 operator/(const vec3& arg1, const vec3& arg2);
/// Compute vector multiplied by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v * s
vec3 operator*( const vec3& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec3
/// @return s * v
vec3 operator*( float s, const vec3& v  );
/// Compute vector divided by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v / s
vec3 operator/( const vec3& v, float s);
/// Compute vector multiplied by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v * s
vec3 operator*( const vec3& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec3
/// @return s * v
vec3 operator*( double s, const vec3& v  );
/// Compute vector divided by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v / s
vec3 operator/( const vec3& v, double s);
/// Compute vector multiplied by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v * s
vec3 operator*( const vec3& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec3
/// @return s * v
vec3 operator*( std::int32_t s, const vec3& v  );
/// Compute vector divided by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v / s
vec3 operator/( const vec3& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v * s
vec3 operator*( const vec3& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec3
/// @return s * v
vec3 operator*( std::uint32_t s, const vec3& v  );
/// Compute vector divided by scalar
/// @param v The vec3
/// @param s The scalar
/// @return v / s
vec3 operator/( const vec3& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z.
bool operator<(const vec3& v1, const vec3& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z.
bool operator>(const vec3& v1, const vec3& v2);
/// vec3 < operator.
/// @param v1 The first vec3
/// @param v2 The second vec3
/// @return true if v1<v2; false otherwise
bool operator<=(const vec3& v1, const vec3& v2);
/// vec3 > operator.
/// @param v1 The first vec3
/// @param v2 The second vec3
/// @return true if v1>v2; false otherwise
bool operator>=(const vec3& v1, const vec3& v2);
/// vec3 equality operator.
/// @param v1 The first vec3
/// @param v2 The second vec3
/// @return true if v1==v2; false otherwise
bool operator==(const vec3& v1, const vec3& v2);
/// vec3 inequality operator.
/// @param v1 The first vec3
/// @param v2 The second vec3
/// @return true if v1!=v2; false otherwise
bool operator!=(const vec3& v1, const vec3& v2);
/// vec3 negation
/// @param v The vec3 to negate
/// @return The negated vec3
vec3 operator-(const vec3& v);
/// Unary plus: This is basically a no-op.
/// @param v The vec3.
/// @return The vec3.
vec3 operator+(const vec3& v);
/// Vector dot product
/// @param v1 First vec3
/// @param v2 Second vec3
/// @return v1 (dot) v2
float dot(const vec3& v1, const vec3& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const vec3& v);
/// Stream extractor for outputting vec3.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const vec3& v);
/// vec3 cross product.
/// @param v First vec3
/// @param w Second vec3
/// @return v x w
vec3 cross(const vec3& v, const vec3& w);
/// Vector min operation (componentwise).
/// @param v1 First vec3
/// @param v2 Second vec3
/// @return vec3 where each component is the min of the corresponding components of v1 and v2
vec3 min(const vec3& v1, const vec3& v2);
/// Vector max operation (componentwise).
/// @param v1 First vec3
/// @param v2 Second vec3
/// @return vec3 where each component is the max of the corresponding components of v1 and v2
vec3 max(const vec3& v1, const vec3& v2);

/// A 3-dimensional vector with std::uint32_t components
class uvec3 {
  public:
    std::uint32_t x;   ///< The x component
    std::uint32_t y;   ///< The y component
    std::uint32_t z;   ///< The z component
    /// Default constructor: Initialize to 0's
    uvec3();
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec3(const vec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    uvec3(const uvec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec3(const ivec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec3(const dvec3& v);
    /// @param x_,y_,z_ Vector components
    uvec3(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_);
    /// Create uvec3
    /// @param v xy components of uvec3
    /// @param z_ z_ component of uvec3
    uvec3(const uvec2& v, const AnyScalar& z_);
    /// Initialize uvec3's x,y,z to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit uvec3(const AnyScalar& v);
    /// Get item from uvec3
    /// @param idx Index (0...2)
    /// @return The uvec3's x,y,z value
    std::uint32_t operator[](unsigned idx) const;
    /// Get item from uvec3
    /// @param idx Index (0...2)
    /// @return The uvec3's x,y,z value
    std::uint32_t operator[](int idx) const;
    /// Get item from uvec3
    /// @param idx Index (0...2)
    /// @return The uvec3's x,y,z value
    std::uint32_t& operator[](unsigned idx);
    /// Get item from uvec3
    /// @param idx Index (0...2)
    /// @return The uvec3's x,y,z value
    std::uint32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const uvec3& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const uvec3& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const uvec3& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const uvec3& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const uvec3& o);
    /// In-place multiplication operation: Computes uvec3 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes uvec3 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the uvec3
    operator std::string() const;
    /// Vector size: Always returns 3.
    /// @return 3
    unsigned size() const;
    /// Return slice of a uvec3
    /// @return The x,y components as a uvec2
    uvec2 xy() const;
    /// Return slice of a uvec3
    /// @return The x,y,z components as a uvec3
    uvec3 xyz() const;
};
/// Componentwise Addition operation
/// @param arg1 First uvec3
/// @param arg2 Second uvec3
/// @return arg1 + arg2
uvec3 operator+(const uvec3& arg1, const uvec3& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First uvec3
/// @param arg2 Second uvec3
/// @return arg1 - arg2
uvec3 operator-(const uvec3& arg1, const uvec3& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First uvec3
/// @param arg2 Second uvec3
/// @return arg1 * arg2
uvec3 operator*(const uvec3& arg1, const uvec3& arg2);
/// Componentwise Division operation
/// @param arg1 First uvec3
/// @param arg2 Second uvec3
/// @return arg1 / arg2
uvec3 operator/(const uvec3& arg1, const uvec3& arg2);
/// Compute vector multiplied by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v * s
uvec3 operator*( const uvec3& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec3
/// @return s * v
uvec3 operator*( float s, const uvec3& v  );
/// Compute vector divided by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v / s
uvec3 operator/( const uvec3& v, float s);
/// Compute vector multiplied by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v * s
uvec3 operator*( const uvec3& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec3
/// @return s * v
uvec3 operator*( double s, const uvec3& v  );
/// Compute vector divided by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v / s
uvec3 operator/( const uvec3& v, double s);
/// Compute vector multiplied by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v * s
uvec3 operator*( const uvec3& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec3
/// @return s * v
uvec3 operator*( std::int32_t s, const uvec3& v  );
/// Compute vector divided by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v / s
uvec3 operator/( const uvec3& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v * s
uvec3 operator*( const uvec3& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec3
/// @return s * v
uvec3 operator*( std::uint32_t s, const uvec3& v  );
/// Compute vector divided by scalar
/// @param v The uvec3
/// @param s The scalar
/// @return v / s
uvec3 operator/( const uvec3& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z.
bool operator<(const uvec3& v1, const uvec3& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z.
bool operator>(const uvec3& v1, const uvec3& v2);
/// uvec3 < operator.
/// @param v1 The first uvec3
/// @param v2 The second uvec3
/// @return true if v1<v2; false otherwise
bool operator<=(const uvec3& v1, const uvec3& v2);
/// uvec3 > operator.
/// @param v1 The first uvec3
/// @param v2 The second uvec3
/// @return true if v1>v2; false otherwise
bool operator>=(const uvec3& v1, const uvec3& v2);
/// uvec3 equality operator.
/// @param v1 The first uvec3
/// @param v2 The second uvec3
/// @return true if v1==v2; false otherwise
bool operator==(const uvec3& v1, const uvec3& v2);
/// uvec3 inequality operator.
/// @param v1 The first uvec3
/// @param v2 The second uvec3
/// @return true if v1!=v2; false otherwise
bool operator!=(const uvec3& v1, const uvec3& v2);
//no negation for unsigned vec type
/// Unary plus: This is basically a no-op.
/// @param v The uvec3.
/// @return The uvec3.
uvec3 operator+(const uvec3& v);
/// Vector dot product
/// @param v1 First uvec3
/// @param v2 Second uvec3
/// @return v1 (dot) v2
std::uint32_t dot(const uvec3& v1, const uvec3& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const uvec3& v);
/// Stream extractor for outputting uvec3.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const uvec3& v);
/// uvec3 cross product.
/// @param v First uvec3
/// @param w Second uvec3
/// @return v x w
uvec3 cross(const uvec3& v, const uvec3& w);
/// Vector min operation (componentwise).
/// @param v1 First uvec3
/// @param v2 Second uvec3
/// @return uvec3 where each component is the min of the corresponding components of v1 and v2
uvec3 min(const uvec3& v1, const uvec3& v2);
/// Vector max operation (componentwise).
/// @param v1 First uvec3
/// @param v2 Second uvec3
/// @return uvec3 where each component is the max of the corresponding components of v1 and v2
uvec3 max(const uvec3& v1, const uvec3& v2);

/// A 3-dimensional vector with std::int32_t components
class ivec3 {
  public:
    std::int32_t x;   ///< The x component
    std::int32_t y;   ///< The y component
    std::int32_t z;   ///< The z component
    /// Default constructor: Initialize to 0's
    ivec3();
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec3(const vec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec3(const uvec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    ivec3(const ivec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec3(const dvec3& v);
    /// @param x_,y_,z_ Vector components
    ivec3(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_);
    /// Create ivec3
    /// @param v xy components of ivec3
    /// @param z_ z_ component of ivec3
    ivec3(const ivec2& v, const AnyScalar& z_);
    /// Initialize ivec3's x,y,z to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit ivec3(const AnyScalar& v);
    /// Get item from ivec3
    /// @param idx Index (0...2)
    /// @return The ivec3's x,y,z value
    std::int32_t operator[](unsigned idx) const;
    /// Get item from ivec3
    /// @param idx Index (0...2)
    /// @return The ivec3's x,y,z value
    std::int32_t operator[](int idx) const;
    /// Get item from ivec3
    /// @param idx Index (0...2)
    /// @return The ivec3's x,y,z value
    std::int32_t& operator[](unsigned idx);
    /// Get item from ivec3
    /// @param idx Index (0...2)
    /// @return The ivec3's x,y,z value
    std::int32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const ivec3& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const ivec3& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const ivec3& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const ivec3& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const ivec3& o);
    /// In-place multiplication operation: Computes ivec3 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes ivec3 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the ivec3
    operator std::string() const;
    /// Vector size: Always returns 3.
    /// @return 3
    unsigned size() const;
    /// Return slice of a ivec3
    /// @return The x,y components as a ivec2
    ivec2 xy() const;
    /// Return slice of a ivec3
    /// @return The x,y,z components as a ivec3
    ivec3 xyz() const;
};
/// Componentwise Addition operation
/// @param arg1 First ivec3
/// @param arg2 Second ivec3
/// @return arg1 + arg2
ivec3 operator+(const ivec3& arg1, const ivec3& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First ivec3
/// @param arg2 Second ivec3
/// @return arg1 - arg2
ivec3 operator-(const ivec3& arg1, const ivec3& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First ivec3
/// @param arg2 Second ivec3
/// @return arg1 * arg2
ivec3 operator*(const ivec3& arg1, const ivec3& arg2);
/// Componentwise Division operation
/// @param arg1 First ivec3
/// @param arg2 Second ivec3
/// @return arg1 / arg2
ivec3 operator/(const ivec3& arg1, const ivec3& arg2);
/// Compute vector multiplied by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v * s
ivec3 operator*( const ivec3& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec3
/// @return s * v
ivec3 operator*( float s, const ivec3& v  );
/// Compute vector divided by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v / s
ivec3 operator/( const ivec3& v, float s);
/// Compute vector multiplied by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v * s
ivec3 operator*( const ivec3& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec3
/// @return s * v
ivec3 operator*( double s, const ivec3& v  );
/// Compute vector divided by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v / s
ivec3 operator/( const ivec3& v, double s);
/// Compute vector multiplied by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v * s
ivec3 operator*( const ivec3& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec3
/// @return s * v
ivec3 operator*( std::int32_t s, const ivec3& v  );
/// Compute vector divided by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v / s
ivec3 operator/( const ivec3& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v * s
ivec3 operator*( const ivec3& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec3
/// @return s * v
ivec3 operator*( std::uint32_t s, const ivec3& v  );
/// Compute vector divided by scalar
/// @param v The ivec3
/// @param s The scalar
/// @return v / s
ivec3 operator/( const ivec3& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z.
bool operator<(const ivec3& v1, const ivec3& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z.
bool operator>(const ivec3& v1, const ivec3& v2);
/// ivec3 < operator.
/// @param v1 The first ivec3
/// @param v2 The second ivec3
/// @return true if v1<v2; false otherwise
bool operator<=(const ivec3& v1, const ivec3& v2);
/// ivec3 > operator.
/// @param v1 The first ivec3
/// @param v2 The second ivec3
/// @return true if v1>v2; false otherwise
bool operator>=(const ivec3& v1, const ivec3& v2);
/// ivec3 equality operator.
/// @param v1 The first ivec3
/// @param v2 The second ivec3
/// @return true if v1==v2; false otherwise
bool operator==(const ivec3& v1, const ivec3& v2);
/// ivec3 inequality operator.
/// @param v1 The first ivec3
/// @param v2 The second ivec3
/// @return true if v1!=v2; false otherwise
bool operator!=(const ivec3& v1, const ivec3& v2);
/// ivec3 negation
/// @param v The ivec3 to negate
/// @return The negated ivec3
ivec3 operator-(const ivec3& v);
/// Unary plus: This is basically a no-op.
/// @param v The ivec3.
/// @return The ivec3.
ivec3 operator+(const ivec3& v);
/// Vector dot product
/// @param v1 First ivec3
/// @param v2 Second ivec3
/// @return v1 (dot) v2
std::int32_t dot(const ivec3& v1, const ivec3& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const ivec3& v);
/// Stream extractor for outputting ivec3.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const ivec3& v);
/// ivec3 cross product.
/// @param v First ivec3
/// @param w Second ivec3
/// @return v x w
ivec3 cross(const ivec3& v, const ivec3& w);
/// Vector min operation (componentwise).
/// @param v1 First ivec3
/// @param v2 Second ivec3
/// @return ivec3 where each component is the min of the corresponding components of v1 and v2
ivec3 min(const ivec3& v1, const ivec3& v2);
/// Vector max operation (componentwise).
/// @param v1 First ivec3
/// @param v2 Second ivec3
/// @return ivec3 where each component is the max of the corresponding components of v1 and v2
ivec3 max(const ivec3& v1, const ivec3& v2);

/// A 3-dimensional vector with double components
class dvec3 {
  public:
    double x;   ///< The x component
    double y;   ///< The y component
    double z;   ///< The z component
    /// Default constructor: Initialize to 0's
    dvec3();
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec3(const vec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec3(const uvec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec3(const ivec3& v);
    /// Casting constructor
    /// @param v The vector to cast
    dvec3(const dvec3& v);
    /// @param x_,y_,z_ Vector components
    dvec3(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_);
    /// Create dvec3
    /// @param v xy components of dvec3
    /// @param z_ z_ component of dvec3
    dvec3(const dvec2& v, const AnyScalar& z_);
    /// Initialize dvec3's x,y,z to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit dvec3(const AnyScalar& v);
    /// Get item from dvec3
    /// @param idx Index (0...2)
    /// @return The dvec3's x,y,z value
    double operator[](unsigned idx) const;
    /// Get item from dvec3
    /// @param idx Index (0...2)
    /// @return The dvec3's x,y,z value
    double operator[](int idx) const;
    /// Get item from dvec3
    /// @param idx Index (0...2)
    /// @return The dvec3's x,y,z value
    double& operator[](unsigned idx);
    /// Get item from dvec3
    /// @param idx Index (0...2)
    /// @return The dvec3's x,y,z value
    double& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const dvec3& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const dvec3& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const dvec3& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const dvec3& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const dvec3& o);
    /// In-place multiplication operation: Computes dvec3 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes dvec3 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the dvec3
    operator std::string() const;
    /// Vector size: Always returns 3.
    /// @return 3
    unsigned size() const;
    /// Return slice of a dvec3
    /// @return The x,y components as a dvec2
    dvec2 xy() const;
    /// Return slice of a dvec3
    /// @return The x,y,z components as a dvec3
    dvec3 xyz() const;
};
/// Componentwise Addition operation
/// @param arg1 First dvec3
/// @param arg2 Second dvec3
/// @return arg1 + arg2
dvec3 operator+(const dvec3& arg1, const dvec3& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First dvec3
/// @param arg2 Second dvec3
/// @return arg1 - arg2
dvec3 operator-(const dvec3& arg1, const dvec3& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First dvec3
/// @param arg2 Second dvec3
/// @return arg1 * arg2
dvec3 operator*(const dvec3& arg1, const dvec3& arg2);
/// Componentwise Division operation
/// @param arg1 First dvec3
/// @param arg2 Second dvec3
/// @return arg1 / arg2
dvec3 operator/(const dvec3& arg1, const dvec3& arg2);
/// Compute vector multiplied by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v * s
dvec3 operator*( const dvec3& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec3
/// @return s * v
dvec3 operator*( float s, const dvec3& v  );
/// Compute vector divided by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v / s
dvec3 operator/( const dvec3& v, float s);
/// Compute vector multiplied by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v * s
dvec3 operator*( const dvec3& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec3
/// @return s * v
dvec3 operator*( double s, const dvec3& v  );
/// Compute vector divided by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v / s
dvec3 operator/( const dvec3& v, double s);
/// Compute vector multiplied by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v * s
dvec3 operator*( const dvec3& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec3
/// @return s * v
dvec3 operator*( std::int32_t s, const dvec3& v  );
/// Compute vector divided by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v / s
dvec3 operator/( const dvec3& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v * s
dvec3 operator*( const dvec3& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec3
/// @return s * v
dvec3 operator*( std::uint32_t s, const dvec3& v  );
/// Compute vector divided by scalar
/// @param v The dvec3
/// @param s The scalar
/// @return v / s
dvec3 operator/( const dvec3& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z.
bool operator<(const dvec3& v1, const dvec3& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z.
bool operator>(const dvec3& v1, const dvec3& v2);
/// dvec3 < operator.
/// @param v1 The first dvec3
/// @param v2 The second dvec3
/// @return true if v1<v2; false otherwise
bool operator<=(const dvec3& v1, const dvec3& v2);
/// dvec3 > operator.
/// @param v1 The first dvec3
/// @param v2 The second dvec3
/// @return true if v1>v2; false otherwise
bool operator>=(const dvec3& v1, const dvec3& v2);
/// dvec3 equality operator.
/// @param v1 The first dvec3
/// @param v2 The second dvec3
/// @return true if v1==v2; false otherwise
bool operator==(const dvec3& v1, const dvec3& v2);
/// dvec3 inequality operator.
/// @param v1 The first dvec3
/// @param v2 The second dvec3
/// @return true if v1!=v2; false otherwise
bool operator!=(const dvec3& v1, const dvec3& v2);
/// dvec3 negation
/// @param v The dvec3 to negate
/// @return The negated dvec3
dvec3 operator-(const dvec3& v);
/// Unary plus: This is basically a no-op.
/// @param v The dvec3.
/// @return The dvec3.
dvec3 operator+(const dvec3& v);
/// Vector dot product
/// @param v1 First dvec3
/// @param v2 Second dvec3
/// @return v1 (dot) v2
double dot(const dvec3& v1, const dvec3& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const dvec3& v);
/// Stream extractor for outputting dvec3.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const dvec3& v);
/// dvec3 cross product.
/// @param v First dvec3
/// @param w Second dvec3
/// @return v x w
dvec3 cross(const dvec3& v, const dvec3& w);
/// Vector min operation (componentwise).
/// @param v1 First dvec3
/// @param v2 Second dvec3
/// @return dvec3 where each component is the min of the corresponding components of v1 and v2
dvec3 min(const dvec3& v1, const dvec3& v2);
/// Vector max operation (componentwise).
/// @param v1 First dvec3
/// @param v2 Second dvec3
/// @return dvec3 where each component is the max of the corresponding components of v1 and v2
dvec3 max(const dvec3& v1, const dvec3& v2);

/// A 4-dimensional vector with float components
class vec4 {
  public:
    float x;   ///< The x component
    float y;   ///< The y component
    float z;   ///< The z component
    float w;   ///< The w component
    /// Default constructor: Initialize to 0's
    vec4();
    /// Casting constructor
    /// @param v The vector to cast
    vec4(const vec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec4(const uvec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec4(const ivec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit vec4(const dvec4& v);
    /// @param x_,y_,z_,w_ Vector components
    vec4(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_);
    /// Create vec4
    /// @param v xy components of vec4
    /// @param z_ z_ component of vec4
    /// @param w_ w_ component of vec4
    vec4(const vec2& v, const AnyScalar& z_, const AnyScalar& w_);
    /// Create vec4
    /// @param v xyz components of vec4
    /// @param w_ w_ component of vec4
    vec4(const vec3& v, const AnyScalar& w_);
    /// Initialize vec4's x,y,z,w to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit vec4(const AnyScalar& v);
    /// Get item from vec4
    /// @param idx Index (0...3)
    /// @return The vec4's x,y,z,w value
    float operator[](unsigned idx) const;
    /// Get item from vec4
    /// @param idx Index (0...3)
    /// @return The vec4's x,y,z,w value
    float operator[](int idx) const;
    /// Get item from vec4
    /// @param idx Index (0...3)
    /// @return The vec4's x,y,z,w value
    float& operator[](unsigned idx);
    /// Get item from vec4
    /// @param idx Index (0...3)
    /// @return The vec4's x,y,z,w value
    float& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const vec4& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const vec4& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const vec4& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const vec4& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const vec4& o);
    /// In-place multiplication operation: Computes vec4 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes vec4 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the vec4
    operator std::string() const;
    /// Vector size: Always returns 4.
    /// @return 4
    unsigned size() const;
    /// Return slice of a vec4
    /// @return The x,y components as a vec2
    vec2 xy() const;
    /// Return slice of a vec4
    /// @return The x,y,z components as a vec3
    vec3 xyz() const;
    /// Return slice of a vec4
    /// @return The x,y,z,w components as a vec4
    vec4 xyzw() const;
};
/// Componentwise Addition operation
/// @param arg1 First vec4
/// @param arg2 Second vec4
/// @return arg1 + arg2
vec4 operator+(const vec4& arg1, const vec4& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First vec4
/// @param arg2 Second vec4
/// @return arg1 - arg2
vec4 operator-(const vec4& arg1, const vec4& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First vec4
/// @param arg2 Second vec4
/// @return arg1 * arg2
vec4 operator*(const vec4& arg1, const vec4& arg2);
/// Componentwise Division operation
/// @param arg1 First vec4
/// @param arg2 Second vec4
/// @return arg1 / arg2
vec4 operator/(const vec4& arg1, const vec4& arg2);
/// Compute vector multiplied by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v * s
vec4 operator*( const vec4& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec4
/// @return s * v
vec4 operator*( float s, const vec4& v  );
/// Compute vector divided by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v / s
vec4 operator/( const vec4& v, float s);
/// Compute vector multiplied by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v * s
vec4 operator*( const vec4& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec4
/// @return s * v
vec4 operator*( double s, const vec4& v  );
/// Compute vector divided by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v / s
vec4 operator/( const vec4& v, double s);
/// Compute vector multiplied by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v * s
vec4 operator*( const vec4& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec4
/// @return s * v
vec4 operator*( std::int32_t s, const vec4& v  );
/// Compute vector divided by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v / s
vec4 operator/( const vec4& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v * s
vec4 operator*( const vec4& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The vec4
/// @return s * v
vec4 operator*( std::uint32_t s, const vec4& v  );
/// Compute vector divided by scalar
/// @param v The vec4
/// @param s The scalar
/// @return v / s
vec4 operator/( const vec4& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator<(const vec4& v1, const vec4& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator>(const vec4& v1, const vec4& v2);
/// vec4 < operator.
/// @param v1 The first vec4
/// @param v2 The second vec4
/// @return true if v1<v2; false otherwise
bool operator<=(const vec4& v1, const vec4& v2);
/// vec4 > operator.
/// @param v1 The first vec4
/// @param v2 The second vec4
/// @return true if v1>v2; false otherwise
bool operator>=(const vec4& v1, const vec4& v2);
/// vec4 equality operator.
/// @param v1 The first vec4
/// @param v2 The second vec4
/// @return true if v1==v2; false otherwise
bool operator==(const vec4& v1, const vec4& v2);
/// vec4 inequality operator.
/// @param v1 The first vec4
/// @param v2 The second vec4
/// @return true if v1!=v2; false otherwise
bool operator!=(const vec4& v1, const vec4& v2);
/// vec4 negation
/// @param v The vec4 to negate
/// @return The negated vec4
vec4 operator-(const vec4& v);
/// Unary plus: This is basically a no-op.
/// @param v The vec4.
/// @return The vec4.
vec4 operator+(const vec4& v);
/// Vector dot product
/// @param v1 First vec4
/// @param v2 Second vec4
/// @return v1 (dot) v2
float dot(const vec4& v1, const vec4& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const vec4& v);
/// Stream extractor for outputting vec4.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const vec4& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First vec4
/// @param v2 Second vec4
/// @return vec4 where each component is the min of the corresponding components of v1 and v2
vec4 min(const vec4& v1, const vec4& v2);
/// Vector max operation (componentwise).
/// @param v1 First vec4
/// @param v2 Second vec4
/// @return vec4 where each component is the max of the corresponding components of v1 and v2
vec4 max(const vec4& v1, const vec4& v2);

/// A 4-dimensional vector with std::uint32_t components
class uvec4 {
  public:
    std::uint32_t x;   ///< The x component
    std::uint32_t y;   ///< The y component
    std::uint32_t z;   ///< The z component
    std::uint32_t w;   ///< The w component
    /// Default constructor: Initialize to 0's
    uvec4();
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec4(const vec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    uvec4(const uvec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec4(const ivec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit uvec4(const dvec4& v);
    /// @param x_,y_,z_,w_ Vector components
    uvec4(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_);
    /// Create uvec4
    /// @param v xy components of uvec4
    /// @param z_ z_ component of uvec4
    /// @param w_ w_ component of uvec4
    uvec4(const uvec2& v, const AnyScalar& z_, const AnyScalar& w_);
    /// Create uvec4
    /// @param v xyz components of uvec4
    /// @param w_ w_ component of uvec4
    uvec4(const uvec3& v, const AnyScalar& w_);
    /// Initialize uvec4's x,y,z,w to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit uvec4(const AnyScalar& v);
    /// Get item from uvec4
    /// @param idx Index (0...3)
    /// @return The uvec4's x,y,z,w value
    std::uint32_t operator[](unsigned idx) const;
    /// Get item from uvec4
    /// @param idx Index (0...3)
    /// @return The uvec4's x,y,z,w value
    std::uint32_t operator[](int idx) const;
    /// Get item from uvec4
    /// @param idx Index (0...3)
    /// @return The uvec4's x,y,z,w value
    std::uint32_t& operator[](unsigned idx);
    /// Get item from uvec4
    /// @param idx Index (0...3)
    /// @return The uvec4's x,y,z,w value
    std::uint32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const uvec4& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const uvec4& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const uvec4& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const uvec4& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const uvec4& o);
    /// In-place multiplication operation: Computes uvec4 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes uvec4 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the uvec4
    operator std::string() const;
    /// Vector size: Always returns 4.
    /// @return 4
    unsigned size() const;
    /// Return slice of a uvec4
    /// @return The x,y components as a uvec2
    uvec2 xy() const;
    /// Return slice of a uvec4
    /// @return The x,y,z components as a uvec3
    uvec3 xyz() const;
    /// Return slice of a uvec4
    /// @return The x,y,z,w components as a uvec4
    uvec4 xyzw() const;
};
/// Componentwise Addition operation
/// @param arg1 First uvec4
/// @param arg2 Second uvec4
/// @return arg1 + arg2
uvec4 operator+(const uvec4& arg1, const uvec4& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First uvec4
/// @param arg2 Second uvec4
/// @return arg1 - arg2
uvec4 operator-(const uvec4& arg1, const uvec4& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First uvec4
/// @param arg2 Second uvec4
/// @return arg1 * arg2
uvec4 operator*(const uvec4& arg1, const uvec4& arg2);
/// Componentwise Division operation
/// @param arg1 First uvec4
/// @param arg2 Second uvec4
/// @return arg1 / arg2
uvec4 operator/(const uvec4& arg1, const uvec4& arg2);
/// Compute vector multiplied by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v * s
uvec4 operator*( const uvec4& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec4
/// @return s * v
uvec4 operator*( float s, const uvec4& v  );
/// Compute vector divided by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v / s
uvec4 operator/( const uvec4& v, float s);
/// Compute vector multiplied by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v * s
uvec4 operator*( const uvec4& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec4
/// @return s * v
uvec4 operator*( double s, const uvec4& v  );
/// Compute vector divided by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v / s
uvec4 operator/( const uvec4& v, double s);
/// Compute vector multiplied by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v * s
uvec4 operator*( const uvec4& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec4
/// @return s * v
uvec4 operator*( std::int32_t s, const uvec4& v  );
/// Compute vector divided by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v / s
uvec4 operator/( const uvec4& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v * s
uvec4 operator*( const uvec4& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The uvec4
/// @return s * v
uvec4 operator*( std::uint32_t s, const uvec4& v  );
/// Compute vector divided by scalar
/// @param v The uvec4
/// @param s The scalar
/// @return v / s
uvec4 operator/( const uvec4& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator<(const uvec4& v1, const uvec4& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator>(const uvec4& v1, const uvec4& v2);
/// uvec4 < operator.
/// @param v1 The first uvec4
/// @param v2 The second uvec4
/// @return true if v1<v2; false otherwise
bool operator<=(const uvec4& v1, const uvec4& v2);
/// uvec4 > operator.
/// @param v1 The first uvec4
/// @param v2 The second uvec4
/// @return true if v1>v2; false otherwise
bool operator>=(const uvec4& v1, const uvec4& v2);
/// uvec4 equality operator.
/// @param v1 The first uvec4
/// @param v2 The second uvec4
/// @return true if v1==v2; false otherwise
bool operator==(const uvec4& v1, const uvec4& v2);
/// uvec4 inequality operator.
/// @param v1 The first uvec4
/// @param v2 The second uvec4
/// @return true if v1!=v2; false otherwise
bool operator!=(const uvec4& v1, const uvec4& v2);
//no negation for unsigned vec type
/// Unary plus: This is basically a no-op.
/// @param v The uvec4.
/// @return The uvec4.
uvec4 operator+(const uvec4& v);
/// Vector dot product
/// @param v1 First uvec4
/// @param v2 Second uvec4
/// @return v1 (dot) v2
std::uint32_t dot(const uvec4& v1, const uvec4& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const uvec4& v);
/// Stream extractor for outputting uvec4.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const uvec4& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First uvec4
/// @param v2 Second uvec4
/// @return uvec4 where each component is the min of the corresponding components of v1 and v2
uvec4 min(const uvec4& v1, const uvec4& v2);
/// Vector max operation (componentwise).
/// @param v1 First uvec4
/// @param v2 Second uvec4
/// @return uvec4 where each component is the max of the corresponding components of v1 and v2
uvec4 max(const uvec4& v1, const uvec4& v2);

/// A 4-dimensional vector with std::int32_t components
class ivec4 {
  public:
    std::int32_t x;   ///< The x component
    std::int32_t y;   ///< The y component
    std::int32_t z;   ///< The z component
    std::int32_t w;   ///< The w component
    /// Default constructor: Initialize to 0's
    ivec4();
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec4(const vec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec4(const uvec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    ivec4(const ivec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit ivec4(const dvec4& v);
    /// @param x_,y_,z_,w_ Vector components
    ivec4(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_);
    /// Create ivec4
    /// @param v xy components of ivec4
    /// @param z_ z_ component of ivec4
    /// @param w_ w_ component of ivec4
    ivec4(const ivec2& v, const AnyScalar& z_, const AnyScalar& w_);
    /// Create ivec4
    /// @param v xyz components of ivec4
    /// @param w_ w_ component of ivec4
    ivec4(const ivec3& v, const AnyScalar& w_);
    /// Initialize ivec4's x,y,z,w to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit ivec4(const AnyScalar& v);
    /// Get item from ivec4
    /// @param idx Index (0...3)
    /// @return The ivec4's x,y,z,w value
    std::int32_t operator[](unsigned idx) const;
    /// Get item from ivec4
    /// @param idx Index (0...3)
    /// @return The ivec4's x,y,z,w value
    std::int32_t operator[](int idx) const;
    /// Get item from ivec4
    /// @param idx Index (0...3)
    /// @return The ivec4's x,y,z,w value
    std::int32_t& operator[](unsigned idx);
    /// Get item from ivec4
    /// @param idx Index (0...3)
    /// @return The ivec4's x,y,z,w value
    std::int32_t& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const ivec4& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const ivec4& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const ivec4& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const ivec4& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const ivec4& o);
    /// In-place multiplication operation: Computes ivec4 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes ivec4 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the ivec4
    operator std::string() const;
    /// Vector size: Always returns 4.
    /// @return 4
    unsigned size() const;
    /// Return slice of a ivec4
    /// @return The x,y components as a ivec2
    ivec2 xy() const;
    /// Return slice of a ivec4
    /// @return The x,y,z components as a ivec3
    ivec3 xyz() const;
    /// Return slice of a ivec4
    /// @return The x,y,z,w components as a ivec4
    ivec4 xyzw() const;
};
/// Componentwise Addition operation
/// @param arg1 First ivec4
/// @param arg2 Second ivec4
/// @return arg1 + arg2
ivec4 operator+(const ivec4& arg1, const ivec4& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First ivec4
/// @param arg2 Second ivec4
/// @return arg1 - arg2
ivec4 operator-(const ivec4& arg1, const ivec4& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First ivec4
/// @param arg2 Second ivec4
/// @return arg1 * arg2
ivec4 operator*(const ivec4& arg1, const ivec4& arg2);
/// Componentwise Division operation
/// @param arg1 First ivec4
/// @param arg2 Second ivec4
/// @return arg1 / arg2
ivec4 operator/(const ivec4& arg1, const ivec4& arg2);
/// Compute vector multiplied by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v * s
ivec4 operator*( const ivec4& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec4
/// @return s * v
ivec4 operator*( float s, const ivec4& v  );
/// Compute vector divided by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v / s
ivec4 operator/( const ivec4& v, float s);
/// Compute vector multiplied by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v * s
ivec4 operator*( const ivec4& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec4
/// @return s * v
ivec4 operator*( double s, const ivec4& v  );
/// Compute vector divided by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v / s
ivec4 operator/( const ivec4& v, double s);
/// Compute vector multiplied by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v * s
ivec4 operator*( const ivec4& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec4
/// @return s * v
ivec4 operator*( std::int32_t s, const ivec4& v  );
/// Compute vector divided by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v / s
ivec4 operator/( const ivec4& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v * s
ivec4 operator*( const ivec4& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The ivec4
/// @return s * v
ivec4 operator*( std::uint32_t s, const ivec4& v  );
/// Compute vector divided by scalar
/// @param v The ivec4
/// @param s The scalar
/// @return v / s
ivec4 operator/( const ivec4& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator<(const ivec4& v1, const ivec4& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator>(const ivec4& v1, const ivec4& v2);
/// ivec4 < operator.
/// @param v1 The first ivec4
/// @param v2 The second ivec4
/// @return true if v1<v2; false otherwise
bool operator<=(const ivec4& v1, const ivec4& v2);
/// ivec4 > operator.
/// @param v1 The first ivec4
/// @param v2 The second ivec4
/// @return true if v1>v2; false otherwise
bool operator>=(const ivec4& v1, const ivec4& v2);
/// ivec4 equality operator.
/// @param v1 The first ivec4
/// @param v2 The second ivec4
/// @return true if v1==v2; false otherwise
bool operator==(const ivec4& v1, const ivec4& v2);
/// ivec4 inequality operator.
/// @param v1 The first ivec4
/// @param v2 The second ivec4
/// @return true if v1!=v2; false otherwise
bool operator!=(const ivec4& v1, const ivec4& v2);
/// ivec4 negation
/// @param v The ivec4 to negate
/// @return The negated ivec4
ivec4 operator-(const ivec4& v);
/// Unary plus: This is basically a no-op.
/// @param v The ivec4.
/// @return The ivec4.
ivec4 operator+(const ivec4& v);
/// Vector dot product
/// @param v1 First ivec4
/// @param v2 Second ivec4
/// @return v1 (dot) v2
std::int32_t dot(const ivec4& v1, const ivec4& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const ivec4& v);
/// Stream extractor for outputting ivec4.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const ivec4& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First ivec4
/// @param v2 Second ivec4
/// @return ivec4 where each component is the min of the corresponding components of v1 and v2
ivec4 min(const ivec4& v1, const ivec4& v2);
/// Vector max operation (componentwise).
/// @param v1 First ivec4
/// @param v2 Second ivec4
/// @return ivec4 where each component is the max of the corresponding components of v1 and v2
ivec4 max(const ivec4& v1, const ivec4& v2);

/// A 4-dimensional vector with double components
class dvec4 {
  public:
    double x;   ///< The x component
    double y;   ///< The y component
    double z;   ///< The z component
    double w;   ///< The w component
    /// Default constructor: Initialize to 0's
    dvec4();
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec4(const vec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec4(const uvec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    explicit dvec4(const ivec4& v);
    /// Casting constructor
    /// @param v The vector to cast
    dvec4(const dvec4& v);
    /// @param x_,y_,z_,w_ Vector components
    dvec4(const AnyScalar& x_, const AnyScalar& y_, const AnyScalar& z_, const AnyScalar& w_);
    /// Create dvec4
    /// @param v xy components of dvec4
    /// @param z_ z_ component of dvec4
    /// @param w_ w_ component of dvec4
    dvec4(const dvec2& v, const AnyScalar& z_, const AnyScalar& w_);
    /// Create dvec4
    /// @param v xyz components of dvec4
    /// @param w_ w_ component of dvec4
    dvec4(const dvec3& v, const AnyScalar& w_);
    /// Initialize dvec4's x,y,z,w to v
    /// @param v Any scalar type: float, double, int, unsigned
    explicit dvec4(const AnyScalar& v);
    /// Get item from dvec4
    /// @param idx Index (0...3)
    /// @return The dvec4's x,y,z,w value
    double operator[](unsigned idx) const;
    /// Get item from dvec4
    /// @param idx Index (0...3)
    /// @return The dvec4's x,y,z,w value
    double operator[](int idx) const;
    /// Get item from dvec4
    /// @param idx Index (0...3)
    /// @return The dvec4's x,y,z,w value
    double& operator[](unsigned idx);
    /// Get item from dvec4
    /// @param idx Index (0...3)
    /// @return The dvec4's x,y,z,w value
    double& operator[](int idx);
    /// Mathematical = operation
    /// @param o Compute this = o
    void operator=(const dvec4& o);
    /// Mathematical += operation
    /// @param o Compute this += o
    void operator+=(const dvec4& o);
    /// Mathematical -= operation
    /// @param o Compute this -= o
    void operator-=(const dvec4& o);
    /// Mathematical *= operation
    /// @param o Compute this *= o
    void operator*=(const dvec4& o);
    /// Mathematical /= operation
    /// @param o Compute this /= o
    void operator/=(const dvec4& o);
    /// In-place multiplication operation: Computes dvec4 *= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator*=(const AnyScalar& s);
    /// In-place division operation: Computes dvec4 /= scalar
    /// @param s The scalar: float, double, int, or unsigned
    void operator/=(const AnyScalar& s);
    /// Cast to string
    /// @return Readable representation of the dvec4
    operator std::string() const;
    /// Vector size: Always returns 4.
    /// @return 4
    unsigned size() const;
    /// Return slice of a dvec4
    /// @return The x,y components as a dvec2
    dvec2 xy() const;
    /// Return slice of a dvec4
    /// @return The x,y,z components as a dvec3
    dvec3 xyz() const;
    /// Return slice of a dvec4
    /// @return The x,y,z,w components as a dvec4
    dvec4 xyzw() const;
};
/// Componentwise Addition operation
/// @param arg1 First dvec4
/// @param arg2 Second dvec4
/// @return arg1 + arg2
dvec4 operator+(const dvec4& arg1, const dvec4& arg2);
/// Componentwise Subtraction operation
/// @param arg1 First dvec4
/// @param arg2 Second dvec4
/// @return arg1 - arg2
dvec4 operator-(const dvec4& arg1, const dvec4& arg2);
/// Componentwise Multiplication operation
/// @param arg1 First dvec4
/// @param arg2 Second dvec4
/// @return arg1 * arg2
dvec4 operator*(const dvec4& arg1, const dvec4& arg2);
/// Componentwise Division operation
/// @param arg1 First dvec4
/// @param arg2 Second dvec4
/// @return arg1 / arg2
dvec4 operator/(const dvec4& arg1, const dvec4& arg2);
/// Compute vector multiplied by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v * s
dvec4 operator*( const dvec4& v, float s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec4
/// @return s * v
dvec4 operator*( float s, const dvec4& v  );
/// Compute vector divided by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v / s
dvec4 operator/( const dvec4& v, float s);
/// Compute vector multiplied by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v * s
dvec4 operator*( const dvec4& v, double s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec4
/// @return s * v
dvec4 operator*( double s, const dvec4& v  );
/// Compute vector divided by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v / s
dvec4 operator/( const dvec4& v, double s);
/// Compute vector multiplied by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v * s
dvec4 operator*( const dvec4& v, std::int32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec4
/// @return s * v
dvec4 operator*( std::int32_t s, const dvec4& v  );
/// Compute vector divided by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v / s
dvec4 operator/( const dvec4& v, std::int32_t s);
/// Compute vector multiplied by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v * s
dvec4 operator*( const dvec4& v, std::uint32_t s);
/// Compute scalar multiplied by vector
/// @param s The scalar
/// @param v The dvec4
/// @return s * v
dvec4 operator*( std::uint32_t s, const dvec4& v  );
/// Compute vector divided by scalar
/// @param v The dvec4
/// @param s The scalar
/// @return v / s
dvec4 operator/( const dvec4& v, std::uint32_t s);
/// Relational < operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 < v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x < v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator<(const dvec4& v1, const dvec4& v2);
/// Relational > operation.
/// @param v1 The first argument
/// @param v2 The second argument
/// @return True if v1 > v2; false otherwise. The comparison
///       is carried out in lexicographical order: If v1.x != v2.x
///       return (v1.x > v2.x). Otherwise, do the same test with y
///       and then z and then w.
bool operator>(const dvec4& v1, const dvec4& v2);
/// dvec4 < operator.
/// @param v1 The first dvec4
/// @param v2 The second dvec4
/// @return true if v1<v2; false otherwise
bool operator<=(const dvec4& v1, const dvec4& v2);
/// dvec4 > operator.
/// @param v1 The first dvec4
/// @param v2 The second dvec4
/// @return true if v1>v2; false otherwise
bool operator>=(const dvec4& v1, const dvec4& v2);
/// dvec4 equality operator.
/// @param v1 The first dvec4
/// @param v2 The second dvec4
/// @return true if v1==v2; false otherwise
bool operator==(const dvec4& v1, const dvec4& v2);
/// dvec4 inequality operator.
/// @param v1 The first dvec4
/// @param v2 The second dvec4
/// @return true if v1!=v2; false otherwise
bool operator!=(const dvec4& v1, const dvec4& v2);
/// dvec4 negation
/// @param v The dvec4 to negate
/// @return The negated dvec4
dvec4 operator-(const dvec4& v);
/// Unary plus: This is basically a no-op.
/// @param v The dvec4.
/// @return The dvec4.
dvec4 operator+(const dvec4& v);
/// Vector dot product
/// @param v1 First dvec4
/// @param v2 Second dvec4
/// @return v1 (dot) v2
double dot(const dvec4& v1, const dvec4& v2);
/// Vector length
/// @param v The vector
/// @return The length
float length(const dvec4& v);
/// Stream extractor for outputting dvec4.
/// @param o The stream
/// @param v The vector
std::ostream& operator<<(std::ostream& o, const dvec4& v);
//no cross product for non-3d vec
/// Vector min operation (componentwise).
/// @param v1 First dvec4
/// @param v2 Second dvec4
/// @return dvec4 where each component is the min of the corresponding components of v1 and v2
dvec4 min(const dvec4& v1, const dvec4& v2);
/// Vector max operation (componentwise).
/// @param v1 First dvec4
/// @param v2 Second dvec4
/// @return dvec4 where each component is the max of the corresponding components of v1 and v2
dvec4 max(const dvec4& v1, const dvec4& v2);

/// A 2 x 2 matrix
class mat2 {
  public:
    /// The matrix data, padded to 4 columns since GLSL pads rows to 4 elements
    float _M[2][4];
    /// Helper class for [] access
    class RowProxy{
        friend class mat2;
        mat2* m;
        unsigned r;
        RowProxy(mat2* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...2)
        /// @return The element
        float& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class mat2;
        const mat2* m;
        unsigned r;
        CRowProxy(const mat2* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...2)
        /// @return The element
        float operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 2 x 2 identity matrix
    /// @return The matrix
    static mat2 identity();
    /// Default constructor: Initialize mat2 to all zeros
    mat2();
/// Construct matrix from scalars
/// @param m00,m01,m10,m11 Matrix entry
    mat2(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m10, const AnyScalar& m11);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of float's
    /// @returns The vector.
    std::vector<float> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
mat2 operator+(const mat2& m1, const mat2& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
mat2 operator-(const mat2& m1, const mat2& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const mat2& m1, const mat2& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const mat2& m1, const mat2& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
mat2 operator*(const mat2& m1, const mat2& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
vec2 operator*(const mat2& m, const vec2& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
vec2 operator*(const vec2& v, const mat2& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat2 operator*(const mat2& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat2 operator*(const mat2& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat2 operator*(const mat2& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat2 operator*(const mat2& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat2 operator/(const mat2& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat2 operator/(const mat2& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat2 operator/(const mat2& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat2 operator/(const mat2& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat2 operator*(float s, const mat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat2 operator*(double s, const mat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat2 operator*(std::int32_t s, const mat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat2 operator*(std::uint32_t s, const mat2& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
mat2 operator+(const mat2& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
mat2 operator-(const mat2& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
mat2 transpose(const mat2& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const mat2& m);

/// A 2 x 2 matrix
class dmat2 {
  public:
    /// The matrix data, padded to 4 columns since GLSL pads rows to 4 elements
    double _M[2][4];
    /// Helper class for [] access
    class RowProxy{
        friend class dmat2;
        dmat2* m;
        unsigned r;
        RowProxy(dmat2* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...2)
        /// @return The element
        double& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class dmat2;
        const dmat2* m;
        unsigned r;
        CRowProxy(const dmat2* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...2)
        /// @return The element
        double operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 2 x 2 identity matrix
    /// @return The matrix
    static dmat2 identity();
    /// Default constructor: Initialize dmat2 to all zeros
    dmat2();
/// Construct matrix from scalars
/// @param m00,m01,m10,m11 Matrix entry
    dmat2(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m10, const AnyScalar& m11);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of double's
    /// @returns The vector.
    std::vector<double> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
dmat2 operator+(const dmat2& m1, const dmat2& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
dmat2 operator-(const dmat2& m1, const dmat2& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const dmat2& m1, const dmat2& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const dmat2& m1, const dmat2& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
dmat2 operator*(const dmat2& m1, const dmat2& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
dvec2 operator*(const dmat2& m, const dvec2& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
dvec2 operator*(const dvec2& v, const dmat2& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat2 operator*(const dmat2& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat2 operator*(const dmat2& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat2 operator*(const dmat2& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat2 operator*(const dmat2& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat2 operator/(const dmat2& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat2 operator/(const dmat2& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat2 operator/(const dmat2& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat2 operator/(const dmat2& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat2 operator*(float s, const dmat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat2 operator*(double s, const dmat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat2 operator*(std::int32_t s, const dmat2& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat2 operator*(std::uint32_t s, const dmat2& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
dmat2 operator+(const dmat2& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
dmat2 operator-(const dmat2& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
dmat2 transpose(const dmat2& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const dmat2& m);

/// A 3 x 3 matrix
class mat3 {
  public:
    /// The matrix data, padded to 4 columns since GLSL pads rows to 4 elements
    float _M[3][4];
    /// Helper class for [] access
    class RowProxy{
        friend class mat3;
        mat3* m;
        unsigned r;
        RowProxy(mat3* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...3)
        /// @return The element
        float& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class mat3;
        const mat3* m;
        unsigned r;
        CRowProxy(const mat3* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...3)
        /// @return The element
        float operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 3 x 3 identity matrix
    /// @return The matrix
    static mat3 identity();
    /// Default constructor: Initialize mat3 to all zeros
    mat3();
/// Construct matrix from scalars
/// @param m00,m01,m02,m10,m11,m12,m20,m21,m22 Matrix entry
    mat3(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of float's
    /// @returns The vector.
    std::vector<float> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
mat3 operator+(const mat3& m1, const mat3& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
mat3 operator-(const mat3& m1, const mat3& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const mat3& m1, const mat3& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const mat3& m1, const mat3& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
mat3 operator*(const mat3& m1, const mat3& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
vec3 operator*(const mat3& m, const vec3& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
vec3 operator*(const vec3& v, const mat3& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat3 operator*(const mat3& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat3 operator*(const mat3& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat3 operator*(const mat3& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat3 operator*(const mat3& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat3 operator/(const mat3& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat3 operator/(const mat3& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat3 operator/(const mat3& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat3 operator/(const mat3& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat3 operator*(float s, const mat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat3 operator*(double s, const mat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat3 operator*(std::int32_t s, const mat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat3 operator*(std::uint32_t s, const mat3& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
mat3 operator+(const mat3& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
mat3 operator-(const mat3& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
mat3 transpose(const mat3& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const mat3& m);

/// A 3 x 3 matrix
class dmat3 {
  public:
    /// The matrix data, padded to 4 columns since GLSL pads rows to 4 elements
    double _M[3][4];
    /// Helper class for [] access
    class RowProxy{
        friend class dmat3;
        dmat3* m;
        unsigned r;
        RowProxy(dmat3* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...3)
        /// @return The element
        double& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class dmat3;
        const dmat3* m;
        unsigned r;
        CRowProxy(const dmat3* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...3)
        /// @return The element
        double operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 3 x 3 identity matrix
    /// @return The matrix
    static dmat3 identity();
    /// Default constructor: Initialize dmat3 to all zeros
    dmat3();
/// Construct matrix from scalars
/// @param m00,m01,m02,m10,m11,m12,m20,m21,m22 Matrix entry
    dmat3(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of double's
    /// @returns The vector.
    std::vector<double> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
dmat3 operator+(const dmat3& m1, const dmat3& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
dmat3 operator-(const dmat3& m1, const dmat3& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const dmat3& m1, const dmat3& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const dmat3& m1, const dmat3& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
dmat3 operator*(const dmat3& m1, const dmat3& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
dvec3 operator*(const dmat3& m, const dvec3& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
dvec3 operator*(const dvec3& v, const dmat3& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat3 operator*(const dmat3& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat3 operator*(const dmat3& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat3 operator*(const dmat3& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat3 operator*(const dmat3& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat3 operator/(const dmat3& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat3 operator/(const dmat3& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat3 operator/(const dmat3& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat3 operator/(const dmat3& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat3 operator*(float s, const dmat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat3 operator*(double s, const dmat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat3 operator*(std::int32_t s, const dmat3& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat3 operator*(std::uint32_t s, const dmat3& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
dmat3 operator+(const dmat3& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
dmat3 operator-(const dmat3& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
dmat3 transpose(const dmat3& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const dmat3& m);

/// A 4 x 4 matrix
class mat4 {
  public:
    /// The matrix data
    float _M[4][4];
    /// Helper class for [] access
    class RowProxy{
        friend class mat4;
        mat4* m;
        unsigned r;
        RowProxy(mat4* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...4)
        /// @return The element
        float& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class mat4;
        const mat4* m;
        unsigned r;
        CRowProxy(const mat4* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...4)
        /// @return The element
        float operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 4 x 4 identity matrix
    /// @return The matrix
    static mat4 identity();
    /// Default constructor: Initialize mat4 to all zeros
    mat4();
/// Construct matrix from scalars
/// @param m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33 Matrix entry
    mat4(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m03, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m13, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22, const AnyScalar& m23, const AnyScalar& m30, const AnyScalar& m31, const AnyScalar& m32, const AnyScalar& m33);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    float& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of float's
    /// @returns The vector.
    std::vector<float> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
mat4 operator+(const mat4& m1, const mat4& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
mat4 operator-(const mat4& m1, const mat4& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const mat4& m1, const mat4& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const mat4& m1, const mat4& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
mat4 operator*(const mat4& m1, const mat4& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
vec4 operator*(const mat4& m, const vec4& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
vec4 operator*(const vec4& v, const mat4& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat4 operator*(const mat4& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat4 operator*(const mat4& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat4 operator*(const mat4& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
mat4 operator*(const mat4& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat4 operator/(const mat4& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat4 operator/(const mat4& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat4 operator/(const mat4& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
mat4 operator/(const mat4& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat4 operator*(float s, const mat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat4 operator*(double s, const mat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat4 operator*(std::int32_t s, const mat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
mat4 operator*(std::uint32_t s, const mat4& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
mat4 operator+(const mat4& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
mat4 operator-(const mat4& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
mat4 transpose(const mat4& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const mat4& m);

/// A 4 x 4 matrix
class dmat4 {
  public:
    /// The matrix data
    double _M[4][4];
    /// Helper class for [] access
    class RowProxy{
        friend class dmat4;
        dmat4* m;
        unsigned r;
        RowProxy(dmat4* m_, int r_);
        RowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        RowProxy(RowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...4)
        /// @return The element
        double& operator[](unsigned idx);
    };
    class CRowProxy{
        friend class dmat4;
        const dmat4* m;
        unsigned r;
        CRowProxy(const dmat4* m_, int r_);
        CRowProxy(const RowProxy&) = delete;
        void operator=(const RowProxy&) = delete;
      public:
        /// Move constructor
        /// @param r Object to move
        CRowProxy(CRowProxy&& r) noexcept;
        /// Access a given element of the matrix

        /// @param idx The column index (0...4)
        /// @return The element
        double operator[](unsigned idx) ;
    };
    /// Function to allow accessing matrix with [].
    /// Example: m[0][1] = 42
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    RowProxy operator[](unsigned row);
    /// Function to allow accessing matrix with [].
    /// Example: float tmp = m[0][1]
    /// @param row The row number
    /// @return A proxy object that can be used to get a given column of the row.
    CRowProxy operator[](unsigned row) const;
    /// Return 4 x 4 identity matrix
    /// @return The matrix
    static dmat4 identity();
    /// Default constructor: Initialize dmat4 to all zeros
    dmat4();
/// Construct matrix from scalars
/// @param m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33 Matrix entry
    dmat4(const AnyScalar& m00, const AnyScalar& m01, const AnyScalar& m02, const AnyScalar& m03, const AnyScalar& m10, const AnyScalar& m11, const AnyScalar& m12, const AnyScalar& m13, const AnyScalar& m20, const AnyScalar& m21, const AnyScalar& m22, const AnyScalar& m23, const AnyScalar& m30, const AnyScalar& m31, const AnyScalar& m32, const AnyScalar& m33);
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double operator()(unsigned r, unsigned c) const;
    /// Matrix component access
    /// @param r The row
    /// @param c The column
    /// @return Matrix element [r][c]
    double& operator()(unsigned r, unsigned c);
    /// Return matrix data as a row-major list of double's
    /// @returns The vector.
    std::vector<double> data() const;
/// Matrix string conversion
/// @return String representation of the matrix
operator std::string() const;
};
//matrix binary operations
/// Matrix addition
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 + m2
dmat4 operator+(const dmat4& m1, const dmat4& m2);
/// Matrix subtraction
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 - m2
dmat4 operator-(const dmat4& m1, const dmat4& m2);
//matrix equality
/// Matrix equality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 == m2, false otherwise
bool operator==(const dmat4& m1, const dmat4& m2);
//matrix inequality
/// Matrix inequality
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return true if m1 != m2, false otherwise
bool operator!=(const dmat4& m1, const dmat4& m2);
//matrix-matrix multiply
/// Matrix multiplication
/// @param m1 First matrix
/// @param m2 Second matrix
/// @return m1 * m2
dmat4 operator*(const dmat4& m1, const dmat4& m2);
//matrix-vector multiply
/// Matrix-vector multiplication
/// @param m Matrix
/// @param v Vector
/// @return m * v
dvec4 operator*(const dmat4& m, const dvec4& v);
//vector-matrix multiply
/// Vector-matrix multiplication
/// @param v Vector
/// @param m Matrix
/// @return v * m
dvec4 operator*(const dvec4& v, const dmat4& m);
//matrix-scalar operations
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat4 operator*(const dmat4& m, float s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat4 operator*(const dmat4& m, double s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat4 operator*(const dmat4& m, std::int32_t s);
/// Matrix-scalar multiplication
/// @param m Matrix
/// @param s Scalar
/// @return m * s
dmat4 operator*(const dmat4& m, std::uint32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat4 operator/(const dmat4& m, float s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat4 operator/(const dmat4& m, double s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat4 operator/(const dmat4& m, std::int32_t s);
/// Matrix-scalar division
/// @param m Matrix
/// @param s Scalar
/// @return m / s
dmat4 operator/(const dmat4& m, std::uint32_t s);
//scalar-matrix operations
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat4 operator*(float s, const dmat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat4 operator*(double s, const dmat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat4 operator*(std::int32_t s, const dmat4& m);
/// Scalar-matrix multiplication
/// @param s Scalar
/// @param m Matrix
/// @return s * m
dmat4 operator*(std::uint32_t s, const dmat4& m);
//unary matrix operations
/// Matrix unary plus
/// @param m Matrix
/// @return +m
dmat4 operator+(const dmat4& m);
/// Matrix negation
/// @param m Matrix
/// @return -m
dmat4 operator-(const dmat4& m);
//matrix transpose
/// Matrix transposition.
/// @param m The matrix
/// @return Transposed matrix
dmat4 transpose(const dmat4& m);
//matrix output
/// Matrix stream extractor (output).
/// @param o The stream
/// @param m The matrix
/// @return The stream
std::ostream& operator<<(std::ostream& o, const dmat4& m);


/// Return the upper 3x3 part of a 4x4 matrix
/// @param m The 4x4 matrix
/// @return The upper 3x3 matrix
mat3 upper3x3(const mat4& m);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
vec2 normalize(const vec2& a);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
vec3 normalize(const vec3& a);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
vec4 normalize(const vec4& a);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
dvec2 normalize(const dvec2& a);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
dvec3 normalize(const dvec3& a);

/// Normalize a vector (make it unit length)
/// @param a The vector
/// @return The unit length vector.
dvec4 normalize(const dvec4& a);

/// Return a 3x3 translation matrix for 2D points.
/// The matrix should be postmultiplied with points
/// (i.e., p' = p*M).
/// @param t The translation amounts
/// @return The matrix
mat3 translation2D(const vec2& t);

/// Return a 4x4 translation matrix for 3D points.
/// The matrix should be postmultiplied with points
/// (i.e., p' = p*M).
/// @param t The translation amounts
/// @return The matrix
mat4 translation(const vec3& t);

/// Return a 3x3 translation matrix for 2D points.
/// The matrix should be postmultiplied with points
/// (i.e., p' = p*M).
/// @param tx The translation x amount
/// @param ty The translation y amount
/// @return The matrix
mat3 translation2D(const AnyScalar& tx, const AnyScalar& ty);

/// Return a 4x4 translation matrix for 3D points.
/// The matrix should be postmultiplied with points
/// (i.e., p' = p*M).
/// @param tx The translation x
/// @param ty The translation y
/// @param tz The translation z
/// @return The matrix
mat4 translation(const AnyScalar& tx, const AnyScalar& ty, const AnyScalar& tz);

/// Return a 4x4 scale matrix for 3D points or vectors.
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param sx The scale x
/// @param sy The scale y
/// @param sz The scale z
/// @return The matrix
mat4 scaling( const AnyScalar& sx, const AnyScalar& sy, const AnyScalar& sz );

/// Return a 4x4 scale matrix for 3D points or vectors.
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param v The scale amount
/// @return The matrix
mat4 scaling( const vec3& v);

/// Return a 3x3 scale matrix for 3D points or vectors.
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param sx The scale x
/// @param sy The scale y
/// @param sz The scale z
/// @return The matrix
mat3 scaling3x3( const AnyScalar& sx, const AnyScalar& sy, const AnyScalar& sz );

/// Return a 3x3 scale matrix for 3D points or vectors.
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param v The scale amount
/// @return The matrix
mat3 scaling3x3( const vec3& v);

/// Return a 3x3 scale matrix for 2D points or vectors
/// (i.e., M[2][2] == 1)
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param sx,sy The scale amounts
/// @return The matrix
mat3 scaling2D( const AnyScalar& sx, const AnyScalar& sy);

/// Return a 3x3 scale matrix for 2D points or vectors
/// (i.e., M[2][2] == 1)
/// The matrix should be postmultiplied with the point (vector).
/// (i.e., p' = p*M).
/// @param v The scale amount
/// @return The matrix
mat3 scaling2D( const vec2& v);

/// Convert a quaternion to a 4x4 rotation matrix
/// @param q The quaternion
/// @return The rotation matrix
mat4 quaternionToMat4(const vec4& q);

/// Compute rotation matrix
/// @param axis The rotation axis (should be unit length)
/// @param angle The angle in radians
/// @return Rotation matrix
mat4 axisRotation(const vec3& axis, const AnyScalar& angle);

/// Compute rotation matrix
/// @param axis The rotation axis (should be unit length)
/// @param angle The angle in radians
/// @return Rotation matrix
mat3 axisRotation3x3(vec3 axis, float angle);

/// Compute rotation matrix
/// @param axis The rotation axis (should be unit length; w is ignored)
/// @param angle The angle in radians
/// @return Rotation matrix
mat4 axisRotation(const vec4& axis, float angle);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
mat2 inverse(const mat2& m);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
dmat2 inverse(const dmat2& m);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
mat3 inverse(const mat3& m);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
dmat3 inverse(const dmat3& m);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
mat4 inverse(const mat4& m);

/// Compute matrix inverse
/// @param m The matrix. If it is not invertible, the result will be nonsense.
/// @return The inverse
dmat4 inverse(const dmat4& m);

/// Convert degrees to radians
/// @param deg The degree value
/// @return The radian value
float radians(double deg);

/// Return random number uniformly distributed between min and max
/// @param min The minimum value
/// @param max The maximum value
/// @return The random number
float uniform( float min, float max);

/// Return random number between 0.0 and 1.0
/// @return The random number
float uniform();

/// Return random integer x such that min <= x < max
/// @param min Lower bound
/// @param max Upper bound
/// @return Random value
int randrange( int min, int max);

/// Reflect vector about a surface normal, like the GLSL reflect() intrinsic.
/// @param incoming The incoming vector
/// @param N Normal; need not be unit length
/// @return The reflected vector
vec3 reflect(vec3 incoming, vec3 N);

/// Reflect vector about a surface normal, like the GLSL reflect() intrinsic.
/// @param incoming The incoming vector
/// @param N Normal; need not be unit length
/// @return The reflected vector
dvec3 reflect(dvec3 incoming, dvec3 N);

};  //namespace
