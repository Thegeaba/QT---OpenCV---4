#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QtGui>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QColorDialog>

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_loadImage_clicked();

    void on_btn_changeBackgroundColor_clicked();

    void on_slider_threshold_valueChanged(int value);

    void on_comboBox_chosenThreshold_activated(int index);

private:
    Ui::MainWindow *ui;

    Mat background;
    Mat histogram;
    Mat thresholded;
    Mat mask;

    QString path;
    int backgroundWidth = 512;
    int backgroundHeight = 512;
    int sequence = 1;

    // valori default alese de mine :)
    int thresholdValue = 120;
    int thresholdType = 0;
    Scalar color = Scalar(0, 0, 0);

};
#endif // MAINWINDOW_H
