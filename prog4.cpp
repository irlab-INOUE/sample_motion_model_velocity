#include <iostream>
#include <vector>
#include "Drawer.h"
#include "Robot.h"

struct STATISTIC
{
    double xg, yg;
    double sxx, sxy, syy;
    double u, v;
    double lambda;
};

STATISTIC calcCovariance(std::vector<Robot> &rb) 
{
    STATISTIC stat;

    // 姿勢の重心を求める
    double xg = 0.0;
    double yg = 0.0;
    int N = rb.size();
    for (Robot &x: rb) {
        xg += x.getX();
        yg += x.getY();
    }
    xg /= N;
    yg /= N;
    std::cerr << "平均位置: " << xg << "," << yg << std::endl;
    stat.xg = xg;
    stat.yg = yg;

    // 分散・共分散
    double sxx = 0.0;
    double syy = 0.0;
    double sxy = 0.0;
    for (Robot &x: rb) {
        sxx += (x.getX() - xg) * (x.getX() - xg);
        sxy += (x.getX() - xg) * (x.getY() - yg);
        syy += (x.getY() - yg) * (x.getY() - yg);
    }
    sxx /= N;
    sxy /= N;
    syy /= N;
    std::cerr << "共分散行列\n";
    std::cerr 
        << sxx << "\t" << sxy << "\n"
        << sxy << "\t" << syy << "\n";
    stat.sxx = sxx;
    stat.sxy = sxy;
    stat.syy = syy;

    // 累乗法で固有ベクトルと固有値を求める
    double u = 1.0;
    double v = 0.0;     // 固有ベクトル

    for (int i = 0; i < 10; i++) {
        double u_ = sxx * u + sxy * v;
        double v_ = sxy * u + syy * v;
        // 規格化
        double k = sqrt(u_ * u_ + v_ * v_);
        u = u_ / k;
        v = v_ / k;
    }
    // 固有値
    double a = sxx * u + sxy * v;
    double b = sxy * u + sxy * v;
    double lambda = sqrt(a*a + b*b);

    std::cerr << "固有ベクトル " << u << "," << v << "\n";
    std::cerr << "固有値 " << lambda << "\n";
    std::cerr << "\n";

    stat.u = u;
    stat.v = v;
    stat.lambda = lambda;

    return stat;
}

int main(int argc, char* argv[])
{
    std::vector<Robot> rb(1000);
    Drawer dr;

    dr.setCsize(0.015);
    dr.setImgWidth(20.0);
    dr.setImgHight(10.0);
    dr.setOriginXfromLeft(10.0);
    dr.setOriginYfromBottom(1.0);
    dr.includeImage(-10, 9, "../fig/logo.jpeg");
    dr.text(-10, 7, "K.INOUE");
    dr.show();

    // 目標経路
    dr.setLineWidth(2);                   
    dr.setLineColor(cv::Scalar(0, 0, 180));            
    dr.line(0.0, 0.0, 6.0, 0.0);
    dr.line(6.0, 0.0, 6.0, 6.0);
    dr.line(6.0, 6.0,-6.0, 6.0);

    double dt = 0.01;                           // 時間の刻み幅
    int drawStep = 2.0/dt;                      // 画像に出力する間隔
    dr.setPointColor(cv::Scalar(200, 0, 0));    // 点を描画するための色をセットする

    STATISTIC stat;
    dr.setLineColor(cv::Scalar(0, 180, 0));

    // 経路1
    for (int i = 0; i < 6.0/dt; i++) {
        for (Robot &x: rb) 
            x.move(1.0, 0.0, dt);
            
        if (i % drawStep == 0) {
            for (Robot x: rb)
                dr.drawing<Robot>(x);
            stat = calcCovariance(rb);
            dr.line(stat.xg, stat.yg, stat.xg + stat.lambda * stat.u, stat.yg + stat.lambda * stat.v);
            dr.show();
            cv::waitKey(5);
        }
    }

    // 経路2
    for (int i = 0; i < M_PI/2.0/0.1/dt; i++) {
        for (Robot &x: rb) 
            x.move(0.0, 0.1, dt);
    }

    // 経路3
    for (int i = 0; i < 6.0/dt; i++) {
        for (Robot &x: rb) 
            x.move(1.0, 0.0, dt);

        if (i % drawStep == 0) {
            for (Robot x: rb)
                dr.drawing<Robot>(x);
            stat = calcCovariance(rb);
            dr.line(stat.xg, stat.yg, stat.xg + stat.lambda * stat.u, stat.yg + stat.lambda * stat.v);
            dr.show();
            cv::waitKey(5);
        }
    }

    // 経路4
    for (int i = 0; i < M_PI/2.0/0.1/dt; i++) {
        for (Robot &x: rb) 
            x.move(0.0, 0.1, dt);
    }

    // 経路5
    for (int i = 0; i < 13.0/dt; i++) {
        for (Robot &x: rb) 
            x.move(1.0, 0.0, dt);

        if (i % drawStep == 0) {
            for (Robot x: rb)
                dr.drawing<Robot>(x);
            stat = calcCovariance(rb);
            dr.line(stat.xg, stat.yg, stat.xg + stat.lambda * stat.u, stat.yg + stat.lambda * stat.v);
            dr.show();
            cv::waitKey(5);
        }
    }

    dr.imgWrite();                            // img をファイルに書き出す
    cv::waitKey(0);

    return 0;
}

