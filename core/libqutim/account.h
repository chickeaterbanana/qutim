/****************************************************************************
*  account.h
*
*  Copyright (c) 2010 by Nigmatullin Ruslan <euroelessar@gmail.com>
*
***************************************************************************
*                                                                         *
*   This library is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************
*****************************************************************************/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "configbase.h"
#include "menucontroller.h"
#include "status.h"
#include <QMetaType>

namespace qutim_sdk_0_3
{
class ChatUnit;
class Contact;
class Protocol;
class Conference;
class AccountPrivate;
class GroupChatManager;
class ContactsFactory;

class Account;
typedef QList<Account*> AccountList;

/*!
  Account is base class for all account entites.
*/
class LIBQUTIM_EXPORT Account : public MenuController
{
	Q_DECLARE_PRIVATE(Account)
	Q_OBJECT
	Q_PROPERTY(QString id READ id)
	Q_PROPERTY(qutim_sdk_0_3::Status status READ status WRITE setStatus NOTIFY statusChanged)
	Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
	/*!
	  Account's contructor with identification \a id and \a protocol.
	  Identification is unique in current \a protocol, i.e. JID for
	  XMPP or UIN for ICQ.
	*/
	Account(const QString &id, Protocol *protocol);
	Account(AccountPrivate &p, Protocol *protocol);
	/*!
	  Account destructor
	*/
	virtual ~Account();
	/*!
	  Returns account's identification, which is unique for protocol
	*/
	QString id() const;
	/*!
	  Returns account's representable name
	*/
	virtual QString name() const;
	/*!
	  Returns \ref Config for current account. It's equal to
	  \code Config(protocol()->id() + '.' + id() + "/account") \endcode
	*/
	Config config();
	/*!
	  Returns \ref ConfigGroup for certain group with \a name. It's equal to
	  \code config().group(name) \endcode
	*/
	ConfigGroup config(const QString &name);
	/*!
	  Returns account's status
	*/
	Status status() const;
	/*!
	  Returns pointer to account's \ref Protocol
	*/
	Protocol *protocol();
	/*!
	  Returns pointer to account's \ref Protocol
	*/
	const Protocol *protocol() const;
	/*!
	  Asks account to change \a status on server. If \a status is not offline and
	  acount hasn't already connected to server it should try to do it, else if
	  \a status is offline and account is conntected to server it should disconnect.
	*/
	virtual void setStatus(Status status);
	/*!
	  Method looks for appropriate \ref ChatUnit for conversation with \a unit.
	  Returns ChatUnit for \ref ChatSession.
	*/
	virtual ChatUnit *getUnitForSession(ChatUnit *unit);
	/*!
	  Method Returns \ref ChatUnit by it's identification string \a unitId.
	  If \a create is \b true create new ChatUnit if it doesn't exist.
	  Returnes ChatUnit with iq equal to unitId.

	  If unitId is invalid, i.e. invalid JID, unit won't be created and NULL will be returned.
	*/
	virtual ChatUnit *getUnit(const QString &unitId, bool create = false) = 0;

	Q_INVOKABLE inline qutim_sdk_0_3::ChatUnit *unit(const QString &unitId, bool create = false);
	static AccountList all();
	/*!
	  Returns the group chat manager of the account.

	  \see resetGroupChatManager()
	*/
	GroupChatManager *groupChatManager();
	ContactsFactory *contactsFactory();
protected:
	/**
	  Sets the group chat \a manager to be used by this account.

	  \see groupChatManager()
	*/
	void resetGroupChatManager(GroupChatManager *manager = 0);
	void setContactsFactory(ContactsFactory *factory);
signals:
	/*!
	  Signal is emitted when new \a contact was created.
	*/
	void contactCreated(qutim_sdk_0_3::Contact *contact);
	/*!
	  Signal is emitted when new \a conference was created.
	*/
	void conferenceCreated(qutim_sdk_0_3::Conference *conference);
	/*!
	  Signal is emitted when account's \a name was changed.
	*/
	void nameChanged(const QString &current, const QString &previous);
	/*!
	  Signal is emitted when account's \a status was changed.
	*/
	void statusChanged(const qutim_sdk_0_3::Status &current, const qutim_sdk_0_3::Status &previous);
	/*!
	  Signal is emitted whenever the group chat manager has been reset.

	  \see groupChatManager(), resetGroupChatManager()
	*/
	void groupChatManagerChanged(qutim_sdk_0_3::GroupChatManager *manager);
};

ChatUnit *Account::unit(const QString &unitId, bool create)
{
	return getUnit(unitId, create);
}
}

Q_DECLARE_METATYPE(qutim_sdk_0_3::Account*)
Q_DECLARE_METATYPE(QList<qutim_sdk_0_3::Account*>)

#endif // ACCOUNT_H