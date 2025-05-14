# labeling.cpp — preenchendo regiões com OpenCV

Observando-se o programa [labeling.cpp](https://agostinhobritojr.github.io/tutorial/pdi/labeling.html) como exemplo, é possível verificar que caso existam mais de 255 objetos na cena, o processo de rotulação poderá ficar comprometido, visto que o tipo de dado usado para suportar imagens cinzentas permitem armazenar apenas um byte por pixel. Identifique a situação em que isso ocorre e proponha uma solução para este problema.

Aprimore o algoritmo de contagem apresentado para identificar regiões com ou sem buracos internos que existam na cena. Assuma que objetos com mais de um buraco podem existir. Inclua suporte no seu algoritmo para não contar bolhas que tocam as bordas da imagem. Não se pode presumir, a priori, que elas tenham buracos ou não.

<p align="center">
  <img src="bolhas.png" width="500"/>
</p>

<p align="center"><i>Figura 1: Imagem bolhas.</i></p>

---
