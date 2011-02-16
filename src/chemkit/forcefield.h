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

#ifndef CHEMKIT_FORCEFIELD_H
#define CHEMKIT_FORCEFIELD_H

#include "chemkit.h"

#include <QtCore>

#include "point.h"
#include "vector.h"
#include "forcefieldatom.h"
#include "forcefieldcalculation.h"

namespace chemkit {

class Atom;
class Molecule;
class ForceFieldPrivate;

class CHEMKIT_EXPORT ForceField
{
    public:
        // enumerations
        enum Flag {
            AnalyticalGradient = 0x01
        };
        Q_DECLARE_FLAGS(Flags, Flag)

        // typedefs
        typedef ForceField* (*CreateFunction)();

        // construction and destruction
        virtual ~ForceField();

        // properties
        QString name() const;
        ForceField::Flags flags() const;
        int size() const;
        QList<ForceFieldAtom *> atoms() const;
        int atomCount() const;
        ForceFieldAtom* atom(int index) const;
        ForceFieldAtom* atom(const Atom *atom) const;

        // setup
        void addMolecule(const Molecule *molecule);
        void removeMolecule(const Molecule *molecule);
        QList<const Molecule *> molecules() const;
        int moleculeCount() const;
        virtual bool setup();
        bool isSetup() const;
        virtual void clear();

        // parameters
        void setParameterSet(const QString &name);
        QString parameterSet() const;
        QStringList parameterSets() const;
        void setParameterFile(const QString &fileName);
        QString parameterFile() const;

        // calculations
        QList<ForceFieldCalculation *> calculations() const;
        int calculationCount() const;
        virtual Float energy() const;
        QVector<Vector> gradient() const;
        QVector<Vector> numericalGradient() const;
        Float largestGradient() const;
        Float rootMeanSquareGradient() const;

        // coordinates
        void readCoordinates(const Molecule *molecule);
        void readCoordinates(const Atom *atom);
        void writeCoordinates(Molecule *molecule) const;
        void writeCoordinates(Atom *atom) const;

        // energy minimization
        bool minimizationStep(Float converganceValue = 0.1);
        QFuture<bool> minimizationStepAsync(Float converganceValue = 0.1);

        // geometry
        Float distance(const ForceFieldAtom *a, const ForceFieldAtom *b) const;
        Float bondAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        Float bondAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
        Float torsionAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float torsionAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float wilsonAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
        Float wilsonAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;

        // error handling
        QString errorString() const;

        // static methods
        static ForceField* create(const QString &name);
        static QStringList forceFields();
        static void registerForceField(const QString &name, CreateFunction function);
        static void unregisterForceField(const QString &name, CreateFunction function);

    protected:
        ForceField(const QString &name);
        void setFlags(Flags flags);
        void addAtom(ForceFieldAtom *atom);
        void removeAtom(ForceFieldAtom *atom);
        void addCalculation(ForceFieldCalculation *calculation);
        void removeCalculation(ForceFieldCalculation *calculation);
        void setCalculationSetup(ForceFieldCalculation *calculation, bool setup);
        void addParameterSet(const QString &name, const QString &fileName);
        void removeParameterSet(const QString &name);
        void setErrorString(const QString &errorString);

    private:
        ForceFieldPrivate* const d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ForceField::Flags)

} // end chemkit namespace

#endif // CHEMKIT_FORCEFIELD_H