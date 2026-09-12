### pg. 23


Explica o caminho completo desde um ficheiro Fashion-MNIST em disco até à classe prevista.

Tenta responder tu primeiro, em 4–6 linhas. Quero ver se consegues incluir estas seis palavras/conceitos:

data representation
preprocessing
input tensor
LiteRT runtime
output tensor
interpretation


---

Primeiro lemos a data representation do Fashion-MNIST, em uint8, com imagens 28×28. Depois fazemos o preprocessing, convertendo para float32 e normalizando os píxeis para o intervalo esperado pelo modelo. Em seguida colocamos os dados no input tensor e usamos o LiteRT runtime para executar a inferência. O modelo produz um output tensor com 10 scores, um por classe. Por fim fazemos a interpretation, escolhendo a classe com maior score e comparando-a com a label verdadeira.

---

