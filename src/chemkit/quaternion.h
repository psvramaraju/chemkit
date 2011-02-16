/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
**
** This file is part of chemkit. For more information see
** <http://www.chemkit.org>.
**
** chemkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** chemkit is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with chemkit. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#ifndef CHEMKIT_QUATERNION_H
#define CHEMKIT_QUATERNION_H

#include "chemkit.h"

#include "point.h"
#include "vector.h"
#include "genericquaternion.h"

namespace chemkit {

class CHEMKIT_EXPORT Quaternion : public GenericQuaternion<Float>
{
    public:
        // construction and destruction
        Quaternion(Float x, Float y, Float z, Float r);
        Quaternion(const Point &point, Float r);
        Quaternion(const Vector &vector, Float r);
        Quaternion(const GenericQuaternion<Float> &quaternion);
        Quaternion(const StaticVector<Float, 4> &quaternion);

        // properties
        Point toPoint() const;
        Vector toVector() const;

        // static methods
        static Quaternion rotation(const Vector &axis, Float angle);
        static Quaternion rotationRadians(const Vector &axis, Float angle);
        static Point rotate(const Point &point, const Vector &axis, Float angle);
        static Point rotateRadians(const Point &point, const Vector &axis, Float angle);
        static Vector rotate(const Vector &vector, const Vector &axis, Float angle);
        static Vector rotateRadians(const Vector &vector, const Vector &axis, Float angle);
};

} // end chemkit namespace

#include "quaternion-inline.h"

#endif // CHEMKIT_QUATERNION_H