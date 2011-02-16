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

#include "coordinatematrix.h"

#include "vector.h"
#include "molecule.h"

namespace chemkit {

// === CoordinateMatrix ==================================================== //
/// \class CoordinateMatrix coordinatematrix.h chemkit/coordinatematrix.h
/// \ingroup chemkit
/// \brief The CoordinateMatrix class contains coordinates.

// --- Construction and Destruction ---------------------------------------- //
/// Creates a new, empty coordinate matrix.
CoordinateMatrix::CoordinateMatrix()
    : m_matrix(0, 3)
{
}

/// Creates a new, empty coordinate matrix with space for \p size
/// points.
CoordinateMatrix::CoordinateMatrix(int size)
    : m_matrix(size, 3)
{
}

/// Creates a new coordinate matrix with the coordinates from
/// \p molecule.
CoordinateMatrix::CoordinateMatrix(const Molecule *molecule)
    : m_matrix(molecule->size(), 3)
{
    int size = molecule->size();

    for(int i = 0; i < size; i++){
        Point position = molecule->atom(i)->position();
        m_matrix.setValue(i, 0, position.x());
        m_matrix.setValue(i, 1, position.y());
        m_matrix.setValue(i, 2, position.z());
    }
}

/// Creates a new coordinate matrix with the coordinates from
/// \p conformer.
CoordinateMatrix::CoordinateMatrix(const Conformer *conformer)
    : m_matrix(conformer->molecule()->size(), 3)
{
    int size = conformer->molecule()->size();

    for(int i = 0; i < size; i++){
        Point position = conformer->position(conformer->molecule()->atom(i));
        m_matrix.setValue(i, 0, position.x());
        m_matrix.setValue(i, 1, position.y());
        m_matrix.setValue(i, 2, position.z());
    }
}

/// Creates a new coordinate matrix with the coordinates from
/// \p atoms.
CoordinateMatrix::CoordinateMatrix(const QList<Atom *> &atoms)
    : m_matrix(atoms.size(), 3)
{
    int size = atoms.size();

    for(int i = 0; i < size; i++){
        Point position = atoms[i]->position();
        m_matrix.setValue(i, 0, position.x());
        m_matrix.setValue(i, 1, position.y());
        m_matrix.setValue(i, 2, position.z());
    }
}

/// Creates a new coordinate matrix that contains \p points.
CoordinateMatrix::CoordinateMatrix(const QList<Point> &points)
    : m_matrix(points.size(), 3)
{
    for(int i = 0; i < points.size(); i++){
        Point position = points[i];
        m_matrix.setValue(i, 0, position.x());
        m_matrix.setValue(i, 1, position.y());
        m_matrix.setValue(i, 2, position.z());
    }
}

/// Creates a new coordinate matrix that is a copy of \p matrix.
CoordinateMatrix::CoordinateMatrix(const CoordinateMatrix &matrix)
    : m_matrix(matrix.m_matrix)
{
}

/// Destroys the coordinate matrix.
CoordinateMatrix::~CoordinateMatrix()
{
}

// --- Properties ---------------------------------------------------------- //
/// Sets the size of the matrix to \p size.
void CoordinateMatrix::setSize(int size)
{
    m_matrix.setRowCount(size);
}

/// Returns the number of coordinates in the matrix.
int CoordinateMatrix::size() const
{
    return m_matrix.rowCount();
}

/// Returns \c true if the matrix is empty.
bool CoordinateMatrix::isEmpty() const
{
    return size() == 0;
}

/// Returns a matrix containing the data in the coordinate matrix.
Matrix CoordinateMatrix::toMatrix() const
{
    return m_matrix;
}

// --- Coordinates --------------------------------------------------------- //
/// Sets the position at \p index to \p position.
void CoordinateMatrix::setPosition(int index, const Point &position)
{
    m_matrix.setValue(index, 0, position.x());
    m_matrix.setValue(index, 1, position.y());
    m_matrix.setValue(index, 2, position.z());
}

/// Sets the position at \p index to (\p x, \p y, \p z).
void CoordinateMatrix::setPosition(int index, Float x, Float y, Float z)
{
    setPosition(index, Point(x, y, z));
}

/// Returns the coordinates at \p index.
Point CoordinateMatrix::position(int index) const
{
    return Point(m_matrix(index, 0),
                 m_matrix(index, 1),
                 m_matrix(index, 2));
}

/// Sets the value at \p row and \p column to \p value.
void CoordinateMatrix::setValue(int row, int column, Float value)
{
    m_matrix.setValue(row, column, value);
}

/// Returns the value at \p row and \p column;
Float CoordinateMatrix::value(int row, int column) const
{
    return m_matrix.value(row, column);
}

/// Appends \p position to the matrix.
void CoordinateMatrix::append(const Point &position)
{
    insert(size(), position);
}

/// Appends the point (\p x, \p y, \p z) to the matrix.
void CoordinateMatrix::append(Float x, Float y, Float z)
{
    append(chemkit::Point(x, y, z));
}

/// Inserts \p position at \p index.
void CoordinateMatrix::insert(int index, const Point &position)
{
    // resize to make space for the new position
    if(index >= size()){
        setSize(index + 1);
    }
    else{
        setSize(size() + 1);
    }

    // copy old positions
    for(int i = size() - 1; i > index; i--){
        setPosition(i, this->position(i - 1));
    }

    // set the new position
    setPosition(index, position);
}

/// Inserts the point (\p x, \p y, \p z) at \p index.
void CoordinateMatrix::insert(int index, Float x, Float y, Float z)
{
    insert(index, chemkit::Point(x, y, z));
}

/// Removes the position at \p index.
void CoordinateMatrix::remove(int index)
{
    for(int i = index + 1; i < size(); i++){
        setPosition(i - 1, position(i));
    }

    setSize(size() - 1);
}

// --- Geometry ------------------------------------------------------------ //
/// Returns the distance between the points at \p i and \p j. The
/// returned distance is in Angstroms.
Float CoordinateMatrix::distance(int i, int j) const
{
    return Point::distance(position(i), position(j));
}

/// Returns the bond angle between the points at \p i, \p j, and
/// \p k. The returned angle is in degrees.
Float CoordinateMatrix::bondAngle(int i, int j, int k) const
{
    return Point::angle(position(i), position(j), position(k));
}

/// Returns the torsion angle between the points at \p i, \p j, \p k,
/// and \p l. The returned angle is in degrees.
Float CoordinateMatrix::torsionAngle(int i, int j, int k, int l) const
{
    return Point::torsionAngle(position(i), position(j), position(k), position(l));
}

/// Returns the wilson angle between the points at \p i, \p j, \p k
/// and \p l. The returned angle is in degrees.
Float CoordinateMatrix::wilsonAngle(int i, int j, int k, int l) const
{
    return Point::wilsonAngle(position(i), position(j), position(k), position(l));
}

/// Returns the center of the positions in the matrix. This is also
/// known as the centroid.
Point CoordinateMatrix::center() const
{
    if(isEmpty()){
        return Point();
    }

    // sums for each component
    Float sx = 0;
    Float sy = 0;
    Float sz = 0;

    for(int i = 0; i < size(); i++){
        sx += m_matrix.value(i, 0);
        sy += m_matrix.value(i, 1);
        sz += m_matrix.value(i, 2);
    }

    int n = size();

    return Point(sx/n, sy/n, sz/n);
}

/// Returns the center of the coordinates in the matrix after
/// weighting each position with \p weights.
Point CoordinateMatrix::weightedCenter(const QVector<Float> &weights) const
{
    Q_ASSERT(size() == weights.size());

    if(isEmpty()){
        return Point();
    }

    // sums for each component
    Float sx = 0;
    Float sy = 0;
    Float sz = 0;

    // sum of weights
    Float sw = 0;

    for(int i = 0; i < size(); i++){
        Float w = weights[i];

        sx += w * m_matrix.value(i, 0);
        sy += w * m_matrix.value(i, 1);
        sz += w * m_matrix.value(i, 2);

        sw += w;
    }

    int n = sw * size();

    return Point(sx/n, sy/n, sz/n);
}

/// Moves all of the coordinates in the matrix by \p vector.
void CoordinateMatrix::moveBy(const Vector &vector)
{
    for(int i = 0; i < size(); i++){
        m_matrix.value(i, 0) += vector.x();
        m_matrix.value(i, 1) += vector.y();
        m_matrix.value(i, 2) += vector.z();
    }
}

/// Moves all of the coordinates in the matrix by (\p x, \p y, \p z).
void CoordinateMatrix::moveBy(Float x, Float y, Float z)
{
    moveBy(Vector(x, y, z));
}

/// Returns a matrix containing the distances between each pair of
/// points in the coordinate matrix.
Matrix CoordinateMatrix::distanceMatrix() const
{
    Matrix matrix(size(), size());

    for(int i = 0; i < size(); i++){
        for(int j = i + 1; j < size(); j++){
            Float d = distance(i, j);

            matrix(i, j) = d;
            matrix(j, i) = d;
        }
    }

    return matrix;
}

// --- Math ---------------------------------------------------------------- //
/// Returns a new coordinate matrix containing the result of adding
/// the coordinates with \p matrix.
CoordinateMatrix CoordinateMatrix::add(const CoordinateMatrix &matrix) const
{
    int size = qMin(this->size(), matrix.size());

    CoordinateMatrix result(size);

    for(int i = 0; i < size; i++){
        const Point &a = position(i);
        const Point &b = matrix.position(i);

        result.setPosition(i, a + b);
    }

    return result;
}

/// Returns a new coordinate matrix containing the result of
/// subtracting the coordinates with \p matrix.
CoordinateMatrix CoordinateMatrix::subtract(const CoordinateMatrix &matrix) const
{
    int size = qMin(this->size(), matrix.size());

    CoordinateMatrix result(size);

    for(int i = 0; i < size; i++){
        const Point &a = position(i);
        const Point &b = matrix.position(i);

        result.setPosition(i, a - b);
    }

    return result;
}

/// Returns the 3x3 matrix product of the transpose of the matrix
/// and \p matrix.
StaticMatrix<Float, 3, 3> CoordinateMatrix::multiply(const CoordinateMatrix *matrix) const
{
    StaticMatrix<Float, 3, 3> product;

    chemkit::blas::gemm(3,
                        3,
                        size(),
                        m_matrix.data(),
                        true,
                        matrix->m_matrix.data(),
                        false,
                        product.data());

    return product;
}

// --- Operators ----------------------------------------------------------- //
CoordinateMatrix CoordinateMatrix::operator+(const CoordinateMatrix &matrix) const
{
    return add(matrix);
}

CoordinateMatrix CoordinateMatrix::operator-(const CoordinateMatrix &matrix) const
{
    return subtract(matrix);
}

CoordinateMatrix& CoordinateMatrix::operator=(const CoordinateMatrix &matrix)
{
    m_matrix = matrix.m_matrix;

    return *this;
}

} // end chemkit namespace