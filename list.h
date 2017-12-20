/******************************************************************************
 * BIBLIOTECA - LISTA                                                         *
 *****************************************************************************/

/**
 *  LISTA DE FUNÇÕES:
 *
 *  Assinatura              Retorno     Parâmetros
 *
 *  addAtIndex              void        List *list, void *item, int index
 *  addElement              void        List *list, void *item
 *  addElementAtEnd         void        List *list, void *item
 *  append                  void        List *l1, List *l2
 *  allMatch                int         List *list, predicate f
 *  anyMatch                int         List *list, predicate f
 *  clearList               void        List *list
 *  collect                 List*       List *list, filter f
 *  contains                int         List *list, void *item, compare f
 *  copyTo                  void        List *from, List *to
 *  countOccurences         int         List *list, void *item, compare f
 *  deleteList              void        List *list
 *  disjoint                int         List *l1, List *l2
 *  fill                    void        List *list, void *item
 *  forEach                 void        List *list, function f
 *  getAtIndex              void*       List *list, int index
 *  getIndexOf              int         List *list, void *item, compare f
 *  getFirst                void*       List *list
 *  getRange                List*       List *list, void *start, void *end
 *  hasNext                 int         Iterator*
 *  isEmpty                 void        List *list
 *  iterator                Iterator*   List *list
 *  join                    List*       List *l1, List *l2
 *  max                     void*       List *list, void *item, compare f
 *  min                     void*       List *list, void *item, compare f
 *  next                    void*       Iterator*
 *  newList                 List*       void
 *  newListFromArray        List*       void **arr, int start, int end
 *  newListOfSize           List*       int size
 *  pop                     void*       List *list
 *  push                    void        List *list, void*
 *  removeAllOccurences     void        List *list, void *item, compare f
 *  removeAtIndex           void*       List *list, int index
 *  removeDuplicateItems    void        List *list, compare f
 *  removeFirstOccurence    void*       List *list, void *item, compare f
 *  removeLastOccurence     void*       List *list, void *item, compare f
 *  removeNulls             void        LIst *list
 *  replace                 void        List *list, void *i, void *j, compare f
 *  reverse                 void        List *list
 *  searchElement           void*       List *list, void *item, compare f
 *  count                   int         List *list
 *  sort                    void        List *list, compare f
 *  toArray                 void**      List *list
 *
 *  As funçoes que só mostram a assinatura estão implementadas em bibliotecas
 *  mais específicas.
 *
 *  ITERATOR:
 *  Utilize iterator() para obter um Iterator, então itere sobre a lista da
 *  seguinte forma:
 *
 *  while (hasNext(Iterator*)) {
 *      next(Iterator*);                (Retorna o próximo elemento da lista.)
 *  }
 */


#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

#define TYPE_OF_LIST "ABSTRACT LIST"



/*******************************************************************************
 * DEFINIÇÃO DE TIPOS                                                          *
 ******************************************************************************/

/**
 * Definição de uma função para aplicação na função forEach().
 */
typedef void (*function) (void*);

/**
 * Definição de uma função comparativa.
 *
 * return:  < 0 , se o primeiro elemento for maior que o segundo.
 *            0 , se os elementos comparados forem iguais.
 *          > 0 , se o primeiro elemento for menor que o segundo.
 *
 * EXEMPLO:
 *
 * int intcmpr(void *i1, void *i2) {
 *     if (i1 == NULL && i2 != NULL) return -1;
 *     else if(i2 == NULL && i1 != NULL) return 1;
 *     else if(i1 == NULL && i2 == NULL) return 0;
 *     return *(int *) i1 - *(int *) i2;
 * }
 */
typedef int (*compare) (void*, void*);

/**
 * Definição de uma função de filtro, para aplicação na função collect().
 *
 * return:  1 , se o elemento corresponder a seleção.
 *          0 , pular elemento da seleção.
 */
typedef int (*filter) (void*);

typedef int (*predicate) (void*);

/*
 * Definição de uma lista.
 */
typedef struct _List List;

/**
 * Definição de um iterador.
 */
typedef struct _Iterator Iterator;


/******************************************************************************
 * FUNÇÕES                                                                    *
 *****************************************************************************/

/**
 * Cria uma nova lista.
 *
 * return:      O endereço da lista criada.
 */
List* newList();

/**
 * Calcula o tamanho da lista.
 *
 * return:      A contagem do número de elementos não nulos da lista.
 *
 */
int count(List *list);

/**
 * Verifica se a lista não contém elementos.
 *
 * return:      1, se estiver vazia.
 */
int isEmpty(List *list);

/**
 * Adiciona um elemento no fim da lista.
 */
void addElementAtEnd(List *list, void *item);

/**
 * Adiciona um elemento no início da lista.
 */
void addElement(List *list, void *item);

/**
 * Cria uma nova lista com tamanho inicial. Útil para uso da função fill().
 *
 * return:      O endereço da lista criada.
 *
 * NOTA:        O uso de listas com valores nulos pode gerar problemas na
 *              manipulação dos dados. Utilize removeNulls() para remover
 *              dalista itens nulos.
 */
List* newListOfSize(int size);

/**
 * Adiciona um elemento de forma ordenada.
 *
 * NOTA:        Essa função não ordena a lista.
 *
 *              É garantido que a lista esteja ordenada ao utilizar somente
 *              essa função para adição de itens.
 *
 *              Implemente a função compare() corretamente para a inserção
 *              de itens de forma ascendente ou descentende.
 *              O algoritmo segue a ordem padrão ( crescente ).
 *
 */
void addElementSorting(List *list, void *item, compare f);

/**
 * Constrói uma lista a partir de um vetor.
 *
 * Entre com o índice de início e fim dos elementos a serem copiados
 * do vetor.
 *
 * return:      O endereço da lista criada.
 */
List* newListFromArray(void **arr, int startIndex, int endIndex);

/**
 * Cria uma nova lista com tamanho inicial. Útil para uso da função fill().
 *
 * return:      O endereço da lista criada.
 *
 * NOTA:        O uso de listas com valores nulos pode gerar problemas na
 *              manipulação dos dados. Utilize removeNulls() para remover
 *              da lista itens nulos.
 */
List* newListOfSize(int size);

/**
 * Obtém o item no índice especificado.
 *
 * return:      O endereço da informação encontrada, NULL caso contrário.
 */
void* getAtIndex(List *list, int index);

/**
 * Constrói uma nova lista a partir de um função de filtro.
 *
 * return:      O endereço da lista criada.
 *
 * NOTA:        Os endereços das informações podem ser os mesmos endereços
 *              da lista original.
 */
List* collect(List *list, filter f);

/**
 * Obtém o índice da primeira ocorrencia do elemento encontrado na lista.
 *
 * return:      o índice da primeira ocorrência do item na lista,
 *              ou -1 caso o item não seja encontrado.
 */
int getIndexOf(List *list, void *item, compare f);

/**
 * Adiciona um item no índice especificado, caso o índice seja maior que o
 * tamanho da lista, o elemento será adicionado no final, se o índice for
 * negativo, o item será adicionado no início.
 */
void addAtIndex(List *list, void *item, int index);

/**
 * Elimina da lista os itens nulos.
 */
void removeNulls(List *list);

/**
 * Obtém o primeiro elemento da lista.
 *
 * return:      O endereço do primeiro elemento da lista.
 */
void* getFirst(List *list);

/**
 * Remove a primeira ocorrência do elemento em um nó da lista.
 *
 * return:      O endereço de memória da informação contida no nó
 *              removido. Caso o elemento não exista, o retorno é NULL.
 */
void* removeFirstOccurence(List *list, void *item, compare f);

/**
 * Remove a última ocorrência do elemento em um nó da lista.
 *
 * return:      O endereço de memória da informação contida no nó
 *              removido. Caso o elemento não exista, o retorno é NULL.
 *
 */
void* removeLastOccurence(List *list, void *item, compare f);

/**
 * Limpa a lista e libera recursos.
 *
 * NOTA:        Os endereços das informações serão mantidos.
 */
void clearList(List *list);

/**
 * Ordena a lista.
 */
void sort(List *list, compare f);

/**
 * Extrai e remove o primeiro elemento da lista.
 *
 * return:      O endereço do primeiro elemento da lista.
 */
void* pop(List *list);

/**
 * Adiciona um elemento no início da lista.
 *
 * Equivalente a addElement().
 */
void push(List *list, void* item);

/**
 * Deleta toda a estrutura da lista. Apenas as informações são mantidas
 * na memória.
 *
 * NOTA:        Apenas os endereços das informações serão mantidos.
 *              Todos os demais recursos serão liberados.
 */
void deleteList(List *list);

/**
 * Remove um item em uma posição específica.
 *
 * return:      O endereço da informação removida da lista.
 */
void* removeAtIndex(List *list, int index);

/**
 * Retorna o número de ocorrências de um item em uma lista.
 *
 * return:      A contagem de ocorrências encontrada.
 */
int countOccurences(List *list, void *item, compare f);

/**
 * Procura um elemento na lista.
 *
 * return:      O endereço do item encontrado, NULL caso contrário.
 */
void* searchElement(List *list, void *item, compare f);

/**
 * Verifica se a lista contém o elemento fornecido.
 *
 * return:      1, se o elemento está contido na lista.
 *              0, caso o elemento não exista na lista.
 */
int contains(List *list, void *item, compare f);

/**
 * Remove todas as ocorrências.
 */
void removeAllOccurences(List *list, void *item, compare f);

/**
 * Remove todos os elementos duplicados da lista.
 */
void removeDuplicateItems(List *list, compare f);

/**
 * Executa um procedimento para cada elemento da lista.
 */
void forEach(List *list, function f);

/**
 * Copia os elementos de uma lista para outra.
 */
void copyTo(List *from, List *to);

/**
 * Retorna uma nova lista independente composta pela junção de duas listas.
 *
 * return:      O endereço da lista criada.
 */
List* join(List *l1, List *l2);

/**
 * Inverte a ordem da lista.
 */
void reverse(List *list);

/**
 * Adiciona a lista l2 no fim da lista l1. Similar a copyTo().
 *
 * NOTA:        A lista l1 é alterada.
 */
void append(List *l1, List *l2);

/**
 * Verifica se duas listas são disjuntas.
 *
 * return:      1, caso sejam.
 *              0, caso não sejam.
 */
int disjoint(List *l1, List *l2, compare f);

/**
 * Preenche a lista com um elemento.
 *
 * NOTA:        Os endereços de todos os itens serão os mesmos.
 */
void fill(List *list, void *item);

/**
 * Substitui todas as ocorrências de um elemento da lista por outro elemento.
 */
void replace(List *list, void *t, void *t2, compare f);

/**
 * Obtém a primeira ocorrência do maior item de uma lista não ordenada.
 *
 * return:      O endereço da informação máxima da lista.
 */
void* max(List *list, compare f);

/**
 * Obtém a primeira ocorrência do menor item de uma lista não ordenada.
 *
 * return:      O endereço da informação mínima da lista.
 */
void* min(List *list, compare f);

/**
 * Verifica se todos os itens da lista satisfazem uma condição.
 *
 * return:      1, se todos os itens satisfazem a condição.
 *              0, se existe pelo menos um item que não satisfaz a condição.
 */
int allMatch(List *list, predicate f);

/**
 * Verifica se pelo menos um item da lista satisfaz uma condição.
 *
 * return:      1, se pelo menos um item da lista satisfaz a condição.
 *              0, se todos os itens da lista não satisfazem a condição.
 */
int anyMatch(List *list, predicate f);

/**
 * Obtém uma cópia superficial dos elementos da lista original.
 *
     * return:      O endereço da lista criada.
 */
List* getRange(List *list, int start, int end);

/**
 * Retorna o endereço de um vetor com as referências aos elementos da lista.
 *
 * return:      Um vetor, de tamanho igual a lista original, contendo as
 *              referências das informações contidas na lista original.
 */
void** toArray(List *list);

/**
 * Retorna um Iterator para iterar sobre os elementos da lista.
 *
 * return:      O endereço de um Iterator.
 */
Iterator* iterator(List *list);

/**
 * Verifica se o iterador contem um proximo elemento.
 *
 * return:      1, se existir um proximo elemento.
 *              0, caso contrario.
 */
int hasNext(Iterator *itr);

/**
 * Retorna o endereço do proximo elemento da lista durante a iteração.
 */
void* next(Iterator *itr);

#endif /*END LIST_H_*/
