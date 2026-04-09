/** 
 * ================================================================
 * Name: Mason Casebeer
 * Section: M6
 * Project: Implementation of Double-Linked List Library
 * =================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "listAsDoubleLinkedList.h"
#include "pagequeue.h"

PageQueue* createLinkedList() {
    PageQueue *list = (PageQueue*) malloc(sizeof(PageQueue));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void deleteLinkedList(PageQueue* list) {
    PqNode* current = list->head;
    while (current != NULL) {
        PqNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}


int lengthOfLinkedList(PageQueue* list) {
    return list->size;
}

void printLinkedList(PageQueue* list) {
    PqNode* currentPqNode = list->head;
    int currentPosition = 1;
    while (currentPosition <= lengthOfLinkedList(list)) {
        printf("%ld ",currentPqNode->pageNum);
        currentPqNode = currentPqNode -> next;
        ++ currentPosition;
    }
    printf("\n");
}

int getElementLinkedList(PageQueue* list, int position) {
    if(position >= lengthOfLinkedList(list) || position < 0) {
        printf("Error, index out of bounds\n");
        return -1;
    }
    PqNode* currentPqNode = list->head;
    for(int i = 0; i < position; ++i) {
        currentPqNode = currentPqNode->next;
    }
    return currentPqNode->pageNum;
}

void deleteElementLinkedList(PageQueue* list, int position) {
    if(position >= list->size) {
        return;
    }
    //do nothing
    if(list -> size == 0) {
        return;
    }
    //no elements
    if(list->size == 1) {
        list-> head = NULL;
        list-> tail = NULL;
        list-> size --;
        return;
    }
    PqNode* temp;
    if(position == 0) {
        //deleting first item
        temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
        list -> size--;
    }
    else {
        //deleting last item
        if(position == lengthOfLinkedList(list)-1) {
            PqNode* temp = list->tail->prev;
            temp->next = NULL;
            free(list->tail);
            list->tail = temp;
            list -> size --;
        }
        else {
            //deleting in list
            PqNode* before = list->head;
            for(int i = 1; i< position; ++i) {
                before = before->next;
            }
            PqNode* del = before->next;               
            before->next = del->next;
            del->next->prev = before;
            free(del);
            list->size --;
        }
    }
}

void insertElementLinkedList(PageQueue* list, int position, long element) {
    PqNode* new = (PqNode*) malloc(sizeof(PqNode));
    new ->pageNum = element;
    //if empty
    if(list->size == 0) {
        list->head = new;
        list->tail = new;
        list -> size++;
        return;
    }
    //inserting at end
    if(position==0){
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
        list -> size++;
        return;
    }
    //inserting at start
    if(position == list->size) {
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
        list -> size++;
        return;
    }
    //if inserting in middle
    PqNode* before = list->head;
    for(int i = 1; i< position; ++i) {
        before = before->next;
    }
    new->next = before->next;
    new->prev = before;
    new->next->prev = new;
    before->next = new;
    list->size ++; 
}

void appendElementLinkedList(PageQueue* list, int element) {
    insertElementLinkedList(list,list->size,element);
}

void changeElementLinkedList(PageQueue* list, int position, int newElement) {
    PqNode* temp = list->head;
    for(int i = 1; i < position; ++i) {
        temp = temp->next;
    }    
    temp->pageNum = newElement;
}

int findElementLinkedList(PageQueue* list, int element) {
    PqNode* temp = list->head;
    for(int i = 0; i <= list->size; ++i) {
        if(temp->pageNum == element) {
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

void selSortLinkedList(PageQueue* list) {
    return;
}

void insertSortLinkedList(PageQueue* list) {
    return;
}



//INSERT AND DELETE ARE ONLY CHANGES FROM SINGLEY LINKED LIST
//REMEMBER APPEND AND PREPEND SHOULD USE INSERT
