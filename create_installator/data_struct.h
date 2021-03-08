#pragma once

#include <QString>

struct files
{
    QString path;
    int quantity;
    QByteArray ba;
    bool link, autostart;
    files()
    {
        path.append(nullptr);
        quantity = 0;
        link = 0;
        autostart = 0;
    }
};
struct dirs
{
    QString path; //!< путь до текущей папки
    int n;        //!< количество указателей
    dirs()
    {
        path.append(nullptr);
        n = 0;

        link = false;
    }
    bool link;
};
