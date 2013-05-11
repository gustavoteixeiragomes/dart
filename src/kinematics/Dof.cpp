/*
 * Copyright (c) 2011, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Sehoon Ha <sehoon.ha@gmail.com>
 * Date: 06/12/2011
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

#include "kinematics/Transformation.h"
#include "kinematics/Dof.h"

namespace kinematics
{

Dof::Dof()
{
    _init();
}

Dof::Dof(double _v)
{
    _init(_v);
}

Dof::Dof(double _v, const char * _name)
{
    _init(_v, _name);
}

Dof::Dof(double _v, double _min, double _max)
{
    _init(_v, "Unknown Dof", _min, _max);
}

Dof::Dof(double _v, const char * _name, double _min, double _max)
{
    _init(_v, _name, _min, _max);
}

void Dof::setValue(double _v)
{
    m_q = _v;

    if (mTrans != NULL)
        mTrans->setDirty();
}

void Dof::_init(double _v, const char * _name, double _min, double _max)
{
    double inf = std::numeric_limits<double>::infinity();

    m_q = _v;
    mMin_q = _min;
    mMax_q = _max;

    m_dq = 0.0;
    mMin_dq = -inf;
    mMax_dq = inf;

    m_ddq = 0.0;
    mMin_ddq = -inf;
    mMax_ddq = inf;

    mTorque = 0.0;
    mMinTorque = -inf;
    mMaxTorque = inf;

    strcpy(mName, _name);
    mSkelIndex = -1;
    mVariable = false;
    mTrans = NULL;
    mJoint = NULL;	// remains null if const dof
}

} // namespace kinematics

