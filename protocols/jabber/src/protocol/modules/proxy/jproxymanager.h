/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Alexey Prokhin <alexey.prokhin@yandex.ru>
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

#ifndef OSCARPROXY_H
#define OSCARPROXY_H

#include "jabber_global.h"
#include <qutim/networkproxy.h>

namespace Jabber {

class JProxyManager : public QObject, public Ureen::NetworkProxyManager
{
	Q_OBJECT
	Q_CLASSINFO("DependsOn", "Jabber::JProtocol")
	Q_INTERFACES(Ureen::NetworkProxyManager)
public:
	JProxyManager();
	QList<Ureen::NetworkProxyInfo*> proxies();
	void setProxy(Ureen::Account *account, Ureen::NetworkProxyInfo *proxy, const Ureen::DataItem &settings);
};

} // namespace Jabber

#endif // OSCARPROXY_H

