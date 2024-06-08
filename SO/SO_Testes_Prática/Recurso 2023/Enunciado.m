Considere uma empresa que utiliza um único ficheiro em formato binário para armazenar todos os registos individuais dos seus
funcionários. Cada registo contém o nome, cargo e salário na empresa de um funcionário, de acordo com a seguinte estrutura:

struct RegistoF {
char nome[20];
char cargo[20];
int salário;
};

1. Escreva a função void aumentaSalarios(char* ficheiro, char* cargo, int valor, long N, int
P) que atualiza o ficheiro com N registos de forma aumentar em valor o salário dos funcionários com um dado cargo.
Valorização: A função deve desencadear uma atualização concorrente com P processos.

2. Escreva a função int validaSalarios(char* ficheiro, char* cargo) que valida o salário de todos os fun-
cionários com um dado cargo. A função deve retornar 1 caso algum funcionário receba menos do que o salário mínimo. Caso
contrário, deve retornar 0. Para resolver este exercício, deve tirar proveito dos seguintes ficheiros executáveis:

• ./filtraCargo <ficheiro> <cargo> - procura no ficheiro de registos os funcionários de um dado cargo
e escreve para o stdout os respectivos registos.

• ./validaMin - lê registos do stdin, no mesmo formato produzido pelo ficheiro executável filtraCargo, e termina
com código de saída 1, caso algum funcionário receba menos que o salário mínimo, ou 0 caso contrário.