#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

int SIDE = 256;
int PERIODOS = 4;

int main() {
    std::stringstream ss_img, ss_yml;
    cv::Mat image(SIDE, SIDE, CV_32FC1);

    // Geração da senoide na horizontal (varia com i, constante em j)
    for (int i = 0; i < SIDE; ++i) {
        float value = 127 * std::sin(2 * M_PI * PERIODOS * i / SIDE) + 128;
        for (int j = 0; j < SIDE; ++j) {
            image.at<float>(i, j) = value;
        }
    }

    // Salvar no YML
    ss_yml << "senoide_horizontal-" << SIDE << ".yml";
    cv::FileStorage fs(ss_yml.str(), cv::FileStorage::WRITE);
    fs << "mat" << image;
    fs.release();

    // Salvar imagem PNG após normalizar e converter
    cv::Mat image_8u;
    cv::normalize(image, image_8u, 0, 255, cv::NORM_MINMAX);
    image_8u.convertTo(image_8u, CV_8U);
    ss_img << "senoide_horizontal-" << SIDE << ".png";
    cv::imwrite(ss_img.str(), image_8u);

    return 0;
}
