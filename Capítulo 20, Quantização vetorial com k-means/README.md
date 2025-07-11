# kmeans.cpp — quantização vetorial com k-means

Utilizando o programa kmeans.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/kmeans.html), prepare um programa exemplo onde a execução do código se dê usando o parâmetro nRodadas=1 e inciar os centros de forma aleatória usando o parâmetro KMEANS_RANDOM_CENTERS ao invés de KMEANS_PP_CENTERS. Realize 10 rodadas diferentes do algoritmo e compare as imagens produzidas. Explique porque elas podem diferir tanto.

---

## Descrição da Tarefa passo a passo

- Implementar uma versão do algoritmo de K-means utilizando o OpenCV para quantização de cores em uma imagem RGB.

- Configurar o número de clusters como 8, e a quantidade de rodadas (nRodadas) como 1 para cada execução do algoritmo.

- Substituir o método de inicialização dos centróides por KMEANS_RANDOM_CENTERS, o que introduz variabilidade no agrupamento.

- Executar o algoritmo 10 vezes sobre a mesma imagem de entrada, salvando os resultados com nomes diferentes.
  
- Comparar visualmente as imagens geradas para observar a sensibilidade do K-means à inicialização aleatória.ontornos.

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

-

<p align="center">
  <img src="./build/saida_0.jpg" width="700"/>
</p>

<p align="center"><i>Figura 1: clusters_v0.</i></p>

<p align="center">
  <img src="./build/saida_1.jpg" width="700"/>
</p>

<p align="center"><i>Figura 2: clusters_v1.</i></p>
