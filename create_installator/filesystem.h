#pragma once

#include <QErrorMessage>
#include <QPair>
#include <QString>

#include "data_struct.h"

class FileSystem
{
public:
    FileSystem();

    QPair<QList<dirs>, QList<files>> read(QString path, QString le_copy);

private:
    void clear();
    void read_dirs(QString path, QString le_copy);
    void read_files(QString path, QString le_copy);

    QErrorMessage msg;
    QList<files> list__struct_file;
    QList<dirs> list_struct_dirs;
};
