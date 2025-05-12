# regions.cpp — Seleção e Negativo de Região em Imagens com OpenCV

Utilizando o programa da Listagem 4, “pixels.cpp” como referência, implemente um programa `regions.cpp`. Esse programa deverá solicitar ao usuário as coordenadas de dois pontos `P1` e `P2` localizados dentro dos limites do tamanho da imagem e exibir a imagem que lhe for fornecida. Entretanto, a região definida pelo retângulo de vértices opostos definidos pelos pontos `P1` e `P2` será exibida com o **negativo** da imagem na região correspondente.

<p align="center">
  <img src="exemplo_negativo.png" width="500"/>
</p>

<p align="center"><i>Figura: Região retangular com efeito negativo aplicada na imagem original.</i></p>

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
