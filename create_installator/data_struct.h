#pragma once

#include <QString>

struct files
{
    QString path;
    int quantity;
    QByteArray ba;
    bool link;
    bool autostart;
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
    dirs()
    {
        n = 0;
        link = false;
    }
    QString path; //!< путь до текущей папки
    int n;        //!< количество указателей
    bool link;
};
