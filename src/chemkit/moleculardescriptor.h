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

#ifndef CHEMKIT_MOLECULARDESCRIPTOR_H
#define CHEMKIT_MOLECULARDESCRIPTOR_H

#include "chemkit.h"

#include <string>

#include <QList>
#include <QVariant>

namespace chemkit {

class Molecule;
class MolecularDescriptorPrivate;

class CHEMKIT_EXPORT MolecularDescriptor
{
    public:
        // typedefs
        typedef MolecularDescriptor* (*CreateFunction)();

        // construction and destruction
        virtual ~MolecularDescriptor();

        // properties
        std::string name() const;

        // descriptor
        virtual QVariant value(const Molecule *molecule) const;

        // static methods
        static MolecularDescriptor* create(const std::string &name);
        static QList<std::string> descriptors();
        static void registerDescriptor(const std::string &name, CreateFunction function);
        static void unregisterDescriptor(const std::string &name, CreateFunction function);

    protected:
        MolecularDescriptor(const std::string &name);

    private:
        MolecularDescriptorPrivate* const d;
};

} // end chemkit namespace

#endif // CHEMKIT_MOLECULARDESCRIPTOR_H
