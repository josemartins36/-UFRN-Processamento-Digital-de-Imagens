# motiondetector.cpp — detector de movimento com webcam

Utilizando o programa exemplos/convolucao.cpp como referência, implemente um programa convolucao2.cpp. O programa deverá realizar a convolução com o filtro da média para máscaras de tamanho 11×11e 21×21 pixels. Compare os resultados obtidos com o filtro de tamanho 3×3 pixels.

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
A função [cv::compareHist](https://docs.opencv.org/4.x/d6/dc7/group__imgproc__hist.html#gaf4190090efa5c47cb367cf97a9a519bd) com o [método de Bhattacharyya](https://docs.opencv.org/4.x/d6/dc7/group__imgproc__hist.html#ga994f53817d621e2e4228fc646342d386) mede a similaridade entre os histogramas. Se a diferença for maior que um limiar definido, é detectado um movimento.

```cpp
double diff = cv::compareHist(prevHist, currHist, cv::HISTCMP_BHATTACHARYYA);
            
if (diff > limiar) {
  cv::putText(frame, "MOVIMENTO DETECTADO!", cv::Point(50,50),
  cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255), 2);
  std::cout << "Movimento detectado! Diferença = " << diff << std::endl;
}
```
Esse limiar de sensibilidade foi testado manualmente visando alcançar o melhor resultado de detecção de movimento — nem muito pequeno ao ponto de ruído ser considerado movimento, nem tão grande ao ponto de não detectar movimentos bruscos na webcam.
```cpp
double limiar = 0.01;  // sensibilidade do detector
```

## Resultados

Durante a [execução do programa](https://youtu.be/HHbtMV1QBB4), é possível observar que, ao haver uma mudança significativa na cena capturada pela webcam (como movimentar as mãos e os dedos), o histograma do frame muda o suficiente para ultrapassar o limiar estabelecido. Com isso, o programa detecta o movimento e imprime o alerta visual e no console.
