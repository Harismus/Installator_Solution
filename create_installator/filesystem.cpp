#include <QDir>

#include "filesystem.h"

FileSystem::FileSystem()
{
    clear();
}

void FileSystem::clear()
{
    list__struct_file.clear();
    list_struct_dirs.clear();
}

QPair<QList<dirs>, QList<files>> FileSystem::read(QString path, QString le_copy)
{
    read_dirs(path, le_copy);

    return QPair<QList<dirs>, QList<files>>(list_struct_dirs, list__struct_file);
}

void FileSystem::read_dirs(QString path, QString le_copy)
{
    auto dir = QDir(le_copy + QString("/") + path);
    auto list_dirs = dir.entryList(QDir::Dirs); //получили список файлов из папки

    for (int i = 0; i < list_dirs.size(); i++)
    {
        if (list_dirs[i] == "." || list_dirs[i] == "..")
        {
            list_dirs.removeAt(i--);
        }
    }

    dirs d;
    d.n = list_dirs.size();
    d.path.append(path);

    list_struct_dirs.append(d);
    read_files(path, le_copy);
    for (int i = 0; i < list_dirs.size(); i++)
    {
        QString path_temp;
        path_temp.append(path);
        path_temp.append(QString("/") + list_dirs[i]);
        read_dirs(path_temp, le_copy);
    }
}

void FileSystem::read_files(QString path, QString le_copy) //относительный путь
{
    auto dir = QDir(le_copy + QString("/") + path); //абсолютный путь
    auto list_files = dir.entryList(QDir::Files);   //получили список файлов из папки
    for (int i = 0; i < list_files.size(); ++i)
    {
        files f;
        f.path.append(path + QString("/") + list_files[i]);

        f.quantity = path.size();
        QFile file;
        QString path_temp;
        path_temp.append(path);
        path_temp.append(QString("/") + list_files[i]);
        file.setFileName(le_copy + path_temp);
        if (!file.open(QIODevice::ReadOnly))
        {
            msg.showMessage(le_copy + path_temp + file.errorString());
            msg.show();
            return;
        }
        f.ba = file.readAll();
        file.close();
        list__struct_file.append(f);
    }
}
