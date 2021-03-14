#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv\highgui.h>

std::string AddNull(int i){
        if (i < 10)
            return "000000";
        if (i > 9 && i < 100)
            return "00000";
        if (i > 99 && i < 1000)
            return "0000";
        if (i > 999 && i < 10000)
            return "000";
        if (i > 9999 && i < 100000)
            return "00";
}

int main() {
    //cv::VideoWriter writer;

    //std::string filename = "F:\\thev.avi";
    //int fcc = CV_FOURCC('M', 'J', 'P', 'G');
    //double fps = 60;
    //cv::Size frameSize(512, 512);
    //writer = cv::VideoWriter(filename, fcc, fps, frameSize);
    //writer.write(frame);
  
    int reb, k = 0;
    cv::Mat Fimage;

    for (int i = 0; i < 9999; i++) {
        std::string d;
        if (i < 10)
            d = "000000";
        if (i > 9 && i < 100)
            d = "00000";
        if (i > 99 && i < 1000)
            d = "0000";
        if (i > 999 && i < 10000)
            d = "000";
        if (i > 9999 && i < 100000)
            d = "00";

        Fimage = cv::imread("F:\\Foton\\!programdata\\вфеф\\images\\1\\"+ d + std::to_string(i) + ".png");
        reb = MIN(Fimage.rows, Fimage.cols);
        cv::Mat frame(Fimage, cv::Rect(0, 0, reb, reb));
        cv::resize(frame, frame, cv::Size(512, 512));
        if (Fimage.data)
            cv::imwrite("F:\\Foton\\!programdata\\вфеф\\images\\2\\" + std::to_string(i - k) + ".png", Fimage);
        else
            k++;
    }
    return 0;
}
