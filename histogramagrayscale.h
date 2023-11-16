#ifndef HISTOGRAMAGRAYSCALE_H
#define HISTOGRAMAGRAYSCALE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class histogramaGrayscale{

    private:
        int histSize[1]; // Numar de pozitii
        float hranges[2]; // min si max - valori pixeli
        const float* ranges[1];
        int channels[1]; // Un singur canal
    public:
        histogramaGrayscale(){
            histSize[0] = 256;
            hranges[0] = 0.0;
            hranges[1] = 255.0;
            ranges[0] = hranges;
            channels[0] = 0;
        }
        MatND getHistogram(const Mat &image){
            MatND hist;
            calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
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

#endif // HISTOGRAMAGRAYSCALE_H
