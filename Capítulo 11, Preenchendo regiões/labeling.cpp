

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
  cv::Mat image, realce;
  int width, height;
  int nobjects;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "imagem nao carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x = 0;
  p.y = 0;

  // busca objetos presentes
  nobjects = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255) {
        // achou um objeto
        nobjects++;
        // para o floodfill as coordenadas
        // x e y são trocadas.
        p.x = j;
        p.y = i;
        // preenche o objeto com o contador
        cv::floodFill(image, p, nobjects);
      }
    }
  }

  // Remove objetos conectados às bordas
  for (int i = 0; i < height; ++i) {
    if (image.at<uchar>(i, 0) != 0 && image.at<uchar>(i, 0) != 255)
      cv::floodFill(image, cv::Point(0, i), 0);
    if (image.at<uchar>(i, width - 1) != 0 && image.at<uchar>(i, width - 1) != 255)
      cv::floodFill(image, cv::Point(width - 1, i), 0);
  }
  for (int j = 0; j < width; ++j) {
    if (image.at<uchar>(0, j) != 0 && image.at<uchar>(0, j) != 255)
      cv::floodFill(image, cv::Point(j, 0), 0);
    if (image.at<uchar>(height - 1, j) != 0 && image.at<uchar>(height - 1, j) != 255)
      cv::floodFill(image, cv::Point(j, height - 1), 0);
  }  

  cv::floodFill(image, cv::Point(0, 0), 255);

  int objetos_com_buracos = 0;
  std::set<int> ja_contados;

  for (int i = 0; i < height; ++i) {
    for (int j = 1; j < width; ++j) { // j começa em 1 para evitar j-1 < 0
      if (image.at<uchar>(i, j) == 0) {
        int cor_esquerda = image.at<uchar>(i, j - 1);

        if (cor_esquerda != 0 && cor_esquerda != 255 && ja_contados.find(cor_esquerda) == ja_contados.end()) {
          objetos_com_buracos++;
          ja_contados.insert(cor_esquerda);
        }

        // pinta o buraco para não contar ele de novo
        cv::floodFill(image, cv::Point(j, i), 254);
      }
    }
  }
   
  std::cout << "a figura tem " << nobjects << " bolhas\n";
  std::cout << "Objetos com buracos: " << objetos_com_buracos << std::endl;
  cv::imshow("image", image);
  cv::imwrite("objetos_com_buracos.png", image);
  cv::waitKey();
  return 0;
}


