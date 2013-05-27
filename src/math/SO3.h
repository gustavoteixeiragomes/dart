/*
 * Copyright (c) 2011, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 * Date: 05/06/2013
 *
 * Geoorgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_MATH_SO3_H
#define DART_MATH_SO3_H

#include <Eigen/Dense>
#include "math/UtilsMath.h"

// TODO: Let's use noalias().
// TODO: Not using Eigen?

namespace dart {
namespace math {

class so3; // Lie algebra of SO(3)
class SO3; // SO(3), Special orthogonal group (3x3 rotation matrix)

typedef Eigen::Vector3d Vec3;

//==============================================================================
/// @brief
class so3
{
public: // Constructors and destructor
    // Aligned allocator for Eigen member variable.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    /// @brief
    so3();
    
    /// @brief
    explicit so3(double _w0, double _w1, double _w2);
    
    /// @brief
    explicit so3(const Eigen::Vector3d& _w);
    
    /// @brief
    virtual ~so3();
    
public: // Operators
    /// @brief Substitution operator.
    const so3& operator=(const so3& _w);

    /// @brief Casting operator.
    so3* operator&() { return this; }

    /// @brief Const Casting operator.
    const so3* operator&() const { return this; }

    /// @brief Access to the idx th element.
    double& operator()(int _i);

    /// @brief Access to the idx th element.
    const double& operator()(int _i) const;

    /// @brief
    bool operator==(const so3& _w) const;

    /// @brief Unary plus operator.
    so3 operator+(void) const;

    /// @brief Unary minus operator.
    so3 operator-(void) const;

    /// @brief Addition and substitution operator.
    const so3& operator+=(const so3& _w);

    /// @brief -= operator.
    const so3& operator-=(const so3& _w);

    /// @brief *= operator.
    const so3& operator*=(double _c);

    /// @brief Addition operator.
    so3 operator+(const so3& _w) const;

    /// @brief Subtraction operator.
    so3 operator-(const so3& _w) const;

    /// @brief Multiplication operator.
    so3 operator*(double _c) const;

    /// @brief Double multiplication.
    friend so3 operator*(double c, const so3& _w);

    /// @brief std::ostream standard output
    friend std::ostream& operator<<(std::ostream& _os, const so3& _w)
    {
        _os << math::precision(_w.mw(0), 6)
            << " "
            << math::precision(_w.mw(1), 6)
            << " "
            << math::precision(_w.mw(2), 6);
    }

    /// @brief
    std::string toString() const;

public:
    /// @brief
    void setValues(double _w0, double _w1, double _w2);

    /// @brief
    void setZero(void) { mw.setZero(); }

    /// @brief
    double getAngle(void) const { return mw.norm(); }
    
    /// @brief
    void setNormalize(void) { mw.normalize(); }

    /// @brief
    void setFromSkewSymmetrixMatrix(const Eigen::Matrix3d& _ssm);

    /// @brief
    Eigen::Matrix3d getSkewSymmetrixMatrix(void) const;

    /// @brief
    void setVector(const Eigen::Vector3d& _w);
    
    /// @brief
    const Eigen::Vector3d& getVector(void) const { return mw; }
    
protected:
    /// @brief
    Eigen::Vector3d mw;
    
private:

    friend class se3;
    friend class dse3;
    friend class SO3;
    friend class SE3;
};

//==============================================================================
/// @brief Special orthogonal group in 3d space.
class SO3
{
public: // Constructors and destructor
    // Aligned allocator for Eigen member variable.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    /// @brief
    SO3();
    
    /// @brief
    explicit SO3(const Eigen::Matrix3d& _rotation);
    
//    /// @brief
//    explicit SO3(const Eigen::Vector3d& _axisX,
//                 const Eigen::Vector3d& _axisY,
//                 const Eigen::Vector3d& _axisZ);
    
    /// @brief
    explicit SO3(double _R00, double _R01, double _R02,
                 double _R10, double _R11, double _R12,
                 double _R20, double _R21, double _R22);
    
    /// @brief
    explicit SO3(const so3& _w);
    
    /// @brief
    // TODO: NOT IMPLEMENTED !
    SO3(double _EulerX, double _EulerY, double _EulerZ);

    /// @brief
    virtual ~SO3();
    
public:
    /// @brief Substitution operator.
    const SO3& operator=(const SO3& _R);

    /// @brief Casting operator.
    SO3* operator&() { return this; }

    /// @brief Const Casting operator.
    const SO3* operator&() const { return this; }

    /// @brief
    double& operator()(int _i, int _j);

    /// @brief
    const double& operator()(int _i, int _j) const;

    /// @brief Multiplication operator.
    /// T_this *= T is a fast version of T_this = T_this * T.
    const SO3& operator*=(const SO3 & _R);

    //    /// @brief Multiplication operator.
    //    ///	T_this /= T is a fast version of T_this =  T_this * Inv(T).
    //    const SO3& operator/=(const SO3& _R);

    //	/// @brief Multiplication operator.
    //	///	T_this \%= T is a fast version of T_this= Inv(T_this) * T.
    //	const SO3& operator%=(const SO3& _R);

    /// @brief Multiplication operator.
    SO3 operator*(const SO3& _R) const;

    //	/// @brief Multiplication operator, T_this / T = T_this * Inv(T).
    //	SO3 operator/(const SO3& _R) const;

    //	/// @brief Multiplication operator, T_this \% T = Inv(T_this) * T.
    //	SO3 operator%(const SO3& _R) const;

    /// @brief
    Eigen::Vector3d operator*(const Eigen::Vector3d& _q) const;

    /// @brief
    so3 operator*(const so3& _w) const;

    //    /// @brief
    //    Eigen::Vector3d operator%(const Eigen::Vector3d& _q) const;

    /// @brief
    bool operator==(const SO3& _R) const;

    // @brief std::ostream standard output
    friend std::ostream& operator<<(std::ostream& _os, const SO3& _R)
    {
        Eigen::Vector3d vec = _R.getEulerXYZ();

        _os << math::precision(vec(0), 6)
            << " "
            << math::precision(vec(1), 6)
            << " "
            << math::precision(vec(2), 6);
    }

public:
    /// @brief
    void setValues(double _R00, double _R01, double _R02,		//Rx
                   double _R10, double _R11, double _R12,		//Ry
                   double _R20, double _R21, double _R22);
    
    /// @brief
    void setIdentity(void) { mRotation.setIdentity(); }
    
    /// @brief
    void setExp(const so3& _S);
    
    /// @brief
    void setExp(const so3& _S, double theta);
    
    /// @brief
    const SO3 getInverse() const { return SO3(mRotation.transpose()); }
    
    /// @brief
    const Eigen::Matrix3d& getMatrix() const { return mRotation; }

    /// @brief
    void setEulerXYZ(const Eigen::Vector3d& _EulerAngles);

    /// @brief
    void setEulerZXY(const Eigen::Vector3d& _EulerAngles);

    /// @brief
    void setEulerZYX(const Eigen::Vector3d& _EulerAngles);

    /// @brief
    void setEulerZYZ(const Eigen::Vector3d& _EulerAngles);

    /// @brief
    Eigen::Vector3d getEulerXYZ() const;

    /// @brief
    Eigen::Vector3d getEulerZXY() const;

    /// @brief
    Eigen::Vector3d getEulerZYX() const;

    /// @brief
    Eigen::Vector3d getEulerZYZ() const;
    
    /// @brief
    // TODO: NOT IMPLEMENTED
    so3 getLog() const;

    /// @brief
    double getAxisAngle(Eigen::Vector3d* _axis, double* _angle) const;

protected:
    /// @brief
    Eigen::Matrix3d mRotation;
    
private:
};

} // namespace math
} // namespace dart

#endif // DART_MATH_LIE_GROUPS_H