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

void Parser::parse()
{
    if (!findDelimiterInstallator())
    {
        throw("Delimiter didn't find");
    }

    unInstallator = readUninstallator();
    if (unInstallator.isEmpty())
    {
        throw("uninstallator is Empty");
    }

    applicationName = readApplicationName();
    if (applicationName.isEmpty())
    {
        throw("appName is Empty");
    }

    auto filesCount = readFilesCount();
    if (filesCount == 0)
    {
        throw("filesCount is 0");
    }
    listFiles.clear();
    for (int i = 0; i < filesCount; ++i)
    {
        auto data = readFile();
        if ((data.ba.size() == 0) || (data.count == 0))
        {
            throw("data file is empty");
        }

        listFiles.append(data);
    }

    auto dirsCount = readDirsCount();
    if (dirsCount == 0)
    {
        throw("dirsCount is 0");
    }
    listDirs.clear();
    for (int i = 0; i < dirsCount; ++i)
    {
        auto data = readDirs();
        //        if ((data.path.isEmpty()))
        //        {
        //            throw("data dir is empty");
        //        }

        listDirs.append(data);
    }

    qDebug() << ("Succesful!");
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

QList<Data> Parser::getListFiles()
{
    return listFiles;
}

QList<Data> Parser::getListDirs()
{
    return listDirs;
}

QByteArray Parser::getUnInstallator()
{
    return unInstallator;
}

QString Parser::getApplicationName()
{
    return applicationName;
}

void Parser::closeFile()
{
    file.close();
}

Parser::~Parser()
{
    closeFile();
}
