# equalize.cpp — equalização de histogramas com webcam

Utilizando o programa histograma.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/histograma.html), implemente um programa equalize.cpp. Este deverá, para cada imagem capturada, realizar a equalização do histogram antes de exibir a imagem. Teste sua implementação apontando a câmera para ambientes com iluminações variadas e observando o efeito gerado. Assuma que as imagens processadas serão em tons de cinza.

---

## Descrição da Tarefa

- Capturar imagens em tempo real da webcam.

- Converter cada frame para tons de cinza.

- Realizar a equalização do histograma antes da exibição.

---

## Trechos-chave do código


### 1. Abertura da câmera e configuração da resolução
O programa utiliza a `cv::VideoCapture` para acessar a webcam padrão (índice 0) e define a resolução da imagem capturada.

```cpp
  cv::VideoCapture cap(camera);
  if (!cap.isOpened()) {
    std::cerr << "Erro: câmera indisponível." << std::endl;
    return -1;
  }

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
```

### 2. Conversão para escala de cinza
Para preparar a imagem para equalização, ela é convertida de BGR (formato da câmera) para tons de cinza.

```cpp
cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

```

### 3. Equalização do histograma
A função cv::equalizeHist é aplicada à imagem em tons de cinza para realçar o contraste, especialmente em áreas mal iluminadas.

```cpp
cv::equalizeHist(gray, equalized);  
```
## Resultados

Durante a [execução do programa](https://youtu.be/5gvMbqbpmCk), é possível observar a diferença significativa no contraste das imagens ao comparar a versão original em tons de cinza com a versão equalizada. O efeito é mais evidente em ambientes com baixa ou iluminação irregular.

<p align="center">
  <img src="equalizer_luz.png" width="700"/>
</p>

<p align="center"><i>Figura 1: Efeito do equalizer com iluminação. [Equalizer na imagem da direita]</i></p>

<p align="center">
  <img src="equalizer_escuridao.png" width="700"/>
</p>

<p align="center"><i>Figura 1: Efeito do equalizer na escuridão. [Equalizer na imagem da direita]</i></p>
