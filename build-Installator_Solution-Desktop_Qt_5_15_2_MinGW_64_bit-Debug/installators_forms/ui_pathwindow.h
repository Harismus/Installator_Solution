/********************************************************************************
** Form generated from reading UI file 'pathwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHWINDOW_H
#define UI_PATHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_path_window
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *lay;
    QLabel *label;
    QLineEdit *le_guide;
    QPushButton *pb_guide;

    void setupUi(QWidget *path_window)
    {
        if (path_window->objectName().isEmpty())
            path_window->setObjectName(QString::fromUtf8("path_window"));
        path_window->resize(723, 261);
        path_window->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(path_window);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(65, 30, 281, 25));
        lay = new QHBoxLayout(layoutWidget);
        lay->setObjectName(QString::fromUtf8("lay"));
        lay->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        lay->addWidget(label);

        le_guide = new QLineEdit(layoutWidget);
        le_guide->setObjectName(QString::fromUtf8("le_guide"));

        lay->addWidget(le_guide);

        pb_guide = new QPushButton(layoutWidget);
        pb_guide->setObjectName(QString::fromUtf8("pb_guide"));

        lay->addWidget(pb_guide);


        retranslateUi(path_window);

        QMetaObject::connectSlotsByName(path_window);
    } // setupUi

    void retranslateUi(QWidget *path_window)
    {
        path_window->setWindowTitle(QCoreApplication::translate("path_window", "Widget", nullptr));
        label->setText(QCoreApplication::translate("path_window", "\320\237\321\203\321\202\321\214", nullptr));
        pb_guide->setText(QCoreApplication::translate("path_window", "\320\277\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class path_window: public Ui_path_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHWINDOW_H
