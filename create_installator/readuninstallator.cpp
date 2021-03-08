#include <QFile>
#include <QString>

#include "message.h"
#include "readuninstallator.h"

QByteArray ReadUnInstallator::readUnInstallator()
{
#ifdef Q_OS_WIN
    auto name_install = QString("uninstallators_forms.exe");
#elif Q_OS_LINUX
    auto name_install = QString("uninstallators_forms");
#endif
    QFile file(name_install);
    if (!file.open(QIODevice::ReadOnly))
    {
        Message::showMessage(QString("При открытие деинсталлятора: ") + file.errorString());
        return QByteArray();
    }
    auto uninstallator = file.readAll();

    file.close();
    return uninstallator;
}
