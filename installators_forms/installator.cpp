#include <QDir>
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
    auto ppage2 = new QWizardPage;
    ppage2->setLayout(path_window->lay);
    auto ptrNextButton = new QPushButton;
    ptrNextButton = qobject_cast<QPushButton *>(this->button(QWizard::NextButton));
    path_window->setButton(ptrNextButton);
    path_window->setInstallationPath(&installation_path);
    addPage(ppage2);

    auto ppage3 = new QWizardPage;
    progressDialog->setCancelButton(nullptr);
    progressDialog->setAutoClose(false);
    progressDialog->setAutoReset(false);
    auto vlay3page = new QVBoxLayout;
    vlay3page->addWidget(progressDialog);
    te.setReadOnly(true);
    vlay3page->addSpacing(50);
    vlay3page->addWidget(&te);
    ppage3->setLayout(vlay3page);
    addPage(ppage3);

    auto ppage4 = new QWizardPage;
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

    ppage4->setLayout(vlay4page);
    addPage(ppage4);
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
        path_window->le_guide->setText(checkInstallDir());
        if (!path_window->le_guide->text().isEmpty())
        {
            button(QWizard::NextButton)->setEnabled(true);
        }
    }

    if (i == 1) //!< страница загрузки
    {
        QDir dir(installation_path);

        if (!dir.exists()) //!< если такой папки не существует, то создаем ее
            dir.mkdir(installation_path);

        button(QWizard::NextButton)->setEnabled(false);
        button(QWizard::CancelButton)->hide();
        /*        Копирования данных, разбор и создание папок        */
        long long temp = 0;
        int count = 0;
        /*        Открытие и считывания самого себя         */
        file.setFileName(qApp->applicationFilePath());
        float current_percent = 0;
        auto percent_from_file = static_cast<float>(100) / file.size();

        if (!file.open(QIODevice::ReadOnly))
        {
            msg.showMessage(file.errorString());
            msg.show();
            return;
        }

        while (!file.atEnd())
        {
            file.read(reinterpret_cast<char *>(&temp), sizeof(long long));

            current_percent += percent_from_file * (sizeof(temp)); //вычисляем количество(считаем инсталлятор)
            progressDialog->setValue(static_cast<int>(current_percent));

            if (temp == razd)
            {
                count++;
            }

            if (count == 1) //файлы инсталлируемого приложения
            {
                char bytes;
                int uninstall_size; //размер деинсталлятора
                file.read(reinterpret_cast<char *>(&uninstall_size), sizeof(uninstall_size));
                for (int i = 0; i < uninstall_size; i++)
                {
                    file.read(&bytes, sizeof(bytes));
                    uninstall.append(bytes);
                }

                current_percent += percent_from_file * uninstall_size; //вычисляем количество(считаем деинсталлятор)
                //читаем  название приложения
                int count_string_name = 0;

                file.read(reinterpret_cast<char *>(&count_string_name), sizeof(count_string_name));

                current_percent += percent_from_file * sizeof(count_string_name);
                progressDialog->setValue(static_cast<int>(current_percent));

                auto application_name = new char[count_string_name + 1];
                file.read(application_name, count_string_name);

                current_percent += percent_from_file * sizeof(count_string_name);
                progressDialog->setValue(static_cast<int>(current_percent));

                application_name[count_string_name] = 0;
                applicationName.clear();
                applicationName.append(application_name);

                while (!file.atEnd())
                {
                    datas d;
                    file.read(reinterpret_cast<char *>(&d.quantity), sizeof(d.quantity));

                    current_percent += percent_from_file * sizeof(d.quantity); //вычисляем количество
                    progressDialog->setValue(static_cast<int>(current_percent));

                    int n = 0;
                    file.read(reinterpret_cast<char *>(&n), sizeof(n));
                    d.str = new char[n + 1];

                    file.read(d.str, n);

                    d.str[n] = 0;

                    d.path.append(QString().fromLocal8Bit(d.str));

                    te.append(installation_path + d.path + QString(" - файл скопирован.."));
                    //создание папок
                    QString path;
                    QStringList list_dirs = d.path.split("/");
                    path.clear();
                    for (int j = 1; j < list_dirs.size() - 1; j++)
                    {
                        path.append(list_dirs[j] + QString("/"));
                        QDir dir(installation_path + QString("/") + path);
                        if (!dir.exists()) //если такой папки не существует, то создаем ее
                            dir.mkdir(installation_path + QString("/") + path);
                    }

                    QFile file_creator;
                    file_creator.setFileName(installation_path + QString("/") + d.path);
                    if (!file_creator.open(QIODevice::ReadWrite))
                    {
                        msg.showMessage(installation_path + d.path + file.errorString());
                        msg.show();
                        return;
                    }
                    //дальше в файл нужно слить всю инфу
                    ba_files.clear();
                    for (int j = 0; j < d.quantity; j++)
                    {
                        file.read(&bytes, sizeof(bytes));
                        ba_files.append(bytes);
                    }
                    current_percent += percent_from_file * d.quantity; //вычисляем количество
                    progressDialog->setValue(static_cast<int>(current_percent));
                    file_creator.write(ba_files.data(), d.quantity);
                    file_creator.setPermissions(QFileDevice::ExeUser | QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup
                                                | QFileDevice::WriteUser | QFileDevice::ReadUser);
                    file_creator.close();

                    file.read(reinterpret_cast<char *>(&d.link), sizeof(bool));
                    current_percent += percent_from_file * sizeof(bool); //вычисляем количество
                    progressDialog->setValue(static_cast<int>(current_percent));
                    file.read(reinterpret_cast<char *>(&d.autostart), sizeof(bool));
                    current_percent += percent_from_file * sizeof(bool); //вычисляем количество
                    progressDialog->setValue(static_cast<int>(current_percent));
                    files_list.append(d);

                    if (d.link)
                        link_list.append(d);

                    if (d.autostart)
                        autostart_list.append(d);
                }
                progressDialog->setValue(100);
            }
        }
        file.close();

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
        auto name_uninstall = QString("uninstall.exe");
#elif __linux__
        auto name_uninstall = QString("uninstall");
#endif
        file.setFileName(installation_path + QString("/") + name_uninstall);
        if (!file.open(QIODevice::WriteOnly))
        {
            msg.showMessage(file.errorString());
            msg.show();
            return;
        }
        file.write(uninstall);
        file.write(reinterpret_cast<char *>(&razd_uninstall), sizeof(razd_uninstall));

        auto application_name = new char[applicationName.toLocal8Bit().size()];
        for (int k = 0; k < applicationName.toLocal8Bit().size(); k++)
        {
            application_name[k] = *(applicationName.toLocal8Bit().data() + k);
        }

        int application_name_string_size = applicationName.toLocal8Bit().size();
        file.write(reinterpret_cast<char *>(&application_name_string_size), sizeof(application_name_string_size));
        file.write(application_name, applicationName.toLocal8Bit().size());
        for (int i = 0; i < files_list.size(); i++)
        {
            int size = files_list[i].path.toLocal8Bit().size();
            file.write(reinterpret_cast<char *>(&size), sizeof(size));
            auto buff = new char[size];
            for (int k = 0; k < files_list[i].path.toLocal8Bit().size(); k++)
            {
                buff[k] = *(files_list[i].path.toLocal8Bit().data() + k);
            }
            file.write(buff, size);
            file.write(reinterpret_cast<char *>(&files_list[i].autostart), sizeof(bool));
            file.write(reinterpret_cast<char *>(&files_list[i].link), sizeof(bool));
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
