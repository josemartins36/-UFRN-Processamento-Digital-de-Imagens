#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Carrega a imagem
    cv::Mat imagem = cv::imread("papagaio.png", cv::IMREAD_COLOR);
    if (imagem.empty()) {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    // Assume que as dimensões são múltiplos de 2
    int meio_linha = imagem.rows / 2;
    int meio_coluna = imagem.cols / 2;

    // Define os quadrantes usando ROI (Region of Interest)
    cv::Mat A = imagem(cv::Rect(0, 0, meio_coluna, meio_linha));                         // superior esquerdo
    cv::Mat B = imagem(cv::Rect(meio_coluna, 0, meio_coluna, meio_linha));               // superior direito
    cv::Mat C = imagem(cv::Rect(0, meio_linha, meio_coluna, meio_linha));                // inferior esquerdo
    cv::Mat D = imagem(cv::Rect(meio_coluna, meio_linha, meio_coluna, meio_linha));      // inferior direito

    // Clones para preservar os dados originais antes da troca
    cv::Mat A_clone = A.clone();
    cv::Mat B_clone = B.clone();
    cv::Mat C_clone = C.clone();
    cv::Mat D_clone = D.clone();

    // Troca os quadrantes em diagonal
    A_clone.copyTo(D);
    D_clone.copyTo(A);
    B_clone.copyTo(C);
    C_clone.copyTo(B);

    // Exibe a imagem modificada
    cv::imshow("Imagem com quadrantes trocados", imagem);
    cv::waitKey(0);
    cv::imwrite("imagem_editada.png", imagem);
    return 0;
}

