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

#ifndef DART_MATH_SE3_H
#define DART_MATH_SE3_H

#include <Eigen/Dense>
#include "math/UtilsMath.h"

#include "math/SO3.h"

// TODO: Let's use noalias().
// TODO: Not using Eigen?
namespace dart {
namespace math {

class se3;  // se(3), Lie algebra of SE(3)
class dse3; // se*(3), Dual space of se(3)
class SE3;  // SE(3), Special Euclidean group
class TSE3; // TSE(3), Tangential space of SE(3)

// TODO: Is here right place?
typedef Matrix<double, 6, 1> Vector6d;

/// @brief Transform the reference frame of the generalized velocity
/// (angular velocity + linear velocity) from frame 2 to frame 1.
/// @param[in] _T12 Transformation matrix from frame 1 to frame 2.
/// @param[in] _vel2 Generalized velocity represented in frame 2.
/// @return Generalized velocity represented in frame 1.
se3 Ad(const SE3& _T12, const se3& _vel2);

/// @brief Transform the reference frame of the generalized velocity
/// (angular velocity + linear velocity) from frame 1 to frame 2.
/// @param[in] _T12 Transformation matrix from frame 1 to frame 2.
/// @param[in] _vel1 Generalized velocity represented in frame 1.
/// @return Generalized velocity represented in frame 2.
se3 InvAd(const SE3& _T21, const se3& _vel2);

/// @brief
dse3 dAd(const SE3& _T12, const dse3& _force2);

/// @brief
dse3 InvdAd(const SE3& _T21, const dse3& _force2);

/// @brief
se3 ad(const se3& V1, const se3& V2);

/// @brief
dse3 dad(const se3& V, const dse3& F);

//==============================================================================
/// @brief se3 is a class for representing \f$se(3)\f$, the Lie algebra of
/// \f$SE(3)\f$.
///
/// Geometrically se3 deals with generalized velocity which consist of linear
/// velocity and angular velocity.
class se3
{
public:
    // CONSTRUCTORS AND DESTRUCTOR ---------------------------------------------

    // Aligned allocator for Eigen member variable.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /// @brief Default constructor.
    se3();

    /// @brief Copy constructor.
    se3(const se3& _V);

    /// @brief
    explicit se3(const Vector6d& _V);

    /// @brief
    se3(double _w0, double _w1, double _w2,
        double _v0, double _v1, double _v2);

    /// @brief
    se3(const so3& _w,
        const Eigen::Vector3d& _v);

    /// @brief
    se3(const math::so3& _w);

    /// @brief
    se3(const Eigen::Vector3d& _v);

    /// @brief Default destructor.
    virtual ~se3();

public:
    // OPERATORS ---------------------------------------------------------------

    /// @brief Substitution operator.
    const se3& operator=(const se3& _V);

    /// @brief Casting operator.
    se3* operator&() { return this; }

    /// @brief Const Casting operator.
    const se3* operator&() const { return this; }

//    /// @brief Access to the idx th element.
//    double& operator()(int _i);

//    /// @brief Access to the idx th element.
//    const double& operator()(int _i) const;

    /// @brief Unary plus operator.
    se3 operator+(void) const;

    /// @brief Unary minus operator.
    se3 operator-(void) const;

    /// @brief += operator.
    const se3& operator+=(const se3& _V);

    /// @brief -= operator.
    const se3& operator-=(const se3& _V);

    //	/// @brief *= operator.
    //	const se3& operator*=(const se3& _V);

    /// @brief *= operator with double.
    const se3& operator*=(double _c);

    /// @brief Addition operator.
    se3 operator+(const se3& _V) const;

    /// @brief Subtraction operator.
    se3 operator-(const se3& _V) const;

    //	/// @brief Multiplication operator.
    //	se3 operator*(const se3& _V) const;

    /// @brief double multiplication operator.
    se3 operator*(double _c) const;

    /// @brief Multiplication operator.
    ///
    /// Geometically the return is a tangent vector at _T corresponding to
    /// the body velocity, (mAngular, mLinear).
    TSE3 operator*(const SE3& _T) const;

    /// @brief Multiplication operator.
    //TSE3 operator*(const TSE3& _dT) const;

    /// @brief double multiplication operator.
    friend se3 operator*(double _c, const se3& _V);

public:
    /// @brief
    void setVector(const Vector6d& _V);

    /// @brief
    Vector6d getVector(void) const;

    /// @brief
    void setLinear(const Eigen::Vector3d& _linear) { mLinear = _linear; }
    
    /// @brief
    const Eigen::Vector3d& getLinear() const { return mLinear; }
    
    /// @brief
    void setAngular(const so3& _angular) { mAngular = _angular; }
    
    /// @brief
    const so3& getAngular() const { return mAngular; }
    
    /// @brief
    void setZero(void) { mAngular.setZero(); mLinear.setZero(); }

    /// @brief
    void setAd(const SE3& _T12, const se3& _V2);
    
    /// @brief
    void setInvAd(const SE3& _T21, const se3& _V2);
    
    /// @brief
    void setad(const se3& _V1, const se3& _V2);
    
    /// @brief
    /// @note \f$ \langle F, V\rangle = \langle V, F\rangle = \langle m, w\rangle + \langle f, v\rangle \f$
    ///	,where \f$F=(m,f)\in se(3)^*,\quad V=(w,v)\in se(3)\f$.
    double innerProduct(const dse3& _F) const;

    /// @brief
    std::string toString() const;

protected:
    /// @brief
    so3 mAngular;

    /// @brief
    Eigen::Vector3d mLinear;
    
private:
};

//==============================================================================
/// @brief Dual space of se(3).
///
/// dse3 is a class for representing \f$se^{*}(3)\f$, a dual of the Lie algebra
/// \f$se(3)\f$. Geometrically it deals with generalized force.
class dse3
{
public: // Constructors and destructor -----------------------------------------
    // Aligned allocator for Eigen member variable.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /// @brief Default constructor.
    dse3();

    /// @brief Copy constructor.
    dse3(const dse3& _V);

    /// @brief
    explicit dse3(const Vector6d& _V);

    /// @brief
    explicit dse3(double _m0, double _m1, double _m2,	// angular force
                  double _f0, double _f1, double _f2);	// linear force

    /// @brief
    explicit dse3(const Eigen::Vector3d& _angular,
                  const Eigen::Vector3d& _linear);

    /// @brief Default destructor.
    virtual ~dse3();

public: // Operators -----------------------------------------------------------
    /// @brief Substitution operator.
    const dse3& operator=(const dse3& _F);

    /// @brief Casting operator.
    dse3* operator&() { return this; }

    /// @brief Const Casting operator.
    const dse3* operator&() const { return this; }

    /// @brief Unary plus operator.
    dse3 operator+(void) const;

    /// @brief Unary minus operator.
    dse3 operator-(void) const;

    /// @brief += operator.
    const dse3& operator+=(const dse3& _F);

    /// @brief -= operator.
    const dse3& operator-=(const dse3& _F);

    /// @brief  *= operator with double.
    const dse3& operator*=(double _c);

    /// @brief Addition operator.
    dse3 operator+(const dse3& _F) const;

    /// @brief Subtraction operator.
    dse3 operator-(const dse3& _F) const;

    /// @brief double multiplication operator.
    dse3 operator*(double _c) const;

    /// @brief double multiplication operator. */
    friend dse3 operator*(double _c, const dse3& _F);

public:
    /// @brief
    void setLinear(const Eigen::Vector3d& _linear) { mLinear = _linear; }
    
    /// @brief
    const Eigen::Vector3d& getLinear() const { return mLinear; }
    
    /// @brief
    void setAngular(const Eigen::Vector3d& _angular) { mAngular = _angular; }
    
    /// @brief
    const Eigen::Vector3d& getAngular() const { return mAngular; }
    
    /// @brief
    void setdAd(const SE3& _T12, const dse3& _F2);
    
    /// @brief
    void setInvdAd(const SE3& _T21, const dse3& _F2);
    
    /// @brief
    void setdad(const se3& _V, const dse3& _F);
    
protected:
    /// @brief
    Eigen::Vector3d mLinear;
    
    /// @brief
    Eigen::Vector3d mAngular;
private:
};

//==============================================================================
/// @brief Special Euclidean group in 3d space.
///
/// SE3 is a class for representing the special Euclidean group.
/// Geometrically, it deals with rigid transformations on \f$ \mathbb{R}^3 \f$.
/// SE(3) is defined as the set of
/// mappings \f$g: \mathbb{R}^3 \rightarrow \mathbb{R}^3\f$ of the form \f$g(x) = Rx + p\f$,
/// where \f$R\in\f$ the special orthogonal group and \f$p\in \mathbb{R}^3\f$.
/// An element of SE(3), written as (R, p), can also be represented in
/// the matrix form	\f$\begin{bmatrix} R & p \\ 0 & 1\end{bmatrix}.\f$
class SE3
{
public: // Constructors and destructor
    // Aligned allocator for Eigen member variable.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    /// @brief
    SE3();
    
    /// @brief Copy constructor.
    SE3(const SE3& _T);
    
    /// @brief
    explicit SE3(const Eigen::Matrix4d& _T);
    
    /// @brief
    explicit SE3(const SO3& _R);

    /// @brief
    explicit SE3(const Eigen::Vector3d& _p);

    /// @brief
    SE3(const SO3& _R, const Eigen::Vector3d& _p);
    
    /// @brief Constructor rotation and position part */
    SE3(double _R00, double _R01, double _R02,
        double _R10, double _R11, double _R12,
        double _R20, double _R21, double _R22,
        double _p0, double _p1, double _p2);	// p
    
    /// @brief
    explicit SE3(const so3& _w);
    
    /// @brief
    SE3(const so3& _w, double _theta);
    
    /// @brief
    explicit SE3(const se3& _S);
    
    /// @brief
    SE3(const se3& _S, double _theta);
    
    /// @brief
    SE3(double _EulerX, double _EulerY, double _EulerZ,
        double _x, double _y, double _z);

    /// @brief
    virtual ~SE3();
    
public: // OPERATORS -----------------------------------------------------------
    //    /// @brief Access to the (i, j) element.
    //    double& operator()(int _i, int _j);
    
    /// @brief Substitution operator.
    const SE3& operator=(const SE3& _T);
    
    /// @brief Casting operator.
    SE3* operator&() { return this; }
    
    /// @brief Const Casting operator.
    const SE3* operator&() const { return this; }
    
    /// @brief Multiplication operator.
    /// T_this *= T is a fast version of T_this = T_this * T.
    const SE3& operator*=(const SE3& _T);
    
    //	/// @brief Multiplication operator.
    //	/// T_this /= T is a fast version of T_this =  T_this * Inv(T).
    //	const SE3& operator/=(const SE3& _T);
    
    //	/// @brief Multiplication operator.
    //	/// T_this \%= T is a fast version of T_this= Inv(T_this) * T.
    //	const SE3& operator%=(const SE3& _T);
    
    /// @brief Multiplication operator.
    SE3 operator*(const SE3& _T) const;
    
    /// @brief Multiplication operator.
    TSE3 operator*(const TSE3& _dT) const;

    //	/// @brief Multiplication operator, T_this / T = T_this * Inv(T).
    //	SE3 operator/(const SE3& _T) const;
    
    //	/// @brief Multiplication operator, T_this \% T = Inv(T_this) * T.
    //	SE3 operator%(const SE3& _T) const;
    
    /// @brief Multiplication operator.
    /// @note \f$ T q = R q + p\f$, where
    /// \f$T=(R,p)\in SE(3), \quad q\in\mathbb{R}^3\f$.
    Eigen::Vector3d operator*(const Eigen::Vector3d& _p) const;
    
    //	/// @brief Multiplication operator, T \% q = Inv(T) * q.
    //	Eigen::Vector3d operator%(const Eigen::Vector3d& _q) const;
    
    /// @brief
    bool operator==(const SE3& _T) const;
    
    /// @brief std::ostream standard output
    friend std::ostream& operator<<(std::ostream& _os, const SE3& _T)
    {
        Eigen::RowVector3d rowVec = _T.mPosition.transpose();
        _os << _T.mRotation
            << " "
            << math::precision(rowVec(0), 6)
            << " "
            << math::precision(rowVec(1), 6)
            << " "
            << math::precision(rowVec(2), 6);
    }

public:
    /// @brief
    void setValues(double _R00, double _R01, double _R02,
                   double _R10, double _R11, double _R12,
                   double _R20, double _R21, double _R22,
                   double _p0, double _p1, double _p2);
    
    /// @brief
    void setRotation(const SO3& _rotation) { mRotation = _rotation; }
    
    /// @brief
    const SO3& getRotation() const { return mRotation; }
    
    /// @brief
    void setPosition(const Eigen::Vector3d& _position) { mPosition = _position; }
    
    /// @brief
    const Eigen::Vector3d& getPosition() const { return mPosition; }
    
    /// @brief
    void setExp(const so3& _w);
    
    /// @brief
    void setExp(const so3& _w, double _theta);
    
    /// @brief
    void setExp(const se3& _S);
    
    /// @brief
    void setExp(const se3& _S, double _theta);
    
    /// @brief
    void setValues(double _EulerX, double _EulerY, double _EulerZ,
                   double _x, double _y, double _z);

    /// @brief
    void setIdentity(void);
    
    /// @brief
    void setInverse(void);
    
    /// @brief
    SE3 getInverse(void) const;
    
    /// @brief
    Eigen::Matrix4d getMatrix() const;

protected:
    /// @brief
    SO3 mRotation;
    
    /// @brief
    Eigen::Vector3d mPosition;
    
    friend class TSE3;

private:
};

//==============================================================================
/// @class TSE3
/// @brief Tangent space of SE(3) which consist of se(3) and SE(3)
class TSE3
{
public: // CONSTRUCTORS AND DESTRUCTOR -----------------------------------------
    /// @brief Default constructor.
    TSE3();
    
    /// @brief Copy constructor.
    TSE3(const TSE3& _dT);
    
    /// @brief
    TSE3(const se3& _S, const SE3& _T);

    /// @brief
    TSE3(const SE3& _T, const se3& _S);
    
    /// @brief Default destructor.
    ~TSE3();
    
public: // OPERATORS -----------------------------------------------------------
    /// @brief Substitution operator.
    const TSE3& operator=(const TSE3& _dT);
    
    /// @brief Casting operator.
    TSE3* operator&() { return this; }
    
    /// @brief Const Casting operator.
    const TSE3* operator&() const { return this; }
    
    /// @brief Multiplication operator.
    //const TSE3& operator*=(const TSE3& _dT);
    
    /// @brief Multiplication operator.
    const TSE3& operator*=(const SE3& _T);
    
    /// @brief Multiplication operator.
    const TSE3& operator*=(const se3& _S);
    
    /// @brief Multiplication operator.
    //TSE3 operator*(const TSE3& _dT) const;
    
    /// @brief Multiplication operator.
    TSE3 operator*(const SE3& _T) const;
    
    /// @brief Multiplication operator.
    TSE3 operator*(const se3& _S) const;
    
public: //----------------------------------------------------------------------
    /// @brief
    void setZero(void);
    
private: //---------------------------------------------------------------------
    /// @brief
    se3 mS;

    /// @brief
    SE3 mT;

    friend class SE3;
};

} // namespace math
} // namespace dart

#endif // DART_MATH_LIE_GROUPS_H