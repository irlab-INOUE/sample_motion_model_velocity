#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <opencv2/opencv.hpp>

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
            void drawing(T &a, cv::Vec3b color);// 引数の座標に点を描く
        void show();                            // imgをウィンドウ表示する
        void imgWrite();                        // img をファイルに書き出す

        // 便利な描画関数
        void line(cv::Point p1, cv::Point p2);                  // 2点を結ぶ直線 ピクセル座標系
        void line(double x1, double y1, double x2, double y2);  // 実座標系, 境界処理有り
        void line(double x1, double y1, double angle);          // 通過点と傾きを与えた直線
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
void Drawer::drawing(T &a, cv::Vec3b color)
{
    int ix = a.getX() / csize + IMG_ORIGIN_X;
    int iy =-a.getY() / csize + IMG_ORIGIN_Y;

    if (ix >= 0 && ix < IMG_WIDTH && iy >= 0 && iy < IMG_HIGHT) 
        img.at<cv::Vec3b>(iy, ix) = color;
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

// 2点を結ぶ直線
void Drawer::line(cv::Point p1, cv::Point p2)
{
    cv::line(img, p1, p2, cv::Scalar(150, 0, 0), 1, cv::LINE_8, 0);
}

void Drawer::line(double x1, double y1, double x2, double y2)
{
    // アスキー出版局 入門グラフィックス に詳解がある
    // window境界を実座標に変換する
    double cx1 = csize * (          - IMG_ORIGIN_X);
    double cx2 = csize * (IMG_WIDTH - IMG_ORIGIN_X);
    double cy1 =-csize * (IMG_HIGHT - IMG_ORIGIN_Y);
    double cy2 =-csize * (          - IMG_ORIGIN_Y);

    // 平行・垂直の場合の処理
    if (x1 == x2) {
        if (y1 < cy1) y1 = cy1;
        else if (y1 > cy2) y1 = cy2;

        if (y2 < cy1) y2 = cy1;
        else if (y2 > cy2) y2 = cy2;
    } else if (y1 == y2) {
        if (x1 < cx1) x1 = cx1;
        else if (x1 > cx2) x1 = cx2;

        if (x2 < cx1) x2 = cx1;
        else if (x2 > cx2) x2 = cx2;
    }
        
    while (1) {
        char c1 = 0b0000;
        char c2 = 0b0000;
        if (y1 > cy2) c1 |= 0b1000;
        if (y1 < cy1) c1 |= 0b0100;
        if (x1 > cx2) c1 |= 0b0010;
        if (x1 < cx1) c1 |= 0b0001;

        if (y2 > cy2) c2 |= 0b1000;
        if (y2 < cy1) c2 |= 0b0100;
        if (x2 > cx2) c2 |= 0b0010;
        if (x2 < cx1) c2 |= 0b0001;

        if (c1 == 0b0000 && c2 == 0b0000) {
            int px1 = x1 / csize + IMG_ORIGIN_X;
            int py1 =-y1 / csize + IMG_ORIGIN_Y;
            int px2 = x2 / csize + IMG_ORIGIN_X;
            int py2 =-y2 / csize + IMG_ORIGIN_Y;
            line(cv::Point(px1, py1), cv::Point(px2, py2));
            break;
        } 

        char c;
        if (c1 == 0b0000) c = c2;
        else              c = c1;

        double x, y;
        if ((c & 0b0001) != 0) {
            // 左端
            y = y1 + (y2 - y1) / (x2 - x1) * (cx1 - x1);
            x = cx1;
        } else if ((c & 0b0010) != 0) {
            // 右端
            y = y1 + (y2 - y1) / (x2 - x1) * (cx2 - x1);
            x = cx2;
        } else if ((c & 0b0100) != 0) {
            // 下端
            x = x1 + (x2 - x1) / (y2 - y1) * (cy1 - y1);
            y = cy1;
        } else if ((c & 0b1000) != 0) {
            // 上端
            x = x1 + (x2 - x1) / (y2 - y1) * (cy2 - y1);
            y = cy2;
        }
        if (c == c1) {
            x1 = x; y1 = y;
        } else {
            x2 = x; y2 = y;
        }
    }
}

// 通過点と傾きを与えられた直線
void Drawer::line(double x, double y, double angle)
{
    // 与えられたパラメータにより描かれる直線とウィンドウとの交点を算出する
    // 今の場合，端点座標は不明なので，可能な最大最小の座標を仮定する
    double x1 = x + 99999.0 * cos(angle);
    double y1 = y + 99999.0 * sin(angle);
    double x2 = x - 99999.0 * cos(angle);
    double y2 = y - 99999.0 * sin(angle);
    std::cerr << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    line(x1, y1, x2, y2);  
}
#endif
