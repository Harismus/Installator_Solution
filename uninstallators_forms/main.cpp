#include <QProcess>
#include <QTextCodec>
#include <QTextStream>

#include <shlobj.h>
#include <unistd.h>
#include <wchar.h>
#include <windows.h>

#include "mainwindow.h"

QString path_application;
QString path_bat;
QString name_application;
QString raschirenie;
extern QString path_dir;

void SelfDelete()
{
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)

    QString name = "batfile.bat";

    raschirenie.append(".exe");
    QString temp = path_application;
    path_application.clear();
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp.toLocal8Bit()[i] == '/')
        {
            path_application.append('\\');
            continue;
        }
        path_application.append(temp[i]);
    }
    temp.clear();
    temp.append(path_dir + QString("\\") + QString("batfile.bat"));
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp.toLocal8Bit()[i] == '/')
        {
            path_bat.append('\\');
            continue;
        }
        path_bat.append(temp[i]);
    }

    QString buff;
    buff.append("@echo off\n");
    buff.append("\n TIMEOUT /T 1 /NOBREAK \n");
    buff.append("\ndel \\F \\Q ");
    buff.append(path_dir + QString("\\") + name_application + raschirenie);

    auto codec = QTextCodec::codecForName("CP 866");
    QTextStream in(codec->fromUnicode(buff), QIODevice::ReadOnly | QIODevice::Text);
    in.setCodec(codec);
    in << (buff, QIODevice::ReadOnly | QIODevice::Text);
    QString str = in.readAll();

    QFile opened_file(path_dir + QString("\\") + name);
    if (!opened_file.open(QIODevice::WriteOnly))
    {
        qDebug() << (path_dir + name);
    }

    opened_file.write(codec->fromUnicode(buff));
    opened_file.close();

    auto wchar_path_bat = reinterpret_cast<LPCWSTR>(QString(path_dir + QString("\\") + name).utf16());

    ShellExecute(0, L"open", wchar_path_bat, NULL, NULL, SW_SHOW);

#elif Q_OS_LINUX
    system(QString(QString("rm -f ") + path).toLocal8Bit().data());

#endif
}

int main(int argc, char *argv[])
{
    bool flag = false;

    QApplication a(argc, argv);
    MainWindow w(flag);

    path_application.append(qApp->applicationFilePath());
    name_application.append(qApp->applicationDisplayName());

    w.show();
    a.exec();

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    // Sleep(2000);
#elif Q_OS_LINUX
    sleep(1);
#endif

    if (flag)
        SelfDelete();

    return 0;
}
