#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define maxsizestring 20
#define maxbranchs 3

int caminho;

typedef struct data{
  int codigo;
  char nome[maxsizestring];
}data;

typedef struct no{
  data* value;
  no* back;
  no *next[maxbranchs];
}node;

typedef struct arvere{
  node* root;
  int tamanho;
}tree;

int caminhoglobal;

data* insert_data();
bool insert_node(tree* target,node* valor);
node* create_node(data* valor);
void print_tree(node* root);
void print_data(data*valor);
node* acha_caminho(node* corrente,int path,node* valor);
bool search(node* root);
bool found_key(node* raiz, int key);
int path_menu(node* current);
int options_menu();

int main(){

  arvere teste;
  teste.root = NULL;
  teste.tamanho = 0;
  int option;

  do{
    option = options_menu();
    switch(option){
      case 1:
        insert_node(&teste,create_node(insert_data()));
      break;
      case 2:
        print_tree(teste.root);
        system("pause");
      break;
      case 3:
        search(teste.root);
      break;
    }
  }while(option!=0);
  system("pause");

}

int options_menu(){
  int option;
  do{
    system("cls");
    printf("\n1: Inserir dados na arvore");
    printf("\n2: Imprimir arvore inteira");
    printf("\n3: Pesquisar codigo na arvore");
    printf("\n0: Sair\n");
    scanf("%d",&option);
    if(0>option>4){
    printf("\nopcao invalida");
    system("pause");
    }
  }while(0>option>4);
  return option;
}


bool search(node* root){
    int codigo;
    bool achou = 0;
    printf("\n digite o codigo a buscar:\t");
    scanf("%d",&codigo);
    printf("\n-----%d-----", achou);
    achou = found_key(root,codigo);
    printf("\n-----%d-----", achou);
    if(achou==1)    printf("\ncodigo encontrado");
    else printf("\ncodigo nao encontrado");
    system("pause");
    return achou;
}

//função que percorre a arvore apartir de sua raiz e retorna true se achou o codigo
bool found_key(node* raiz, int key){
  if(raiz->value->codigo==key) {
    printf("\no nome do codigo %d eh: %s",key, raiz->value->nome);
    return true;
  }
  else{
    for(int i=0; i<maxbranchs;i++){
      if(raiz->next[i] != NULL )  return found_key(raiz->next[i], key);
    }
  }
}

//imprime um nó e seus filhos
void print_node(node* current){
  if(current!=NULL){
    printf("\n no pai:");
    print_data(current->value);
    for(int i=0; i<maxbranchs;i++){
      printf("\nfilho%d:",i+1);
      if(current->next[i]!=NULL) print_data(current->next[i]->value);
      else printf("\tvazio");
    }
  }
}

/*
  imprime a arvore inteira
  parametro: raiz da arvore
*/
void print_tree(node* root){
  print_data(root->value);
  for(int i=0; i<maxbranchs;i++){
    if(root->next[i]!=NULL) print_tree(root->next[i]);
  }
}

//imprime dados individualmente
void print_data(data* valor){
  printf("\ncodigo: %d ", valor->codigo);
  printf("\nnome: %s ", valor->nome);
}


node* acha_caminho(node* corrente,int path,node* valor){

  if(corrente==NULL){
    corrente = valor;
    return valor;
  }
  if(path==maxbranchs){
    caminhoglobal = path_menu(corrente);
    return acha_caminho(corrente,caminhoglobal,valor);
  }
  if(path==-1) acha_caminho(corrente->back,path_menu(corrente->back),valor);
  else{
    corrente->next[path] = acha_caminho(corrente->next[path],path_menu(corrente),valor);
    valor->back = corrente;
  }
  
}

/*
  insere um nó em uma arvore
  parametros:
    1° - ponteiro para estrutura de arvore contendo a raiz
    2° - node a ser inserido
*/
bool insert_node(tree* target,node* valor){
  bool inseriu = false;
  if(target->root == NULL){
    target->root = valor;
    target->tamanho++;
    printf("novo no inserido na raiz: ");
    print_data(target->root->value);
    inseriu = true;
  }
  else{
    if(acha_caminho(target->root,maxbranchs,valor) == valor){
       inseriu = true;
       target->tamanho++;
    }
  }
  return inseriu;
}


// imprime opções de caminho e devolve caminho selecionado (-1 para voltar)
int path_menu(node *current){  
  int option;


  do{
    system("cls");
    print_node(current);
    printf("\nselecione um caminho:\n");
    for(int i=0; i<maxbranchs;i++){
      printf("%d, ", i+1 );
    }    
    printf("\n 0 para voltar");

    scanf("%d",&option);
    if(0>option>maxbranchs){
      printf("\nopcao invalida");
      system("pause");
    }

  }while(0>option>maxbranchs);

  return option - 1;
}

/*
  cria nó a partir de um ponteiro de dados
  parametro:
    ponteiro para dado a ser inserido
*/
node* create_node(data* value){
  node *new_node;
  new_node = (node*)malloc(sizeof(node));
  new_node->value = value;
   for(int i=0; i<maxbranchs;i++){
     new_node->next[i] = NULL;
   }
  new_node->back = NULL;
  return new_node;
}

// insere valores na estrutura de dados e retorna seu ponteiro
data* insert_data(){
    data *new_data;
    new_data = (data*)malloc(sizeof(data));
    printf("\nescreva o nome:");
    scanf("%s",&new_data->nome);
    printf("\ndigite o codigo:");
    scanf("%d",&new_data->codigo);
    return new_data;
}