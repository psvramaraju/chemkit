/******************************************************************************
**
** Copyright (C) 2009-2012 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#ifndef CHEMKIT_MOLECULEGEOMETRYOPTIMIZER_H
#define CHEMKIT_MOLECULEGEOMETRYOPTIMIZER_H

#include "md.h"

#include <string>

#include <boost/thread/future.hpp>

namespace chemkit {

class Molecule;
class MoleculeGeometryOptimizerPrivate;

class CHEMKIT_MD_EXPORT MoleculeGeometryOptimizer
{
public:
    // construction and destruction
    MoleculeGeometryOptimizer(Molecule *molecule = 0);
    ~MoleculeGeometryOptimizer();

    // properties
    void setMolecule(Molecule *molecule);
    Molecule* molecule() const;
    bool setForceField(const std::string &forceField);
    std::string forceField() const;

    // energy
    Real energy() const;

    // optimization
    bool setup();
    void step();
    bool converged();
    bool optimize();
    void writeCoordinates();

    // error handling
    std::string errorString() const;

    // static methods
    static bool optimizeCoordinates(Molecule *molecule);
    static boost::shared_future<bool> optimizeCoordinatesAsync(Molecule *molecule);

private:
    MoleculeGeometryOptimizerPrivate* const d;
};

} // end chemkit namespace

#endif // CHEMKIT_MOLECULEGEOMETRYOPTIMIZER_H
