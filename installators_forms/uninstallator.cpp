#include <QProcess>
#include <qdebug.h>

#include <windows.h>

#include "proto.h"
#include "uninstallator.h"

Uninstallator::Uninstallator(QString name)
{
    applicationName.append(name);
}

void Uninstallator::openUninstallor()
{
    QString installation_path;
    /*  Получить путь до папки через реестр  */
    QSettings settings(QString(reestrUninstall) + applicationName, QSettings::NativeFormat);

    QStringList list;
    list.append(settings.allKeys());
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] == QString("UninstallString"))
        {
            installation_path.append(settings.value(list[i]).toString()); //тут
            break;
        }
    }

    SHELLEXECUTEINFO shExInfo = {0};
    shExInfo.cbSize = sizeof(shExInfo);
    shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExInfo.hwnd = 0;
    shExInfo.lpVerb = TEXT("runas");                       // Operation to perform
    shExInfo.lpFile = (LPCWSTR) installation_path.utf16(); // Application to start
    shExInfo.lpParameters = TEXT("");                      // Additional parameters
    shExInfo.lpDirectory = 0;
    shExInfo.nShow = SW_SHOW;
    shExInfo.hInstApp = 0;

    if (ShellExecuteEx(&shExInfo))
    {
        WaitForSingleObject(shExInfo.hProcess, INFINITE);
        CloseHandle(shExInfo.hProcess);
    }
}

Uninstallator::~Uninstallator() {}
