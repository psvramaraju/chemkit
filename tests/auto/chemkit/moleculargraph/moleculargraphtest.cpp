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

#include <QtTest>

#include <chemkit/molecule.h>
#include <chemkit/atommapping.h>
#include <chemkit/moleculargraph.h>

class MolecularGraphTest : public QObject
{
    Q_OBJECT

    private slots:
        void initTestCase();
        void cleanupTestCase();

        void basic();
        void cyclicGraph();
        void hydrogenDepletedGraph();
        void isomorphism();

    private:
        chemkit::Molecule *m_empty;
        chemkit::Molecule *m_benzene;
        chemkit::Molecule *m_diphenylEther;
        chemkit::Molecule *m_ethanol;
        chemkit::Molecule *m_octane;
        chemkit::Molecule *m_tyrosine;
};

void MolecularGraphTest::initTestCase()
{
    m_empty = new chemkit::Molecule;
    QCOMPARE(m_empty->formula(), QString());
    m_benzene = new chemkit::Molecule("1/C6H6/c1-2-4-6-5-3-1/h1-6H", "inchi");
    QCOMPARE(m_benzene->formula(), QString("C6H6"));
    m_diphenylEther = new chemkit::Molecule("1/C12H10O/c1-3-7-11(8-4-1)13-12-9-5-2-6-10-12/h1-10H", "inchi");
    QCOMPARE(m_diphenylEther->formula(), QString("C12H10O"));
    m_ethanol = new chemkit::Molecule("1/C2H6O/c1-2-3/h3H,2H2,1H3", "inchi");
    QCOMPARE(m_ethanol->formula(), QString("C2H6O"));
    m_octane = new chemkit::Molecule("1/C8H18/c1-3-5-7-8-6-4-2/h3-8H2,1-2H3", "inchi");
    QCOMPARE(m_octane->formula(), QString("C8H18"));
    m_tyrosine = new chemkit::Molecule("1/C9H11NO3/c10-8(9(12)13)5-6-1-3-7(11)4-2-6/h1-4,8,11H,5,10H2,(H,12,13)", "inchi");
    QCOMPARE(m_tyrosine->formula(), QString("C9H11NO3"));
}

void MolecularGraphTest::cleanupTestCase()
{
    delete m_empty;
    delete m_benzene;
    delete m_diphenylEther;
    delete m_ethanol;
    delete m_octane;
    delete m_tyrosine;
}

void MolecularGraphTest::basic()
{
    chemkit::MolecularGraph graph(m_ethanol);
    QVERIFY(graph.molecule() == m_ethanol);
    QCOMPARE(graph.atomCount(), 9);
    QCOMPARE(graph.bondCount(), 8);
    QCOMPARE(graph.size(), 9);
    QCOMPARE(graph.isEmpty(), false);

    for(int i = 0; i < graph.size(); i++){
        const chemkit::Atom *atom = graph.atom(i);
        QCOMPARE(graph.indexOf(atom), i);

        if(atom->is(chemkit::Atom::Carbon)){
            QCOMPARE(graph.neighborCount(i), 4);
            QCOMPARE(graph.neighbors(i).size(), 4);
        }
        else if(atom->is(chemkit::Atom::Hydrogen)){
            QCOMPARE(graph.neighborCount(i), 1);
            QCOMPARE(graph.neighbors(i).size(), 1);
        }
        else if(atom->is(chemkit::Atom::Oxygen)){
            QCOMPARE(graph.neighborCount(i), 2);
            QCOMPARE(graph.neighbors(i).size(), 2);
        }
    }

    graph = chemkit::MolecularGraph(m_empty);
    QCOMPARE(graph.atomCount(), 0);
    QCOMPARE(graph.bondCount(), 0);
    QCOMPARE(graph.size(), 0);
}

void MolecularGraphTest::cyclicGraph()
{
    chemkit::MolecularGraph *graph;

    // empty
    graph = chemkit::MolecularGraph::cyclicGraph(m_empty);
    QCOMPARE(graph->size(), 0);
    delete graph;

    // benzene
    graph = chemkit::MolecularGraph::cyclicGraph(m_benzene);
    QCOMPARE(graph->size(), 6);
    delete graph;

    // diphenyl ether
    graph = chemkit::MolecularGraph::cyclicGraph(m_diphenylEther);
    QCOMPARE(graph->size(), 13);
    delete graph;

    // ethanol
    graph = chemkit::MolecularGraph::cyclicGraph(m_ethanol);
    QCOMPARE(graph->size(), 0);
    delete graph;

    // octane
    graph = chemkit::MolecularGraph::cyclicGraph(m_octane);
    QCOMPARE(graph->size(), 0);
    delete graph;

    // tyrosine
    graph = chemkit::MolecularGraph::cyclicGraph(m_tyrosine);
    QCOMPARE(graph->size(), 6);
    delete graph;
}

void MolecularGraphTest::hydrogenDepletedGraph()
{
    chemkit::MolecularGraph *graph;

    // empty
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_empty);
    QCOMPARE(graph->size(), 0);
    delete graph;

    // benzene
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_benzene);
    QCOMPARE(graph->size(), 6);
    for(int i = 0; i < graph->size(); i++)
        QCOMPARE(graph->atom(i)->isTerminalHydrogen(), false);
    delete graph;

    // diphenyl ether
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_diphenylEther);
    QCOMPARE(graph->size(), 13);
    for(int i = 0; i < graph->size(); i++)
        QCOMPARE(graph->atom(i)->isTerminalHydrogen(), false);
    delete graph;

    // ethanol
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_ethanol);
    QCOMPARE(graph->size(), 3);
    for(int i = 0; i < graph->size(); i++)
        QCOMPARE(graph->atom(i)->isTerminalHydrogen(), false);
    delete graph;

    // octane
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_octane);
    QCOMPARE(graph->size(), 8);
    for(int i = 0; i < graph->size(); i++)
        QCOMPARE(graph->atom(i)->isTerminalHydrogen(), false);
    delete graph;

    // tyrosine
    graph = chemkit::MolecularGraph::hydrogenDepletedGraph(m_tyrosine);
    QCOMPARE(graph->size(), 13);
    for(int i = 0; i < graph->size(); i++)
        QCOMPARE(graph->atom(i)->isTerminalHydrogen(), false);
    delete graph;
}

void MolecularGraphTest::isomorphism()
{
    chemkit::MolecularGraph *benzene = chemkit::MolecularGraph::hydrogenDepletedGraph(m_benzene);
    chemkit::MolecularGraph *tyrosine = chemkit::MolecularGraph::hydrogenDepletedGraph(m_tyrosine);

    chemkit::AtomMapping mapping = chemkit::MolecularGraph::isomorphism(benzene, tyrosine);
    QVERIFY(mapping.source() == m_benzene);
    QVERIFY(mapping.target() == m_tyrosine);
    QCOMPARE(mapping.size(), 6);

    delete benzene;
    delete tyrosine;
}

QTEST_APPLESS_MAIN(MolecularGraphTest)
#include "moleculargraphtest.moc"