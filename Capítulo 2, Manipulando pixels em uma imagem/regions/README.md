# regions.cpp — Seleção e Negativo de Região em Imagens com OpenCV

Utilizando o programa da Listagem 4, “pixels.cpp” como referência, implemente um programa `regions.cpp`. Esse programa deverá solicitar ao usuário as coordenadas de dois pontos `P1` e `P2` localizados dentro dos limites do tamanho da imagem e exibir a imagem que lhe for fornecida. Entretanto, a região definida pelo retângulo de vértices opostos definidos pelos pontos `P1` e `P2` será exibida com o **negativo** da imagem na região correspondente.

<p align="center">
  <img src="exemplo_negativo.png" width="500"/>
</p>

<p align="center"><i>Figura 1: Região retangular com efeito negativo aplicada na imagem original.</i></p>

---

## Descrição da Tarefa

Inspirado na **Listagem 4 ("pixels.cpp")** de um material de estudo sobre acesso a pixels com OpenCV, o objetivo desta tarefa é desenvolver um programa chamado `regions.cpp` com as seguintes funcionalidades:

- Carregar uma imagem (`papagaio.png`) em modo **grayscale**.
- Solicitar ao usuário dois pontos (`P1(x1, y1)` e `P2(x2, y2)`) que definem um retângulo dentro da imagem.
- Aplicar o **efeito negativo** (inversão dos tons de cinza) apenas na região interna ao retângulo.
- Exibir a imagem modificada em uma janela.

---

## Trechos-chave do código

### 1. Carregamento da imagem
Este trecho usa a função cv::imread para abrir o arquivo "papagaio.png" no modo IMREAD_GRAYSCALE, ou seja, convertendo a imagem para tons de cinza. Cada pixel passa a ser representado por um valor entre 0 (preto) e 255 (branco), facilitando operações de processamento.

```cpp
cv::Mat image = cv::imread("papagaio.png", cv::IMREAD_GRAYSCALE);
if (!image.data) {
    std::cout << "Erro ao abrir a imagem!" << std::endl;
    return -1;
}
```

### 2. Leitura dos pontos P1 e P2 fornecidos pelo usuário 
Essas linhas solicitam ao usuário que digite as coordenadas dos pontos P1 e P2, que serão usados para definir uma região retangular da imagem. Cada ponto é representado por dois inteiros (x, y). Esses pontos são os vértices opostos do retângulo onde será aplicado o efeito de negativo. 

```cpp
int x1, y1, x2, y2;
std::cout << "Digite as coordenadas de P1 (x y): ";
std::cin >> x1 >> y1;

std::cout << "Digite as coordenadas de P2 (x y): ";
std::cin >> x2 >> y2;
```

### 3. Aplicação do negativo na região delimitada
Esse trecho percorre a região retangular definida pelos pontos P1 e P2. Em cada iteração, o valor do pixel na posição (i, j) é acessado com image.at<uchar>(i, j) e substituído por seu negativo (255 - valor). O resultado é a inversão dos tons de cinza naquela área, criando o efeito visual de negativo fotográfico apenas dentro da área selecionada.

```cpp
for (int i = ymin; i <= ymax; i++) {
    for (int j = xmin; j <= xmax; j++) {
        image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
    }
}
```
---

## Resultados
<p align="center">
  <img src="./build/papagaio.png" width="500"/>
</p>

<p align="center"><i>Figura 2: Imagem original.</i></p>

<p align="center">
  <img src="./build/imagem_editada.png" width="500"/>
</p>

<p align="center"><i>Figura 3: Imagem editada.</i></p>



