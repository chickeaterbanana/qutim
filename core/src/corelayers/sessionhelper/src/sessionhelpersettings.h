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
#ifndef SESSIOBHELPERSETTINGS_H
#define SESSIONHELPERSETTINGS_H

#include <QWidget>
#include <qutim/settingswidget.h>

class QCheckBox;

namespace Ui {
	class SessionHelperSettings;
}

namespace Core
{

using namespace Ureen;

class SessionHelperSettings : public Ureen::SettingsWidget
{
	Q_OBJECT
public:
	explicit SessionHelperSettings();
	~SessionHelperSettings();
	virtual void loadImpl();
	virtual void cancelImpl();
	virtual void saveImpl();
private:
	Ui::SessionHelperSettings *ui;
	void reloadCombobox();
};
	
}


#endif // SIMPLECONTACTLISTSETTINGS_H

