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

#ifndef SCRIPTPLUGINWRAPPER_H
#define SCRIPTPLUGINWRAPPER_H

#include <qutim/plugin.h>

class ScriptEngine;
class QScriptValue;

class ScriptPluginWrapper : public Ureen::Plugin
{
	Q_OBJECT
public:
    explicit ScriptPluginWrapper(const QString &name);
	virtual ~ScriptPluginWrapper();
	
	virtual void init();
	virtual bool load();
	virtual bool unload();
private:
	QString m_name;
	ScriptEngine *m_engine;
	bool m_apiInited;
};

#endif // SCRIPTPLUGINWRAPPER_H

