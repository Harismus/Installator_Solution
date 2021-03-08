#pragma once

#include <QSettings>

class Uninstallator
{
public:
    Uninstallator(QString name);
    ~Uninstallator();
    void openUninstallor();

private:
    QString applicationName;
};
