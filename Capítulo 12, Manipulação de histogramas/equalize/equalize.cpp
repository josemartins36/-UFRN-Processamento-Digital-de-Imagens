#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
  cv::Mat image, gray, equalized;
  int camera = 0;

  cv::VideoCapture cap(camera);
  if (!cap.isOpened()) {
    std::cerr << "Erro: câmera indisponível." << std::endl;
    return -1;
  }

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  while (true) {
    cap >> image;
    if (image.empty()) {
      std::cerr << "Erro: não foi possível capturar a imagem." << std::endl;
      break;
    }

    // Converter para escala de cinza
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Equalizar o histograma
    cv::equalizeHist(gray, equalized);

    // Juntar lado a lado para visualização
    cv::Mat combined;
    cv::hconcat(gray, equalized, combined);

    // Exibir a imagem
    cv::imshow("Original (esq) vs Equalizada (dir)", combined);

    int key = cv::waitKey(30);
    if (key == 27) break; // tecla ESC
  }

  return 0;
}

