#include "mainwindow.h"
#include <QtWidgets>
#include "player.h"
#include <string.h>
#include <QFileDialog>
#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <libudev.h>
#include <QProcess>
#include <QtConcurrent>
#include <QtConcurrent/QtConcurrent>
#include <qtconcurrentrun.h>
#include <QThread>

using namespace std;


#define SUBSYSTEM "block"

#if 1




void MainWindow::print_device(struct udev_device* dev)
{
    const char* action = (char *)malloc(sizeof(char)*10);

    action = udev_device_get_action(dev);
    if (! action)
        action = "exists";

    const char* vendor = (char *)malloc(sizeof(char)*10);
    vendor = udev_device_get_sysattr_value(dev, "idVendor");
    if (! vendor)
        vendor = "0000";

    const char* product = (char *)malloc(sizeof(char)*10);
    product = udev_device_get_sysattr_value(dev, "idProduct");
    if (! product)
        product = "0000";

    /*
    printf("%s %s %6s %s:%s %s\n",
           udev_device_get_subsystem(dev),
           udev_device_get_devtype(dev),
           action,
           vendor,
           product,
           udev_device_get_devnode(dev));
    //*/

    char *concat = (char *)malloc(sizeof(char) * 100);
    strcpy(concat,udev_device_get_subsystem(dev));
    strcat(concat," ");
    strcat(concat,udev_device_get_devtype(dev));
    strcat(concat," ");
    strcat(concat,action);
    strcat(concat," ");
    strcat(concat,vendor);
    strcat(concat," ");
    strcat(concat,product);
    strcat(concat," ");
    strcat(concat,udev_device_get_devnode(dev));
    strcat(concat,"\n");
    //printf("device = %s",concat);

    char *sub_str = (char *)malloc(sizeof(char)*20);
    strcpy(sub_str,"/dev/sd");


    if(((strstr(concat,sub_str) != NULL) && (strstr(concat,"disk") != NULL)) && ( strstr(action,"exists") != NULL ||  strstr(concat,"add") != NULL || strstr(concat,"change") != NULL))
    {
        //printf("device mass storage found\n");
        ui->stackedWidget->setCurrentIndex(1);
    }
    if((strstr(concat,"remove") != NULL) && (strstr(concat,"disk") != NULL))
    {
        printf("Mass storage device REMOVED\n");
        ui->stackedWidget->setCurrentIndex(0);
    }








}

void MainWindow:: process_device(struct udev_device* dev)
{
    if (dev) {
        if (udev_device_get_devnode(dev))
            print_device(dev);

        udev_device_unref(dev);
    }
}

void MainWindow:: enumerate_devices(struct udev* udev)
{
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, SUBSYSTEM);
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry* entry;

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        struct udev_device* dev = udev_device_new_from_syspath(udev, path);
        process_device(dev);
    }

    udev_enumerate_unref(enumerate);
}

void MainWindow:: monitor_devices(struct udev* udev)
{
    struct udev_monitor* mon = udev_monitor_new_from_netlink(udev, "udev");

    udev_monitor_filter_add_match_subsystem_devtype(mon, SUBSYSTEM, NULL);
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);

    while (1) {


        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int ret = select(fd+1, &fds, NULL, NULL, NULL);
        if (ret <= 0)
            break;

        if (FD_ISSET(fd, &fds)) {
            struct udev_device* dev = udev_monitor_receive_device(mon);
            process_device(dev);
        }
    }
}

void MainWindow:: check()
{
    while(1)
    {
        qDebug() << "run thread\n";
        if(player->count2 == 1)
        {
            //ui->stackedWidget->setEnabled(true);
        }
        else
        {
            //ui->stackedWidget->setEnabled(false);
        }
    }

}

#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    auto  rec = QApplication::desktop()->screenGeometry();
    auto  height = rec.height();
    auto  width = rec.width();






    ui->setupUi(this);

    QSize size;
    size = ui->pushButton_2->size();

    int offset_player_x = ((size.rwidth() + 50) / 1082.0) * width;
    int offset_player_y = (109.0 / 420) * height;


    QPoint point;
    point = ui->gridLayoutWidget->pos();
    cout<<"size push button = "<<size.rwidth()<<"coord = "<<point.x()<<"coord2 = "<<point.y()<<"\n";
    //player->move(point.x(),offset_player_y);
    player->move(point.x(),point.x());


    struct udev* udev = udev_new();

    QFuture<void> future = QtConcurrent::run(this,&MainWindow::monitor_devices, udev);
    //QFuture<void> future1 = QtConcurrent::run(this,&MainWindow::check);

    //timer.setInterval(5000);// give it a interval, like 100ms?
    //connect(&timer, SIGNAL(timeout()), this, SLOT(check()));

    //timer.start();


    createFilesTable();

    ui->mainLayout->addWidget(ui->filesTable, 0, 0, 1, 3);

    //connect(ui->findButton, &QAbstractButton::clicked, this, &MainWindow::find);
    connect(ui->findButton, &QAbstractButton::clicked, this, &MainWindow::findall);
    //pushButton_5
    connect(ui->pushButton_5, &QAbstractButton::clicked, this, &MainWindow::find);


    //connect(ui->findVideoButton, &QAbstractButton::clicked, this, &MainWindow::findVideo);

    //pushButton_6
    connect(ui->pushButton_6, &QAbstractButton::clicked, this, &MainWindow::findVideo);


    ui->stackedWidget->setCurrentIndex(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}



//! [17]
enum { absoluteFileNameRole = Qt::UserRole + 1 };
//! [17]

//! [18]
static inline QString fileNameOfItem(const QTableWidgetItem *item)
{
    return item->data(absoluteFileNameRole).toString();
}
//! [18]

//! [14]
void MainWindow::openFile(const QString &fileName)
{

    player->concat_play(fileName);

    player->show();


    /*
    if(player->count2 == 1)
    ui->stackedWidget->setEnabled(true);
    if(player->count2 == 0)
    ui->stackedWidget->setEnabled(false);
    //*/

}


void MainWindow::findall()
{
    ui->filesTable->setRowCount(0);


    QString fileName;// = "*.";


    QString text;// = textComboBox->currentText();

    QString path = "/media/pi/";
    ui->currentDir = QDir(path);
    //! [3]



    //! [4]
    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;

    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFiles(files);
}


//! [3]
void MainWindow::find()
{
    ui->filesTable->setRowCount(0);


    QString fileName = "*.mp3";
    QString fileName2 = "*.wav";

    QString text;// = textComboBox->currentText();

    QString path = "/media/pi/";
    ui->currentDir = QDir(path);
    //! [3]



    //! [4]
    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    if (!fileName2.isEmpty())
        filter << fileName2;

    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFiles(files);
}
//! [4]
//!
void MainWindow::findVideo()
{
    ui->filesTable->setRowCount(0);


    QString fileName = "*.mp4";
    QString fileName2 = "*.webm";
    QString text ;//= textComboBox->currentText();

    QString path = "/media/pi/";

    ui->currentDir = QDir(path);
    //! [3]


    //! [4]
    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    if (!fileName2.isEmpty())
        filter << fileName2;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFiles(files);
}
//! [4]

void MainWindow::animateFindClick()
{
    ui->findButton->animateClick();
}

//! [5]
QStringList MainWindow::findFiles(const QStringList &files, const QString &text)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));

    //! [5] //! [6]
    QMimeDatabase mimeDatabase;
    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %n...", nullptr, files.size()).arg(i));
        QCoreApplication::processEvents();
        //! [6]

        if (progressDialog.wasCanceled())
            break;

        //! [7]
        const QString fileName = files.at(i);
        const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
        if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
            qWarning() << "Not searching binary file " << QDir::toNativeSeparators(fileName);
            continue;
        }
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}
//! [7]

//! [8]
void MainWindow::showFiles(const QStringList &paths)
{
    for (const QString &filePath : paths) {
        const QString toolTip = QDir::toNativeSeparators(filePath);
        const QString absolutePath = QDir::toNativeSeparators(ui->currentDir.absoluteFilePath(filePath));
        QFileInfo info(absolutePath);
        const QString filename = info.fileName();


        const qint64 size = QFileInfo(filePath).size();
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(filename);
        fileNameItem->setData(absoluteFileNameRole, QVariant(absolutePath));
        fileNameItem->setTextColor(QColor(255, 255, 255));
        fileNameItem->setToolTip(toolTip);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        fileNameItem->setFont(font);

        //fileNameItem->setForeground();
        QTableWidgetItem *sizeItem = new QTableWidgetItem(QLocale().formattedDataSize(size));
        sizeItem->setData(absoluteFileNameRole, QVariant(filePath));
        sizeItem->setToolTip(toolTip);
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);
        sizeItem->setTextColor(QColor(255, 255, 255));

        int row = ui->filesTable->rowCount();
        ui->filesTable->insertRow(row);
        ui->filesTable->setItem(row, 0, fileNameItem);
        ui->filesTable->setItem(row, 1, sizeItem);
    }
    ui->filesFoundLabel->setText(tr("%n file(s) found (Double click on a file to open it)", nullptr, paths.size()));
    ui->filesFoundLabel->setWordWrap(true);
}
//! [8]


//! [10]

//! [11]
void MainWindow::createFilesTable()
{
    ui->filesTable = new QTableWidget(0, 2);
    ui->filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename") << tr("Size");
    ui->filesTable->setHorizontalHeaderLabels(labels);
    ui->filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->filesTable->verticalHeader()->hide();
    ui->filesTable->setShowGrid(false);
    //ui->filesTable->setStyleSheet(QString::fromUtf8("foreground-color: rgb(255, 255, 255);"));
    //ui->filesTable->setStyleSheet("selection-background-color:rgb(128, 128, 128); ");
    ui->filesTable->setStyleSheet("QHeaderView::section { background-color:rgb(255, 255, 255);font-weight:1300; }");
    //ui->filesTable->setStyleSheet("selection-background-color:rgb(128, 128, 128); ");

    //ui->filesTable->setStyleSheet("QTreeView::item:selected{background-color: palette(highlight); color:rgb(128, 128, 128): palette(highlightedText);};");

    //! [15]
    ui->filesTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->filesTable, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::contextMenu);
    connect(ui->filesTable, &QTableWidget::cellActivated,
            this, &MainWindow::openFileOfItem);
    //! [15]
}
//! [11]


//! [12]

void MainWindow::openFileOfItem(int row, int /* column */)
{
    const QTableWidgetItem *item = ui->filesTable->item(row, 0);
    openFile(fileNameOfItem(item));
}

//! [12]

//! [16]
void MainWindow::contextMenu(const QPoint &pos)
{
    const QTableWidgetItem *item = ui->filesTable->itemAt(pos);
    if (!item)
        return;
    QMenu menu;
#ifndef QT_NO_CLIPBOARD
    QAction *copyAction = menu.addAction("Copy Name");
#endif
    QAction *openAction = menu.addAction("Open");
    QAction *action = menu.exec(ui->filesTable->mapToGlobal(pos));
    if (!action)
        return;
    const QString fileName = fileNameOfItem(item);
    if (action == openAction)
        openFile(fileName);
#ifndef QT_NO_CLIPBOARD
    else if (action == copyAction)
        QGuiApplication::clipboard()->setText(QDir::toNativeSeparators(fileName));
#endif
}
//! [16]





void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_pressed()
{


}

void MainWindow::on_pushButton_11_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    findall();
}

void MainWindow::on_pushButton_8_clicked()
{

}

