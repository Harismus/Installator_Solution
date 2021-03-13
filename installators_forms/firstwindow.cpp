#include <QDebug>

#include "firstwindow.h"
#include "proto.h"

FirstWindow::FirstWindow(QWidget *parent)
    : QWidget(parent)
    , pb_inst(new QPushButton("Установить", this))
    , pb_uninst(new QPushButton("Удалить", this))
    , applicationName("")
    , pix(QPixmap(":/resource/installator.png"))
    , widgetPix(new QWidget)
    , lay(new QVBoxLayout(this))
    , red(0)
    , znak(1)
    , font(11)
    , flag(3)
    , radius(0)

{
    pal.setBrush(widgetPix->backgroundRole(), QBrush(pix));
    widgetPix->setPalette(pal);
    widgetPix->setAutoFillBackground(true);
    widgetPix->setMouseTracking(true);
    widgetPix->setFixedSize(pix.size());

    lay->addWidget(pb_inst);
    lay->addWidget(pb_uninst);
    lay->addWidget(widgetPix);
    setLayout(lay);

    pb_inst->setMouseTracking(true);
    pb_uninst->setMouseTracking(true);
    setMouseTracking(true);
    searchProjectName(); //!<  Поиск имени проекта
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    checkReestr();
#endif
    connect(&timer, &QTimer::timeout, this, &FirstWindow::timeout);
}
void FirstWindow::searchProjectName()
{
    QFile file(qApp->applicationFilePath());
    int count = 0;
    long long temp = 0;
    long long razd = 0xAABBAABB;

    if (!file.open(QIODevice::ReadOnly))
    {
        msg.showMessage(file.errorString());
        msg.show();
        return;
    }

    while (!file.atEnd())
    {
        file.read(reinterpret_cast<char *>(&temp), sizeof(long long));
        if (temp == razd)
        {
            count++;
        }

        if (count == 1) //файлы инсталлируемого приложения
        {
            char bytes;
            int uninstall_size; //размер деинсталлятора
            file.read(reinterpret_cast<char *>(&uninstall_size), sizeof(uninstall_size));
            for (int i = 0; i < uninstall_size; i++)
            {
                file.read(&bytes, sizeof(bytes));
            }
            //читаем  название приложения
            int count_string_name = 0;

            file.read(reinterpret_cast<char *>(&count_string_name), sizeof(count_string_name));

            auto application_name = new char[count_string_name + 1];

            file.read(application_name, count_string_name);

            application_name[count_string_name] = 0;
            applicationName.clear();
            applicationName.append(application_name);
            break;
        }
    }
    setWindowTitle(applicationName);
}

void FirstWindow::checkReestr()
{
    if (applicationName.isEmpty())
        return;

    bool flag = false;

    QSettings settings(reestrUninstall, QSettings::NativeFormat);
    QStringList list(settings.allKeys());

    for (int i = 0; i < list.size(); i++)
    {
        if (settings.value(list[i]).toString() == applicationName)
        {
            flag = true;
            break;
        }
    }

    if (flag)
    {
        pb_uninst->setDisabled(false);
        pb_inst->setText("Переустановить");
    }
    else
    {
        pb_uninst->setDisabled(true);
    }
}

void FirstWindow::mouseMoveEvent(QMouseEvent *me)
{
    if (me->x() >= pb_inst->x() && me->x() <= (pb_inst->x() + pb_inst->width()) && me->y() >= pb_inst->y()
        && me->y() <= (pb_inst->y() + pb_inst->height()))
    {
        if (flag == 1)
        {
            timer.stop();

            setColor(pb_uninst, 0);
        }
        if (!timer.isActive())
        {
            timer.start(50);
            flag = 0; //флаг того, что указатель наведен на кнопку установки
        }
    }
    else if (me->x() >= pb_uninst->x() && me->x() <= pb_uninst->x() + pb_uninst->width() && me->y() >= pb_uninst->y()
             && me->y() <= pb_uninst->y() + pb_uninst->height())
    {
        if (flag == 0)
        {
            timer.stop();
            setColor(pb_inst, 0);
        }
        if (!timer.isActive())
        {
            timer.start(50);
            flag = 1; //флаг того, что указатель наведен на кнопку удаления
        }
    }
    else if (flag == 0 || flag == 1)
    {
        timer.stop();
        if (flag == 0)
        {
            setColor(pb_inst, 0);
        }
        else if (flag == 1)
        {
            setColor(pb_uninst, 0);
        }
        flag = 3;
    }
}

void FirstWindow::timeout()
{
    auto pos = mapFromGlobal(cursor().pos());
    if (flag == 0)
    {
        radius += 0.02;
        if (radius >= 1)
        {
            radius = 0;
        }
        setColor(pb_inst, radius);
        if (pos.x() >= pb_inst->x() && pos.x() <= (pb_inst->x() + pb_inst->width()) && pos.y() >= pb_inst->y()
            && pos.y() <= (pb_inst->y() + pb_inst->height()))
        {
            return;
        }
        else
        {
            timer.stop();
            setColor(pb_inst, 0);
        }
    }
    else if (flag == 1)
    {
        radius -= 0.02;
        if (radius <= 0)
        {
            radius = 1;
        }
        setColor(pb_uninst, radius);
        if (pos.x() >= pb_uninst->x() && pos.x() <= pb_uninst->x() + pb_uninst->width() && pos.y() >= pb_uninst->y()
            && pos.y() <= pb_uninst->y() + pb_uninst->height())
        {
            return;
        }
        else
        {
            timer.stop();
            setColor(pb_uninst, 0);
        }
    }
}

void FirstWindow::setfront(QPushButton *button, float frontsize)
{
    auto qfont = button->font();
    qfont.setPointSizeF(frontsize);
    button->setFont(qfont);
}

void FirstWindow::setColor(QPushButton *button, float radius)
{
    QString background_color;
    QString radius_str = QString::number(radius);
    background_color.append(QString("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:") + radius_str
                            + QString(", fx:0.5, fy:0.5, "
                                      "stop:0 rgba(0, 0, 0, 0)"
                                      ", stop:0.52 rgba(0, 0, 0, 0), "
                                      "stop:0.565 rgba(82, 121, 76, 33)"
                                      ", stop:0.65 rgba(159, 235, 148, 64),"
                                      " stop:0.721925 rgba(255, 238, 150, 129), "
                                      "stop:0.77 rgba(255, 128, 128, 204),"
                                      " stop:0.89 rgba(191, 128, 255, 64), "
                                      "stop:1 rgba(0, 0, 0, 0))"));
    button->setStyleSheet(background_color);
}

FirstWindow::~FirstWindow() {}
