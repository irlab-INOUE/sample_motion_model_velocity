#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <opencv2/opencv.hpp>
#include "Robot.h"

class Drawer
{
    private:
        int IMG_WIDTH, IMG_HIGHT;           // 描画ウィンドウのサイズ
        int IMG_ORIGIN_X, IMG_ORIGIN_Y;     // 描画ウィンドウの原点
        double csize;                       // 解像度 [m/pixel]

        cv::Mat img;

    public:
        void drawing(Robot &rb);
        Drawer();                                   // デフォルトコンストラクタ
        void show();                                // imgをウィンドウ表示する
        void imgWrite();                            // img をファイルに書き出す

};

Drawer::Drawer()
{
    IMG_WIDTH = 800;
    IMG_HIGHT = 600;
    IMG_ORIGIN_X = IMG_WIDTH / 2;
    IMG_ORIGIN_Y = IMG_HIGHT * (1.0 - 1.0/ 6);
    csize = 0.0125/3;

    img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HIGHT), CV_8UC3, cv::Scalar(182, 182, 182));

    // 座標軸
    cv::line(img, cv::Point(0, IMG_ORIGIN_Y), cv::Point(IMG_WIDTH, IMG_ORIGIN_Y), cv::Scalar(0, 0, 0), 1, cv::LINE_8, 0);
    cv::line(img, cv::Point(IMG_ORIGIN_X, 0), cv::Point(IMG_ORIGIN_X, IMG_HIGHT), cv::Scalar(0, 0, 0), 1, cv::LINE_8, 0);
}

void Drawer::drawing(Robot &rb) 
{
    int ix = rb.getX() / csize + IMG_ORIGIN_X;
    int iy =-rb.getY() / csize + IMG_ORIGIN_Y;

    if (ix >= 0 && ix < IMG_WIDTH && iy >= 0 && iy < IMG_HIGHT) 
        img.at<cv::Vec3b>(iy, ix) = cv::Vec3b(200, 0, 0);
}

void Drawer::show()
{
    cv::imshow("Robot", img);
    cv::waitKey(5);
}

void Drawer::imgWrite()
{
    cv::imwrite("result.png", img);
}

#endif
