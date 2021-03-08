#pragma once

#include <QByteArray>
#include <QDir>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>

#include "data_struct.h"
#include "ui_create_installator.h"

class MainWindow : public QDialog, public Ui_test_inst
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief read_installator  читаем инсталлятор
     */
    void read_installator();
    /**
     * @brief read_uninstallator  читаем деинсталлятор
     */
    void read_uninstallator();

    QFile file;
    QDir dir;
    QStringList list;
    QByteArray installator;
    QByteArray uninstallator;
    QList<files> list__struct_file;
    QList<dirs> list_struct_dirs;
    dirs *current_dir;
    dirs *first_dir;
    long long razd;
    QString name_icon_string;
    std::function<void(QString)> showMessage;
public slots:
    void files_copy();
    void files_delete();
    void files_install();
    void filedialog_copy();
    void filedialog_delete();
    void filedialog_install();
    void copy_icon();
    void choice_icon();
};
