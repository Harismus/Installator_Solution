#pragma once

#include <QByteArray>
#include <QDir>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>

#include "data_struct.h"

namespace Ui
{
class create_installator;
}

class MainWindow : public QDialog //, public Ui_create_installator
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief read_uninstallator  читаем деинсталлятор
     */
    void read_uninstallator();

    QFile file;
    QDir dir;
    QStringList list;
    QByteArray installator;
    QByteArray uninstallator;
    QList<files> listFiles;
    QList<dirs> listDirs;
    dirs *current_dir;
    dirs *first_dir;
    unsigned long long razd;
    QString name_icon_string;
    Ui::create_installator *ui;

public slots:
    void onCopy();
    void onDelete();
    void onInstall();
    void onValid();

    void fileDialogCopy();
    void fileDialogDelete();
    void fileDialogInstall();
    void copy_icon();
    void choice_icon();
};
