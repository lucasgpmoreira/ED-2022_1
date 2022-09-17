#include<stdio.h>
#include<stdlib.h>

#define ERRO        0
#define OK          1

#define CAPACIDADE  10

#define F           0
#define V           1

/*******************************************************************************
  Função auxiliar para escrever os elementos de um vector no ecrã.
*/
void print_vector(int *v, int tam){
  int i;
  printf("[");
  for(i=0; i<tam; i++)
    printf("%d ", v[i]);
  printf("]\n");  
}

/*******************************************************************************
  Inserção ordenada num vector ordenado
  
    -> Entradas:
                
        n:     valor a inserir no vector
        
        vec:   o vector (ou um ponteiro para o seu início)
        
        elems: o número de elementos úteis do vector antes da inserção
               (a função deve actualizar este valor, por isso é passado
               por referência)
               
        cap:   a capacidade máxima do vector
         
    <- Saída:
             
        ERRO:  se o vector estiver cheio        
        OK:    se conseguir inserir com sucesso
*/
int inserir(int n, int vec[], int *elems, int cap){
    int i, j;

    /* Se o vector estiver cheio não insere */
    if (*elems == cap) return ERRO;

    /* Se o vector está vazio insere n na primeira posição, actualiza 
     o número de elementos do vector e termina */
    if (*elems == 0){
        vec[0] = n;
        (*elems)++;
        return OK;
    }

    /* Percorre o vector até encontrar o primeiro elemento maior que n */
    for(i = 0; i < (*elems); i++)
          if(vec[i] > n) break;

    /* Desloca uma posição para a direita todos os valores maiores que n */
    for(j = (*elems); j > i; j--)
          vec[j] = vec[j-1];

    /* (!) Neste ponto, i == j e ambos indexam correctamente a posição
    onde deve ser inserido o valor n */

    /* Insere n na posição correcta, actualiza o número de elementos 
    do vector e termina */
    vec[i] = n;
    (*elems)++;
    return OK;
}

/*******************************************************************************
  Remoção ordenada num vector ordenado
  
    -> Entradas:
                
        n:     valor a remover do vector (se houver repetição, remove
               apenas uma ocorrência)
        
        vec:   o vector (ou um ponteiro para o seu início)
        
        elems: o número de elementos úteis do vector antes da remoção
               (a função deve actualizar este valor, por isso é passado
               por referência)
               
    <- Saída:
             
        ERRO:  se o vector estiver vazio ou o elemento a remover não
               for encontrado
                       
        OK:    se conseguir inserir com sucesso
*/
int remover(int n, int vec[], int *elems){
    int encontrou = F; //sinaliza se n foi encontrado no vector
    int p, t;
    
    

    /* Percorre o vector à procura de n. No final deste ciclo,
    a variável p fica como valor da posição do elemento a remover */
    for(p = 0; p < (*elems); p++)
        if(vec[p] == n){
            encontrou = V;
            break;
        }
    
    
    /* Se a flag ainda estiver falsa é porque o vector estava vazio
    ou o valor não foi encontrado */
    if(!encontrou) return ERRO;
    
    /* Desloca uma posição para a esquerda todos os valores 
    à direita de n. Notar que não é necessário acção explícita para
    remover o valor. Basta escrever-lhe por cima */
    for(t = p + 1; t < (*elems); t++)
        vec[t - 1] = vec[t];
        
    /* Actualiza número de elementos e termina */
    (*elems)--;
    return OK;
}

/*******************************************************************************
                           PROGRAMA PRINCIPAL
*/
int main(void){
    int vec[CAPACIDADE];
    int elementos = 0;
    
    int num, op;
    
    do{
        print_vector(vec, elementos);
        printf("\nMenu\n1 - Inserir\n2 - Remover\n3 - Sair\nOpcao: ");
        scanf("%d", &op);
        
        if(op == 1){
            printf("\nElemento a inserir: ");
            scanf("%d", &num);
            
            if(!inserir(num, vec, &elementos, CAPACIDADE))
                printf("\nCapacidade esgotada.\n");
        }

        if(op == 2){
            printf("\nElemento a remover: ");
            scanf("%d", &num);
            
            if(!remover(num, vec, &elementos))
                printf("\nVector vazio ou elemento nao existente.\n");
        }

    } while(op != 3);
    
    system("pause");
}
