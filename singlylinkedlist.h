#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include "linkedlist.h"

#ifdef TYPE_OF_LIST
    #undef TYPE_OF_LIST
    #define TYPE_OF_LIST "SINGLY LINKED LIST"
#endif

/******************************************************************************
 * IMPLEMENTAÇÕES ESPECÍFICAS DA LISTA SIMPLESMENTE ENCADEADA                 *
 ******************************************************************************/

List* newList() 
{
    List *l;

    l = (List *) malloc(sizeof(List));  /*Aloca memória para a lista.*/
    l->_start = NULL;
    return l;
}

static void _releaseNode(_Node *node, _Node *prev, List *list);

void addElement(List *list, void *item) 
{
   _Node *newNode;

   newNode = malloc(sizeof(_Node));    /*Aloca memória para o nó.*/
   newNode->info = item;               /*Realiza atribuições.*/

   newNode->next = list->_start;
   list->_start = newNode;             /*Adiciona nó ao início da lista.*/
}

void addElementAtEnd(List *list, void *item) 
{
    _Node *newNode,
          *p;

    if (list->_start == NULL)           /*Se a lista está vazia.*/
    {
        addElement(list, item);         /*Adiciona o elemento.*/
        return;                         /*Retorna.*/
    }
    newNode = malloc(sizeof(_Node));    /*Se a lista contém elementos,
                                          cria um nó.*/
    newNode->info = item;               /*Realiza atribuições.*/
    newNode->next = NULL;

    p = list->_start;                   /*Percorre a lista até o final.*/
    while (p->next != NULL) 
    {
        p = p->next;
    }

    p->next = newNode;                  /*Adiciona o endereço ao proximo nó
                                          do último nó da lista.*/
}

void addElementSorting(List *list, void *item, compare f) 
{
    _Node *p,                           /*Declaração de ponteiros.*/
          *prev,
          *newNode;

    p = list->_start;
    newNode = malloc(sizeof(_Node));
    newNode->info = item;
    if (prev == NULL);                  /*C Warning*/
    while (p != NULL &&
          f(item, p->info) >= 0)        /*Encontra a posição para adição
                                          do elemento na ordem certa.*/
    {
        prev = p;
        p = p->next;                    /*Próxima iteração.*/
    }
    newNode->next = p;                  /*Atribui referências.*/

    if (p == NULL || prev == NULL)      /*Se o elemento é o menor da lista.*/
    {
        list->_start = newNode;
    } 
    else 
    {
        prev->next = newNode;
    }
}

static void _addAtIndex(List *list, void *item, int index) 
{
    _Node *node,
          *p;
    int i;

    node = malloc(sizeof(_Node));       /*Cria um novo nó.*/
    node->info = item;                  /*Atribui a informação.*/
    p = list->_start;

    for (i = 1; p != NULL;              /*Percorre a lista até o índice.*/
            i++, p = p->next) 
    {
        if (i == index) 
        {
            node->next = p->next;       /*Adiciona os elementos no índice.*/
            p->next = node;
            break;                      /*Termina.*/
        }
    }
}

void addAtIndex(List *list, void *item, int index) 
{
    if (index > count(list))            /*Se o índice fornecido é maior
                                          que o tamanho da lista.*/
    {
        addElementAtEnd(list, item);
    } 
    else if(index <= 0) 
    {                                   /*Índice negativo.*/
        addElement(list, item);
    } 
    else                                /*Indice válido.*/
    {
        _addAtIndex(list, item, index); /*Adiciona no indice especificado.*/
    }
}

List* newListFromArray(void **arr, int startIndex, int endIndex) 
{
    List *l;
    _Node *newNode;
    int i;

    l = newList();                      /*Cria uma nova lista.*/
    newNode = malloc(sizeof(_Node));    /*Aloca memória para um nó.*/
    l->_start = newNode;                /*Atribui início da nova lista ao
                                          nó alocado.*/

    i = startIndex;                     /*Início do indíce para percorrer
                                          o vetor.*/
    while (1) 
    {
        newNode->info = arr[i];         /*Atribui informação do vetor ao nó*/

        if (i == endIndex)              /*Se a cópia chegou ao fim.*/
        {
            newNode->next = NULL;       /*Termina a lista.*/
            break;                      /*Termina a criação de nós.*/
        }
        newNode->next =
            malloc(sizeof(_Node));      /*Aloca um novo nó para o pŕoximo
                                          nó da lista.*/
        newNode = newNode->next;        /*Atribui endereço a novo nó para
                                          a próxima iteração.*/
        i++;
    }

    return l;
}

void _releaseNode(_Node *node, _Node *prev, List *list) 
{
    if (node == list->_start)           /*Se o nó a ser desconectado é o
                                          primeiro nó da lista.*/
    {
        list->_start = node->next;      /*O primeiro nó da lista recebe o
                                          endereço do próximo nó.*/
    } 
    else 
    {
        prev->next = node->next;
        /* Se o nó a ser desconectado é qualquer outro nó da lista, então
         * o endereço do próximo nó do nó anterior a ser desconectado recebe
         * o endereço do próximo nó a ser desconectado.*/
    }

    free(node);                         /*Libera o nó da memória.*/
}

void removeNulls(List *list) 
{
    _Node *p,
          *prev;

    p = list->_start;
    while (p != NULL)                   /*Percorre a lista.*/
    {
        if (p->info == NULL)            /*Se a informação é nula.*/
            _releaseNode(p, prev, list);/*Libera o nó da lista.*/
        prev = p;                       /*Próxima iteração.*/
        p = p->next;
    }
}

void* removeLastOccurence(List *list, void *item, compare f) 
{
    /*
     *  NOTA:    Uso da função _releaseNode().
     */

    _Node *p,                           /*Ponteiro para percorrer a lista.*/
          *prev,                        /*Ponteiro para o nó anterior.*/
          *prevToRemove,                /*Ponteiro para o nó anterior ao
                                          nó a ser removido.*/
          *toRemove;                    /*Nó a ser removido.*/
    void *info;                         /*Ponteiro para a informação*/

    p = list->_start;
    while (p != NULL)                   /*Percorre a lista.*/
    {
        if (f(p->info, item) == 0)      /*Se os itens forem iguais.*/
        {

            prevToRemove = prev;        /*Armazena as referências.*/
            toRemove = p;
        }
        prev = p;                       /*Próxima iteração.*/
        p = p->next;
    }

    if (toRemove == NULL) return NULL;  /*Elemento não encontrado.*/
    info = toRemove->info;              /*Armazena referência a informação.*/
    _releaseNode(toRemove,
            prevToRemove, list);        /*Libera o nó da lista.*/
    return info;                        /*Retorna endereço da informação.*/
}

List* getRange(List *list, int start, int end) 
{
    _Node *p,                           /*Declaração de ponteiros para
                                          percorrer a lista e inserir novos
                                          nós na nova lista*/
          *newNode,
          *newNodePrev;
    List *shallow;                      /*Declaração da nova lista*/
    int i;

    shallow = malloc(sizeof(List));
    p = list->_start;
    i = -1;
    while (p != NULL)                   /*Percorre a lista até a posição de
                                          inicio.*/
    {
        i++;
        if (i == start || i > end)       /*Até a posição de fim, ou o fim
                                          da lista*/
        {
            break;
        }
        p = p->next;
    }

    newNode = malloc(sizeof(_Node));
    newNode->info = p->info;
    shallow->_start = newNode;
    while (p != NULL)                   /*Copia os elementos no intervalo
                                          fornecido.*/
    {
        i++;
        if (i == end) break;            /*No indice final, terminar execução.*/
        p = p->next;
        newNodePrev = newNode;
        newNode = malloc(sizeof(_Node));
        newNodePrev->next = newNode;
        newNode->info = p->info;
    }
    newNode->next = NULL;

    return shallow;                     /*Retorna a lista criada*/
}

#endif /*END SINGLY_LINKED_LIST_H_*/
