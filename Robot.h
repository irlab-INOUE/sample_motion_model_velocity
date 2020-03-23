#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <opencv2/opencv.hpp>

// 乱数初期化
cv::RNG rng(cv::getTickCount());

double sample(double b2)
{
    double sum = 0.0;
    double b = sqrt(b2);

    for (int i = 0; i < 12; i++) {
        sum += rng.uniform(-b, b);
    }

    return 0.5 * sum;
}

class Robot
{
    private:
        double x, y, th;

        // 動作モデルのパラメータ
        double a1 = 0.1;
        double a2 = 0.01;
        double a3 = 0.001;
        double a4 = 0.01;
        double a5 = 0.05;
        double a6 = 0.01;

    public:
        Robot();        // デフォルトコンストラクタ
        void set(double x_, double y_, double th_);
        void move(double v, double w, double dt);
        void print();

        double getX();
        double getY();
        double getTh();
};

Robot::Robot()
{
    x = 0.0;
    y = 0.0;
    th= 0.0;
}

void Robot::set(double x_, double y_, double th_)
{
    x = x_;
    y = y_;
    th= th_;
}

void Robot::move(double v, double w, double dt)
{
    double v_ = v + sample(a1 * v * v + a2 * w * w);
    double w_ = w + sample(a3 * v * v + a4 * w * w);
    double r_ =     sample(a5 * v * v + a6 * w * w);

    if (fabs(w_) < 1e-6) w_ = 1e-6;

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

double Robot::getX()
{
    return x;
}

double Robot::getY()
{
    return y;
}

double Robot::getTh()
{
    return th;
}

#endif
