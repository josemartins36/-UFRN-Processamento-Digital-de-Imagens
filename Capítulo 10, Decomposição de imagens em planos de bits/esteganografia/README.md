# esteganografia.cpp — Imagem oculta usando bits menos significativos com OpenCV

Usando o programa bitplanes.cpp como [referência](https://agostinhobritojr.github.io/tutorial/pdi/bitplanes.html) para esteganografia, escreva um programa que recupere a imagem codificada de uma imagem resultante de esteganografia. Lembre-se que os bits menos significativos dos pixels da imagem fornecida deverão compor os bits mais significativos dos pixels da imagem recuperada. O programa deve receber como parâmetros de linha de comando o nome da imagem resultante da esteganografia. Teste a sua implementação com a imagem da Figura 28, “Imagem codificada” (desafio-esteganografia.png).

<p align="center">
  <img src="desafio-esteganografia.png" width="500"/>
</p>

<p align="center"><i>Figura 1: Imagem codificada.</i></p>

---
## Descrição da Tarefa

O objetivo desta tarefa é desenvolver um programa chamado `esteganografia.cpp` que recupere uma imagem escondida nos bits menos significativos de uma imagem esteganografada, com as seguintes funcionalidades:

- Carregar uma imagem esteganografada (`imagem_esteganografada.png`).
- Extrair os 3 bits menos significativos de cada componente de cor (R, G, B) e colocá-los nos bits mais significativos da imagem recuperada.
- Salvar a imagem recuperada em um arquivo chamado `imagem_recuperada.png`.

---
