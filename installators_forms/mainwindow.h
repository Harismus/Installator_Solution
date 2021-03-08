#pragma once

#include <QErrorMessage>
#include <QMainWindow>
#include <QObject>

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#include <windows.h>
#endif

#include "firstwindow.h"
#include "installator.h"
#include "uninstallator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

private:
    FirstWindow *firstWindow;
    QErrorMessage msg;
    Installator *installator;
    Uninstallator *unInstallator;

public slots:
    void onInstallWindow();
    void onUninstallWindow();
};
