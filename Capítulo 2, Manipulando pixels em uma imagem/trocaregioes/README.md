# trocaregions.cpp — Troca de quadrantes diagonais com OpenCV

Utilizando o programa da **Listagem 4**, “pixels.cpp” como referência, implemente um programa `trocaregions.cpp`. Seu programa deverá trocar os quadrantes em diagonal na imagem. Explore o uso da classe `cv::Mat` e seus construtores para criar as regiões que serão trocadas. O efeito é ilustrado na Figura 1, “Exemplo de saída do programa trocaregions.cpp”. Assuma que a imagem de entrada tem dimensões múltiplas de 2 para facilitar a implementação do processo de troca.

<p align="center">
  <img src="exemplo_trocaregioes.png" width="500"/>
</p>

<p align="center"><i>Figura 1: Troca dos quadrantes diagonais na imagem original.</i></p>

---
## Descrição da Tarefa

Inspirado na **Listagem 4 ("pixels.cpp")** do material de estudo sobre acesso a pixels com OpenCV, o objetivo desta tarefa é desenvolver um programa chamado `trocaregions.cpp` com as seguintes funcionalidades:

- Carregar uma imagem (`imagem.jpg`) em modo **colorido**.
- Dividir a imagem em quatro quadrantes iguais.
- Trocar os quadrantes em diagonal:  
  - superior esquerdo ↔ inferior direito  
  - superior direito ↔ inferior esquerdo
- Exibir a imagem modificada em uma janela.

---
