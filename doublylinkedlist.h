#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include "linkedlist.h"

#ifdef TYPE_OF_LIST
    #undef TYPE_OF_LIST
    #define TYPE_OF_LIST "DOUBLY LINKED LIST"
#endif


/******************************************************************************
 * IMPLEMENTAÇÕES ESPECÍFICAS DA LISTA DUPLAMENTE ENCADEADA                   *
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

   newNode->prev = NULL;
   if (list->_start != NULL)           /*Se a lista contém elementos.*/
       list->_start->prev = newNode;   /*Atribui endereço do nó anterior.*/

   list->_start = newNode;             /*Adiciona nó ao início da lista.*/
}

void addElementAtEnd(List *list, void *item) 
{
   _Node *newNode,
         *p;

   if (list->_start == NULL) 
   {                                   /*Se a lista está vazia.*/
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
   newNode->prev = p;                  /*No caso de lista duplamente
                                         encadeada.*/
   p->next = newNode;                  /*Adiciona o endereço ao proximo nó do
                                         último nó da lista.*/
}

void addElementSorting(List *list, void *item, compare f) 
{
    _Node *p,                           /*Declaração de ponteiros.*/
          *prev = NULL,
          *newNode;

    p = list->_start;
    newNode = malloc(sizeof(_Node));
    newNode->info = item;
    if (prev == NULL);                  /*C90 Warning*/
    while (p != NULL && 
            f(item, p->info) >= 0)      /*Encontra a posição para adição
                                          do elemento na ordem certa.*/
    {
        prev = p;
        p = p->next;                    /*Próxima iteração.*/
    }
    newNode->next = p;                  /*Atribui referências.*/

    if (prev == NULL) 
    {
        list->_start = newNode;
    } 
    else 
    {
        newNode->next = prev->next;
        if (prev->next != NULL)
        {
            prev->next->prev = newNode;
        }
        prev->next = newNode;
        newNode->prev = prev;
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
            node->next = p->next;
            node->prev = p;
            p->next = node;
            node->next->prev
                = node;
        }
    }
}

void addAtIndex(List *list, void *item, int index) {
    if (index > count(list))            /*Se o índice fornecido é maior
                                          que o tamanho da lista.*/
    {
        addElementAtEnd(list, item);
    } 
    else if(index <= 0)                 /*Índice negativo.*/
    {
        addElement(list, item);
    } 
    else                                /*O indice é valido.*/
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
    l->_start->prev = NULL;

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
        newNode->next->prev = newNode;
        newNode = newNode->next;        /*Atribui endereço a novo nó para
                                          a próxima iteração.*/
        i++;
    }

    return l;
}

void _releaseNode(_Node *node, _Node *prev, List *list) 
{
    if (node == list->_start) 
    {
        list->_start = node->next;
        if (node->next != NULL)
        {
            node->next->prev = NULL;
        }
    } 
    else 
    {
        node->prev->next = node->next;
        if (node->next != NULL)
        {
            node->prev->next->prev
                = node->prev;
        }
    }

    free(node);                         /*Libera o nó da memória.*/
}

void removeNulls(List *list) 
{
    _Node *p;

    p = list->_start;
    while (p != NULL)                   /*Percorre a lista.*/
    {
        if (p->info == NULL)            /*Se a informação é nula.*/
        {
            _releaseNode(p,
                    p->prev, list);     /*Libera o nó da lista.*/
        }
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
          *toRemove;                    /*Nó a ser removido.*/
    void *info;                         /*Ponteiro para a informação*/

    p = list->_start;
    while (p != NULL)                   /*Percorre a lista.*/
    {
        if (f(p->info, item) == 0)      /*Se os itens forem iguais.*/
        {
            toRemove = p;
        }
        prev = p;                       /*Próxima iteração.*/
        p = p->next;
    }

    if (toRemove == NULL) return NULL;  /*Elemento não encontrado.*/
    info = toRemove->info;              /*Armazena referência a informação.*/

    _releaseNode(toRemove,
            toRemove->prev, list);
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


    newNode = malloc(sizeof(_Node));    /*Inicia a cópia das informações.*/
    newNode->info = p->info;
    newNode->prev = NULL;
    shallow->_start = newNode;
    while (p != NULL) 
    {
        i++;
        if (i == end) break;            /*No índice final, terminar execução.*/
        p = p->next;
        newNodePrev = newNode;
        newNode = malloc(sizeof(_Node));
        newNode->info = p->info;
        newNode->prev = newNodePrev;
        newNodePrev->next = newNode;
    }
    newNode->next = NULL;

    return shallow;                     /*Retorna a lista criada.*/
}

#endif /*END DOUBLY_LINKED_LIST_H_*/
