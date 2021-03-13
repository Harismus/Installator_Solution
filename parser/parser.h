#pragma once

#include <QFile>
#include <QString>

struct Data
{
public:
    Data()
        : count(0)
        , link(false)
        , autostart(false)
    {
    }

    QString path;
    int count;
    bool link;
    bool autostart;
    QByteArray ba;
};

class Parser
{
public:
    Parser(const QString &pathToFile);
    ~Parser();
    bool findDelimiterInstallator();
    void closeFile();
    QByteArray readUninstallator();
    QString readApplicationName();
    int readFilesCount();
    Data readFile();
    int readDirsCount();
    Data readDirs();

private:
    QFile file;
    QByteArray ba;
    unsigned long long delimiterInstallator;
    int indexBeginData;
    int currentIndex;
};
