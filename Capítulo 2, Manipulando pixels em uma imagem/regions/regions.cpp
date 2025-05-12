#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat image;
  int p1_x, p1_y, p2_x, p2_y;

  // Leitura da imagem em tons de cinza
  image = cv::imread("papagaio.png", cv::IMREAD_GRAYSCALE);
  if (!image.data) {
    std::cout << "Erro ao abrir a imagem 'bolhas.png'" << std::endl;
    return -1;
  }

  // Tamanho da imagem
  int rows = image.rows;
  int cols = image.cols;
  std::cout << "Tamanho da imagem: " << cols << "x" << rows << std::endl;

  // Solicita ao usuário os dois pontos
  std::cout << "Digite as coordenadas de P1 (x y): ";
  std::cin >> p1_x >> p1_y;

  std::cout << "Digite as coordenadas de P2 (x y): ";
  std::cin >> p2_x >> p2_y;

  // Garante que os pontos estão dentro da imagem
  if (p1_x < 0 || p1_x >= cols || p2_x < 0 || p2_x >= cols ||
      p1_y < 0 || p1_y >= rows || p2_y < 0 || p2_y >= rows) {
    std::cout << "Coordenadas fora dos limites da imagem." << std::endl;
    return -1;
  }

  // Define os limites da região (em ordem crescente)
  int min_x = std::min(p1_x, p2_x);
  int max_x = std::max(p1_x, p2_x);
  int min_y = std::min(p1_y, p2_y);
  int max_y = std::max(p1_y, p2_y);

  // Aplica o negativo na região selecionada
  for (int i = min_y; i <= max_y; i++) {
    for (int j = min_x; j <= max_x; j++) {
      image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
    }
  }

  // Exibe o resultado
  cv::namedWindow("Regiao com Negativo", cv::WINDOW_AUTOSIZE);
  cv::imshow("Regiao com Negativo", image);
  cv::waitKey();
  cv::imwrite("imagem_editada.png", image);
  return 0;
}
