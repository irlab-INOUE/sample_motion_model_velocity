#include <iostream>
#include <vector>
#include "Drawer.h"
#include "Robot.h"

int main(int argc, char* argv[])
{
    int WAIT_TIME = 0;
    // 初期設定
    Drawer dr;
    dr.setCsize(0.007);
    dr.setImgWidth(10.0);
    dr.setImgHight(6.0);
    dr.setOriginXfromLeft(2.0);
    dr.setOriginYfromBottom(1.0);

    // 背景画像
    dr.setLineColor(cv::Scalar(0, 0, 0));
    dr.text( 0.2, -0.6, "Fig. Robot Odometory");
    dr.text(-0.3,  0.0, "O");
    dr.text( 7.0, -0.3, "X");
    dr.text(-0.3,  4.5, "Y");
    dr.includeImage(-2, 5, "../fig/logo.jpeg");
    dr.text(-2, 4, "K.INOUE");
    dr.show(WAIT_TIME);

    // Page 1
    dr.setLineWidth(2);
    dr.setLineColor(cv::Scalar(150, 0, 0));
    dr.robot(5, 0, 0.5, M_PI/2);
    dr.show(WAIT_TIME);

    // Page 2
    dr.setLineWidth(1);
    dr.setLineColor(cv::Scalar(200, 80, 80));
    dr.circle(0, 0, 5, 0.0, -45.0, false);
    dr.lineRA(0, 0, 5, M_PI/4);
    dr.text(2.5*cos(M_PI/4), 2.5*sin(M_PI/4)+0.2, "R");
    dr.circle(0, 0, 1.0, 0,-45, false);
    dr.overText(1.0, 0.8, "../fig/theta.png");
    dr.show(WAIT_TIME);

    // Page 3
    dr.setLineWidth(2);
    dr.setLineColor(cv::Scalar(150, 0, 0));
    dr.robot(5 * cos(M_PI/4), 5 * sin(M_PI/4), 0.5, M_PI/2 + M_PI/4);
    dr.text(4.6, 2.0, "D");
    dr.show(WAIT_TIME);

    // Page 4
    dr.setLineWidth(1);
    dr.setLineColor(cv::Scalar(200, 80, 80));
    dr.circle(0, 0, 5 - 0.5, 0.0, -45.0, false);
    dr.text(5.5*cos(M_PI/8), 5.5*sin(M_PI/8), "D_R");
    dr.circle(0, 0, 5 + 0.5, 0.0, -45.0, false);
    dr.text(3.8*cos(M_PI/8), 3.8*sin(M_PI/8), "D_L");
    dr.show(WAIT_TIME);

    // Page 5
    dr.lineRA(0, 0, 5, 0);
    dr.lineRA(0, 0, 5, M_PI/4);
    dr.show(WAIT_TIME);

    // Page 6
    dr.lineRA(5 * cos(M_PI/4), 5 * sin(M_PI/4), 2.0, M_PI/2);
    dr.lineRA(5 * cos(M_PI/4), 5 * sin(M_PI/4), 2.0, M_PI/2 + M_PI/4);
    dr.circle(5 * cos(M_PI/4), 5 * sin(M_PI/4), 1.0, -90, -135);
    dr.show(WAIT_TIME);

    // Page END
    dr.setLineColor(cv::Scalar(0, 0, 200));
    dr.text(0.5, 4, "Finish!");
    dr.show(0);
    return 0;
}
