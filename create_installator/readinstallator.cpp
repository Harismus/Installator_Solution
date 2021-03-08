#include <QFile>
#include <QString>

#include "message.h"
#include "readinstallator.h"

QByteArray ReadInstallator::readInstallator()
{
#ifdef Q_OS_WIN32
    auto name_uninstall = QString("installators_forms.exe");
#elif Q_OS_LINUX
    auto name_uninstall = QString("installators_forms");
#endif
    QFile file(name_uninstall);
    if (!file.open(QIODevice::ReadOnly))
    {
        Message::showMessage(QString("При открытие инсталлятора: ") + file.errorString());
        return QByteArray();
    }
    auto installator = file.readAll();
    file.close();
    return installator;
}
