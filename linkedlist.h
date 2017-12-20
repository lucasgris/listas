/******************************************************************************
 * BIBLIOTECA - LISTA ENCADEADA                                               *
 *****************************************************************************/

/**
 *  FUNÇÕES DE USO INTERNO:
 *
 *  _forEachNode            void        List *list, function f
 *  _releaseNode            void        _Node *node, _Node *prev, List *list
 *
 *  TODO:
 *  Alteração do algoritmo para ordenação: Merge Sort.
 *  Remoção dos nós da lista recursivamente.
 *
 *  BUGS:
 *  A função clearList() parece não surtir efeito no uso de memória.
 */


#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "list.h"

#ifdef TYPE_OF_LIST
    #undef TYPE_OF_LIST
    #define TYPE_OF_LIST "ABSTRACT LINKED LIST"
#endif

/*******************************************************************************
 * DEFINIÇÃO DE TIPOS                                                          *
 ******************************************************************************/

typedef struct _Node_ _Node;
/*
 * Definição de um nó da lista encadeada. Não manipule essa estrutura
 *      diretamente.
 */
struct _Node_ 
{
    /*
     * Ponteiro para a informação a ser adicionada.
     */
    void *info;
    /*
     * Ponteiro para o próximo nó da lista.
     */
    _Node *next;

    #ifdef DOUBLY_LINKED_LIST_H_
    /*
     * Ponteiro para o nó anterior da lista.
     */
    _Node *prev;
    #endif
};

/*
 * Definição de uma lista.
 */
struct _List 
{
    /*
     * Início da lista, ponteiro para o primeiro nó.
     */
    _Node *_start;
};

/*
 * Definição de um iterador.
 */
struct _Iterator 
{
    _Node *_actual;
};

/******************************************************************************
 * IMPLEMENTAÇÕES GERAIS DA LISTA ENCADEADA                                   *
 ******************************************************************************/

int count(List *list) 
{
    _Node *p;                           /*Ponteiro auxiliar para o início
                                          da lista.*/
    int i;                              /*Contador.*/

    p = list->_start;
    i = 0;
    while (p != NULL)                   /*Percorre a lista e incrementa o
                                          contador a cada nó.*/
    {
        if (p->info != NULL) i++;       /*Se a informação não for nula, 
                                          incrementa.*/
        p = p->next;
    }
    return i;
}

/*
 * Desconecta um nó da lista.
 *
 * NOTA:    O nó será liberado da memória.
 */
static void _releaseNode(_Node *node, _Node *prev, List *list);

int isEmpty(List *list) 
{
    _Node *p;

    if (list->_start == NULL) return 1;

    p = list->_start;
    while(p != NULL) 
    {
        if (p->info != NULL) return 0;
        p = p->next;
    }

    return 1;
}

List* newListOfSize(int size) 
{
    List* list;
    int i;

    list = newList();                   /*Cria uma nova lista.*/
    for (i = 0; i < size; i++)          /*Cria novos nós e atribui a lista,
                                          mas não atribui dados.*/
    {
        addElement(list, NULL);
    }
    return list;
}

/*
 * NOTA:    Uso da função addElementAtEnd().
 */
List* collect(List *list, filter f) 
{
    List *l;
    _Node *p;

    l = newList();                      /*Cria uma nova lista.*/
    p = list->_start;                   /*Atribui referência para o
                                          início da lista.*/

    while (p != NULL)                   /*Percorre a lista.*/
    {
        if (f(p->info))                 /*Se satisfaz a condição.*/
        {
            addElementAtEnd(l,
              p->info);                 /*Adiciona.*/
        }
        p = p->next;                    /*Próxima iteração.*/
    }
    return l;                           /*Retorna endereço da lista criada*/
}

void* getAtIndex(List *list, int index) 
{
    _Node *p;                           /*Para percorrer a lista.*/
    int i;

    for (
            i = 0, p = list->_start;
            p != NULL;
            i++, p = p->next
        )
    {
        if (i == index) 
        {
            return p->info;             /*Retorna a informação do índice.*/
        }
    }

    return NULL;                        /*Se o índice não é valido.*/
}

int getIndexOf(List *list, void *item, compare f) 
{
    _Node *p;
    int i;

    for (
            i = 0, p = list->_start;    /*Itera sobre a lista.*/
            p != NULL;
            i++, p = p->next
        )
    {
        if (f(item, p->info)) 
        {
            return i;                   /*Retorna o índice da informação*/
        }
    }

    return -1;
}

void* getFirst(List *list) 
{
    if (list->_start != NULL) return list->_start->info;
    return NULL;
}

/*
 * NOTA:    Uso da função _releaseNode().
 */
void* removeFirstOccurence(List *list, void *item, compare f) 
{
    _Node *p,                           /*Ponteiro para percorrer a lista.*/
          *prev;                        /*Ponteiro para o nó anterior da
                                          lista.*/
    void *info;                         /*Ponteiro para a informação*/

    p = list->_start;
    prev = NULL;
    while (p != NULL &&
      (f(p->info, item) != 0))          /*Percorre a lista até o fim, ou
                                          até encontrar a primeira
                                          ocorrencia.*/
    {
        prev = p;                       /*Atribui endereço ao nó anterior.*/
        p = p->next;                    /*Próxima iteração.*/
    }
    if (p == NULL) return NULL;         /*Retorna NULL se o elemento não
                                          foi encontrado.*/
    info = p->info;                     /*Armazena o endereço de info do nó.*/
    _releaseNode(p, prev, list);        /*Libera o nó da lista.*/
    return info;                        /*Retorna o endereço da
                                          informação contida no nó
                                          liberado.*/
}

void* pop(List *list) 
{
    _Node *p;
    void *info;                         /*Ponteiro para a informação*/

    if (list->_start == NULL)
        return NULL;                    /*Se a lista está vazia*/
    p = list->_start;                   /*Atribui endereço do primeiro
                                          elemento da lista.*/
    info = list->_start->info;          /*Atribui início da lista ao
                                          segundo elemento.*/
    list->_start = list->_start->next;
    free(p);
    return info;                        /*Retorna endereço da informação*/
}

/*
 *  NOTA:    Uso da função addElement().
 */
void push(List *list, void* item) 
{
    addElement(list, item);             /*Adiciona elemento no início.*/
}

/*
 *  NOTA:    Uso da função _releaseNode().
 */
void* removeAtIndex(List *list, int index) 
{
    _Node *p,                           /*Ponteiros para percorrer a lista.*/
         *prev;

    void *info = NULL;

    int i;
    for (
            i = 0, p = list->_start;
            p != NULL;
            i++, prev = p, p = p->next
        )
    {
        if (i == index)                 /*Índice encontrado.*/
        {
            info = p->info;             /*Armazena referência a informação.*/
            _releaseNode(p, prev, list);/*Libera o nó da lista.*/
            break;                      /*Termina.*/
        }
    }
    return info;                        /*Retorna endereço da informação.*/
}

void clearList(List *list) 
{
    _Node *p,
          *prev;
    
    p = list->_start;                   /*Ponteiros para percorrer a lista.*/
    prev = list->_start;

    while (p != NULL)                   /*Percorre a lista.*/
    {
        p = p->next;
        free(prev);                     /*Libera nó anterior.*/
        prev = p;
    }
}

/*
 * NOTA:    Uso da função clearList().
 */
void deleteList(List *list) 
{
    clearList(list);                    /*Limpa lista.*/
    free(list);                         /*Libera endereço da lista.*/
}

int countOccurences(List *list, void *item, compare f) 
{
    int count;
    _Node *p;

    p = list->_start;                   /*Ponteiro para percorrer a lista.*/
    count = 0;
    while (p != NULL)
    {
        if(f(item, p->info) == 0)
            count++;                    /*Incrementa contagem.*/
        p = p->next;
    }
    return count;
}

void* searchElement(List *list, void *item, compare f) 
{
    _Node *p;

    p = list->_start;
    while (p != NULL &&
          f(p->info, item) != 0)        /*Percorre a lista até o fim ou até
                                          encontrar o elemento.*/
    {
        p = p->next;
    }

    if (p != NULL) return p->info;      /*Retorna endereço da informação.*/
    return NULL;
}

/*
 * NOTA:   Uso da função searchElement().
 */
int contains(List *list, void *item, compare f) 
{
    return searchElement(list, item, f)
        != NULL;                        /*Se o retorno da busca é nulo, o
                                          elemento não existe na lista.*/
}

/*
 *  NOTA:   Uso da função _releaseNode().
 */
void removeAllOccurences(List *list, void *item, compare f) 
{
    _Node *p,                           /*Atribui endereço da lista.*/
          *prev,                        /*Utilizado para remoção de nós.*/
          *aux;

    p = list->_start;
    while (p != NULL)                   /*Itera sobre a lista.*/
    {
        if (f(p->info, item) == 0)      /*Compara o item com os elementos
                                          da lista.*/
        {
            aux = p;                    /*Atribui ao ponteiro auxiliar
                                          o endereço de p,
                                          pois p será liberado da
                                          memória.*/
            _releaseNode(p, prev, list);/*Libera o nó.*/
            p = aux->next;              /*Atribui endereço para a próxima
                                          iteração.*/
            prev = aux;
            continue;                   /*Próxima iteração.*/
        }

        prev = p;                       /*Próxima iteração, caso nenhum
                                          nó tenha sido eliminado.*/
        p = p->next;
    }
}

/*
 * NOTA:   Uso da função removeLastOccurence().
 */
void removeDuplicateItems(List *list, compare f) 
{
    _Node *p;

    p = list->_start;
    while (p != NULL)                   /*Itera sobre a lista.*/
    {
        while (countOccurences(list,
                    p->info, f) > 1)    /*Enquanto existir elementos
                                          duplicados.*/
        {
            removeLastOccurence(list,
                p->info, f);            /*Remove a última ocorrência do item.*/
        }
        p = p->next;
    }
}

/*
 *  NOTA:   Uso da função addElementSorting() e clearList().
 *
 *          Os endereços dos nós da lista são alterados, entretanto isso não
 *          afeta o comportamento da lista, já que os endereços dos nós
 *          são necessários para o funcionamento interno da lista e não
 *          devem ser acessados de forma direta.
 *
 *  TODO:   Reimplementar função utilizando o algoritmo merge sort.
 */
void sort(List *list, compare f) 
{
    List *temp;                         /*Cria uma nova lista.*/
    _Node *p;                           /*Ponteiro para percorrer a lista.*/

    temp = newList();
    p = list->_start;
    while (p != NULL) 
    {
        addElementSorting(temp,
              p->info, f);              /*Adiciona cada elemento da lista
                                          antiga a nova, de forma
                                          ordenada.*/
        p = p->next;
    }
    clearList(list);                    /*Limpa a lista antiga.*/

    list->_start = temp->_start;        /*Atribui referência do ínicio da
                                          lista nova ao início da
                                          lista antiga.*/
    free(temp);                         /*Libera endereço da lista temporária.*/
}

void forEach(List *list, function f) 
{
    _Node *p;

    p = list->_start;
    while (p != NULL)                   /*Percorre a lista.*/
    {
        (*f)(p->info);                  /*Aplica a função a info do nó.*/
        p = p->next;
    }
}

/*Função comentada pela falta de uso*/
#if 0
/*
 * NOTA:    Função de acesso direto aos nós da lista.
 */
static void _forEachNode(List *list, function f) {
    _Node *p;

    p = list->_start;
    while (p != NULL) {                 /*Percorre a lista.*/
        (*f)(p);                        /*Aplica a função ao nó.*/
        p = p->next;
    }
}
#endif

void copyTo(List *from, List *to) 
{
    /*
     *  NOTA:    Uso da função addElementAtEnd().
     */
    _Node *p;

    p = from->_start;
    while (p != NULL)                   /*Percorre a lista *from.*/
    {
        addElementAtEnd(to, p->info);   /*Adiciona elemento no fim da lista
                                          *to.*/
        p = p->next;
    }
}

void reverse(List *list) 
{
    _Node *p,                           /*Cria nós para percorrer a lista.*/
          *prev,
          *temp;

    p = list->_start;
    prev = NULL;
    while (p != NULL)                   /*Inverte os endereços dos próximos
                                          nós do nó anterior visitado.*/
    {
        temp = p;                       /*Armazena temporariamente o endereço
                                          do nó atual.*/
        p = p->next;                    /*Próximo nó.*/
        temp->next = prev;              /*O nó anterior guardado passa a
                                          apontar para o nó anterior.*/
        prev = temp;
    }
    list->_start = prev;
}

void append(List *l1, List *l2) 
{
    _Node *p;                           /*Ponteiro para percorrer a lista.*/

    p = l1->_start;
    if (p == NULL) 
    {
        l1->_start = l2->_start;        /*Se a lista não tem nós.*/
        return;
    }
    while (p->next != NULL)             /*Procura o fim da lista.*/
    {
        p = p->next;
    }
    p->next = l2->_start;               /*Adiciona o início de l2 a l1.*/
}

/*
 * NOTA:    Uso da função copyTo().
 */
List* join(List *l1, List *l2) 
{
    List *list;                         /*Cria um nova lista.*/

    list = newList();
    copyTo(l1, list);                   /*Copia os nós de *l1 para *list.*/
    copyTo(l2, list);                   /*Copia os nós de *l2 para *list.*/
    /*
     * O uso do append é mais rápido mas pode causar problemas com a manipulação
     * das listas originais e vice versa, já que os endereços serão mantidos.
     */
    return list;
}

/*
 * NOTA: uso da função contains().
 */
int disjoint(List *l1, List *l2, compare f) 
{
    _Node *p;

    p = l1->_start;
    while(p != NULL)                    /*Percorre a lista.*/
    {
        if (contains(l2, p->info, f))   /*Se o elemento da iteração atual
                                          existe em l2, então as duas
                                          listas não são disjuntas.
                                          Retorna falso.*/
            return 0;
        p = p->next;                    /*Próxima iteração.*/
    }
    return 1;                           /*Nenhum elemento de l1 existe em l2,
                                          retorna verdadeiro.*/
}

void fill(List *list, void *item) 
{
    _Node *p;
    int i;
    for (
            i = 0, p = list->_start;
            i < count(list);
            i++, p = p->next
        )
    {
        p->info = item;                 /*Preenche a lista com o item.*/
    }
}

void replace(List *list, void *t, void *t2, compare f) 
{
    _Node *p;

    p = list->_start;
    while(p != NULL)                    /*Percorre a lista.*/
    {
        if (f(p->info, t) == 0)         /*Se o elemento da lista é igual a t.*/
        {
            p->info = t2;               /*Substitui por t2.*/
        }
        p = p->next;                    /*Próxima iteração.*/
    }
}

void* max(List *list, compare f) 
{
    _Node *p;
    void *max;

    p = list->_start;
    max = p->info;                      /*O maior item recebe o primeiro item
                                          da lista.*/
    while(p != NULL) 
    {
        if (p->info != NULL &&
                f(p->info, max) > 0)    /*Se o item da lista é maior que o
                                          maior item atualmente.*/
        {
            max = p->info;              /*Substitui o maior item pelo
                                          encontrado.*/
        }
        p = p->next;
    }
    return max;                         /*Retorna o endereço do maior item.*/
}

void* min(List *list, compare f) 
{
    _Node *p;
    void *min;

    p = list->_start;
    min = p->info;                      /*O menor item recebe o primeiro item
                                          da lista.*/
    while(p != NULL) 
    {
        if (p->info != NULL &&
                f(p->info, min) < 0)    /*Se o item da lista é maior que o
                                          maior item atualmente.*/
        {
            min = p->info;              /*Substitui o menor item pelo
                                          encontrado.*/
        }
        p = p->next;
    }
    return min;                         /*Retorna o endereço do menor item.*/
}

int allMatch(List *list, predicate f) 
{
    _Node *p;

    p = list->_start;
    while(p != NULL)                    /*Percorre a lista.*/
    {
        if (!f(p->info))                /*Caso o item não satisfaça a condição*/
            return 0;                   /*Retorna falso.*/
        p = p->next;                    /*Próxima iteração.*/
    }
    return 1;                           /*Retorna verdadeiro.*/
}

int anyMatch(List *list, predicate f) 
{
    _Node *p;

    p = list->_start;
    while(p != NULL)                    /*Percorre a lista.*/
    {
        if (f(p->info))                 /*Caso o item satisfaça a condição.*/
            return 1;                   /*Retorna verdadeiro.*/
        p = p->next;                    /*Próxima iteração.*/
    }
    return 0;                           /*Retorna falso.*/
}

void** toArray(List *list) 
{
    void **arr;

    _Node *p;                           /*Para percorrer a lista.*/
    int i;

    arr = malloc(count(list) *
            sizeof(void*));             /*Cria um novo vetor de referências*/
    for (
            i = 0, p = list->_start;
            p != NULL;                  /*Percorre até o fim da lista.*/
            i++, p = p->next
        )
    {
        arr[i] = p->info;               /*Atribui referencias aos elementos
                                          do vetor.*/
    }
    return arr;
}


/******************************************************************************
 * ITERATOR                                                                   *
 *****************************************************************************/

/* TODO:    Substituição do código do iterator por array obtido na função
 *          toArray.
 *
 *          Isso evita possíveis side effects, e possibilita reúso de código
 *          ja que todas as estruturas utilizam o Iterator. Além disso é uma
 *          boa maneira de implementar o iterator para a estrutura pilha.
 */

Iterator* iterator(List *list) 
{
    Iterator *itr;

    itr = malloc(sizeof(Iterator));     /*Aloca um novo iterator na memória.*/
    itr->_actual = list->_start;        /*Atribui início do iterator para o
                                          primeiro elemento da lista.*/
    return itr;
}

int hasNext(Iterator *itr) 
{
    return itr->_actual != NULL;        /*Se a lista não contem próximos nós.*/
}

void* next(Iterator *itr) 
{
    void *info;

    if (itr->_actual == NULL)           /*Se o iterator chegou ao fim.*/
        return NULL;
    info = itr->_actual->info;          /*Senão, retorna a informação atual e
                                          incrementa para a próxima
                                          iteração.*/
    itr->_actual = itr->_actual->next;
    return info;
}

#endif /*END LINKED_LIST_H_*/
