/*
 * Copyright (c) 2014-2016 Alex Spataru <alex_spataru@outlook.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include "Window.h"
#include "ui_Window.h"

#include <QDebug>
#include <QSimpleUpdater.h>

//==============================================================================
// Define the URL of the Update Definitions file
//==============================================================================

static const QString DEFS_URL = "https://raw.githubusercontent.com/"
                                "alex-spataru/QSimpleUpdater/master/tutorial/"
                                "definitions/updates.json";

static const QString DEFS_URL2 = "https://raw.githubusercontent.com/"
                                 "OrangeCiiCii/VersionUpdate/main/"
                                 "definitions/updates2.json";

static const QString DEFS_URL3 = "https://raw.githubusercontent.com/"
                                 "OrangeCiiCii/VersionUpdate/main/"
                                 "definitions/updates3.json";

//==============================================================================
// Window::Window
//==============================================================================

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui = new Ui::Window;
    m_ui->setupUi(this);
    m_ui->label_4->setText("当前的版本号: "+QCoreApplication::applicationVersion());

    setWindowTitle("在线升级窗口");
    setWindowIcon(QIcon(":/icons/nupdate.png"));

    /* QSimpleUpdater is single-instance */
    m_updater = QSimpleUpdater::getInstance();

    /* Check for updates when the "Check For Updates" button is clicked */
//    connect(m_updater, SIGNAL(checkingFinished(QString)), this, SLOT(updateChangelog(QString)));
    connect(m_updater, SIGNAL(appcastDownloaded(QString, QByteArray)), this, SLOT(displayAppcast(QString, QByteArray)));

    /* React to button clicks */
    connect(m_ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_ui->checkButton, SIGNAL(clicked()), this, SLOT(checkForUpdates()));

    /* Resize the dialog to fit */
    setMinimumSize(minimumSizeHint());
    resize(minimumSizeHint());

}

//==============================================================================
// Window::~Window
//==============================================================================

Window::~Window()
{
    delete m_ui;
}

//==============================================================================
// Window::checkForUpdates
//==============================================================================

void Window::checkForUpdates()
{
    /* Apply the settings */
    //   m_updater->setModuleVersion(DEFS_URL, version);//回滚机制
    m_updater->setNotifyOnFinish(DEFS_URL3, true);
    m_updater->setNotifyOnUpdate(DEFS_URL3, true);
    m_updater->setDownloaderEnabled(DEFS_URL3, true); //若不启用集成下载器，则弹出网页端进行下载
    m_updater->setUseCustomInstallProcedures(DEFS_URL3,false);//默认false,启用自动安装
    m_updater->setUseCustomAppcast(DEFS_URL3, false);
    m_updater->setMandatoryUpdate(DEFS_URL3, false);//默认false,不强制更新

    /* Check for updates */
    m_updater->checkForUpdates(DEFS_URL3);
}

//==============================================================================
// Window::updateChangelog
//==============================================================================

//void Window::updateChangelog(const QString &url)
//{
//    if (url == DEFS_URL3)
//        m_ui->changelogText->setText(m_updater->getChangelog(url));
//}

//==============================================================================
// Window::displayAppcast
//==============================================================================

void Window::displayAppcast(const QString &url, const QByteArray &reply)
{
    if (url == DEFS_URL3)
    {
        QString text = "This is the downloaded appcast: <p><pre>" + QString::fromUtf8(reply)
                + "</pre></p><p> If you need to store more information on the "
                  "appcast (or use another format), just use the "
                  "<b>QSimpleUpdater::setCustomAppcast()</b> function. "
                  "It allows your application to interpret the appcast "
                  "using your code and not QSU's code.</p>";

        m_ui->changelogText->setText(text);
    }
}
