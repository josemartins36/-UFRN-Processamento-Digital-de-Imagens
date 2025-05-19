#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Erro ao abrir a câmera." << std::endl;
        return -1;
    }

    cv::Mat frame, gray, prevHist, currHist;
    int nbins = 64;
    float range[] = {0, 256};
    const float* histRange = {range};
    bool uniform = true, accumulate = false;
    double limiar = 0.01;  // sensibilidade do detector

    bool firstFrame = true;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::calcHist(&gray, 1, 0, cv::Mat(), currHist, 1, &nbins, &histRange, uniform, accumulate);
        cv::normalize(currHist, currHist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        if (!firstFrame) {
            double diff = cv::compareHist(prevHist, currHist, cv::HISTCMP_BHATTACHARYYA);
            
            if (diff > limiar) {
                cv::putText(frame, "MOVIMENTO DETECTADO!", cv::Point(50,50),
                            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255), 2);
                std::cout << "Movimento detectado! Diferença = " << diff << std::endl;
            }
        }

        currHist.copyTo(prevHist);
        firstFrame = false;

        cv::imshow("Detector de Movimento", frame);
        if (cv::waitKey(30) == 27) break;  // tecla ESC
    }

    return 0;
}

