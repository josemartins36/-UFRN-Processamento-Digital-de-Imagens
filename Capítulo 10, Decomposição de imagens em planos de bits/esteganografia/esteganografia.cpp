#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Uso: " << argv[0] << " <imagem_esteganografada>" << std::endl;
    return -1;
  }

  cv::Mat imagemEsteganografada = cv::imread(argv[1], cv::IMREAD_COLOR);
  if (imagemEsteganografada.empty()) {
    std::cout << "Erro ao carregar a imagem." << std::endl;
    return -1;
  }

  int nbits = 3;  // número de bits usados para esconder a imagem
  cv::Mat imagemRecuperada = imagemEsteganografada.clone();
  cv::Vec3b pixelEsteganografado, pixelRecuperado;

  for (int i = 0; i < imagemEsteganografada.rows; i++) {
    for (int j = 0; j < imagemEsteganografada.cols; j++) {
      pixelEsteganografado = imagemEsteganografada.at<cv::Vec3b>(i, j);

      // Extrai os nbits menos significativos e os move para os bits mais significativos
      for (int c = 0; c < 3; c++) {
        unsigned char lsb = pixelEsteganografado[c] & ((1 << nbits) - 1); // máscara para nbits
        pixelRecuperado[c] = lsb << (8 - nbits);
      }

      imagemRecuperada.at<cv::Vec3b>(i, j) = pixelRecuperado;
    }
  }

  cv::imwrite("imagem_recuperada.png", imagemRecuperada);
  std::cout << "Imagem recuperada salva como imagem_recuperada.png" << std::endl;

  return 0;
}
