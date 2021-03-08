#include <QDebug>

#include "pathwindow.h"

PathWindow::PathWindow()
{
    setupUi(this);
    connect(pb_guide, &QPushButton::clicked, this, &PathWindow::slot_pbguide);
    connect(le_guide, &QLineEdit::textChanged, this, &PathWindow::slot_leguide);
}

void PathWindow::setButton(QPushButton *next)
{
    this->next = next;
}
void PathWindow::setInstallationPath(QString *s)
{
    str = s;
}

void PathWindow::setApplicationName(QString text)
{
    applicationName.append(text);
}

void PathWindow::slot_pbguide()
{
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", le_guide->text());
    if (!str.isEmpty())
    {
        le_guide->setText(str + QString("/") + applicationName);
    }

    QString str_test;

    { //проверка на двойной слеш  "//"
        bool flag = false;
        auto textTemp = le_guide->text();
        for (int i = 0; i < le_guide->text().size(); i++)
        {
            char buff = (textTemp.toLocal8Bit().data() + i)[0];
            char buff1 = (textTemp.toLocal8Bit().data() + i + 1)[0];

            if (static_cast<int>(buff) == static_cast<int>('/') && static_cast<int>(buff1) == (int) '/')
            {
                flag = true;
                continue;
            }
            else
            {
                str_test.append(textTemp[i]);
            }
        }
        if (flag)
        {
            le_guide->clear();
            le_guide->setText(str_test);
        }
    }
}

void PathWindow::slot_leguide(QString text)
{
    str->clear();
    str->append(text);
    if (!QDir(text).exists())
    {
        qDebug() << "Каталог не существует";
        return;
    }

    if (le_guide->text().isEmpty())
    {
        next->setEnabled(false);
    }
    else
    {
        next->setEnabled(true);
    }
}

PathWindow::~PathWindow()
{
    delete lay;
}
