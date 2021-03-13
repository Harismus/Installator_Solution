#include <QDebug>

#include "filesystem.h"
#include "mainwindow.h"
#include "message.h"
#include "parser.h"
#include "readinstallator.h"
#include "readuninstallator.h"
#include "ui_create_installator.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , current_dir(nullptr)
    , first_dir(nullptr)
    , razd(0xAABBAABB)
    , ui(new Ui::create_installator)
{
    ui->setupUi(this);

    connect(ui->pb_copy, &QPushButton::clicked, this, &MainWindow::onCopy);
    connect(ui->pb_delete, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(ui->pb_install, &QPushButton::clicked, this, &MainWindow::onInstall);
    connect(ui->pb_icon, &QPushButton::clicked, this, &MainWindow::copy_icon);
    connect(ui->pbValidator, &QPushButton::clicked, this, &MainWindow::onValid);

    connect(ui->pb_fileDialogCopy, &QPushButton::clicked, this, &MainWindow::fileDialogCopy);
    connect(ui->pb_fileDialogInstall, &QPushButton::clicked, this, &MainWindow::fileDialogDelete);
    connect(ui->pb_filedialog_install, &QPushButton::clicked, this, &MainWindow::fileDialogInstall);
    connect(ui->pb_filedialog_icon, &QPushButton::clicked, this, &MainWindow::choice_icon);

    connect(ui->listLinks, &QListWidget::clicked, [&](QModelIndex index) {
        listFiles[index.row()].link = !listFiles[index.row()].link;
    }); //создание ярклыка

    connect(ui->listAutoLoading, &QListWidget::clicked, [&](QModelIndex index) {
        listFiles[index.row()].autostart = !listFiles[index.row()].autostart;
    }); //автозагрузка
}

void MainWindow::copy_icon()
{
    if (ui->le_icon->text().isEmpty())
    {
        Message::showMessage("Путь до папки пустой");
        return;
    }

    ui->lbl_icon->setPixmap(QPixmap(ui->le_icon->text()));
}

void MainWindow::choice_icon()
{
    auto str = QFileDialog::getOpenFileName(this, "Select a Directory", ui->le_icon->text(), "Images (*.png *.xpm *.jpg)");

    if (!str.isEmpty())
    {
        ui->le_icon->setText(str);
        auto list = str.split("/");
        name_icon_string.append(list[list.size() - 1]);
    }
}

void MainWindow::onCopy()
{
    if (ui->le_copy->text().isEmpty())
    {
        Message::showMessage("Путь до папки пустой");
        return;
    }
    if (listFiles.size())
    {
        Message::showMessage("Перезапустите приложение");
        return;
    }

    installator = ReadInstallator::readInstallator();
    uninstallator = ReadUnInstallator::readUnInstallator();
    /* Создаем дерево папок */
    FileSystem fileSystem;
    auto [listDirs, listFiles] = fileSystem.read("", ui->le_copy->text());
    this->listDirs = listDirs;
    this->listFiles = listFiles;

    for (int i = 0; i < listFiles.size(); i++)
    {
        ui->listLinks->addItem(listFiles[i].path);
        ui->listAutoLoading->addItem(listFiles[i].path);
    }
}

void MainWindow::onDelete()
{
    if (ui->le_delete->text().isEmpty())
    {
        Message::showMessage("Путь до папки пустой");
        return;
    }
    dir = QDir(ui->le_delete->text());
    list = dir.entryList(QDir::Files);

    QFile file;
    for (int i = 0; i < list.size(); i++)
    {
        file.setFileName(ui->le_delete->text() + QString("/") + list[i]);
        file.remove();
        file.close();
    }
}

void MainWindow::onInstall()
{
    if (ui->le_install->text().isEmpty())
    {
        Message::showMessage("Путь до папки пустой");
        return;
    }

    if (installator.isEmpty())
    {
        Message::showMessage("Пустой буфер");
        return;
    }

#ifdef Q_OS_WIN
    auto name_setup = QString("/setup.exe");
#elif Q_OS_LINUX
    auto name_setup.append("/setup");
#endif
    QFile file(ui->le_install->text() + name_setup);
    if (!file.open(QIODevice::ReadWrite))
    {
        Message::showMessage("Невозможно открыть  файл");
        return;
    }
    //дальше в файл нужно слить всю инфу

    file.write(installator); //!< запись инсталлятора

    file.write((reinterpret_cast<char *>(&razd)), sizeof(unsigned long long)); //!< запись разделителя

    int size = uninstallator.size();
    file.write(reinterpret_cast<char *>(&size), sizeof(size)); //!< размер деинсталлятора
    file.write(uninstallator);                                 //!< деинсталлятор

    auto applicationName = ui->le_ApplicationName->text().toLocal8Bit(); //!< название приложения
    int nameLength = applicationName.size();

    file.write(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    file.write(applicationName);

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
    //    ba_icon.append(ui->lbl_icon->pixmap()->data_ptr().data());
    //    file.write((char*)&ui->lbl_icon->pixmap()->,sizeof(name_icon_string_size));
    //     for(int k = 0;k<ui->lbl_icon->pixmap()->size();k++)
    //    {
    //        ui->lbl_icon->pixmap()->data_ptr().data()
    //    }
    int filesCount = listFiles.size();
    file.write(reinterpret_cast<char *>(&filesCount), sizeof(filesCount));

    for (int i = 0; i < listFiles.size(); i++) //!< информация о файлах
    {
        int ba_size = listFiles[i].ba.size();
        file.write(reinterpret_cast<char *>(&ba_size), sizeof(ba_size));
        file.write(listFiles[i].ba); //сам файл

        int path_size = listFiles[i].path.toLocal8Bit().size();
        file.write(reinterpret_cast<char *>(&path_size), sizeof(path_size));
        file.write(listFiles[i].path.toLocal8Bit()); //!< сам путь

        file.write(reinterpret_cast<char *>(&listFiles[i].link), sizeof(bool)); //флаг добавления в автозагрузку
        file.write(reinterpret_cast<char *>(&listFiles[i].autostart), sizeof(bool)); //флаг добавления в автозагрузку
    }

    int dirsCount = listDirs.size();
    file.write(reinterpret_cast<char *>(&dirsCount), sizeof(dirsCount));

    for (int i = 0; i < listDirs.size(); ++i)
    {
        int path_size = listDirs[i].path.toLocal8Bit().size();
        file.write(reinterpret_cast<char *>(&path_size), sizeof(path_size));
        file.write(listDirs[i].path.toLocal8Bit()); //!< сам путь
    }

    file.setPermissions(QFileDevice::ExeUser | QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup
                        | QFileDevice::WriteUser | QFileDevice::ReadUser);
    file.close();
}

void MainWindow::onValid()
{
    auto setStatusValid = [&](const QString &text) {
        qDebug() << text;
        ui->lblValid->setText(text);
    };

    qDebug() << ui->le_install->text();
    if (ui->le_install->text().isEmpty())
    {
        setStatusValid("le_install isEmpty");
        return;
    }

    Parser parser(ui->le_install->text() + QString("/setup.exe"));
    parser.findDelimiterInstallator();
    auto unInst = parser.readUninstallator();
    if (unInst != uninstallator)
    {
        setStatusValid("uninstallator is not Valid");
        return;
    }

    auto appName = parser.readApplicationName();

    auto filesCount = parser.readFilesCount();
    if (filesCount != listFiles.size())
    {
        setStatusValid("listFilesSize is not Valid");
        return;
    }

    for (int i = 0; i < filesCount; ++i)
    {
        auto data = parser.readFile();
        if ((data.ba.size() == 0) || (data.count == 0))
        {
            setStatusValid("error read file " + data.path + QString::number(data.count) + QString::number(data.ba.size()));
            return;
        }
    }

    auto dirsCount = parser.readDirsCount();
    if (dirsCount != listDirs.size())
    {
        setStatusValid("listDirs is not Valid");
        return;
    }

    for (int i = 0; i < dirsCount; ++i)
    {
        auto data = parser.readDirs();
    }

    setStatusValid("Succesful!");
}

void MainWindow::fileDialogCopy()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", ui->le_copy->text());
    if (!str.isEmpty())
    {
        ui->le_copy->setText(str);
    }
}

void MainWindow::fileDialogDelete()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", ui->le_delete->text());
    if (!str.isEmpty())
    {
        ui->le_delete->setText(str);
    }
}

void MainWindow::fileDialogInstall()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", ui->le_install->text());
    if (!str.isEmpty())
    {
        ui->le_install->setText(str);
    }
}

MainWindow::~MainWindow() {}
