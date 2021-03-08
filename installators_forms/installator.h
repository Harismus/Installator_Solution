#pragma once

#include <QCheckBox>
#include <QDebug>
#include <QErrorMessage>
#include <QFile>
#include <QProgressDialog>
#include <QRadioButton>
#include <QStandardPaths>
#include <QTextEdit>
#include <QWizard>

#include "pathwindow.h"
#include "proto.h"

class Installator : public QWizard
{
    Q_OBJECT
public:
    Installator();
    void setAutoStartApplication();
    void addUninstall(QString application_name);
    QString checkInstallDir();
    void setApplicationName(QString applicationName);

private:
    void createPages();

    PathWindow *path_window;
    QProgressDialog *progressDialog;
    QFile file;
    QList<datas> files_list;
    QList<datas> link_list;
    QList<datas> autostart_list;
    QErrorMessage msg;
    QByteArray uninstall;
    QString installation_path;
    QStringList strlist; //строки при разбиении файла
    QList<QByteArray> balist;
    QByteArray ba;
    QByteArray ba_informs;
    QByteArray ba_files;
    long long razd;
    long long razd_uninstall;
    QTextEdit te;
    QRadioButton *radio;
    QCheckBox *checkbox;
    QString applicationName;
    QString applicationNameReestr;

public slots:
    void onPageChanged(int i);
    void slot_radiobutton(bool);
    void slot_createlink(bool);
    void onAutoStartApplication();
};
