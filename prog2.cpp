#include <iostream>
#include <vector>
#include "Drawer.h"
#include "Robot.h"

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

    // 経路1
    for (int i = 0; i < 6.0/dt; i++) {
        for (Robot &x: rb) 
            x.move(1.0, 0.0, dt);
            
        if (i % drawStep == 0) {
            for (Robot x: rb)
                dr.drawing<Robot>(x);
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
            dr.show();
            cv::waitKey(5);
        }
    }

    dr.imgWrite();                            // img をファイルに書き出す
    cv::waitKey(0);
    return 0;
}
