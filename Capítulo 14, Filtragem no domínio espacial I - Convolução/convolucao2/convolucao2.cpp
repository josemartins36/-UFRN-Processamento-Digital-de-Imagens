#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

cv::Mat createAverageKernel(int size) {
  float value = 1.0f / (size * size);
  return cv::Mat(size, size, CV_32F, cv::Scalar(value));
}

int main(int, char**) {
  cv::VideoCapture cap;
  int camera = cameraEnumerator();
  cap.open(camera);

  if (!cap.isOpened()) {
    std::cerr << "Erro ao abrir a câmera!" << std::endl;
    return -1;
  }

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  cv::namedWindow("original", cv::WINDOW_NORMAL);
  cv::namedWindow("filtrada", cv::WINDOW_NORMAL);

  int kernelSize = 3;
  cv::Mat mask = createAverageKernel(kernelSize);

  cv::Mat frame, gray, gray32f, filtered, result;
  char key;

  for (;;) {
    cap >> frame;
    if (frame.empty()) break;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::flip(gray, gray, 1);
    cv::imshow("original", gray);

    gray.convertTo(gray32f, CV_32F);
    cv::filter2D(gray32f, filtered, CV_32F, mask, cv::Point(-1, -1), 0, cv::BORDER_REPLICATE);

    filtered.convertTo(result, CV_8U);
    cv::imshow("filtrada", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break; // ESC

    switch (key) {
      case '3':
        kernelSize = 3;
        mask = createAverageKernel(kernelSize);
        std::cout << "Kernel 3x3" << std::endl;
        break;
      case '1':
        kernelSize = 11;
        mask = createAverageKernel(kernelSize);
        std::cout << "Kernel 11x11" << std::endl;
        break;
      case '2':
        kernelSize = 21;
        mask = createAverageKernel(kernelSize);
        std::cout << "Kernel 21x21" << std::endl;
        break;
      default:
        break;
    }
  }

  return 0;
}

