/****************************************************************************
 *  chatappearance.cpp
 *
 *  Copyright (c) 2011 by Sidorov Aleksey <sauron@citadelspb.com>
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
#include "chatappearance.h"
#include "ui_chatappearance.h"
#include <qutim/configbase.h>
#include <qutim/protocol.h>
#include <qutim/account.h>
#include <qutim/notificationslayer.h>
#include <qutim/thememanager.h>
#include <QLabel>
#include <QSpacerItem>
#include <QFormLayout>
#include <QDateTime>
#include <QStringBuilder>
#include <QDebug>
#include <qutim/adiumchat/chatsessionimpl.h>
#include "../quickchatviewcontroller.h"
#include "../quickchatviewwidget.h"
#include <QDeclarativeEngine>

namespace Core
{
namespace AdiumChat
{

class FakeChatUnit : public ChatUnit
{
public:
	FakeChatUnit(Account* account) : ChatUnit(account) {}

	virtual QString title() const
	{
		return ChatAppearance::tr("Vasya Pupkin");
	}

	virtual bool sendMessage(const qutim_sdk_0_3::Message& message)
	{
		Q_UNUSED(message);
		return true;
	}

	virtual QString id() const
	{
		return ChatAppearance::tr("Noname");
	}
};
class FakeAccount : public Account
{
public:
	FakeAccount(const QString& id, Protocol* protocol) : Account(id,protocol)
	{
		m_unit = new FakeChatUnit(this);
	}

	virtual ~FakeAccount()
	{
		m_unit->deleteLater();
	}

	virtual ChatUnit* getUnit(const QString &unitId, bool create = true)
	{
		Q_UNUSED(unitId);
		Q_UNUSED(create);
		return m_unit;
	}

	virtual FakeChatUnit *getFakeUnit()
	{
		return m_unit;
	}

private:
	FakeChatUnit *m_unit;
};

ChatAppearance::ChatAppearance(): ui(new Ui::quickChatAppearance),m_controller(0)
{
	ui->setupUi(this);
	m_widget = new QuickChatViewWidget(this);
	ui->verticalLayout->addWidget(m_widget);
	if (!Protocol::all().isEmpty()) {
		FakeAccount *account = new FakeAccount("Noname", Protocol::all().begin().value());
		FakeChatUnit *unit = account->getFakeUnit();
		ChatSessionImpl *session = new ChatSessionImpl(unit, ChatLayer::instance());
		m_controller = new QuickChatController(new QDeclarativeEngine(this), this);
		m_controller->setChatSession(session);
		connect(ui->chatBox,SIGNAL(currentIndexChanged(int)),SLOT(onThemeChanged(int)));
		m_widget->setViewController(m_controller);
		account->setParent(this);
	}
	connect(ui->openGLBox, SIGNAL(stateChanged(int)), SLOT(onStateChanged(int)));
}

ChatAppearance::~ChatAppearance()
{
}

void ChatAppearance::cancelImpl()
{

}

void ChatAppearance::onStateChanged(int)
{
	emit modifiedChanged(true);
}

void ChatAppearance::loadImpl()
{
	if (!m_controller) {
		Notifications::send(Notification::System, this, tr("Unable to create chat session"));
		return;
	}
	ConfigGroup quickChat = Config("appearance/qmlChat");
	ui->openGLBox->setChecked(quickChat.value("openGL",false));
	quickChat.beginGroup(QLatin1String("style"));
	m_currentStyleName = quickChat.value<QString>("name","default");
	quickChat.endGroup();
	getThemes();
	int index = ui->chatBox->findText(m_currentStyleName);
	isLoad = true;

	index = index == -1 ? 0 : index;
	if(index == ui->chatBox->currentIndex())
		onThemeChanged(index);
	else
		ui->chatBox->setCurrentIndex(index);
}

void ChatAppearance::saveImpl()
{
	Config config("appearance/qmlChat");
	config.setValue("openGL", ui->openGLBox->isChecked());
	config.beginGroup("style");
	config.setValue("name",m_currentStyleName);
	config.endGroup();
	config.sync();
}

void ChatAppearance::getThemes()
{
	ui->chatBox->blockSignals(true);
	QString category = "qmlchat";
	QStringList themes = ThemeManager::list(category);
	ui->chatBox->clear();
	foreach (const QString &name, themes)
		ui->chatBox->addItem(name);
	ui->chatBox->blockSignals(false);
}

void ChatAppearance::onThemeChanged(int index)
{
	m_currentStyleName = ui->chatBox->itemText(index);
	m_controller->loadTheme(m_currentStyleName);
	makePage();
	if (!isLoad)
		emit modifiedChanged(true);
	isLoad = false;
}

void ChatAppearance::makePage()
{
	if (!m_controller) {
		Notifications::send(Notification::System, this, tr("Unable to create chat session"));
		return;
	}
	Message message(tr("Preview message"));
	message.setProperty("silent",true);
	message.setProperty("history",true);
	message.setProperty("store",false);
	message.setTime(QDateTime::currentDateTime());
	message.setIncoming(true);
	message.setChatUnit(m_controller->getSession()->getUnit());
	message.setText(tr("Hello!"));
	m_controller->appendMessage(message);
	message.setProperty("history",false);
	message.setText(tr("How are you?"));
	m_controller->appendMessage(message);
	message.setTime(QDateTime::currentDateTime());
	message.setText(tr("I am fine!"));
	message.setIncoming(false);
	m_controller->appendMessage(message);
	message.setText(tr("/me is thinking!"));
	m_controller->appendMessage(message);
	message.setProperty("service",true);
	message.setText(tr("Vasya Pupkin is reading you mind"));
	m_controller->appendMessage(message);
}

}
}
