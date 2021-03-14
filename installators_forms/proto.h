#pragma once

#include <QString>

enum PAGE
{
    FIRST = 0,
    SECOND,
    THIRD
};

constexpr char reestrUninstall[] = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
constexpr char reestRun[] = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
