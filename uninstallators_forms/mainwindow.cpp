#include "mainwindow.h"

QString application_name_string, path_dir;

MainWindow::MainWindow(bool &flagTemp)
    : flag(&flagTemp)
    , razd(0xABCD)
{
    createPages();

    connect(this, &MainWindow::currentIdChanged, this, &MainWindow::slot_IdChanged);
}

void MainWindow::createPages()
{
    QWizardPage *ppage1 = new QWizardPage;
    vlay1 = new QVBoxLayout;
    te1.setText(QString("Чтобы удалить приложение нажмите далее..."));
    te1.setReadOnly(true);
    vlay1->addWidget(&te1);
    ppage1->setLayout(vlay1);
    ppage1->setButtonText(QWizard::NextButton, QString("Далее"));
    ppage1->setButtonText(QWizard::CancelButton, QString("Отмена"));

    addPage(ppage1);

    QWizardPage *ppage2 = new QWizardPage;
    pprd = new QProgressDialog("Удаление файлов ....", "", 0, 100);
    pprd->setCancelButton(nullptr);
    pprd->setMinimumDuration(100);
    pprd->setAutoClose(false);
    pprd->setAutoReset(false);
    vlay2 = new QVBoxLayout;
    vlay2->addWidget(pprd);
    te2.setReadOnly(true);
    vlay2->addSpacing(50);
    vlay2->addWidget(&te2);
    ppage2->setLayout(vlay2);
    ppage2->setButtonText(QWizard::NextButton, QString("Далее"));
    ppage2->setButtonText(QWizard::FinishButton, QString("Закрыть"));
    ppage2->setButtonText(QWizard::CancelButton, QString("Отмена"));
    addPage(ppage2);
}

void MainWindow::slot_IdChanged(int i)
{
    button(QWizard::BackButton)->hide();
    if (i == 1)
    {
        button(QWizard::NextButton)->setEnabled(false);
        button(QWizard::CancelButton)->hide();
        long long temp = 0;
        int count = 0;
        file.setFileName(qApp->applicationFilePath());
        QFileInfo fileinfo(file);
        long long size = fileinfo.size(), uninstall_size = 0;
        float current_percent = 0, percent_from_file = (float) (((float) 100) / ((float) (size)));
        ;
        if (!file.open(QIODevice::ReadOnly))
        {
            msg.showMessage(qApp->applicationFilePath() + QString(" ") + file.errorString());
            msg.show();
            return;
        }

        while (!file.atEnd())
        {
            file.read((char *) &temp, sizeof(long long));
            current_percent += sizeof(temp) * percent_from_file;
            pprd->setValue((int) current_percent);
            if (temp == razd && !count)
            {
                count = 1;
            }
            if (count == 1)
            {
                int count_string_name = 0;
                file.read((char *) &count_string_name, sizeof(count_string_name));
                current_percent += percent_from_file * sizeof(count_string_name);
                pprd->setValue((int) current_percent);
                char *application_name = new char[count_string_name + 1];
                file.read(application_name, count_string_name);
                current_percent += percent_from_file * sizeof(count_string_name);
                pprd->setValue((int) current_percent);
                application_name[count_string_name] = 0;
                application_name_string.append(application_name);

                while (!file.atEnd())
                {
                    datas d;
                    file.read((char *) &d.quantity, sizeof(d.quantity));
                    current_percent += sizeof(d.quantity) * percent_from_file;
                    pprd->setValue((int) current_percent);
                    d.str = new char[d.quantity + 1];
                    file.read(d.str, d.quantity);
                    current_percent += sizeof(d.quantity) * percent_from_file;
                    pprd->setValue((int) current_percent);
                    file.read((char *) &d.autostart,
                              sizeof(bool)); //если true, то экзешник был добавлен в автозагрузку и нужно удалить его из автозагрузки
                    current_percent += sizeof(bool) * percent_from_file;
                    pprd->setValue((int) current_percent);
                    file.read((char *) &d.link,
                              sizeof(bool)); //если true, то возмжно был создан ярлык на рабочем столе, что нужно и проверить
                    current_percent += sizeof(bool) * percent_from_file;
                    pprd->setValue((int) current_percent);

                    d.str[d.quantity] = 0;
                    d.path.append(QString().fromLocal8Bit(d.str));
                    files_list.append(d);
                    te2.append(qApp->applicationDirPath() + d.path + QString(" - файл удален.."));
                    //дальше нужно удалить все папки и файлы
                    QFile opened_file(qApp->applicationDirPath() + d.path);
                    if (!opened_file.open(QIODevice::ReadOnly))
                    {
                        msg.showMessage(d.path + QString("   ") + opened_file.errorString());
                        msg.show();
                        continue;
                    }
                    opened_file.remove();
                    opened_file.close();
                    if (d.autostart)
                    {
                        deleteautoStartApplication(d.path); //удаление из автозагрузки
                        //проверка существует ли ярлык в папке автозагрузки, если да, то удаляем
                        //                         QStringList strlist = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
                        QStringList filename = d.path.split("/");
                        //                         for(int j = 0;j<strlist.size();j++)
                        //                         {
                        path_dir.append(open_uninst());
                        //                           msg.showMessage(path_dir);
                        //                            msg.show();
                        opened_file.setFileName(path_dir + QString("/") + filename[filename.size() - 1] + QString(".lnk"));
                        if (!opened_file.open(QIODevice::ReadOnly))
                        {
                            msg.showMessage(path_dir + QString("/") + filename[filename.size() - 1] + QString(".lnk ")
                                            + opened_file.errorString());
                            msg.show();
                            //                              continue;
                        }
                        opened_file.remove();
                        opened_file.close();
                        //                         }
                        deleteuninstall(application_name_string); //удаление из списка установленных программ
                    }
                    if (d.link)
                    {
                        //проверка существует ли ярлык на рабочем столе, если да, то удаляем
                        QStringList strlist = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
                        QStringList filename = d.path.split("/");
                        for (int j = 0; j < strlist.size(); j++)
                        {
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
                            opened_file.setFileName(strlist[j] + QString("/") + filename[filename.size() - 1] + QString(".lnk"));
#elif Q_OS_LINUX
                            opened_file.setFileName(strlist[j] + QString("/") + filename[filename.size() - 1]);
#endif
                            if (!opened_file.open(QIODevice::ReadOnly))
                            {
                                //                                 #ifdef Q_OS_WIN32//вывод о том, что не найдено не делаем, так как какая разница нашел - удалил, а не нашел, то пофиг
                                //                                 msg.showMessage(strlist[j]  + QString("/") + filename[filename.size()-1] +  QString(".lnk ") + opened_file.errorString());
                                //                                 #else Q_OS_LINUX
                                //                                 msg.showMessage(strlist[j]  + QString("/") + filename[filename.size()-1] + opened_file.errorString());
                                //                                 #endif
                                //                                 msg.show();
                                continue;
                            }
                            opened_file.remove();
                            opened_file.close();
                        }
                    }
                }
                //дальше  пропубем удалить папку
            }
        }
        file.close();
        for (int i = 0; i < files_list.size(); i++)
        {
            QString path;
            QStringList list_dirs = files_list[i].path.split("/");
            int k = 0;
            while (list_dirs.size() - 1 - k > 1)
            {
                path.clear();
                for (int j = 1; j < list_dirs.size() - 1 - k; j++)
                    path.append(list_dirs[j] + QString("/"));
                QDir dir(qApp->applicationDirPath() + QString("/") + path);
                if (dir.exists()) //если такая папка существует, то удаляем ее
                    dir.rmdir(qApp->applicationDirPath() + QString("/") + path);
                k++;
            }
        }
        pprd->setValue(100);
        *flag = true;
    }
}

void MainWindow::deleteautoStartApplication(QString application_name)
{
#ifdef Q_OS_WIN32
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    //    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.remove(application_name);
#else Q_OS_LINUX
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QString("/autostart-scripts");
    QFile autorunFile(autostartPath + application_name + QString(".sh"));
    msg.showMessage(autostartPath + application_name + QString(".sh"));
    msg.show();
    if (!autorunFile.open(QIODevice::ReadOnly))
    {
        msg.showMessage(QString("Не получилось открыть файл автозагрузки: ") + file.errorString());
        msg.show();
        return;
    }
    autorunFile.remove();
    autorunFile.close();
#endif
}

void MainWindow::deleteuninstall(QString application_name)
{
#ifdef Q_OS_WIN32
    QSettings settings(QString("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), QSettings::NativeFormat);
    settings.remove(application_name);
    // settings.sync();
#endif
}

QString MainWindow::open_uninst()
{
    QString installation_path;
    /*  Получить путь до папки через реестр  */
    QSettings settings(QString(QString("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\")
                               + application_name_string),
                       QSettings::NativeFormat);
    QStringList list;
    list.append(settings.allKeys());
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] == QString("InstallDir"))
        {
            installation_path.append(settings.value(list[i]).toString()); //тут
            break;
        }
    }
    //   qDebug()<<installation_path;
    //   return 0;
    return installation_path;
}

MainWindow::~MainWindow()
{
    if (pprd)
        delete pprd;
    if (vlay1)
        delete vlay1;
    if (vlay2)
        delete vlay2;
}
