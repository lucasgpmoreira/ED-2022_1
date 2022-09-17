#include<stdio.h>
#include<stdlib.h>

#define ERRO        0
#define OK          1

#define CAPACIDADE  10

#define F           0
#define V           1

/*******************************************************************************
  Fun��o auxiliar para escrever os elementos de um vector no ecr�.
*/
void print_vector(int *v, int tam){
  int i;
  printf("[");
  for(i=0; i<tam; i++)
    printf("%d ", v[i]);
  printf("]\n");  
}

/*******************************************************************************
  Inser��o ordenada num vector ordenado
  
    -> Entradas:
                
        n:     valor a inserir no vector
        
        vec:   o vector (ou um ponteiro para o seu in�cio)
        
        elems: o n�mero de elementos �teis do vector antes da inser��o
               (a fun��o deve actualizar este valor, por isso � passado
               por refer�ncia)
               
        cap:   a capacidade m�xima do vector
         
    <- Sa�da:
             
        ERRO:  se o vector estiver cheio        
        OK:    se conseguir inserir com sucesso
*/
int inserir(int n, int vec[], int *elems, int cap){
    int i, j;

    /* Se o vector estiver cheio n�o insere */
    if (*elems == cap) return ERRO;

    /* Se o vector est� vazio insere n na primeira posi��o, actualiza 
     o n�mero de elementos do vector e termina */
    if (*elems == 0){
        vec[0] = n;
        (*elems)++;
        return OK;
    }

    /* Percorre o vector at� encontrar o primeiro elemento maior que n */
    for(i = 0; i < (*elems); i++)
          if(vec[i] > n) break;

    /* Desloca uma posi��o para a direita todos os valores maiores que n */
    for(j = (*elems); j > i; j--)
          vec[j] = vec[j-1];

    /* (!) Neste ponto, i == j e ambos indexam correctamente a posi��o
    onde deve ser inserido o valor n */

    /* Insere n na posi��o correcta, actualiza o n�mero de elementos 
    do vector e termina */
    vec[i] = n;
    (*elems)++;
    return OK;
}

/*******************************************************************************
  Remo��o ordenada num vector ordenado
  
    -> Entradas:
                
        n:     valor a remover do vector (se houver repeti��o, remove
               apenas uma ocorr�ncia)
        
        vec:   o vector (ou um ponteiro para o seu in�cio)
        
        elems: o n�mero de elementos �teis do vector antes da remo��o
               (a fun��o deve actualizar este valor, por isso � passado
               por refer�ncia)
               
    <- Sa�da:
             
        ERRO:  se o vector estiver vazio ou o elemento a remover n�o
               for encontrado
                       
        OK:    se conseguir inserir com sucesso
*/
int remover(int n, int vec[], int *elems){
    int encontrou = F; //sinaliza se n foi encontrado no vector
    int p, t;
    
    

    /* Percorre o vector � procura de n. No final deste ciclo,
    a vari�vel p fica como valor da posi��o do elemento a remover */
    for(p = 0; p < (*elems); p++)
        if(vec[p] == n){
            encontrou = V;
            break;
        }
    
    
    /* Se a flag ainda estiver falsa � porque o vector estava vazio
    ou o valor n�o foi encontrado */
    if(!encontrou) return ERRO;
    
    /* Desloca uma posi��o para a esquerda todos os valores 
    � direita de n. Notar que n�o � necess�rio ac��o expl�cita para
    remover o valor. Basta escrever-lhe por cima */
    for(t = p + 1; t < (*elems); t++)
        vec[t - 1] = vec[t];
        
    /* Actualiza n�mero de elementos e termina */
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
