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
#ifndef RESOURCEICONLOADER_H
#define RESOURCEICONLOADER_H
#include <qutim/notification.h>
#include <QStringList>
#include <hwrmvibra.h>

namespace Symbian
{
using namespace Ureen;

class Vibration : public QObject, public Ureen::NotificationBackend
{
	Q_OBJECT
	Q_CLASSINFO("Service", "VibrationAlert")
	Q_CLASSINFO("Type", "VibrationAlert")
public:
	Vibration();
	~Vibration();

	virtual void handleNotification(Ureen::Notification *notification);
private:
	CHWRMVibra *m_vibra;
};

} //namespace Embedded

#endif // RESOURCEICONLOADER_H

