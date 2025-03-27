//Sistema de Gerenciamento de Faturas de Pagamento
//
//Desenvolver em linguagem de programação C um sistema de gerenciamento de faturas de pagamento utilizando uma árvore binária de busca (BST). O sistema permitirá o cadastro de faturas, a visualização de faturas ordenadas por número de fatura, a busca por faturas específicas, a atualização do status de pagamento das faturas e a remoção de faturas do sistema.
//
//
//
//Descrição do sistema:
//
//Cada fatura será representada por um nó na árvore binária, com os seguintes campos:
//
//Número da Fatura (int): Identificador único da fatura.
//Data de Vencimento (string): Data de vencimento da fatura.
//Valor (float): Valor da fatura.
//Status (string): "pendente" ou "paga".
//Ponteiros para os filhos esquerdo e direito (para estrutura da árvore binária).
//
//
//Operações
//
//Inserção de faturas: O sistema permitirá inserir novas faturas na árvore binária de busca, organizadas por número da fatura.
//Busca de faturas: O sistema permitirá buscar uma fatura específica pelo número da fatura.
//Atualização de status de pagamento: O sistema permitirá alterar o status de uma fatura para "paga" ou "pendente".
//Remoção de faturas: O sistema permitirá remover uma fatura do sistema pela chave de número da fatura, reorganizando a árvore após a remoção.
//Exibição das informações: Listar todas as faturas em ordem crescente sendo exibido o número da fatura, data de vencimento, valor e status de pagamento.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct para iniciar a fatura(nó)
typedef struct Fatura{
  int numFatura;
  char vencimentoFatura[10];
  float valor;
  char status[10];
  struct Fatura *right, *left;
}Fatura;

//função para criar o primeiro nó
struct Fatura* criarUmNo(int numFatura, char* vencimentoFatura, float valorFatura) {
  struct Fatura* novoNo = (struct Fatura*)malloc(sizeof(struct Fatura));

  novoNo -> numFatura = numFatura;
  strcpy(novoNo -> vencimentoFatura, vencimentoFatura);
  novoNo -> valor = valorFatura;
  strcpy(novoNo -> status, "pendente");
  novoNo -> right = NULL;
  novoNo -> left = NULL;
  return novoNo;
}

//Função para inserir um novo nó na arvore
Fatura* inserirNo(Fatura* raiz, int numFatura, char* vencimentoFatura, float valorFatura) {
  if (raiz == NULL) {
    return criarUmNo(numFatura, vencimentoFatura, valorFatura);
  }

  if (numFatura < raiz -> numFatura) {
    raiz -> left = inserirNo(raiz -> left, numFatura, vencimentoFatura, valorFatura);
    return raiz;
  }
  if (numFatura > raiz -> numFatura) {
    raiz -> right = inserirNo(raiz -> right, numFatura, vencimentoFatura, valorFatura);
    return raiz;
  }
  return raiz;
}

//função para imprimir em ordem crescente
void imprimirEmOrdem(Fatura* raiz) {
  if (raiz != NULL) {
    imprimirEmOrdem(raiz -> left);
    printf("%d - %s - %.2f - %s\n", raiz -> numFatura, raiz -> vencimentoFatura, raiz -> valor, raiz -> status);
    imprimirEmOrdem(raiz -> right);
  }
}

//Função para liberar a arvore
void liberarArvore(Fatura* raiz) {
  if (raiz != NULL) {
    liberarArvore(raiz -> left);
    liberarArvore(raiz -> right);
    free(raiz);
  }
}

Fatura* menorValorArvore(Fatura* raiz) {
  Fatura* atual = raiz;
  while (atual && atual -> left != NULL) {
    atual = atual -> left;
  }
  return atual;
}

void opcoes(){
  printf("1 - Inserir Fatura\n");
  printf("2 - Listar Fatura\n");
  printf("3 - Buscar Fatura\n");
  printf("4 - Atualizar Status\n");
  printf("5 - Remover Fatura\n");
  printf("0 - Sair\n");
  printf("Digite a opcao desejada: ");
};
//função para inserir uma nova fatura
Fatura* inserirFatura(Fatura* raiz ){
  int numFatura;
  char vencimentoFatura[10];
  float valorFatura;
  printf("Digite o numero da fatura: ");
  scanf_s("%d", &numFatura);
  printf("Digite a data de vencimento: ");
  scanf_s("%s", vencimentoFatura, 10);
  printf("Digite o valor da fatura: ");
  scanf_s("%f", &valorFatura);
  return inserirNo(raiz, numFatura, vencimentoFatura, valorFatura);
}

void listarFaturas(Fatura *raiz){
  printf("Faturas:\n");
  imprimirEmOrdem(raiz);
  printf("\n");
}

Fatura* buscarFatura(int numeroFatura, Fatura* raiz) {
  //Verifica se a fatura foi encontrada
  if(raiz == NULL) {
    return NULL;
  }
  //Verifica se a fatura foi encontrada e printa os dados
  if(numeroFatura == raiz -> numFatura) {
    printf("Fatura encontrada\n");
    printf("Numero da fatura: %d\n", raiz -> numFatura);
    printf("Data de vencimento: %s\n", raiz -> vencimentoFatura);
    printf("Valor da fatura: %.2f\n", raiz -> valor);
    printf("Status da fatura: %s\n", raiz -> status);
    return raiz;
  }

  //Recursividade para caso a fatura esteja a esquerda ou a direita
  if(numeroFatura < raiz -> numFatura) {
    return buscarFatura(numeroFatura, raiz -> left);
  }else{
    return buscarFatura(numeroFatura, raiz -> right);
  }
}

//função para atualizar as tarefas
void atualizarStatus(int numeroFatura, Fatura* raiz) {
  if (raiz == NULL) {
    printf("Não há faturas cadastradas no sistema!\n");
    return;
  }

  // Armazenando o resultado em uma variável do tipo correto
  Fatura* atual = buscarFatura(numeroFatura, raiz);

  // Verificar se a busca retornou um ponteiro válido
  if (atual == NULL) {
    printf("Fatura não encontrada!\n");
    return;
  }

  // Agora que temos certeza que atual é um ponteiro válido, podemos prosseguir
  if (strcmp(atual->status, "pendente") == 0) {
    strcpy(atual->status, "paga");
    printf("Status da fatura %d atualizado para: paga\n", numeroFatura);
  } else {
    printf("Esta fatura não está pendente. Status atual: %s\n", atual->status);
  }
}

// função para a remoção de um nó
Fatura* removerFatura(Fatura *raiz, int numFatura) {
  // verificamos se o nó é nulo, caso verdadeiro, o retornamos
  if (raiz == NULL) {return raiz;}

  // nesta duas primeiras verificações iremos fazer a busca do nó correto
  if (numFatura > raiz -> numFatura) {
    raiz -> right = removerFatura(raiz -> right, numFatura);
  }else if (numFatura < raiz -> numFatura) {
    raiz -> left = removerFatura(raiz -> left, numFatura);
  } else {
    // assim que o nó for encontrado, iremos verificar as condições dos nós
    // veremos se os nós tem 1 ou 2 filhos e em quais posições eles estão

    // esta verifica se o nó a esquerda é null, e caso verdadeiro, iremos salva-lo em uma outra variável e liberar o nó
    if (raiz -> left == NULL) {
      Fatura* temp = raiz -> right;
      free(raiz);
      return temp;
    }
    // seguirá a mesma lógica do caso do nó a esquerda
    if (raiz -> right ==  NULL) {
      Fatura* temp = raiz -> left;
      free(raiz);
      return temp;
    }
    // aqui é o caso em que se tem 2 filhos
    Fatura* temp = menorValorArvore(raiz -> right);
    // iremos encotrar o melhor valor para se colocar no local do nó que for removido
    // por lógica o melhor nó seria o menor valor dos valores a direita, assim manteriamos uma estrutura balenceada
    raiz -> numFatura = temp -> numFatura;
    strcpy(raiz->vencimentoFatura, temp->vencimentoFatura);
    raiz -> valor = temp -> valor;
    strcpy(raiz->status, temp->status);
    raiz -> right = removerFatura(raiz -> right, temp -> numFatura);
  }

  return raiz;
}


int main(){
  int menu;
  Fatura* raiz = NULL;
  int numFatura;
  while(menu != 0){
    opcoes();
    scanf_s("%d", &menu);
    switch(menu){
      case 1:
        raiz = inserirFatura(raiz);
        break;
      case 2:
        listarFaturas(raiz);
        break;
      case 3:
        printf("Digite o numero da fatura: ");
        scanf_s("%d", &numFatura);
        if(buscarFatura(numFatura, raiz) == NULL){
          printf("Fatura nao encontrada");
          }
        break;
      case 4:
        printf("Digite o numero da fatura: ");
        scanf_s("%d", &numFatura);
        atualizarStatus(numFatura, raiz);
        break;
      case 5:
        printf("Digite o numero da fatura: ");
        scanf_s("%d", &numFatura);
        raiz = removerFatura(raiz, numFatura);
        break;
      case 0:
        break;
      default:
        printf("Numero invalido");
        break;
    };
  };

  return 0;
  };