#include <QApplication>
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QSettings>

#include "installator.h"
#include "proto.h"

Installator::Installator()
    : path_window(new PathWindow)
    , progressDialog(new QProgressDialog("Установка приложения ....", "", 0, 100))
    , razd(0xAABBAABB)
    , razd_uninstall(0xABCD)
    , checkbox(new QCheckBox[2])
{
    createPages();

    connect(this, &Installator::currentIdChanged, this, &Installator::onPageChanged);
    connect(&checkbox[0], &QRadioButton::clicked, this, &Installator::slot_radiobutton);
    connect(&checkbox[1], &QRadioButton::clicked, this, &Installator::slot_radiobutton);
}

void Installator::createPages()
{
    auto page2 = new QWizardPage;
    page2->setLayout(path_window->getLay());
    auto nextButton = new QPushButton;
    nextButton = qobject_cast<QPushButton *>(this->button(QWizard::NextButton));
    path_window->setButton(nextButton);
    path_window->setInstallationPath(&installation_path);
    addPage(page2);

    auto page3 = new QWizardPage;
    progressDialog->setCancelButton(nullptr);
    progressDialog->setAutoClose(false);
    progressDialog->setAutoReset(false);
    auto vlay3page = new QVBoxLayout;
    vlay3page->addWidget(progressDialog);
    te.setReadOnly(true);
    vlay3page->addSpacing(50);
    vlay3page->addWidget(&te);
    page3->setLayout(vlay3page);
    addPage(page3);

    auto page4 = new QWizardPage;
    auto vlay4page = new QVBoxLayout;

    auto hlay = new QHBoxLayout[2];

    auto lbl = new QLabel[2];
    lbl[0].setText(QString("Добавить ярлык на рабочем столе?"));
    lbl[1].setText(QString("Добавить приложение в автозагрузку?"));

    checkbox[0].setText(QString("Да"));
    checkbox[1].setText(QString("Да"));

    hlay[0].addWidget(&lbl[0]);
    hlay[0].addWidget(&checkbox[0]);

    hlay[1].addWidget(&lbl[1]);
    hlay[1].addWidget(&checkbox[1]);

    vlay4page->addLayout(&hlay[0]);
    vlay4page->addLayout(&hlay[1]);

    page4->setLayout(vlay4page);
    addPage(page4);
}

void Installator::setAutoStartApplication()
{
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    for (int i = 0; i < autostart_list.size(); i++)
    {
        //нужно создать ярлык и поместить его в папку автозагрузки
        QFile file(installation_path + autostart_list[i].path);
        auto filename = autostart_list[i].path.split("/");

        if (!file.open(QIODevice::ReadWrite))
        {
            msg.showMessage(file.errorString());
            msg.show();
            return;
        }
        file.link(installation_path + QString("/") + filename[filename.size() - 1] + QString(".lnk"));
        file.close();

        QSettings settings(QString(reestRun), QSettings::NativeFormat);
        settings.setValue(autostart_list[i].path, QDir::toNativeSeparators(installation_path + autostart_list[i].path + QString(".lnk")));
    }

#elif Q_OS_LINUX

    //    msg.showMessage(QString("setAutoStartApplication"));
    //    msg.show();
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QString("/autostart-scripts");
    /* Проверяем, существует ли директория, в которой будет храниться файл автозапуска.
         * А то мало ли... пользователь удалил...
         * */
    QDir autorunDir(autostartPath);
    if (!autorunDir.exists())
    {
        // Если не существует, то создаём
        autorunDir.mkpath(autostartPath);
    }

    // Далее проверяем наличие самого файла автозапуска
    /* Далее открываем файл и записываем в него необходимые данные
    * с указанием пути к исполняемому файлу, с помощью QCoreApplication::applicationFilePath()
     * */
    //    msg.showMessage(QString("Количество файлов для авторана   ") + QString().setNum(autostart_list.size()));
    //    msg.show();
    for (int i = 0; i < autostart_list.size(); i++)
    {
        QStringList filename = autostart_list[i].path.split("/");
        QFile autorunFile(autostartPath + QString("/") + filename[filename.size() - 1] + QString(".sh"));
        if (!autorunFile.open(QIODevice::WriteOnly))
        {
            msg.showMessage(QString("Не получилось создать файл автозагрузки: ") + file.errorString());
            msg.show();
            return;
        }
        QString path;
        path.append(QString("cd ") + installation_path);
        for (int j = 0; j < filename.size() - 1; j++)
            path.append(filename[j] + QString("/"));
        QString autorunContent(installation_path + autostart_list[i].path);
        QTextStream outStream(&autorunFile);
        outStream << path << QString("\n") << autorunContent;
        // Устанавливаем права доступа, в том числе и на исполнение файла, иначе автозапуск не сработает
        autorunFile.setPermissions(QFileDevice::ExeUser | QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup
                                   | QFileDevice::WriteUser | QFileDevice::ReadUser);
        autorunFile.close();
    }

#endif
}

void Installator::onAutoStartApplication()
{
    if (!autostart_list.isEmpty())
        setAutoStartApplication();
}

void Installator::addUninstall(QString application_name)
{
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    QSettings settings(QString(reestrUninstall) + application_name, QSettings::NativeFormat);
    settings.setValue(QString("UninstallString"), QDir::toNativeSeparators(installation_path + QString("/") + QString("uninstall.exe")));
    settings.setValue(QString("DisplayName"), QDir::toNativeSeparators(application_name));
    settings.setValue(QString("InstallDir"), QDir::toNativeSeparators(installation_path));
#endif
}

void Installator::setApplicationName(QString applicationName)
{
    applicationNameReestr.clear();
    applicationNameReestr.append(applicationName);
    path_window->setApplicationName(applicationName);
    onPageChanged(0);
}

QString Installator::checkInstallDir()
{
    QString installation_path_local;
    /*  Получить путь до папки через реестр  */
    QSettings settings(QString(reestrUninstall + applicationNameReestr), QSettings::NativeFormat);
    QStringList list(settings.allKeys());

    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] == QString("InstallDir"))
        {
            installation_path_local.append(settings.value(list[i]).toString()); //тут
            break;
        }
    }

    if (installation_path_local.isEmpty()) //если пустая строка, тогда вернем строку на стандартную папку в програм файлс
    {
        auto root_dir = QDir().root().path();
        installation_path_local.append(root_dir + applicationNameReestr);
    }

    return installation_path_local;
}

void Installator::slot_radiobutton(bool)
{
    onPageChanged(2);
}

void Installator::slot_createlink(bool)
{
    for (int i = 0; i < link_list.size(); i++)
    {
        QFile file(installation_path + link_list[i].path);
        auto filename = link_list[i].path.split("/");
        if (!file.open(QIODevice::ReadWrite))
        {
            msg.showMessage(file.errorString());
            msg.show();
            return;
        }
        auto strlist = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
        for (int j = 0; j < strlist.size(); j++)
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
            file.link(strlist[j] + QString("/") + filename[filename.size() - 1] + QString(".lnk"));
#elif Q_OS_LINUX
            file.link(strlist[j] + QString("/") + filename[filename.size() - 1]);
#endif
        file.close();
    }
}

void Installator::onPageChanged(int i)
{
    button(QWizard::NextButton)->setText(QString("Далее"));
    button(QWizard::CancelButton)->setText(QString("Отмена"));
    button(QWizard::FinishButton)->setText(QString("Закрыть"));
    button(QWizard::BackButton)->hide();

    if (i == 0) //!< окно установки пути инсталляции
    {
        path_window->setText(checkInstallDir());
        if (!path_window->isEmpty())
        {
            button(QWizard::NextButton)->setEnabled(true);
        }
    }

    if (i == 1)
    {
        Parser parser(qApp->applicationFilePath());
        parser.findDelimiterInstallator();
        auto unInstallator = parser.readUninstallator();
        auto appName = parser.readApplicationName();

        auto filesCount = parser.readFilesCount();
        for (int i = 0; i < filesCount; ++i)
        {
            auto data = parser.readFile();
            filesList.append(data);
        }

        auto dirsCount = parser.readDirsCount();
        for (int i = 0; i < dirsCount; ++i)
        {
            auto data = parser.readDirs();
            listDirs.append(data);
        }

        for (const auto &dir : listDirs)
        {
            QDir qDir(dir.path);
            if (!qDir.exists())
            {
                qDir.mkdir(installation_path + dir.path);
            }
        }

        for (const auto &file : filesList)
        {
            QFile qFile(installation_path + file.path);
            if (!qFile.open(QIODevice::WriteOnly))
            {
                msg.showMessage(qFile.errorString());
                msg.show();
                return;
            }
            qFile.write(file.ba);
            qFile.close();
        }

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
        auto name_uninstall = QString("uninstall.exe");
#elif __linux__
        auto name_uninstall = QString("uninstall");
#endif
        QFile file(installation_path + name_uninstall);
        if (!file.open(QIODevice::WriteOnly))
        {
            msg.showMessage(file.errorString());
            msg.show();
            return;
        }
        file.write(unInstallator); //!< записываем сам деинсталлятор
        file.write(reinterpret_cast<char *>(&razd_uninstall), sizeof(razd_uninstall)); //!< разделитель между данными

        int appNameLength = appName.toLocal8Bit().size();
        file.write(reinterpret_cast<char *>(&appNameLength), sizeof(appNameLength));
        file.write(appName.toLocal8Bit());

        for (int i = 0; i < filesList.size(); i++)
        {
            int length = filesList[i].path.toLocal8Bit().size();
            file.write(reinterpret_cast<char *>(&length), sizeof(length));
            file.write(filesList[i].path.toLocal8Bit());

            file.write(reinterpret_cast<char *>(&filesList[i].autostart), sizeof(bool));
            file.write(reinterpret_cast<char *>(&filesList[i].link), sizeof(bool));
        }
        addUninstall(applicationName); //добавление деинсталлятора в список установка и удаление программ
        file.setPermissions(QFileDevice::ExeUser | QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup
                            | QFileDevice::WriteUser | QFileDevice::ReadUser);
        file.close();
        button(QWizard::NextButton)->setEnabled(true);
    }
    if (i == 2) //страница создания ярлыка
    {
        button(QWizard::CancelButton)->hide();
        if (!link_list.size())
            checkbox[0].setEnabled(false);
        if (!autostart_list.size())
            checkbox[1].setEnabled(false);

        if (checkbox[0].isChecked())
            connect(button(this->FinishButton), &QAbstractButton::clicked, this, &Installator::slot_createlink);
        else
            disconnect(button(this->FinishButton), &QAbstractButton::clicked, this, &Installator::slot_createlink);
        if (checkbox[1].isChecked())
            connect(button(this->FinishButton), &QAbstractButton::clicked, this, &Installator::onAutoStartApplication);
        else
            disconnect(button(this->FinishButton), &QAbstractButton::clicked, this, &Installator::onAutoStartApplication);
    }
}
