#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

#define STEP 5
#define JITTER 3
#define RAIO 5
#define CANNY_STEPS 4

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <imagem_em_escala_de_cinza>" << std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Erro ao abrir a imagem: " << argv[1] << std::endl;
        return -1;
    }

    int width = image.cols;
    int height = image.rows;

    cv::Mat canvas(height, width, CV_8UC3, cv::Scalar(255, 255, 255)); // fundo branco

    std::vector<int> xrange(height / STEP);
    std::vector<int> yrange(width / STEP);
    std::iota(xrange.begin(), xrange.end(), 0);
    std::iota(yrange.begin(), yrange.end(), 0);

    for (size_t i = 0; i < xrange.size(); i++)
        xrange[i] = xrange[i] * STEP + STEP / 2;
    for (size_t i = 0; i < yrange.size(); i++)
        yrange[i] = yrange[i] * STEP + STEP / 2;

    std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());

    std::shuffle(xrange.begin(), xrange.end(), rng);

    // Passo 1: Pontilhismo básico
    for (int x : xrange) {
        std::shuffle(yrange.begin(), yrange.end(), rng);
        for (int y : yrange) {
            int jittered_x = x + std::rand() % (2 * JITTER + 1) - JITTER;
            int jittered_y = y + std::rand() % (2 * JITTER + 1) - JITTER;

            if (jittered_x >= 0 && jittered_x < height && jittered_y >= 0 && jittered_y < width) {
                int gray = image.at<uchar>(jittered_x, jittered_y);
                cv::circle(canvas, cv::Point(jittered_y, jittered_x), RAIO,
                           cv::Scalar(gray, gray, gray), cv::FILLED, cv::LINE_AA);
            }
        }
    }

    // Passo 2: Reforçar contornos com Canny
    for (int i = 0; i < CANNY_STEPS; ++i) {
        int t_low = 10 + i * 20; // thresholds: 10, 30, 50, 70...
        int t_high = 3 * t_low;

        cv::Mat edges;
        cv::Canny(image, edges, t_low, t_high);

        int raio_borda = std::max(1, RAIO - i); // círculos menores a cada passo

        for (int y = 0; y < edges.rows; ++y) {
            for (int x = 0; x < edges.cols; ++x) {
                if (edges.at<uchar>(y, x) != 0) {
                    int gray = image.at<uchar>(y, x);
                    cv::circle(canvas, cv::Point(x, y), raio_borda,
                               cv::Scalar(gray, gray, gray), cv::FILLED, cv::LINE_AA);
                }
            }
        }
    }

    cv::imwrite("cannypoints.png", canvas);
    std::cout << "Imagem gerada: cannypoints.png\n";

    return 0;
}

