/**
 * @file Drawer.h
 * @brief 実座標系での画像描画クラス
 * @author Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 */

#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <opencv2/opencv.hpp>

class Drawer
{
    private:
        int IMG_WIDTH;      //!< 描画ウィンドウの幅
        int IMG_HIGHT;      //!< 描画ウィンドウの高さ
        int IMG_ORIGIN_X;   //!< 描画ウィンドウの原点X座標
        int IMG_ORIGIN_Y;   //!< 描画ウィンドウの原点Y座標
        double csize;       //!< 解像度 [m/pixel]

        cv::Scalar XaxisColor;      //!< X軸の色
        cv::Scalar YaxisColor;      //!< Y軸の色
        cv::Scalar point_color;     //!< 点を描画するときの現在の設定色
        cv::Scalar line_color;      //!< 線を描画するときの現在の設定色

        int line_width;             //!< 描画する線の太さ

        cv::Mat img;        //!< キャンバス
        cv::Mat img_init;   //!< 初期化用のキャンバスのコピー

    public:
        /**
         * @brief デフォルトコンストラクタ
         *
         * 初期設定の画像および原点を設定する
         */
        Drawer();                                   

        /**
         * @fn void reset()
         * @brief 設定値および画像をリセットする．ただし，画像サイズは現時点のものを引き継ぐ
         * @details 
         */
        void reset();                               

        /**
         * @fn <typename T> void drawing(T &a)
         * @brief img上の引数の座標に点を打つ
         * @param T &a
         * @details 引数で与えるのは任意のクラスのインスタンス．それは x, y の値を得るメソッド getX(), getY() を持っている．
         */
        template <typename T> void drawing(T &a);   

        /**
         * @fn void show(int)
         * @brief imgを表示し，指定時間だけ待つ
         * @param wait 表示後の待機時間[ms]
         * @details 
         */
        void show(int wait = 5);                    

        /**
         * @brief img をファイルに書き出す
         * @details ファイル名は`result.png`になる
         */
        void imgWrite();                            

        /**
         * @brief img を最初の状態に戻す
         * @details img_initをimgにクローンする．imgHold()と組み合わせて使うと良い
         */
        void clear();                              

        /**
         * @brief 現在のimgを初期化用に登録する
         * @details img_initに現在のimgを保存する
         */
        void imgHold();                             

        // 描画するための補助機能
        /**
         * @brief 解像度を設定する
         * @param val [m/pixel]
         */
        void setCsize(double val);                  

        /**
         * @brief 描画領域の幅[m]を設定する
         * @param val [m]
         */
        void setImgWidth(double val);               

        /**
         * @brief 描画領域の高さ[m]を設定する
         * @param val [m]
         */
        void setImgHight(double val);               

        /**
         * @brief 画面左から原点までのX方向の距離[m]
         * @param val [m]
         */
        void setOriginXfromLeft(double val);        

        /**
         * @brief 画面下から原点までのY方向の距離[m]
         * @param val [m]
         */
        void setOriginYfromBottom(double val);      

        /**
         * @brief 点を描画するための色をセットする
         * @param cv::Scalar c (B, G, R の順に指定する)
         */
        void setPointColor(cv::Scalar c);           

        /**
         * @brief 線を描画するための色をセットする
         * @param cv::Scalar c (B, G, R の順に指定する)
         */
        void setLineColor(cv::Scalar c);            

        /**
         * @brief 線を描画するための線の太さをセットする
         * @param w [pixel]
         */
        void setLineWidth(int w);                   

        // 便利な描画関数
        /**
         * @brief 2点を結ぶ直線を描画する
         * @param p1   img画像上の点1
         * @param p2   img画像上の点2
         * @details 線の太さや色は別に設定されたものを用いる
         */
        void line(cv::Point p1, cv::Point p2);                          

        /**
         * @brief 2点を結ぶ直線を描画する
         * @param x1, y1 [m] 実座標系の点1
         * @param x2, y2 [m] 実座標系の点2
         * @details 線の太さや色は別に設定されたものを用いる．境界ではみ出し検出処理が付く
         */
        void line(double x1, double y1, double x2, double y2);          

        /**
         * @brief 通過点と傾きを指定した無限に長い直線
         * @param x1, y1 [m] 実座標系の通過点
         * @param angle [rad]
         * @details 線の太さや色は別に設定されたものを用いる．境界ではみ出し検出処理が付く
         */
        void line(double x1, double y1, double angle);                  

        void lineRA(double x1, double y1, double r, double angle);      // 通過点と方向と長さを与えられた直線
        void lineRA2(double x1, double y1, double r, double angle);     // 通過点と方向と長さを与えられた両側に伸びる線分

        void dots(cv::Point p1, cv::Point p2);                          // 点線
        void dots(double x1, double y1, double x2, double y2);          // 実座標系, 境界処理有り
        void dots(double x1, double y1, double angle);                  // 通過点と傾きを与えた直線
        void dotsRA(double x1, double y1, double r, double angle);      // 通過点と方向と長さを与えられた直線
        void dotsRA2(double x1, double y1, double r, double angle);     // 通過点と方向と長さを与えられた両側に伸びる線分

        void circle(cv::Point p, int radius, bool fill = true);                 // 円を描画 ピクセル座標系
        void circle(double x1, double y1, double radius, bool fill = true);     // 円を描画 実座標系
        void circle(double x, double y, double radius,
                double startAngle, double endAngle, bool fill = true);          // 円を描画 円弧

        void robot(double x1, double y1, double r, double angle);       // 円形のロボット 

        void text(double x, double y, std::string text);                // 指定位置にテキストを描画
        void includeImage(double x, double y, std::string path);        // 指定位置に画像を描画
		void overText(double x, double y, std::string path);
};

// デフォルトコンストラクタ
Drawer::Drawer()
{
    IMG_WIDTH = 600;                    // 画像幅のピクセル数
    IMG_HIGHT = 600;                    // 画像高さのピクセル数
    IMG_ORIGIN_X = IMG_WIDTH / 2;       // 画像原点は幅の中央
    IMG_ORIGIN_Y = IMG_HIGHT * (1.0 - 1.0/ 6);  // 画像原点は下の1/6
    csize = 0.005;                      // 画像解像度[m/pixel]

    img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HIGHT), CV_8UC3, cv::Scalar(182, 182, 182));

    // 描画する色のデフォルト値
    point_color = cv::Scalar(0, 0, 0);
    line_color = cv::Scalar(200, 0, 0);

    // 描画する線幅のデフォルト値
    line_width = 1;

    // 座標軸
    XaxisColor = cv::Scalar(0, 0, 0);
    YaxisColor = cv::Scalar(0, 0, 0);

    cv::line(img, cv::Point(0, IMG_ORIGIN_Y), cv::Point(IMG_WIDTH, IMG_ORIGIN_Y), XaxisColor, 1, cv::LINE_AA, 0);
    cv::line(img, cv::Point(IMG_ORIGIN_X, 0), cv::Point(IMG_ORIGIN_X, IMG_HIGHT), YaxisColor, 1, cv::LINE_AA, 0);

    // clear 用にコピーを残す
    img_init = img.clone();
}

void Drawer::reset()
{
    img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HIGHT), CV_8UC3, cv::Scalar(182, 182, 182));

    // 描画する色のデフォルト値
    point_color = cv::Scalar(0, 0, 0);
    line_color = cv::Scalar(200, 0, 0);

    // 描画する線幅のデフォルト値
    line_width = 1;

    // 座標軸
    XaxisColor = cv::Scalar(0, 0, 0);
    YaxisColor = cv::Scalar(0, 0, 0);

    cv::line(img, cv::Point(0, IMG_ORIGIN_Y), cv::Point(IMG_WIDTH, IMG_ORIGIN_Y), XaxisColor, 1, cv::LINE_AA, 0);
    cv::line(img, cv::Point(IMG_ORIGIN_X, 0), cv::Point(IMG_ORIGIN_X, IMG_HIGHT), YaxisColor, 1, cv::LINE_AA, 0);

    // clear 用にコピーを残す
    img_init = img.clone();
}

template <typename T>
void Drawer::drawing(T &a)
{
    int ix = a.getX() / csize + IMG_ORIGIN_X;
    int iy =-a.getY() / csize + IMG_ORIGIN_Y;

    if (ix >= 0 && ix < IMG_WIDTH && iy >= 0 && iy < IMG_HIGHT) {
        cv::Vec3b cl;
        cl[0] = point_color[0];
        cl[1] = point_color[1];
        cl[2] = point_color[2];
        img.at<cv::Vec3b>(iy, ix) = cl;
    }
}

// 解像度を設定する
void Drawer::setCsize(double val)
{
    csize = val;
    reset();
}

// 描画領域の幅[m]を設定する
void Drawer::setImgWidth(double val)
{
    IMG_WIDTH = val/csize;
    reset();
}

// 描画領域の高さ[m]を設定する
void Drawer::setImgHight(double val)
{
    IMG_HIGHT = val/csize;
    reset();
}

// 画面左から原点までのX方向の距離[m]
void Drawer::setOriginXfromLeft(double val)        
{
    IMG_ORIGIN_X = val/csize;
    reset();
}

// 画面下から原点までのY方向の距離[m]
void Drawer::setOriginYfromBottom(double val)
{
    IMG_ORIGIN_Y = IMG_HIGHT - val/csize;
    reset();
}

// 点を描画するための色をセットする
void Drawer::setPointColor(cv::Scalar c)
{
    point_color = c;
}

// 描画するための色をセットする
void Drawer::setLineColor(cv::Scalar c)
{
    line_color = c;
}

// 描画するための線の太さをセットする
void Drawer::setLineWidth(int w)
{
    line_width = w;
}

// 描画する
void Drawer::show(int wait)
{
    cv::imshow("IRLab.", img);
    cv::waitKey(wait);
}

// ファイルに保存する
void Drawer::imgWrite()
{
    cv::imwrite("result.png", img);
}

void Drawer::clear()
{
    img = img_init.clone();
}

void Drawer::imgHold()
{
    img_init = img.clone();
}

// 2点を結ぶ直線
void Drawer::line(cv::Point p1, cv::Point p2)
{
    cv::line(img, p1, p2, line_color, line_width, cv::LINE_AA, 0);
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
        if ((c & 0b0001) != 0b0000) {
            // 左端
            y = y1 + (y2 - y1) / (x2 - x1) * (cx1 - x1);
            x = cx1;
        } else if ((c & 0b0010) != 0b0000) {
            // 右端
            y = y1 + (y2 - y1) / (x2 - x1) * (cx2 - x1);
            x = cx2;
        } else if ((c & 0b0100) != 0b0000) {
            // 下端
            x = x1 + (x2 - x1) / (y2 - y1) * (cy1 - y1);
            y = cy1;
        } else if ((c & 0b1000) != 0b0000) {
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

// 通過点と方向と長さを与えられた直線
void Drawer::lineRA(double x1, double y1, double r, double angle)
{
    double x2 = x1 + r * cos(angle);
    double y2 = y1 + r * sin(angle);
    line(x1, y1, x2, y2);
}

// 通過点と方向と長さを与えられた両側に伸びる線分
void Drawer::lineRA2(double x1, double y1, double r, double angle)
{
    lineRA(x1, y1, r, angle);
    lineRA(x1, y1, r, angle + M_PI);
}

// 円を描画 ピクセル座標系
void Drawer::circle(cv::Point p, int radius, bool fill)
{
    if (fill)
        cv::circle(img, p, radius, line_color, -1, cv::LINE_AA, 0);
    else 
        cv::circle(img, p, radius, line_color, line_width, cv::LINE_AA, 0);
}

void Drawer::circle(double x1, double y1, double radius, bool fill)
{
    int px = x1/csize + IMG_ORIGIN_X;
    int py =-y1/csize + IMG_ORIGIN_Y;
    if (fill)
        cv::circle(img, cv::Point(px, py), radius/csize, line_color, -1, cv::LINE_AA, 0);
    else 
        cv::circle(img, cv::Point(px, py), radius/csize, line_color, line_width, cv::LINE_AA, 0);
}

void Drawer::circle(double x, double y, double radius, double startAngle, double endAngle, bool fill)
{
    int px = x/csize + IMG_ORIGIN_X;
    int py =-y/csize + IMG_ORIGIN_Y;
    cv::ellipse(img,
            cv::Point(px, py), 
            cv::Size(radius/csize, radius/csize), 0.0, startAngle, endAngle, line_color, line_width, cv::LINE_AA,0);
}

// 円形のロボット 
void Drawer::robot(double x1, double y1, double r, double angle)
{
    int line_width_backup = line_width;
    line_width = 2;
    circle(x1, y1, r, false);
    lineRA(x1, y1, r, angle);

    double x = r * cos(angle);
    double y = r * sin(angle);

    double xr_ = x * cos(-M_PI/2) - y * sin(-M_PI/2);
    double yr_ = x * sin(-M_PI/2) + y * cos(-M_PI/2);

    double xl_ = x * cos( M_PI/2) - y * sin( M_PI/2);
    double yl_ = x * sin( M_PI/2) + y * cos( M_PI/2);

    line_width = 10;
    lineRA2(x1 + xr_, y1 + yr_, 0.2, angle);
    lineRA2(x1 + xl_, y1 + yl_, 0.2, angle);
}

void Drawer::text(double x, double y, std::string text)
{
    int px = x/csize + IMG_ORIGIN_X;
    int py =-y/csize + IMG_ORIGIN_Y;
    cv::putText(img, text, cv::Point(px, py), cv::FONT_HERSHEY_SIMPLEX, 1.0, line_color, 1, cv::LINE_AA, false);
}

// 指定位置に画像を描画
void Drawer::includeImage(double x, double y, std::string path)
{
	int px = x/csize + IMG_ORIGIN_X;
	int py =-y/csize + IMG_ORIGIN_Y;

	cv::Mat img2 = cv::imread(path);
	px = (px < 0) ? 0 : px;
	py = (py < 0) ? 0 : py;
	px = (px > IMG_WIDTH - img2.cols) ? IMG_WIDTH - img2.cols : px;
	py = (py > IMG_HIGHT - img2.rows) ? IMG_HIGHT - img2.rows : py;

	cv::Mat roi = img(cv::Rect(px, py, img2.cols, img2.rows));

	img2.copyTo(roi);
}

void Drawer::overText(double x, double y, std::string path)
{
	int px = x/csize + IMG_ORIGIN_X;
	int py =-y/csize + IMG_ORIGIN_Y;

	cv::Mat img2 = cv::imread(path, cv::IMREAD_UNCHANGED);
	cv::cvtColor(img2, img2, cv::COLOR_RGB2RGBA);

	for (int i = 0; i < img2.rows; i++) {
		for (int j = 0; j < img2.cols; j++) {
			if (img2.at<cv::Vec4b>(i,j)[3] != 0) {
				img.at<cv::Vec3b>(i + py, j + px)[0] = img2.at<cv::Vec4b>(i, j)[0];
				img.at<cv::Vec3b>(i + py, j + px)[1] = img2.at<cv::Vec4b>(i, j)[1];
				img.at<cv::Vec3b>(i + py, j + px)[2] = img2.at<cv::Vec4b>(i, j)[2];
			}
		}
	}
}

#endif
