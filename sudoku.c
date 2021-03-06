#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  

for(int i = 0; i < 9 ; i++ ){
  int *validar_fila =calloc(10,sizeof(int));
  for(int j = 0 ; j <9;j++){
    if(validar_fila[n->sudo[i][j]]) return 0;
    if(validar_fila[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0){
      validar_fila[n->sudo[i][j]] = 1;
    }
  }
}

for(int x = 0; x < 9 ; x++ ){
  int *validar_colum =calloc(10,sizeof(int));
  for(int z = 0 ; z <9 ; z++){
    if(validar_colum[n->sudo[z][x]] != 0) return 0;
    if(validar_colum[n->sudo[z][x]] == 0 && n->sudo[z][x] != 0){
     validar_colum[n->sudo[z][x]] = 1; 
    }
  }
}

for(int b = 0; b < 9 ; b++ ){
  int *validar_matrix =calloc(10,sizeof(int));
  int k = b , p;
   for( p = 0 ; p < 9 ; p++){
     int i=3*(k/3) + (p/3) ;
     int j=3*(k%3) + (p%3) ;
     if(validar_matrix[n->sudo[i][j]] != 0) return 0;
     if(validar_matrix[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0){
      validar_matrix[n->sudo[i][j]] = 1;
     }
   }
}
    return 1;
}


List* get_adj_nodes(Node* n){
  
 List* list=createList();
 int numero = 1;

  for( int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){

      if( n -> sudo[i][j] == 0){
       Node* aux = createNode();

        while(numero < 10){
        aux = copy(n);
        aux -> sudo[i][j] = numero;
        if(is_valid(aux))
        pushBack(list,aux);
        numero++;
        }
      }
    }
  }
    return list;
}


int is_final(Node* n){
  int i;
  int j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[i][j]==0)
        return 0;
    }
  }
    return 1;
}


Node* DFS(Node* initial, int* cont){
  Stack * S = createStack();
  push(S,initial);

  while(get_size(S) != 0){
    Node * aux = top(S);
    pop(S);     
    if(is_final(aux))
      return aux;
    List * adj = get_adj_nodes(aux);
    Node * lista_aux = first (adj);
    while(lista_aux){
      push(S,lista_aux);
      lista_aux = next(adj);
    }
    free(aux);
    cont++;
  }
return NULL; 
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/