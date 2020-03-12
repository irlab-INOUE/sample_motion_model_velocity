#include <iostream>
#include <opencv2/opencv.hpp>
//#include <vector>

// 乱数初期化
cv::RNG rng(cv::getTickCount());

#if 0
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

int main(int argc, char *argv[])
{
    return 0;
}

