# filestorage.cpp — Análise de Precisão na Representação de Imagens PNG versus YML

Utilizando o programa-exemplo filestorage.cpp como base, crie um programa que gere uma imagem de dimensões 256x256 pixels contendo uma senóide de 4 períodos com amplitude igual 127 desenhada na horizontal, semelhante àquela apresentada na Figura 11, “Saída do programa filestorage”. Grave a imagem no formato YML e também em formato PNG, como faz o programa-exemplo. Compare os arquivos gerados, extraindo uma linha correspondente de cada imagem gravada e comparando a diferença entre elas. Trace um gráfico da diferença calculada ao longo da linha correspondente extraída nas imagens. O que você observa? Por que isso acontece?

## Descrição da Tarefa

Inspirado na abordagem do exemplo `filestorage.cpp` no material de estudo, o objetivo desta tarefa é desenvolver um programa com as seguintes funcionalidades:

- Gerar uma imagem de **256x256 pixels** contendo uma **senóide com 4 períodos e amplitude 127**, desenhada horizontalmente.
- Salvar a imagem nos seguintes formatos:
  - **YML**, utilizando `cv::FileStorage`.
  - **PNG**, utilizando `cv::imwrite`.
- Recarregar as imagens gravadas nos dois formatos.
- **Extrair uma linha (linha central, por exemplo, a linha 128)** de cada imagem.
- Calcular a **diferença absoluta** entre os valores dos pixels das duas linhas extraídas.
- Exibir um **gráfico da diferença** ao longo da linha comparada.

---

## Trechos-chave do código

### 1. Geração da senóide

A imagem é inicializada com zeros e preenchida com valores baseados na função seno.

```cpp
cv::Mat senoide(256, 256, CV_8UC1, cv::Scalar(0));
for (int x = 0; x < senoide.cols; ++x) {
    int y = 127 + static_cast<int>(127 * std::sin(4 * 2 * CV_PI * x / senoide.cols));
    senoide.at<uchar>(y, x) = 255;
}
```
