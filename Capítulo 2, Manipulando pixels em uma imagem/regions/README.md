# regions.cpp — Seleção e Negativo de Região em Imagens com OpenCV

Este projeto apresenta um programa em C++ que, utilizando a biblioteca OpenCV, permite ao usuário selecionar dois pontos dentro de uma imagem em tons de cinza e aplicar o efeito de **negativo** sobre a região retangular delimitada por esses pontos.

---

## Descrição da Tarefa

Inspirado na **Listagem 4 ("pixels.cpp")** de um material de estudo sobre acesso a pixels com OpenCV, o objetivo desta tarefa é desenvolver um programa chamado `regions.cpp` com as seguintes funcionalidades:

- Carregar uma imagem (`bolhas.png`) em modo **grayscale**.
- Solicitar ao usuário dois pontos (`P1(x1, y1)` e `P2(x2, y2)`) que definem um retângulo dentro da imagem.
- Aplicar o **efeito negativo** (inversão dos tons de cinza) apenas na região interna ao retângulo.
- Exibir a imagem modificada em uma janela.

---

## Efeito Negativo

O efeito negativo é obtido invertendo o valor de cada pixel da região selecionada:

```cpp
image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
