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

## Trechos-chave do código

### 1. Carregamento da imagem

O código carrega a imagem esteganografada usando a função `cv::imread`. Caso a imagem não seja carregada corretamente, o programa exibe uma mensagem de erro.

```cpp
cv::Mat imagemEsteganografada = cv::imread(argv[1], cv::IMREAD_COLOR);
if (imagemEsteganografada.empty()) {
    std::cout << "Erro ao carregar a imagem." << std::endl;
    return -1;
}
```

### 2. Recuperação dos bits menos significativos
O programa percorre cada pixel da imagem esteganografada e recupera os 3 bits menos significativos (LSB) de cada componente de cor (R, G, B), movendo-os para os bits mais significativos.

```cpp
for (int i = 0; i < imagemEsteganografada.rows; i++) {
    for (int j = 0; j < imagemEsteganografada.cols; j++) {
        pixelEsteganografado = imagemEsteganografada.at<cv::Vec3b>(i, j);

        for (int c = 0; c < 3; c++) {
            unsigned char lsb = pixelEsteganografado[c] & ((1 << nbits) - 1); // máscara para nbits
            pixelRecuperado[c] = lsb << (8 - nbits);
        }

        imagemRecuperada.at<cv::Vec3b>(i, j) = pixelRecuperado;
    }
}
```

### 3. Salvamento da imagem recuperada
```cpp
cv::imwrite("imagem_recuperada.png", imagemRecuperada);
std::cout << "Imagem recuperada salva como imagem_recuperada.png" << std::endl;
```

## Resultados
Após a execução do programa, a imagem recuperada foi gerada com sucesso. Durante o processo, os 3 bits menos significativos (LSB) de cada pixel da imagem esteganografada foram extraídos e reposicionados nos bits mais significativos, revelando assim a imagem oculta que estava escondida.

<p align="center">
  <img src="./build/exemplo_trocaregioes.png" width="500"/>
</p>

<p align="center"><i>Figura 1: Troca dos quadrantes diagonais na imagem original.</i></p>
