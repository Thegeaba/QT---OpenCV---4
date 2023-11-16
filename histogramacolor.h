#ifndef HISTOGRAMACOLOR_H
#define HISTOGRAMACOLOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class histogramaColor{
    private:
        int histSize[3]; // 3 canale - RGB
        float hranges[2]; // min si max - valori pixeli
        const float* ranges[3];
        int channels[3]; // 3 canale - RGB
    public:
        histogramaColor(){

            // Initializare argumente pentru histograma color
            histSize[0] = histSize[1] = histSize[2] = 256;
            hranges[0] = 0.0;
            hranges[1] = 255.0;

            // Canalele au aceleasi intervale
            ranges[0] = hranges;
            ranges[1] = hranges;
            ranges[2] = hranges;

            // Cele 3 canale
            channels[0] = 0;
            channels[1] = 1;
            channels[2] = 2;
        }

        MatND getHistogram(const Mat &image){
            MatND hist;
            calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges);
            return hist;
        }

        SparseMat getSparseHistogram(const Mat &image){
            SparseMat hist(3, histSize, CV_32F);
            calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges);
            return hist;
        }

        Mat getHistogramImage(const Mat &image){
            MatND hist = getHistogram(image);
            double maxVal = 0;
            double minVal = 0;
            minMaxLoc(hist, &minVal, &maxVal, 0, 0);
            Mat histImage(histSize[0], histSize[0], CV_8U, Scalar(255));
            int hpt = static_cast<int>(0.9*histSize[0]);
            for (int h = 0; h < histSize[0]; h++)
            {
                float binVal = hist.at<float>(h);
                int intensity = static_cast<int>(binVal*hpt/maxVal);
                line(histImage, Point(h, histSize[0]), Point(h, histSize[0]-intensity), Scalar::all(0));
            }
            return histImage;
        }

};

#endif // HISTOGRAMACOLOR_H
