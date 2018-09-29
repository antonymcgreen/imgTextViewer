#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void loadPic();
    void setSize(int w, int h);

    void on_openFolder_clicked();

    void on_next_clicked();

    void on_prev_clicked();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    QString folder;
    QStringList imgs;
    int currentImg;
};

#endif // MAINWINDOW_H
