# filestorage.cpp — Análise de Precisão na Representação de Imagens PNG versus YML

Utilizando o programa-exemplo filestorage.cpp como base, crie um programa que gere uma imagem de dimensões 256x256 pixels contendo uma senóide de 4 períodos com amplitude igual 127 desenhada na horizontal, semelhante àquela apresentada na Figura 11, “Saída do programa filestorage”. Grave a imagem no formato YML e também em formato PNG, como faz o programa-exemplo. Compare os arquivos gerados, extraindo uma linha correspondente de cada imagem gravada e comparando a diferença entre elas. Trace um gráfico da diferença calculada ao longo da linha correspondente extraída nas imagens. O que você observa? Por que isso acontece?

## Descrição da Tarefa

Inspirado na abordagem do exemplo `filestorage.cpp` no material de estudo, o objetivo desta tarefa é desenvolver um programa com as seguintes funcionalidades:

- Gerar uma imagem de **256x256 pixels** contendo uma **senóide com 4 períodos e amplitude 127**, desenhada horizontalmente.
- Salvar a imagem nos seguintes formatos:
  - **YML**, utilizando `cv::FileStorage`.
  - **PNG**, utilizando `cv::imwrite`.
- Recarregar as imagens gravadas nos dois formatos.
- **Extrair uma linha (linha central, por exemplo, a linha 128)** de cada imagem.
- Calcular a **diferença absoluta** entre os valores dos pixels das duas linhas extraídas.
- Exibir um **gráfico da diferença** ao longo da linha comparada.

---

## Trechos-chave do código

### 1. Geração da senóide
A geração da senoide na horizontal (varia com i, constante em j) ->float value = 127 * std::sin(2 * M_PI * PERIODOS * **i** / SIDE) + 128;

```cpp
for (int i = 0; i < SIDE; ++i) {
  float value = 127 * std::sin(2 * M_PI * PERIODOS * i / SIDE) + 128;
  for (int j = 0; j < SIDE; ++j) {
    image.at<float>(i, j) = value;
  }
}

```

```cpp
cv::FileStorage fs("senoide_horizontal-256.yml", cv::FileStorage::WRITE);
fs << "mat" << image;
fs.release();
```
