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

int is_valid(Node* n){\
   for (int i = 0; i < 9; i++) {
        int row_check[10] = {0};
        int col_check[10] = {0};
        for (int j = 0; j < 9; j++) {
            // Verificar filas
            if (n->sudo[i][j] != 0 && row_check[n->sudo[i][j]] == 1)
                return 0;
            row_check[n->sudo[i][j]] = 1;
            // Verificar columnas
            if (n->sudo[j][i] != 0 && col_check[n->sudo[j][i]] == 1)
                return 0;
            col_check[n->sudo[j][i]] = 1;
        }
    }

    // Verificar subcuadros 3x3
    for (int block_row = 0; block_row < 9; block_row += 3) {
        for (int block_col = 0; block_col < 9; block_col += 3) {
            int block_check[10] = {0};
            for (int i = block_row; i < block_row + 3; i++) {
                for (int j = block_col; j < block_col + 3; j++) {
                    if (n->sudo[i][j] != 0 && block_check[n->sudo[i][j]] == 1)
                        return 0;
                    block_check[n->sudo[i][j]] = 1;
                }
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
   int row = -1, col = -1;
   for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1 && col != -1)
            break;
    }
    if (row == -1 && col == -1) {
        return list;
    }
    for (int num = 1; num <= 9; num++){
        if (is_valid(n)){
            Node* adj_node = copy(n);
            adj_node->sudo[row][col] = num;
            pushBack(list, adj_node);
        }
    }
   
    return list;
}


int is_final(Node* n){
   
    for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
             if (n->sudo[i][j] == 0)
                 return 0; // No es final
         }
     }
     return 1; 
}

Node* DFS(Node* initial, int* cont){
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