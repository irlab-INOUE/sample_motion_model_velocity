#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <opencv2/opencv.hpp>

struct RGB
{
    int R;
    int G;
    int B;
};

class Drawer
{
    private:
        int IMG_WIDTH, IMG_HIGHT;           // 描画ウィンドウのサイズ
        int IMG_ORIGIN_X, IMG_ORIGIN_Y;     // 描画ウィンドウの原点
        double csize;                       // 解像度 [m/pixel]

        cv::Scalar XaxisColor;
        cv::Scalar YaxisColor;

        cv::Mat img;

    public:
        Drawer();                               // デフォルトコンストラクタ
        template <typename T> 
            void drawing(T &a, RGB color);      // 引数の座標に点を描く
        void show();                            // imgをウィンドウ表示する
        void imgWrite();                        // img をファイルに書き出す

        static RGB RGBcolor(int, int, int);     // 外部から色を指定するときに使う
};

// デフォルトコンストラクタ
Drawer::Drawer()
{
    IMG_WIDTH = 600;
    IMG_HIGHT = 600;
    IMG_ORIGIN_X = IMG_WIDTH / 2;
    IMG_ORIGIN_Y = IMG_HIGHT * (1.0 - 1.0/ 6);
    csize = 0.005;

    img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HIGHT), CV_8UC3, cv::Scalar(182, 182, 182));

    // 座標軸
    XaxisColor = cv::Scalar(0, 0, 0);
    YaxisColor = cv::Scalar(0, 0, 0);

    cv::line(img, cv::Point(0, IMG_ORIGIN_Y), cv::Point(IMG_WIDTH, IMG_ORIGIN_Y), XaxisColor, 1, cv::LINE_8, 0);
    cv::line(img, cv::Point(IMG_ORIGIN_X, 0), cv::Point(IMG_ORIGIN_X, IMG_HIGHT), YaxisColor, 1, cv::LINE_8, 0);
}

// 点を描画する
// 点座標と色を指定する
// NOTE1:
//  引数のオブジェクトは何らかのクラスのインスタンスである．
//  それは x, y の値を得るメソッド getX(), getY() を持っている．
// NOTE2:
//  色の指定は自前のRGBcolor()メソッドを通して指定する
template <typename T>
void Drawer::drawing(T &a, RGB color)
{
    int ix = a.getX() / csize + IMG_ORIGIN_X;
    int iy =-a.getY() / csize + IMG_ORIGIN_Y;

    if (ix >= 0 && ix < IMG_WIDTH && iy >= 0 && iy < IMG_HIGHT) 
        img.at<cv::Vec3b>(iy, ix) = cv::Vec3b(color.B, color.G, color.R);
}


// 描画する
void Drawer::show()
{
    cv::imshow("Robot", img);
    cv::waitKey(5);
}

// ファイルに保存する
void Drawer::imgWrite()
{
    cv::imwrite("result.png", img);
}

// 内部処理用に色を指定するための関数
RGB Drawer::RGBcolor(int val1, int val2, int val3)
{
    RGB tmp;
    tmp.R = val1;
    tmp.G = val2;
    tmp.B = val3;

    return tmp;
}
#endif
