/****************************************************************************
 *
 *  This file is part of qutIM
 *
 *  Copyright (c) 2011 by Nigmatullin Ruslan <euroelessar@gmail.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This file is part of free software; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************
 ****************************************************************************/

#include "textviewfactory.h"
#include "textviewcontroller.h"
#include "textviewwidget.h"

namespace Core
{
namespace AdiumChat
{
TextViewFactory::TextViewFactory()
{
}

QWidget *TextViewFactory::createViewWidget()
{
	return new TextViewWidget();
}

QObject *TextViewFactory::createViewController()
{
	return new TextViewController();
}
}
}