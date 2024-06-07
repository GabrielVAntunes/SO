
Considere um sistema de detecção de anomalias numa linha de produção baseado em algoritmos de Inteligência Artificial (IA).
As anomalias são detectadas com base em fotografias do produto. Por exemplo, no caso do produto ser um chip, os modelos
de IA irão tentar perceber se o chip tem algum defeito visível. Este algoritmos estão implementados no ficheiro executável
detectAnom que recebe como argumento o caminho para um ficheiro de imagem e escreve no stdout uma linha por cada
defeito encontrado.


1. Escreva a função void defeitos(char* imagens[n], int n, int max) que, para um conjunto de caminhos
para imagens passados num array de n elementos, escreve para o stdout todos os defeitos encontrados. A função deve
desencadear uma procura concorrente, recorrendo ao ficheiro executável detectAnom, nunca excendendo um total de max
processos a executar simultâneamente.


2. Escreva a função void conta(char* imagens[n], int n) que, para um conjunto de caminhos para imagens
passados num array de n elementos, devolve para o stdout o número total de defeitos que foram encontrados. Para resolver
este exercício, deve tirar proveito da função defeitos desenvolvida na alínea anterior e também do comando unix wc -l, o
qual lê linhas do stdin e retorna o número total de linhas para o stdout.