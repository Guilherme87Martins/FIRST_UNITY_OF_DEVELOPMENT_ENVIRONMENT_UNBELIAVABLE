#include <stdio.h> // Biblioteca para Input e Output
#include <stdlib.h> //Biblioteca para gerenciamento de alocação de memória
#include <string.h> //Biblioteca para Manipulação de Strings

#define MAXIMO 50
#define LETRAS 20


//Metodo Ordenação utilizado BubbleSort
void bubbleSort(char e[][LETRAS], int n) {
  int i, j;
  char muda[LETRAS];
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (strcmp(e[j], e[j + 1]) > 0) {
        strcpy(muda, e[j]);
        strcpy(e[j], e[j + 1]);
        strcpy(e[j + 1], muda);
      }
    }
  }
}


//Método de pesquisa Binaria, onde trabalha dividindo o codigo ao meio para localizar com mais agilidade o item pesquisado 
void pesquisaBinaria(char e[][LETRAS], int tamanho, char *item) {
  int inicio = 0;
  int fim = tamanho - 1;
  int meio;
  int encontrado = 0;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (strcmp(e[meio], item) == 0) {
      printf("Item encontrado na posição %d.\n", meio);
      encontrado = 1;
      break;
    } else if (strcmp(e[meio], item) < 0) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }

  if (!encontrado) {
    printf("Item não encontrado.\n");
  }
}


//Menu de Exibição, para escolha do tipo de lista que será acrescentado
int menu() {
  int escolha = 0;
  printf("||==============================||\n");
  printf("||                              ||\n");
  printf("||____ESCOLHA UM TEMA ABAIXO____||\n");
  printf("||____(1) CARROS________________||\n");
  printf("||____(2) MÚSICAS_______________||\n");
  printf("||____(3) JOGOS_________________||\n");
  printf("||                              ||\n");
  printf("||==============================||\n");
  
  // Verifica se a escolha abaixo está compatível com o Menu acima:
  while (escolha == 0) {
    printf("\nQual sua escolha?\n");
    scanf("%d", &escolha);
    if (escolha != 3 && escolha != 2 && escolha != 1) {
      printf("Essa não é uma escolha válida!! Digite novamente");
      escolha = 0;
      //limpar o buffer Scanf
      scanf("%*[^\n]");
      system("clear");
    } 
  }
  // Limpa o console;
  system("clear");
  return escolha;
}

// Exibe a escolha selecionada
char* exibirEscolha(int escolha) {
  switch (escolha) {
    case 1:
      return "CARROS";
    case 2:
      return "MÚSICAS";
    case 3:
      return "JOGOS";
    default:
      return "Escolha incorreta!";
  }
}


// Cria a lista com base na escolha selecionada (Não faz verificação)
char* criarLista(char func[]) {
  int opcao = 1;
  char itens[MAXIMO][LETRAS] = { };
  //aloca espaço na memória para criação da lista
  char* lista = malloc(500 * sizeof(char));
  int tamanhoMaximo = 0;
  printf("Fique à vontade para listar os itens do tema *%s* que irá compor a sua lista!!\n", func);

  while (opcao == 1 && tamanhoMaximo < MAXIMO) {
    if(tamanhoMaximo == 0) {
      printf("Digite o item de sua escolha: ");
      scanf("%s", itens[tamanhoMaximo]);
      scanf("%*[^\n]");
      tamanhoMaximo++;
    } else if (tamanhoMaximo != 0) {
      printf("Digite o próximo item da lista: ");
      scanf("%s", itens[tamanhoMaximo]);
      scanf("%*[^\n]");//Limpa o buffer
      tamanhoMaximo++;
    }
    printf("Deseja continuar adicionando itens? [0 = NÃO, 1 = SIM]: ");
    scanf("%d", &opcao);
    scanf("%*[^\n]");
  }
  // '\0' simboliza null dentro de uma string
  lista[0] = '\0'; // Inicializa a lista vazia
  
  system("clear");
  for (int i = 0; i < tamanhoMaximo; i++) {
    strcat(lista, itens[i]);
    if(i < tamanhoMaximo - 1) {
      strcat(lista, "\n");
    }
  }
  return lista;
}


//Exibe a lista na tela
void exibeLista(char lista[]) {
  printf("\n LISTA: \n%s", lista);
}

// Printar a lista
void exibirListaOrdenada(char e[][LETRAS], int tamanho) {
  printf("\n\nLista após a ordenação:\n");
  for (int i = 0; i < tamanho; i++) {
    printf("%s \n", e[i]);
  }
  printf("\n");
}


// Recebe a lista digitada e separa em tokens para criação de uma nova Lista
void separarItens(char lista[], char itens[][LETRAS], int *tamanho) {
  char* token = strtok(lista, "\n");
  //enquanto o token (que utiliza como delimitador \n) for diferente de NULL ('\0') e tamanho menor que MAXIMO(50), copia     os dados de token para itens[tamanho]
  while (token != NULL && *tamanho < MAXIMO) {
    strcpy(itens[*tamanho], token);
    token = strtok(NULL, "\n");
    (*tamanho)++;
  }
}

//Cria o metodo Fila para a Lista
// Fila: First In First Out, Primeiro a entrar será o primeiro a sair!
void interagirFila(char elementos[][LETRAS], char* escolha, int tamanho, char* item) {
  int opcao;
  do {
    system("clear");
    printf("\n1 - Incluir elemento na fila.\n");
    printf("2 - Remover elemento na fila.\n");
    printf("3 - Exibir a fila.\n");
    printf("4 - Aplicar Organizador para os novos itens.\n");
    printf("5 - Procurar item.\n");
    printf("0 - Sair.\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
      case 1:
        if (tamanho < MAXIMO) {
          printf("Digite o item do tipo %s para adicionar à lista: ", escolha);
          scanf("%s", elementos[tamanho]);
          tamanho++;
          printf("Elemento adicionado com sucesso!\n");
        } else {
          printf("A lista está cheia. Não é possível adicionar mais elementos.\n");
        }
        break;
      case 2:
        if (tamanho > 0) {
          printf("Removendo o primeiro elemento da lista: %s\n", elementos[0]);
          for (int i = 0; i < tamanho - 1; i++) {
            strcpy(elementos[i], elementos[i + 1]);
          }
          tamanho--;
        } else {
          printf("A lista está vazia. Não é possível remover elementos.\n");
        }
        break;
      case 3:
        printf("Conteúdo da lista:\n");
        exibirListaOrdenada(elementos, tamanho);
        break;
      case 4:
        bubbleSort(elementos, tamanho);
        printf("Lista Organizada com Sucesso!.\n");
        break;
      case 5:
        printf("Digite o item a ser procurado!\n");
        scanf("%s", item);
        if(item != 0) {
          pesquisaBinaria(elementos, tamanho, item);
        }
        break;
      case 0:
        printf("Saindo do menu de interação da fila.\n");
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
        break;
    }
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
    getchar(); // Aguarda a entrada de um caractere antes de limpar a tela
    system("clear");
  } while (opcao != 0);
}


//Cria o metodo de Pilha para o metodo
//Pilha: First In Last Out, Primeiro a entrar vai ser o ultimo a sair, ou, ultimo a entrar será o primeiro a sair!!
void interagirPilha(char elementos[][LETRAS], char* escolha, int tamanho, char* item) {
  int topo = tamanho;
  int opcao;
  do {
    system("clear");
    printf("\n1 - Incluir elemento na pilha.\n");
    printf("2 - Remover elemento da pilha.\n");
    printf("3 - Exibir a pilha.\n");
    printf("4 - Aplicar organizador para os novos itens.\n");
    printf("5 - Procurar item\n");
    printf("0 - Sair.\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
      case 1:
        if (topo < MAXIMO) {
          printf("Digite o item do tipo %s para adicionar à pilha: ", escolha);
          for (int i = topo; i > 0; i--) {
              strcpy(elementos[i], elementos[i - 1]);
          }
          scanf("%s", elementos[0]);
          (topo)++;
          printf("Elemento adicionado com sucesso!\n");
        } else {
          printf("A pilha está cheia. Não é possível adicionar mais elementos.\n");
        }
        break;
      case 2:
        if (topo > 0) {
          printf("Removendo o elemento do topo da pilha: %s\n", elementos[topo - 1]);
          (topo)--;
        } else {
          printf("A pilha está vazia. Não é possível remover elementos.\n");
        }
        break;
      case 3:
        printf("Conteúdo da pilha:\n");
        //for (int i = topo - 1; i >= 0; i--) {
          //printf("%s\n", elementos[i]);
        //}
        exibirListaOrdenada(elementos, topo);
        break;
      case 4:
        bubbleSort(elementos, topo);
        printf("Pilha organizada com sucesso!\n");
        break;
      case 5:
        printf("Digite o item a ser procurado!\n");
        scanf("%s", item);
        if(item != 0) {
          pesquisaBinaria(elementos, tamanho, item);
        }
        break;
      case 0:
        printf("Saindo do menu de interação da pilha.\n");
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
        break;
    }
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
    getchar(); // Aguarda a entrada de um caractere antes de limpar a tela
    system("clear");
  } while (opcao != 0);
}


//Metodo Principal, roda os metodos acima, responsável por fazer o codigo funcionar!!
int main(void) {
  int i;
  int topo = 0;
  int metodo = 0;
  int tamanho = 0;
  char item[LETRAS];
  // Exibe a escolha do usuário conforme o tema escolhido
  int escolha = menu();
  char* tema = exibirEscolha(escolha);
  printf("Tema escolhido: %s\n", tema);

  // Cria a lista com base no tema escolhido
  char* lista = criarLista(tema);
  printf("\nLista antes da ordenação:\n");
  // Separa os itens da lista
  char itens[MAXIMO][LETRAS] = {};
  separarItens(lista, itens, &tamanho);
  system("clear");
  printf("================================================================================");
  printf("\nEscolha o método para estruturação dos itens que serão adicionados a lista!!\n");
  printf("================================================================================");
  printf("\n 0 = Fila, 1 = Pilha\n");
  scanf("%d", &metodo);
  if(metodo == 0) {
    interagirFila(itens, tema, tamanho, item);
  } else if(metodo == 1) {
    interagirPilha(itens, tema, tamanho, item);
  }
}