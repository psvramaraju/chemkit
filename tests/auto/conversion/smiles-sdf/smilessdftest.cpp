/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
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

#include "smilessdftest.h"

#include <boost/make_shared.hpp>

#include <chemkit/molecule.h>
#include <chemkit/lineformat.h>
#include <chemkit/moleculefile.h>
#include <chemkit/moleculefileformat.h>

void SmilesSdfTest::initTestCase()
{
    std::vector<std::string> lineFormats = chemkit::LineFormat::formats();
    QVERIFY(std::find(lineFormats.begin(), lineFormats.end(), "smiles") != lineFormats.end());

    std::vector<std::string> fileFormats = chemkit::MoleculeFileFormat::formats();
    QVERIFY(std::find(fileFormats.begin(), fileFormats.end(), "sdf") != fileFormats.end());
}

void SmilesSdfTest::ethanol()
{
    boost::shared_ptr<chemkit::Molecule> molecule = boost::make_shared<chemkit::Molecule>("CCO", "smiles");
    QCOMPARE(molecule->formula(), std::string("C2H6O"));

    chemkit::MoleculeFile file;
    file.addMolecule(molecule);

    std::stringstream buffer;
    file.write(buffer, "sdf");

    file.clear();
    file.read(buffer, "sdf");
    QCOMPARE(file.moleculeCount(), size_t(1));
    QCOMPARE(molecule->formula("inchi"), file.molecule(0)->formula("inchi"));
}

QTEST_APPLESS_MAIN(SmilesSdfTest)
