# contornos.cpp — extração de contornos

Utilizando o programa contornos.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/contornos.html), aplique-o na extração do contorno da imagem retangulos.png mostrada na Figura 55, “Retângulos superpostos”. Quantos pontos são gerados para o contorno dos retângulos?

Modifique o programa para extrair os contornos internos das componentes conectadas presentes na imagem formas.png. Para isso, altere o parâmetro cv::CHAIN_APPROX_NONE para cv::CHAIN_APPROX_SIMPLE na função findContours(). O que acontece com os novos contornos extraídos? Mostre quantos pontos são gerados após a alteração e discuta como a modificação do parâmetro cv::CHAIN_APPROX_SIMPLE influencia na extração do contorno.

---

## Descrição da Tarefa passo a passo

- Aplicar binarização automática utilizando o método de Otsu com inversão de tons para destacar os objetos (objetos tornam-se brancos, fundo preto).

- Detectar os contornos de todos os objetos da imagem utilizando a função cv::findContours() da biblioteca OpenCV.

- Testar os dois modos de aproximação de contorno:

  cv::CHAIN_APPROX_SIMPLE: armazena apenas os vértices significativos dos contornos.

  cv::CHAIN_APPROX_NONE: armazena todos os pontos dos contornos, preservando os detalhes completos.

- Gerar visualizações com os contornos desenhados sobre a imagem original, bem como arquivos SVG com os contornos vetorizados.
  
- Contar e exibir o número total de pontos em todos os contornos (para comparar os métodos SIMPLE e NONE).

---

## Trechos-chave do código

### 1. Leitura da imagem e preparação dos dados

```cpp
cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
cv::Mat samples(img.rows * img.cols, 3, CV_32F);

for (int y = 0; y < img.rows; y++) {
  for (int x = 0; x < img.cols; x++) {
    for (int z = 0; z < 3; z++) {
      samples.at<float>(y + x * img.rows, z) = img.at<cv::Vec3b>(y, x)[z];
    }
  }
}
```

### 2. Execução do algoritmo com centros aleatórios

```cpp
cv::kmeans(samples, nClusters, rotulos,
           cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10000, 0.0001),
           1, // nRodadas = 1
           cv::KMEANS_RANDOM_CENTERS, centros);
```

### 3. Reconstrução da imagem rotulada com as cores dos centros

```cpp
for (int y = 0; y < img.rows; y++) {
  for (int x = 0; x < img.cols; x++) {
    int indice = rotulos.at<int>(y + x * img.rows, 0);
    for (int z = 0; z < 3; z++) {
      rotulada.at<cv::Vec3b>(y, x)[z] = (uchar)centros.at<float>(indice, z);
    }
  }
}
```

## Resultados

As imagens resultantes apresentam variações significativas entre si, mesmo tendo sido processadas a partir da mesma imagem de entrada. Isso ocorre devido a:

- Inicialização aleatória dos centróides (KMEANS_RANDOM_CENTERS): como o ponto de partida influencia fortemente a convergência do algoritmo, diferentes execuções resultam em agrupamentos distintos.

- Apenas uma rodada por execução (nRodadas = 1): não há tentativa de buscar uma melhor configuração entre várias, o que acentua ainda mais a variabilidade dos resultados
