/*
 * 移動ロボットの動作モデルと誤差@zoom
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 * 2020.3.13
 *
 * 誤差を含む速度動作モデルのシミュレーションです
 *
 * 2020.3.14
 *  OpenCVを使って画面描画するように機能追加
 * 2020.3.15
 *  点座標の描画を関数テンプレートに修正し，柔軟性をもたせた
 *  描画時の色を指定するようにした
 * 2020.3.23
 *  描画クラスを大幅にアップデート
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "Robot.h"
#include "Drawer.h"

int main(int argc, char *argv[])
{
    Drawer dr;              // ロボット描画する役

    double dt = 0.01;       // シミュレーションの時間ステップ
    double v, w;            // 速度指令
    v = 0.1;        
    w = 0.1;

    int numRobot = 500;                     // シミュレーションするロボットの数
    std::vector<Robot> rb(numRobot);

    int numLoop = 5000;                     // シミュレーション時間（繰り返し数）
    int skipNum = 300;                      // 途中経過の出力するためのスキップ数

    for (int i = 0; i < numLoop; i++) {
        for (int k = 0; k < numRobot; k++) {
            rb[k].move(v, w, dt);                   // すべてのロボットを動作更新
        }
        if (i % skipNum == 0) {                     // 途中経過を表示
            for (int k = 0; k < numRobot; k++) {
                dr.drawing<Robot>(rb[k]);
            }
            dr.show();
        }
    }

    dr.imgWrite();
    cv::waitKey(0);     // 何かキーを押すまで待つ

    return 0;
}
