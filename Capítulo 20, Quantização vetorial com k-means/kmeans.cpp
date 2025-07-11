#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
  int nClusters = 8;
  int nRodadas = 1;

  if (argc != 2) {
    std::cout << "Uso: ./kmeans_random entrada.jpg\n";
    return -1;
  }

  cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
  if (img.empty()) {
    std::cerr << "Erro ao abrir imagem.\n";
    return -1;
  }

  // Preparar os dados
  cv::Mat samples(img.rows * img.cols, 3, CV_32F);
  for (int y = 0; y < img.rows; y++) {
    for (int x = 0; x < img.cols; x++) {
      for (int z = 0; z < 3; z++) {
        samples.at<float>(y + x * img.rows, z) = img.at<cv::Vec3b>(y, x)[z];
      }
    }
  }

  for (int rodada = 0; rodada < 10; rodada++) {
    cv::Mat rotulos, centros;

    // Executa kmeans com inicialização aleatória
    cv::kmeans(samples, nClusters, rotulos,
               cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10000, 0.0001),
               nRodadas, cv::KMEANS_RANDOM_CENTERS, centros);

    // Cria imagem de saída
    cv::Mat rotulada(img.size(), img.type());
    for (int y = 0; y < img.rows; y++) {
      for (int x = 0; x < img.cols; x++) {
        int indice = rotulos.at<int>(y + x * img.rows, 0);
        for (int z = 0; z < 3; z++) {
          rotulada.at<cv::Vec3b>(y, x)[z] = (uchar)centros.at<float>(indice, z);
        }
      }
    }

    // Salva imagem
    std::ostringstream nomeSaida;
    nomeSaida << "saida_" << rodada << ".jpg";
    cv::imwrite(nomeSaida.str(), rotulada);
    std::cout << "Imagem " << nomeSaida.str() << " salva.\n";
  }

  return 0;
}

