#pragma once

#include <QFileDialog>
#include <QHBoxLayout>
#include <QWidget>

namespace Ui
{
class path_window;
}

class PathWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PathWindow();
    ~PathWindow();
    void setButton(QPushButton *next);
    void setInstallationPath(QString *next);
    void setApplicationName(QString text);
    QHBoxLayout *getLay();
    void setText(const QString &text);
    bool isEmpty();

private:
    QPushButton *next;
    QString *str;
    QString applicationName;
    Ui::path_window *ui;

public slots:
    void slot_pbguide();
    void slot_leguide(QString str);
};
