/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Ruslan Nigmatullin <euroelessar@yandex.ru>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
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
#ifndef MACSPELLCHECKER_H
#define MACSPELLCHECKER_H

#include <qutim/spellchecker.h>

namespace MacIntegration
{
using namespace Ureen;

class MacSpellChecker : public SpellChecker
{
	Q_OBJECT
public:
	MacSpellChecker();
	~MacSpellChecker();
	virtual bool isCorrect(const QString &word) const;
	virtual QStringList suggest(const QString &word) const;
	virtual void store(const QString &word) const;
	virtual void storeReplacement(const QString &bad, const QString &good);
	QStringList languages();
	void loadSettings(const QString &lang);
	static MacSpellChecker *instance() { Q_ASSERT(self); return self; }
	static QString toPrettyLanguageName(const QString &lang);
private:
	static MacSpellChecker *self;
};
}

#endif // MACSPELLCHECKER_H

