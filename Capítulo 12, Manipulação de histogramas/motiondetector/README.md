# motiondetector.cpp — detector de movimento com webcam

Utilizando o programa histograma.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/histograma.html), implemente um programa motiondetector.cpp. Este deverá continuamente calcular o histograma da imagem (apenas uma componente de cor é suficiente) e compará-lo com o último histograma calculado. Quando a diferença entre estes ultrapassar um limiar pré-estabelecido, ative um alarme. Utilize uma função de comparação que julgar conveniente.

---

## Descrição da Tarefa

- Capturar imagens em tempo real da webcam.

- Converter cada frame para tons de cinza.

- Calcular o histograma do frame atual e comparar com o histograma do frame anterior.

- Detectar movimento com base na diferença entre os histogramas.

- Exibir uma mensagem de alerta na tela quando houver detecção.

---

## Trechos-chave do código

### 1. Captura da webcam e verificação de funcionamento
O programa utiliza a `cv::VideoCapture` para acessar a webcam padrão (índice 0).

```cpp
cv::VideoCapture cap(0);
if (!cap.isOpened()) {
    std::cout << "Erro ao abrir a câmera." << std::endl;
    return -1;
}

```

### 2. Conversão para escala de cinza
A imagem é convertida para escala de cinza para simplificar a análise de intensidade de pixels, como a detecção de movimento não precisa de cor — por isso o histograma é feito no gray. A exibição final é colorida.

```cpp
cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
```

### 3. Cálculo e normalização do histograma
O histograma é calculado para a imagem em tons de cinza e normalizado com cv::NORM_MINMAX, o que facilita a comparação com o frame anterior.

```cpp
cv::calcHist(&gray, 1, 0, cv::Mat(), currHist, 1, &nbins, &histRange, uniform, accumulate);
cv::normalize(currHist, currHist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
```
### 4. Comparação entre histogramas consecutivos
A função cv::compareHist com o método de Bhattacharyya mede a similaridade entre os histogramas. Se a diferença for maior que um limiar definido, é detectado um movimento.

```cpp
double diff = cv::compareHist(prevHist, currHist, cv::HISTCMP_BHATTACHARYYA);
            
if (diff > limiar) {
  cv::putText(frame, "MOVIMENTO DETECTADO!", cv::Point(50,50),
  cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255), 2);
  std::cout << "Movimento detectado! Diferença = " << diff << std::endl;
}
```

## Resultados

Durante a [execução do programa](https://youtu.be/5gvMbqbpmCk), é possível observar a diferença significativa no contraste das imagens ao comparar a versão original em tons de cinza com a versão equalizada. O efeito é mais evidente em ambientes com baixa ou iluminação irregular, pois o histograma que estava concentrado à esquerda (valores próximos de 0 na escuridão) é espalhado ao longo da faixa de 0 a 255, resultando em áreas muito escuras ganhando intensidade e ficando mais claras.

<p align="center">
  <img src="equalizer_luz.png" width="700"/>
</p>

<p align="center"><i>Figura 1: Efeito do equalizer com iluminação. [Equalizer na imagem da direita]</i></p>

<p align="center">
  <img src="equalizer_escuridao.png" width="700"/>
</p>

<p align="center"><i>Figura 1: Efeito do equalizer na escuridão. [Equalizer na imagem da direita]</i></p>


https://youtu.be/HHbtMV1QBB4
