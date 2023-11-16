#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogramacolor.h"
#include "histogramagrayscale.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Incarca imaginea de fundal
void MainWindow::on_btn_loadImage_clicked()
{
    path = QFileDialog::getOpenFileName(this, "Selectați o imagine", QDir::homePath(), "Imagini (*.png *.jpg *.jpeg)");

        if (!path.isEmpty()) {
            background = imread(path.toStdString());
            cv::resize(background, background, Size(backgroundWidth, backgroundHeight));

            QString tempImagePath = "background.jpg";
            imwrite(tempImagePath.toStdString(), background);

            // histogramaColor hColor;
            histogramaGrayscale hGrayscale;
            histogram = hGrayscale.getHistogramImage(background);
            QString tempHistogramPath = "histogram.jpg";
            imwrite(tempHistogramPath.toStdString(), histogram);

            threshold(background, thresholded, thresholdValue, 255, thresholdType);
            QString tempThresholdPath = "threshold.jpg";
            imwrite(tempThresholdPath.toStdString(), thresholded);

            QString labelThresholdValue = "Valoare threshold: " + QString::number(thresholdValue);

            ui->frame_background->setStyleSheet("background-image: url(" + tempImagePath + ");");
            ui->frame_histogram->setStyleSheet("background-image: url(" + tempHistogramPath + ");");
            ui->frame_threshold->setStyleSheet("background-image: url(" + tempThresholdPath + ");");
            ui->label_thresholdValue->setText(labelThresholdValue);
    }
}

// Alege culoarea de background
void MainWindow::on_btn_changeBackgroundColor_clicked()
{
    if(!path.isEmpty()){
        Mat modifiedBackground = background.clone();
        QColor newColor = QColorDialog::getColor(QColor(color[0], color[1], color[2]), this);
        if (newColor.isValid()) {
            color = Scalar(newColor.blue(), newColor.green(), newColor.red());
        }
        QString tempImagePath = "modified_background.jpg";
        imwrite(tempImagePath.toStdString(), modifiedBackground);

        ui->frame_background->setStyleSheet("background-image: url(" + tempImagePath + ");");
        QString cssColor = QString("background-color: rgb(%1, %2, %3);").arg(color[2]).arg(color[1]).arg(color[0]);
        ui->frame_chosenBackgroundColor->setStyleSheet(cssColor);
    }
}

// valoare threshold
void MainWindow::on_slider_threshold_valueChanged(int value)
{
    if (!path.isEmpty()) {
        thresholdValue = value;
        QString labelThresholdValue = "Valoare threshold: " + QString::number(thresholdValue);

        Mat tempBackground = background.clone(); // Faceți o copie a imaginii de fundal

        Mat thresholded;
        threshold(tempBackground, thresholded, thresholdValue, 255, thresholdType);
        QString tempThresholdPath = "threshold.jpg";
        imwrite(tempThresholdPath.toStdString(), thresholded);

        Mat mask = thresholded.clone();
        Mat coloredBackground(tempBackground.size(), tempBackground.type(), color);

        bitwise_and(coloredBackground, mask, coloredBackground);
        bitwise_not(mask, mask);
        bitwise_and(tempBackground, mask, tempBackground);
        add(tempBackground, coloredBackground, tempBackground);

        imwrite("C:/Users/Cristi/Desktop/rezultat.jpg", tempBackground);

        ui->frame_background->setStyleSheet("background-image: url(C:/Users/Cristi/Desktop/rezultat.jpg);");
        ui->frame_threshold->setStyleSheet("background-image: url(" + tempThresholdPath + ");");
        ui->label_thresholdValue->setText(labelThresholdValue);
    }
}

// Tipul de threshold
void MainWindow::on_comboBox_chosenThreshold_activated(int index)
{
    switch(index){
    // THRESH_BINARY
    case 0:
        thresholdType = THRESH_BINARY;
        threshold(background, thresholded, thresholdValue, 255, thresholdType);
        break;
    // THRESH_BINARY_INV
    case 1:
        thresholdType = THRESH_BINARY_INV;
        threshold(background, thresholded, thresholdValue, 255, thresholdType);
        break;
    // THRESH_TRUNC
    case 2:
        thresholdType = THRESH_TRUNC;
        threshold(background, thresholded, thresholdValue, 255, thresholdType);
        break;
    // THRESH_TOZERO
    case 3:
        thresholdType = THRESH_TOZERO;
        threshold(background, thresholded, thresholdValue, 255, thresholdType);
        break;
    // THRESH_TOZERO_INV
    case 4:
        thresholdType = THRESH_TOZERO_INV;
        threshold(background, thresholded, thresholdValue, 255, thresholdType);
        break;
    }
}

