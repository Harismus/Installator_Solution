#pragma once

#include <QAbstractButton>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QErrorMessage>
#include <QFile>
#include <QMainWindow>
#include <QProgressDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWizard>

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#include <windows.h>
#endif

#include "proto.h"

class MainWindow : public QWizard
{
    Q_OBJECT

public:
    MainWindow(bool &);
    ~MainWindow();

private:
    void deleteuninstall(QString application_name);
    QString open_uninst();
    void deleteautoStartApplication(QString application_name);
    void createPages();

    QVBoxLayout *vlay1;
    QVBoxLayout *vlay2;
    QTextEdit te1;
    QTextEdit te2;
    QProgressDialog *pprd;
    bool *flag;
    QFile file;
    QErrorMessage msg;
    QList<datas> files_list;
    long long razd;

public slots:
    void slot_IdChanged(int i);
};
