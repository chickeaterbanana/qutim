/****************************************************************************
**
** qutIM instant messenger
**
** Copyright (C) 2011 Ruslan Nigmatullin <euroelessar@ya.ru>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QUTIM_END_LICENSE$
**
****************************************************************************/

#include "migrationpagecreator.h"
#include "migrationstartpage.h"

namespace Core
{
	MigrationPageCreator::MigrationPageCreator(QObject *parent)
	{
		setParent(parent);
	}

	double MigrationPageCreator::priority() const
	{
		return 100.0;
	}

	QList<QWizardPage *> MigrationPageCreator::pages(QWidget *parent)
	{
		QList<QWizardPage *> list;
		list << new MigrationStartPage(parent);
		return list;
	}
}