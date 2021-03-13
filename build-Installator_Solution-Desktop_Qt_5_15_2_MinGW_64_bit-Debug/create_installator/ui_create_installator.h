/********************************************************************************
** Form generated from reading UI file 'create_installator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_INSTALLATOR_H
#define UI_CREATE_INSTALLATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_create_installator
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *le_copy;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *le_delete;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *le_install;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QLineEdit *le_icon;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pb_fileDialogCopy;
    QPushButton *pb_fileDialogInstall;
    QPushButton *pb_filedialog_install;
    QPushButton *pb_filedialog_icon;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_copy;
    QPushButton *pb_delete;
    QPushButton *pb_install;
    QPushButton *pb_icon;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *layValid;
    QPushButton *pbValidator;
    QLabel *lblValid;
    QLabel *lbl_icon;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *le_ApplicationName;
    QLabel *label_4;
    QListWidget *listLinks;
    QLabel *label_6;
    QListWidget *listAutoLoading;

    void setupUi(QDialog *create_installator)
    {
        if (create_installator->objectName().isEmpty())
            create_installator->setObjectName(QString::fromUtf8("create_installator"));
        create_installator->resize(380, 809);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(create_installator->sizePolicy().hasHeightForWidth());
        create_installator->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(create_installator);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(create_installator);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        le_copy = new QLineEdit(create_installator);
        le_copy->setObjectName(QString::fromUtf8("le_copy"));

        horizontalLayout_3->addWidget(le_copy);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(create_installator);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        le_delete = new QLineEdit(create_installator);
        le_delete->setObjectName(QString::fromUtf8("le_delete"));

        horizontalLayout_2->addWidget(le_delete);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(create_installator);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        le_install = new QLineEdit(create_installator);
        le_install->setObjectName(QString::fromUtf8("le_install"));

        horizontalLayout->addWidget(le_install);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(create_installator);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        le_icon = new QLineEdit(create_installator);
        le_icon->setObjectName(QString::fromUtf8("le_icon"));

        horizontalLayout_5->addWidget(le_icon);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pb_fileDialogCopy = new QPushButton(create_installator);
        pb_fileDialogCopy->setObjectName(QString::fromUtf8("pb_fileDialogCopy"));

        verticalLayout_2->addWidget(pb_fileDialogCopy);

        pb_fileDialogInstall = new QPushButton(create_installator);
        pb_fileDialogInstall->setObjectName(QString::fromUtf8("pb_fileDialogInstall"));

        verticalLayout_2->addWidget(pb_fileDialogInstall);

        pb_filedialog_install = new QPushButton(create_installator);
        pb_filedialog_install->setObjectName(QString::fromUtf8("pb_filedialog_install"));

        verticalLayout_2->addWidget(pb_filedialog_install);

        pb_filedialog_icon = new QPushButton(create_installator);
        pb_filedialog_icon->setObjectName(QString::fromUtf8("pb_filedialog_icon"));

        verticalLayout_2->addWidget(pb_filedialog_icon);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pb_copy = new QPushButton(create_installator);
        pb_copy->setObjectName(QString::fromUtf8("pb_copy"));

        verticalLayout->addWidget(pb_copy);

        pb_delete = new QPushButton(create_installator);
        pb_delete->setObjectName(QString::fromUtf8("pb_delete"));

        verticalLayout->addWidget(pb_delete);

        pb_install = new QPushButton(create_installator);
        pb_install->setObjectName(QString::fromUtf8("pb_install"));

        verticalLayout->addWidget(pb_install);

        pb_icon = new QPushButton(create_installator);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));

        verticalLayout->addWidget(pb_icon);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(horizontalSpacer);

        layValid = new QHBoxLayout();
        layValid->setObjectName(QString::fromUtf8("layValid"));
        pbValidator = new QPushButton(create_installator);
        pbValidator->setObjectName(QString::fromUtf8("pbValidator"));

        layValid->addWidget(pbValidator);

        lblValid = new QLabel(create_installator);
        lblValid->setObjectName(QString::fromUtf8("lblValid"));

        layValid->addWidget(lblValid);


        verticalLayout_4->addLayout(layValid);

        lbl_icon = new QLabel(create_installator);
        lbl_icon->setObjectName(QString::fromUtf8("lbl_icon"));
        lbl_icon->setMinimumSize(QSize(1, 100));

        verticalLayout_4->addWidget(lbl_icon);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(create_installator);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        le_ApplicationName = new QLineEdit(create_installator);
        le_ApplicationName->setObjectName(QString::fromUtf8("le_ApplicationName"));

        horizontalLayout_6->addWidget(le_ApplicationName);


        verticalLayout_4->addLayout(horizontalLayout_6);

        label_4 = new QLabel(create_installator);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        listLinks = new QListWidget(create_installator);
        listLinks->setObjectName(QString::fromUtf8("listLinks"));
        listLinks->setSelectionMode(QAbstractItemView::MultiSelection);
        listLinks->setMovement(QListView::Snap);

        verticalLayout_4->addWidget(listLinks);

        label_6 = new QLabel(create_installator);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_4->addWidget(label_6);

        listAutoLoading = new QListWidget(create_installator);
        listAutoLoading->setObjectName(QString::fromUtf8("listAutoLoading"));
        listAutoLoading->setSelectionMode(QAbstractItemView::MultiSelection);
        listAutoLoading->setMovement(QListView::Snap);

        verticalLayout_4->addWidget(listAutoLoading);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(create_installator);

        QMetaObject::connectSlotsByName(create_installator);
    } // setupUi

    void retranslateUi(QDialog *create_installator)
    {
        create_installator->setWindowTitle(QCoreApplication::translate("create_installator", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("create_installator", "\320\237\321\203\321\202\321\214", nullptr));
        le_copy->setText(QString());
        label_2->setText(QCoreApplication::translate("create_installator", "\320\237\321\203\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("create_installator", "\320\237\321\203\321\202\321\214", nullptr));
        le_install->setText(QString());
        label_7->setText(QCoreApplication::translate("create_installator", "\320\237\321\203\321\202\321\214", nullptr));
        le_icon->setText(QString());
        pb_fileDialogCopy->setText(QCoreApplication::translate("create_installator", "\320\277\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
        pb_fileDialogInstall->setText(QCoreApplication::translate("create_installator", "\320\277\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
        pb_filedialog_install->setText(QCoreApplication::translate("create_installator", "\320\277\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
        pb_filedialog_icon->setText(QCoreApplication::translate("create_installator", "\320\277\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
        pb_copy->setText(QCoreApplication::translate("create_installator", "\320\241\320\272\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", nullptr));
        pb_delete->setText(QCoreApplication::translate("create_installator", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", nullptr));
        pb_install->setText(QCoreApplication::translate("create_installator", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\270\320\275\321\201\321\202\320\260\320\273\320\273\321\217\321\202\320\276\321\200", nullptr));
        pb_icon->setText(QCoreApplication::translate("create_installator", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203", nullptr));
        pbValidator->setText(QCoreApplication::translate("create_installator", "\320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\260", nullptr));
        lblValid->setText(QCoreApplication::translate("create_installator", "----------------------------------------", nullptr));
        lbl_icon->setText(QCoreApplication::translate("create_installator", "\320\234\320\265\321\201\321\202\320\276 \320\264\320\273\321\217 \320\267\320\275\320\260\321\207\320\272\320\260 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("create_installator", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("create_installator", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273\321\213 \320\264\320\273\321\217 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217 \321\217\321\200\320\273\321\213\320\272\320\276\320\262..", nullptr));
        label_6->setText(QCoreApplication::translate("create_installator", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273\321\213 \320\264\320\273\321\217 \320\267\320\260\320\263\320\276\320\275\320\260 \320\262 \320\260\320\262\321\202\320\276\320\267\320\260\320\263\321\200\321\203\320\267\320\272\321\203..", nullptr));
    } // retranslateUi

};

namespace Ui {
    class create_installator: public Ui_create_installator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_INSTALLATOR_H
