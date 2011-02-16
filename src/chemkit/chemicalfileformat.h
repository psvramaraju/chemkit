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

#ifndef CHEMKIT_CHEMICALFILEFORMAT_H
#define CHEMKIT_CHEMICALFILEFORMAT_H

#include "chemkit.h"

#include "chemicalfile.h"

namespace chemkit {

class ChemicalFileFormatPrivate;

class CHEMKIT_EXPORT ChemicalFileFormat
{
    public:
        // typedefs
        typedef ChemicalFileFormat* (*CreateFunction)();

        // construction and destruction
        virtual ~ChemicalFileFormat();

        // properties
        QString name() const;

        // options
        void setOption(const QString &name, const QVariant &value);
        QVariant option(const QString &name) const;

        // input and output
        virtual bool read(QIODevice *iodev, ChemicalFile *file);
        virtual bool write(const ChemicalFile *file, QIODevice *iodev);

        // error handling
        QString errorString() const;

        // static methods
        static ChemicalFileFormat* create(const QString &format);
        static QStringList formats();
        static void registerFormat(const QString &name, CreateFunction function);
        static void unregisterFormat(const QString &name, CreateFunction function);

    protected:
        ChemicalFileFormat(const QString &name);
        void setErrorString(const QString &error);

    private:
        ChemicalFileFormatPrivate* const d;
};

} // end chemkit namespace

#endif // CHEMKIT_CHEMICALFILEFORMAT_H