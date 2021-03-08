#include <QDebug>

#include "filesystem.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , current_dir(nullptr)
    , first_dir(nullptr)
{
    razd = 0xAABBAABB;

    setupUi(this);

    connect(pb_copy, &QPushButton::clicked, this, &MainWindow::files_copy);
    connect(pb_delete, &QPushButton::clicked, this, &MainWindow::files_delete);
    connect(pb_install, &QPushButton::clicked, this, &MainWindow::files_install);
    connect(pb_icon, &QPushButton::clicked, this, &MainWindow::copy_icon);
    connect(pb_filedialog_copy, &QPushButton::clicked, this, &MainWindow::filedialog_copy);
    connect(pb_filedialog_delete, &QPushButton::clicked, this, &MainWindow::filedialog_delete);
    connect(pb_filedialog_install, &QPushButton::clicked, this, &MainWindow::filedialog_install);
    connect(pb_filedialog_icon, &QPushButton::clicked, this, &MainWindow::choice_icon);

    connect(listLinks, &QListWidget::clicked, [&](QModelIndex index) {
        list__struct_file[index.row()].link = !list__struct_file[index.row()].link;
    }); //создание ярклыка

    connect(listAutoLoading, &QListWidget::clicked, [&](QModelIndex index) {
        list__struct_file[index.row()].autostart = !list__struct_file[index.row()].autostart;
    }); //автозагрузка

    showMessage = [](QString message) {
        QErrorMessage msg;
        msg.showMessage(message);
        msg.show();
    };
}

void MainWindow::copy_icon()
{
    if (le_icon->text().isEmpty())
    {
        showMessage("Путь до папки пустой");
        return;
    }

    lbl_icon->setPixmap(QPixmap(le_icon->text()));
}

void MainWindow::choice_icon()
{
    auto str = QFileDialog::getOpenFileName(this, "Select a Directory", le_icon->text(), "Images (*.png *.xpm *.jpg)");

    if (!str.isEmpty())
    {
        le_icon->setText(str);
        auto list = str.split("/");
        name_icon_string.append(list[list.size() - 1]);
    }
}

void MainWindow::read_installator()
{
    installator.clear();

#ifdef Q_OS_WIN32
    auto name_uninstall = QString("installators_forms.exe");
#elif Q_OS_LINUX
    auto name_uninstall = QString("installators_forms");
#endif
    file.setFileName(name_uninstall);
    if (!file.open(QIODevice::ReadOnly))
    {
        showMessage(QString("При открытие инсталлятора: ") + file.errorString());
        return;
    }
    installator = file.readAll();
    file.close();
}

void MainWindow::read_uninstallator()
{
    uninstallator.clear();

#ifdef Q_OS_WIN
    auto name_install = QString("uninstallators_forms.exe");
#elif Q_OS_LINUX
    auto name_install = QString("uninstallators_forms");
#endif
    file.setFileName(name_install);
    if (!file.open(QIODevice::ReadOnly))
    {
        showMessage(QString("При открытие деинсталлятора: ") + file.errorString());
        return;
    }
    uninstallator = file.readAll();

    file.close();
}

void MainWindow::files_copy()
{
    if (le_copy->text().isEmpty())
    {
        showMessage("Путь до папки пустой");
        return;
    }
    if (list__struct_file.size())
    {
        showMessage("Перезапустите приложение");
        return;
    }
    /* Создаем дерево папок */
    read_installator();
    read_uninstallator();

    FileSystem fileSystem;
    auto [listDirs, listFiles] = fileSystem.read("", le_copy->text());
    list_struct_dirs = listDirs;
    list__struct_file = listFiles;

    for (int i = 0; i < list__struct_file.size(); i++)
    {
        listLinks->addItem(list__struct_file[i].path);
        listAutoLoading->addItem(list__struct_file[i].path);
    }
}

void MainWindow::files_delete()
{
    if (le_delete->text().isEmpty())
    {
        showMessage("Путь до папки пустой");
        return;
    }
    dir = QDir(le_delete->text());
    list = dir.entryList(QDir::Files);

    QFile file;
    for (int i = 0; i < list.size(); i++)
    {
        file.setFileName(le_delete->text() + QString("/") + list[i]);
        file.remove();
        file.close();
    }
}

void MainWindow::files_install()
{
    if (le_install->text().isEmpty())
    {
        showMessage("Путь до папки пустой");
        return;
    }

    if (installator.isEmpty())
    {
        showMessage("Пустой буфер");
        return;
    }

#ifdef Q_OS_WIN
    auto name_setup = QString("/setup.exe");
#elif Q_OS_LINUX
    auto name_setup.append("/setup");
#endif
    QFile file(le_install->text() + name_setup);
    if (!file.open(QIODevice::ReadWrite))
    {
        showMessage("Не открыло файл");
        return;
    }
    //дальше в файл нужно слить всю инфу
    file.write(installator);
    file.write((reinterpret_cast<char *>(&razd)), sizeof(long long));
    int size = uninstallator.size();
    file.write(reinterpret_cast<char *>(&size), sizeof(size));
    file.write(uninstallator);
    //название приложения
    QString application_name_string;
    application_name_string.append(le_applicationname->text());
    auto application_name = new char[application_name_string.toLocal8Bit().size()];
    for (int k = 0; k < application_name_string.toLocal8Bit().size(); k++)
    {
        application_name[k] = *(application_name_string.toLocal8Bit().data() + k);
    }
    int application_name_string_size = application_name_string.toLocal8Bit().size();
    file.write(reinterpret_cast<char *>(&application_name_string_size), sizeof(application_name_string_size));
    file.write(application_name, application_name_string.toLocal8Bit().size());

    //    /*имя иконки*/
    //    char* icon_name = new char [name_icon_string.toLocal8Bit().size()];
    //    for(int k = 0;k<name_icon_string.toLocal8Bit().size();k++)
    //    {
    //        icon_name[k] = *(name_icon_string.toLocal8Bit().data() + k);
    //    }
    //    int name_icon_string_size = name_icon_string.toLocal8Bit().size();
    //    file.write((char*)&name_icon_string_size,sizeof(name_icon_string_size));
    //    file.write(icon_name,icon_name.toLocal8Bit().size());

    /*иконка*/
    //    QByteArray ba_icon;
    //    ba_icon.append(lbl_icon->pixmap()->data_ptr().data());
    //    file.write((char*)&lbl_icon->pixmap()->,sizeof(name_icon_string_size));
    //     for(int k = 0;k<lbl_icon->pixmap()->size();k++)
    //    {
    //        lbl_icon->pixmap()->data_ptr().data()
    //    }

    for (int i = 0; i < list__struct_file.size(); i++) //!< информация о файлах
    {
        list__struct_file[i].path.append(nullptr);
        int ba_size = list__struct_file[i].ba.size();
        file.write(reinterpret_cast<char *>(&ba_size), sizeof(ba_size));
        int path_size = list__struct_file[i].path.size();
        file.write(reinterpret_cast<char *>(&path_size), sizeof(path_size));
        auto buff = new char[list__struct_file[i].path.size()];

        for (int k = 0; k < list__struct_file[i].path.toLocal8Bit().size(); k++)
        {
            buff[k] = *(list__struct_file[i].path.toLocal8Bit().data() + k);
        }
        file.write(buff, path_size);
        file.write(list__struct_file[i].ba);                                //сам файл
        file.write((char *) &list__struct_file[i].link, sizeof(bool));      //флаг добавления в автозагрузку
        file.write((char *) &list__struct_file[i].autostart, sizeof(bool)); //флаг добавления в автозагрузку
    }
    file.setPermissions(QFileDevice::ExeUser | QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup
                        | QFileDevice::WriteUser | QFileDevice::ReadUser);
    file.close();
}

void MainWindow::filedialog_copy()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", le_copy->text());
    if (!str.isEmpty())
    {
        le_copy->setText(str);
    }
}

void MainWindow::filedialog_delete()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", le_delete->text());
    if (!str.isEmpty())
    {
        le_delete->setText(str);
    }
}

void MainWindow::filedialog_install()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", le_install->text());
    if (!str.isEmpty())
    {
        le_install->setText(str);
    }
}

MainWindow::~MainWindow() {}
