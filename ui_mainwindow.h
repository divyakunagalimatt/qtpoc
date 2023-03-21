#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include "player.h"
#include <libudev.h>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <iostream>
//#include "ui_mainwindow.h"
using namespace std;

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_11;
    QWidget *page_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QWidget *gridLayoutWidget;
    QGridLayout *mainLayout;
    QTableWidget *tableWidget;
    QWidget *page_9;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSlider *hSliderVideo_2;
    QLabel *endTime_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *LblNowPlaying_2;
    QGridLayout *gridLayout_2;

    QPushButton *BtnPause_2;
    QComboBox *comboBox_2;
    QPushButton *directory_2;
    QPushButton *BtnPlay_2;
    QGroupBox *groupBox_2;
    QSlider *vSliderSound_2;
    QPushButton *BtnMute_2;

    QLabel *filesFoundLabel;
    QPushButton *findButton;
    QPushButton *findVideoButton;
    QTableWidget *filesTable;




    //QWidget *gridLayoutWidget;

    QDir currentDir;





    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));


        auto  rec = QApplication::desktop()->screenGeometry();
        auto  height = rec.height();
        auto  width = rec.width();
        cout<<"height = "<<height<<" width = "<<width<<"\n";


        int size_x_pb,size_y_pb;
        int size_x_sw,size_y_sw;
        int size_x_gl,size_y_gl;;
        int app_width,app_height;

        float conv_x_pb,conv_y_pb;
        float conv_x_sw,conv_y_sw;
        conv_x_pb = (float)(151.0/1082);
        size_x_pb = conv_x_pb * width;
        conv_y_pb = (float)(141.0/420);
        size_y_pb = conv_y_pb * height;

        conv_x_sw = 1091.0/1082;
        size_x_sw = (int)(conv_x_sw * width);

        conv_y_sw = 601.0/420;
        size_y_sw = (int)(conv_y_sw * height);

        cout<<" size_x = "<<size_x_pb<<" size_y = "<<size_y_pb<<" size_x_sw = "<<size_x_sw<<"\n";

        int offset_power_pb_x = ( 480.0 / 1082) * width ;
        int offset_power_pb_y = ( 130.0 / 420) * height ;

        int offset_array2_pb_x = (930.0 / 1082) * width;
        int offset_gl_x = (149.0 / 1082) * width;
        int offset_array2_pb_y = (140.0 / 420) * height;
        int offset_array3_pb_y = (280.0 / 420) * height;

        size_x_gl = (781.0 / 1082) * width;
        size_y_gl = (421.0 / 420) * height;

        cout << " offset = "<<offset_power_pb_x;

        app_width = width;
        app_height = height;



        MainWindow->resize(app_width, app_height);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 224, 80);"));

        MainWindow->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, size_x_sw, size_y_sw));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        stackedWidget->setFont(font);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        pushButton_11 = new QPushButton(page);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));


        pushButton_11->setGeometry(QRect(offset_power_pb_x, offset_power_pb_y, size_x_pb, size_y_pb));

        ///*
        QPixmap pixmap("power-button-icon-8344.png");
        QIcon ButtonIcon(pixmap);
        pushButton_11->setIcon(ButtonIcon);
        pushButton_11->setIconSize(QSize(80, 80));
        //*/
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/power-button-icon-8344.png"), QSize(), QIcon::Normal, QIcon::On);
        stackedWidget->addWidget(page);

        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(offset_array2_pb_x, offset_array2_pb_y, size_x_pb, size_y_pb));
        QPixmap pixmap1("music-note-icon-34253.png");
        QIcon ButtonIcon1(pixmap1);
        pushButton_5->setIcon(ButtonIcon1);
        pushButton_5->setIconSize(QSize(50, 50));

        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, offset_array2_pb_y, size_x_pb, size_y_pb));
        QPixmap pixmap2("settings-icon-14949.png");
        QIcon ButtonIcon2(pixmap2);
        pushButton_2->setIcon(ButtonIcon2);
        pushButton_2->setIconSize(QSize(50, 50));

        pushButton = new QPushButton(page_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, size_x_pb, size_y_pb));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8(""));
        QPixmap pixmap3("house-top-icon-17749.png");
        QIcon ButtonIcon3(pixmap3);
        pushButton->setIcon(ButtonIcon3);
        pushButton->setIconSize(QSize(50, 50));



        pushButton_6 = new QPushButton(page_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(offset_array2_pb_x, 0, size_x_pb, size_y_pb));
        QPixmap pixmap4("video-icon-8027.png");
        QIcon ButtonIcon4(pixmap4);
        pushButton_6->setIcon(ButtonIcon4);
        pushButton_6->setIconSize(QSize(50, 50));


        pushButton_8 = new QPushButton(page_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(0, offset_array3_pb_y, size_x_pb, size_y_pb));
        QPixmap pixmap5("PngItem_1452866.png");
        QIcon ButtonIcon5(pixmap5);
        pushButton_8->setIcon(ButtonIcon5);
        pushButton_8->setIconSize(QSize(50, 50));

        findButton = new QPushButton(page_2);
        findButton->setObjectName(QString::fromUtf8("findButton"));
        findButton->setGeometry(QRect(offset_array2_pb_x, offset_array3_pb_y, size_x_pb, size_y_pb));
        QPixmap pixmap6("folder2.png");
        QIcon ButtonIcon6(pixmap6);
        findButton->setIcon(ButtonIcon6);
        findButton->setIconSize(QSize(50, 50));

        ///*
        gridLayoutWidget = new QWidget(page_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(offset_gl_x, 0, size_x_gl, size_y_gl));
        gridLayoutWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        mainLayout = new QGridLayout(gridLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);



        filesFoundLabel = new QLabel(page_2);
        filesFoundLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));



        mainLayout->addWidget(filesFoundLabel, 1, 0, 1, 2);

        mainLayout->addWidget(filesTable, 0, 0, 1, 3);



        stackedWidget->addWidget(page_2);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        layoutWidget = new QWidget(page_9);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(270, 320, 582, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        hSliderVideo_2 = new QSlider(layoutWidget);
        hSliderVideo_2->setObjectName(QString::fromUtf8("hSliderVideo_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hSliderVideo_2->sizePolicy().hasHeightForWidth());
        hSliderVideo_2->setSizePolicy(sizePolicy);
        hSliderVideo_2->setAutoFillBackground(false);
        hSliderVideo_2->setInputMethodHints(Qt::ImhNone);
        hSliderVideo_2->setOrientation(Qt::Horizontal);
        hSliderVideo_2->setInvertedAppearance(false);
        hSliderVideo_2->setInvertedControls(false);
        hSliderVideo_2->setTickPosition(QSlider::NoTicks);

        horizontalLayout_4->addWidget(hSliderVideo_2);

        endTime_2 = new QLabel(layoutWidget);
        endTime_2->setObjectName(QString::fromUtf8("endTime_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(endTime_2->sizePolicy().hasHeightForWidth());
        endTime_2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(endTime_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_4);

        LblNowPlaying_2 = new QLabel(layoutWidget);
        LblNowPlaying_2->setObjectName(QString::fromUtf8("LblNowPlaying_2"));

        horizontalLayout_5->addWidget(LblNowPlaying_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));


        BtnPause_2 = new QPushButton(layoutWidget);
        BtnPause_2->setObjectName(QString::fromUtf8("BtnPause_2"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        BtnPause_2->setFont(font2);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnPause_2->setIcon(icon7);
        BtnPause_2->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(BtnPause_2, 0, 1, 1, 1);

        comboBox_2 = new QComboBox(layoutWidget);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/ui_icons/fastforward.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_2->addItem(icon8, QString());
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/ui_icons/speedup.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_2->addItem(icon9, QString());
        comboBox_2->addItem(icon9, QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy3);
        comboBox_2->setFont(font2);
        comboBox_2->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(comboBox_2, 0, 4, 1, 1);

        directory_2 = new QPushButton(layoutWidget);
        directory_2->setObjectName(QString::fromUtf8("directory_2"));
        directory_2->setFont(font2);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/ui_icons/Add File.png"), QSize(), QIcon::Normal, QIcon::Off);
        directory_2->setIcon(icon10);
        directory_2->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(directory_2, 0, 5, 1, 1);

        BtnPlay_2 = new QPushButton(layoutWidget);
        BtnPlay_2->setObjectName(QString::fromUtf8("BtnPlay_2"));
        BtnPlay_2->setFont(font2);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnPlay_2->setIcon(icon11);
        BtnPlay_2->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(BtnPlay_2, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        groupBox_2 = new QGroupBox(page_9);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(290, -30, 501, 421));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setMouseTracking(false);
        groupBox_2->setLayoutDirection(Qt::RightToLeft);
        groupBox_2->setAutoFillBackground(false);
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        vSliderSound_2 = new QSlider(groupBox_2);
        vSliderSound_2->setObjectName(QString::fromUtf8("vSliderSound_2"));
        vSliderSound_2->setGeometry(QRect(60, 319, 421, 41));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(vSliderSound_2->sizePolicy().hasHeightForWidth());
        vSliderSound_2->setSizePolicy(sizePolicy4);
        vSliderSound_2->setOrientation(Qt::Horizontal);



        stackedWidget->addWidget(page_9);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mirafra Music Player", nullptr));
        //pushButton_11->setText(QString());
        pushButton_5->setText(QString());
        pushButton_2->setText(QString());
        pushButton->setText(QString());
        pushButton_6->setText(QString());
        pushButton_8->setText(QString());
        findButton->setText(QString());

    } // retranslateUi

};

#endif // UI_MAINWINDOW_H
