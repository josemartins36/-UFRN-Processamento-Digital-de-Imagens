# equalize.cpp — equalização de histogramas com webcam

Utilizando o programa histograma.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/histograma.html), implemente um programa equalize.cpp. Este deverá, para cada imagem capturada, realizar a equalização do histogram antes de exibir a imagem. Teste sua implementação apontando a câmera para ambientes com iluminações variadas e observando o efeito gerado. Assuma que as imagens processadas serão em tons de cinza.

---

## Descrição da Tarefa

- Capturar imagens em tempo real da webcam.

- Converter cada frame para tons de cinza.

- Realizar a equalização do histograma antes da exibição.

---

## Trechos-chave do código


### 1. Rotulagem inicial com flood fill
Percorre toda a imagem em tons de cinza (0 a 255), e sempre que encontra um pixel branco (255), aplica floodFill para rotular toda a região conectada com um número único (valor de nobjects), contando e rotulando objetos distintos na imagem.

```cpp
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255) {
        nobjects++;
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, nobjects);
      }
    }
  }
```

### 2. Remoção de objetos conectados às bordas
Remove da imagem os objetos (rotulados anteriormente) que tocam as bordas, substituindo-os por 0 (preto).

```cpp
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
```
### 3. Contagem de objetos com buracos
Primeiro, preenche o fundo da imagem com branco, evitando que o fundo seja interpretado como buraco durante a próxima etapa de detecção. Em seguida, procura-se por buracos (áreas pretas) dentro dos objetos e verifica a qual objeto (pela "cor à esquerda") o buraco pertence. Se for um objeto ainda não registrado, ele é contado como tendo buraco(s).

```cpp
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
```
## Resultados

O algoritmo conseguiu identificar corretamente o número de bolhas com e sem buracos, com os objetos tocando a borda da iamgem sendo excluídos da contagem, como exigido.

<p align="center">
  <img src="./build/objetos_com_buracos.png" width="500"/>
</p>

<p align="center"><i>Figura 2: Imagem bolhas pós processamento.</i></p>

https://youtu.be/5gvMbqbpmCk
