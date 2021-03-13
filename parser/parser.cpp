#include <QDebug>

#include "parser.h"

Parser::Parser(const QString &pathToFile)
    : delimiterInstallator(0xAABBAABB)
    , indexBeginData(0)
    , currentIndex(0)
{
    file.setFileName(pathToFile);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw(file.errorString());
    }
    ba = file.readAll();
    qDebug() << ba.size();
}

bool Parser::findDelimiterInstallator()
{
    for (int i = 0; i < ba.size(); ++i)
    {
        auto temp = *reinterpret_cast<unsigned long long *>(ba.data() + i);
        if (temp == delimiterInstallator)
        {
            indexBeginData = i + sizeof(delimiterInstallator);
            currentIndex = indexBeginData;
            return true;
        }
    }

    indexBeginData = 0;
    currentIndex = indexBeginData;
    return false;
}

QByteArray Parser::readUninstallator()
{
    auto uninstall_size = *reinterpret_cast<int *>(ba.data() + currentIndex); //размер деинсталлятора

    currentIndex += sizeof(uninstall_size);

    QByteArray unInstallator(uninstall_size, 0);
    std::copy(ba.begin() + currentIndex, ba.begin() + currentIndex + uninstall_size, unInstallator.begin());

    currentIndex += uninstall_size;

    return unInstallator;
}

QString Parser::readApplicationName()
{
    auto applicationStringSize = *reinterpret_cast<int *>(ba.data() + currentIndex); //размер деинсталлятора

    currentIndex += sizeof(applicationStringSize);

    QString appName(applicationStringSize, 0);
    std::copy(ba.begin() + currentIndex, ba.begin() + currentIndex + applicationStringSize, appName.begin());

    currentIndex += applicationStringSize;

    return appName;
}

int Parser::readFilesCount()
{
    auto filesCount = *reinterpret_cast<int *>(ba.data() + currentIndex); //размер деинсталлятора

    currentIndex += sizeof(filesCount);

    return filesCount;
}

int Parser::readDirsCount()
{
    auto dirsCount = *reinterpret_cast<int *>(ba.data() + currentIndex); //размер деинсталлятора

    currentIndex += sizeof(dirsCount);

    return dirsCount;
}

Data Parser::readFile()
{
    Data data;

    auto fileSize = *reinterpret_cast<int *>(ba.data() + currentIndex);
    currentIndex += sizeof(fileSize);
    QByteArray file(fileSize, 0);
    std::copy(ba.begin() + currentIndex, ba.begin() + currentIndex + fileSize, file.begin());
    data.count = std::move(fileSize);
    data.ba = std::move(file);
    currentIndex += fileSize;

    auto pathLength = *reinterpret_cast<int *>(ba.data() + currentIndex);
    currentIndex += sizeof(pathLength);
    QString path(pathLength, 0);
    std::copy(ba.begin() + currentIndex, ba.begin() + currentIndex + pathLength, path.begin());
    data.path = std::move(path);
    currentIndex += pathLength;

    auto hasLinkFlag = *reinterpret_cast<bool *>(ba.data() + currentIndex);
    currentIndex += sizeof(hasLinkFlag);
    data.link = hasLinkFlag;

    auto hasAutoStartFlag = *reinterpret_cast<bool *>(ba.data() + currentIndex);
    currentIndex += sizeof(hasAutoStartFlag);
    data.link = hasAutoStartFlag;

    return data;
}

Data Parser::readDirs()
{
    Data data;

    auto pathLength = *reinterpret_cast<int *>(ba.data() + currentIndex);
    currentIndex += sizeof(pathLength);
    QString path(pathLength, 0);
    std::copy(ba.begin() + currentIndex, ba.begin() + currentIndex + pathLength, path.begin());
    data.path = std::move(path);
    currentIndex += pathLength;

    return data;
}

void Parser::closeFile()
{
    file.close();
}

Parser::~Parser()
{
    closeFile();
}
