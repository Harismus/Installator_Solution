#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow()
    : firstWindow(new FirstWindow)
    , installator(nullptr)
{
    connect(firstWindow->pb_inst, &QPushButton::clicked, this, &MainWindow::onInstallWindow);
    connect(firstWindow->pb_uninst, &QPushButton::clicked, this, &MainWindow::onUninstallWindow);

    firstWindow->show();
}

void MainWindow::onInstallWindow()
{
    if (!installator)
    {
        installator = new Installator;
        installator->setApplicationName(firstWindow->applicationName);
        installator->show();
    }
    if (firstWindow)
    {
        delete firstWindow;
        firstWindow = 0;
    }
}

void MainWindow::onUninstallWindow()
{
    if (firstWindow)
    {
        delete firstWindow;
        firstWindow = 0;
    }
    if (!firstWindow)
    {
        unInstallator = new Uninstallator(firstWindow->applicationName);
        unInstallator->openUninstallor();
    }
}

MainWindow::~MainWindow() {}
