#include <QDebug>

#include "pathwindow.h"
#include "ui_pathwindow.h"

PathWindow::PathWindow()
    : ui(new Ui::path_window)
{
    ui->setupUi(this);
    connect(ui->pb_guide, &QPushButton::clicked, this, &PathWindow::slot_pbguide);
    connect(ui->le_guide, &QLineEdit::textChanged, this, &PathWindow::slot_leguide);
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
    auto str = QFileDialog::getExistingDirectory(0, "Select a Directory", ui->le_guide->text());
    if (!str.isEmpty())
    {
        ui->le_guide->setText(str + QString("/") + applicationName);
    }

    QString str_test;

    { //проверка на двойной слеш  "//"
        bool flag = false;
        auto textTemp = ui->le_guide->text();
        for (int i = 0; i < ui->le_guide->text().size(); i++)
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
            ui->le_guide->clear();
            ui->le_guide->setText(str_test);
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

    if (ui->le_guide->text().isEmpty())
    {
        next->setEnabled(false);
    }
    else
    {
        next->setEnabled(true);
    }
}

bool PathWindow::isEmpty()
{
    return ui->le_guide->text().isEmpty();
}

void PathWindow::setText(const QString &text)
{
    ui->le_guide->setText(text);
}

QHBoxLayout *PathWindow::getLay()
{
    return ui->lay;
}

PathWindow::~PathWindow() {}
