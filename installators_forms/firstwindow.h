#pragma once

#include <QApplication>
#include <QBitmap>
#include <QErrorMessage>
#include <QFile>
#include <QMouseEvent>
#include <QPalette>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class FirstWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    void mouseMoveEvent(QMouseEvent *);
    void setfront(QPushButton *button, float frontsize);
    void setColor(QPushButton *button, float radius);
    void searchProjectName();
    void checkReestr();

    QPushButton *pb_inst;
    QPushButton *pb_uninst; //!< нужно проверить наличие установленного приложения в реестре, если есть,
    //!< то кнопка активна, если нету, то не активна
    QString applicationName;

private:
    QPalette pal;
    QPixmap pix;
    QErrorMessage msg;
    QWidget *widgetPix;
    QWidget *widget;
    QTimer timer;
    QVBoxLayout *lay;
    int red;
    int green;
    int blue;
    int znak;
    float font;
    int flag;
    float radius;

public slots:
    void timeout();
};
