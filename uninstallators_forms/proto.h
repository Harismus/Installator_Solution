#pragma once

#include <QString>

struct datas
{
    QString path;
    int quantity;
    bool autostart;
    bool link;
    char *str;
};

constexpr char reestrUninstall[] = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
constexpr char reestRun[] = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
