#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat image;
  std::ofstream file;

  // Carrega a imagem em tons de cinza
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "Não abriu " << argv[1] << std::endl;
    return 0;
  }

  // Binariza com Otsu e inverte: objetos escuros viram brancos
  cv::threshold(image, image, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);

  // Vetores para armazenar os contornos e hierarquia
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  // Encontra os contornos (externos e internos) com simplificação
  cv::findContours(image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  // Converte imagem para BGR para desenhar contornos coloridos
  cv::cvtColor(image, image, cv::COLOR_GRAY2BGR);

  // Abre arquivo SVG para salvar os contornos
  file.open("contornos.svg");
  if (!file.is_open()) {
    std::cout << "Não abriu contornos.svg" << std::endl;
    return 0;
  }

  file << "<svg height=\"" << image.rows << "\" width=\"" << image.cols
       << "\" xmlns=\"http://www.w3.org/2000/svg\"> " << std::endl;

  int total_pontos = 0;
  for (size_t i = 0; i < contours.size(); i++) {
    file << "<path d=\"M " << contours[i][0].x << " " << contours[i][0].y << " ";
    for (size_t j = 1; j < contours[i].size(); j++) {
      file << "L" << contours[i][j].x << " " << contours[i][j].y << " ";
    }
    file << "Z\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" />" << std::endl;
    cv::drawContours(image, contours, i, CV_RGB(255, 0, 0), 1);
    total_pontos += contours[i].size();
  }

  std::cout << "Total de contornos encontrados: " << contours.size() << std::endl;
  std::cout << "Total de pontos nos contornos: " << total_pontos << std::endl;

  file << "</svg>" << std::endl;
  file.close();

  cv::imshow("Contornos Detectados", image);
  cv::waitKey(0);
  return 0;
}

