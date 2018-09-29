#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <qDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPic()
{
    QString path=this->folder+"/"+this->imgs.at(this->currentImg);
    QPixmap myPixmap(path);
    setSize(myPixmap.width(),myPixmap.height());
    ui->pic->setPixmap(myPixmap);

    QFile file(path+":text.txt");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString content=file.readAll().replace("\n"," ");
        ui->text->setText(content);
        ui->text->setToolTip(content);
        file.close();
    }
}

void MainWindow::setSize(int w, int h)
{
    int width;
    int height;
    if(w>h && ((float)w/h>(float)800/570))
    {
        width=800;
        height=(int)(800*(float)h/w);
    }
    else
    {
        height=570;
        width=(int)(570*(float)w/h);
    }
    ui->pic->setGeometry(410-(int)width/2,285-(int)height/2,width,height);
}


void MainWindow::on_openFolder_clicked()
{
    this->folder=QFileDialog::getExistingDirectory(this,"Выберите папку","c:/111/pictures",QFileDialog::ShowDirsOnly);
    this->setWindowTitle(this->folder);

    QDir dir;
    dir.setPath(this->folder);
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        if(!(list.at(i).fileName()==".." || list.at(i).fileName()=="."))
        this->imgs.append(list.at(i).fileName());
    }
    this->currentImg=0;
    if(this->imgs.length()>0)
    {
        loadPic();
    }
}

void MainWindow::on_next_clicked()
{
    this->currentImg=++this->currentImg%this->imgs.length();
    loadPic();
}

void MainWindow::on_prev_clicked()
{
    this->currentImg=(--this->currentImg+this->imgs.length())%this->imgs.length();
    loadPic();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_O) on_openFolder_clicked();
    if(event->key()==Qt::Key_Left) on_prev_clicked();
    if(event->key()==Qt::Key_Right) on_next_clicked();

}
