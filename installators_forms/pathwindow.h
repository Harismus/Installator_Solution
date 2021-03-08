#pragma once

#include <QFileDialog>
#include <QWidget>

#include "ui_pathwindow.h"

class PathWindow : public QWidget, public Ui_path_window
{
    Q_OBJECT
public:
    explicit PathWindow();
    ~PathWindow();
    void setButton(QPushButton *next);
    void setInstallationPath(QString *next);
    void setApplicationName(QString text);

private:
    QPushButton *next;
    QString *str;
    QString applicationName;

public slots:
    void slot_pbguide();
    void slot_leguide(QString str);
};
