/******************************************************************************
 * BIBLIOTECA - ARRAY REDIMENSIONÁVEL                                         *
 *****************************************************************************/

/**
 *  TODO: Implementar funções.
 *
 *  BUGS:
 */


#ifndef ARRAYLIST_H_
  #define ARRAYLIST_H_

#ifndef LIST_H_
#   include "list.h"
#endif

#ifdef TYPE_OF_LIST
#   undef TYPE_OF_LIST
#   define TYPE_OF_LIST "ARRAY LIST"
#endif

#define DEFAULT_SIZE    10

/*******************************************************************************
 * DEFINIÇÃO DE TIPOS                                                          *
 ******************************************************************************/

/*
 * Definição de uma lista.
  */
struct _List 
{
    unsigned int _size;
    void** _elements;
};

/*
 * Definição de um iterador.
 */
struct _Iterator {

};

/******************************************************************************
 * IMPLEMENTAÇÕES ARRAYLIST                                                   *
 ******************************************************************************/

List* newList() 
{
    List *list= malloc(sizeof(List));
    list->_size = DEFAULT_SIZE;
    list->_elements = calloc(sizeof(void*), list->size);
}

List* newListOfSize(int size) 
{

}

static void grow(List *list) 
{
    list->_size = list->_size + (list->_size >> 1);
    if (list->_size < 0) list->_size = DEFAULT_SIZE;
}

int count(List *list) 
{
    int i;

    i = 0;
    for (i = 0; i < list->_size; i++) 
    {
        if (list->_elements[i] != NULL) 
        {
            i++;
        }
    }
    return i;
}

int isEmpty(List *list) 
{

}

List* collect(List *list, filter f) 
{

}

void* getAtIndex(List *list, int index) 
{

}

int getIndexOf(List *list, void *item, compare f) 
{

}

void* getFirst(List *list) 
{

}

void* removeFirstOccurence(List *list, void *item, compare f) 
{

}

void* pop(List *list) 
{

}

void push(List *list, void* item) 
{

}

void* removeAtIndex(List *list, int index) 
{

}

void clearList(List *list) 
{

}

void deleteList(List *list) 
{

}

int countOccurences(List *list, void *item, compare f) 
{

}

void* searchElement(List *list, void *item, compare f) {

}

int contains(List *list, void *item, compare f) {

}

void removeAllOccurences(List *list, void *item, compare f) {

}

void removeDuplicateItems(List *list, compare f) {

}

void sort(List *list, compare f) {

}

void forEach(List *list, function f) {

}

void _forEachNode(List *list, function f) {

}

void copyTo(List *from, List *to) {

}

void reverse(List *list) {

}

void append(List *l1, List *l2) {

}

List* join(List *l1, List *l2) {

}

int disjoint(List *l1, List *l2, compare f) {

}

void intercalate(List *l1, List *l2) {

}

void fill(List *list, void *item) {

}

void replace(List *list, void *t, void *t2, compare f) {

}

void* max(List *list, compare f) {

}

void* min(List *list, compare f) {

}

int allMatch(List *list, predicate f) {

}

int anyMatch(List *list, predicate f) {

}

void** toArray(List *list) {

}


/******************************************************************************
 * ITERATOR                                                                   *
 *****************************************************************************/

Iterator* iterator(List *list) {

}

int hasNext(Iterator *itr) {

}

void* next(Iterator *itr) {

}

#endif /*END ARRAYLIST_H_*/
