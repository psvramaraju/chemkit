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

#ifndef CHEMKIT_FORCEFIELDCALCULATION_H
#define CHEMKIT_FORCEFIELDCALCULATION_H

#include "chemkit.h"

#include <QVector>

#include "point3.h"
#include "vector3.h"

namespace chemkit {

class ForceField;
class ForceFieldAtom;
class ForceFieldCalculationPrivate;

class CHEMKIT_EXPORT ForceFieldCalculation
{
    public:
        // enumerations
        enum Type {
            BondStrech = 0x01,
            AngleBend = 0x02,
            Torsion = 0x04,
            Inversion = 0x08,
            VanDerWaals = 0x10,
            Electrostatic = 0x20
        };

        // properties
        int type() const;
        bool isSetup() const;
        ForceField* forceField() const;

        // atoms
        const ForceFieldAtom* atom(int index) const;
        QVector<const ForceFieldAtom *> atoms() const;
        int atomCount() const;
        bool contains(const ForceFieldAtom *atom) const;

        // parameters
        void setParameter(int index, Float value);
        Float parameter(int index) const;
        QVector<Float> parameters() const;
        int parameterCount() const;

        // calculations
        virtual Float energy() const;
        virtual QVector<Vector3> gradient() const;
        QVector<Vector3> numericalGradient() const;

    protected:
        ForceFieldCalculation(int type, int atomCount, int parameterCount);
        virtual ~ForceFieldCalculation();
        void setAtom(int index, const ForceFieldAtom *atom);
        Float distance(const ForceFieldAtom *a, const ForceFieldAtom *b) const;
        QVector<Vector3> distanceGradient(const ForceFieldAtom *a, const ForceFieldAtom *b) const;
        Float bondAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        Float bondAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        QVector<Vector3> bondAngleGradient(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        QVector<Vector3> bondAngleGradientRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        Float torsionAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float torsionAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        QVector<Vector3> torsionAngleGradient(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        QVector<Vector3> torsionAngleGradientRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float wilsonAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float wilsonAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        QVector<Vector3> wilsonAngleGradient(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        QVector<Vector3> wilsonAngleGradientRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;

    private:
        void setSetup(bool setup);
        QVector<Vector3> distanceGradient(const Point3 &a, const Point3 &b) const;
        QVector<Vector3> bondAngleGradientRadians(const Point3 &a, const Point3 &b, const Point3 &c) const;
        QVector<Vector3> torsionAngleGradientRadians(const Point3 &a, const Point3 &b, const Point3 &c, const Point3 &d) const;
        QVector<Vector3> wilsonAngleGradientRadians(const Point3 &a, const Point3 &b, const Point3 &c, const Point3 &d) const;

        friend class ForceField;

    private:
        ForceFieldCalculationPrivate* const d;
};

} // end chemkit namespace

#include "forcefieldcalculation-inline.h"

#endif // CHEMKIT_FORCEFIELDCALCULATION_H
