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

#include "sybyltest.h"

#include <boost/range/algorithm.hpp>

#include <chemkit/molecule.h>
#include <chemkit/atomtyper.h>
#include <chemkit/moleculefile.h>
#include <chemkit/moleculefileformat.h>

const std::string dataPath = "../../../data/";

void SybylTest::initTestCase()
{
    // verify that the sybyl plugin registered itself correctly
    QVERIFY(boost::count(chemkit::AtomTyper::typers(), "sybyl") == 1);
    QVERIFY(boost::count(chemkit::MoleculeFileFormat::formats(), "mol2") == 1);
}

void SybylTest::readMol2_data()
{
    QTest::addColumn<QString>("fileNameString");
    QTest::addColumn<QString>("formulaString");

    QTest::newRow("uridine") << "uridine.mol2" << "C9H13N2O9P";
}

void SybylTest::readMol2()
{
    QFETCH(QString, fileNameString);
    QFETCH(QString, formulaString);

    QByteArray fileName = fileNameString.toAscii();
    QByteArray formula = formulaString.toAscii();

    chemkit::MoleculeFile file(dataPath + fileName.constData());
    bool ok = file.read();
    if(!ok)
        qDebug() << file.errorString().c_str();
    QVERIFY(ok);

    QCOMPARE(file.moleculeCount(), size_t(1));
    boost::shared_ptr<chemkit::Molecule> molecule = file.molecule();
    QVERIFY(molecule != 0);
    QCOMPARE(molecule->formula().c_str(), formula.constData());
}

QTEST_APPLESS_MAIN(SybylTest)
