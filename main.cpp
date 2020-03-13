/*
 * 移動ロボットの動作モデルと誤差@zoom
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 * 2020.3.13
 *
 * 誤差を含む速度動作モデルのシミュレーションです
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

// 乱数初期化
cv::RNG rng(cv::getTickCount());

#if 1
double sample(double b2)
{
    double sum = 0.0;
    double b = sqrt(b2);

    for (int i = 0; i < 12; i++) {
        sum += rng.uniform(-b, b);
    }

    return 0.5 * sum;
}
#endif


class Robot
{
    private:
        double x, y, th;
    public:
        void set(double x_, double y_, double th_);
        void move(double v, double w);
        void print();
};

void Robot::set(double x_, double y_, double th_)
{
    x = x_;
    y = y_;
    th= th_;
}

void Robot::move(double v, double w)
{
    double a1 = 0.001;
    double a2 = 0.5;
    double a3 = 0.001;
    double a4 = 0.5;
    double a5 = 0.001;
    double a6 = 0.5;

    double dt = 0.01;
    double v_ = v + sample(a1 * v * v + a2 * w * w);
    double w_ = w + sample(a3 * v * v + a4 * w * w);
    double r_ =     sample(a5 * v * v + a6 * w * w);

    double x2 = x - v_ / w_ * sin(th) + v_ / w_ * sin(th + w_ * dt);
    double y2 = y + v_ / w_ * cos(th) - v_ / w_ * cos(th + w_ * dt);
    double th2= th + w_ * dt + r_ * dt;

    x  = x2;
    y  = y2;
    th = th2;
}

void Robot::print()
{
    std::cout << x << " " << y << " " << th << "\n";
}

int main(int argc, char *argv[])
{
    double v, w;           // 速度指令
    v = 0.1;        
    w = 0.1;

    int numRobot = 100;                     // シミュレーションするロボットの数
    std::vector<Robot> rb(numRobot);
    for (int i = 0; i < numRobot; i++) {
        rb[i].set(0.0, 0.0, 0.0);
    }

    int numLoop = 3000;                     // シミュレーション時間（繰り返し数）
    int skipNum = 300;
    for (int i = 0; i < numLoop; i++) {
        for (int k = 0; k < numRobot; k++) {
            rb[k].move(v, w);

            if (i % skipNum == 0) 
                rb[k].print();
        }
    }

    return 0;
}
