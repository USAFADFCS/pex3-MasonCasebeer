/** pagequeue.c
 * ===========================================================
 * Name: Mason Casebeer, Apr 8 2026
 * Section: CS483 / M4
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"
#include "listAsDoubleLinkedList.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    PageQueue* p = (PageQueue*) malloc(sizeof(PageQueue));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    p->maxSize = maxSize;
    return p;
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned int pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    PqNode* cur_node = pq->tail;
    long depth = 0;
    while(cur_node) {
        //HIT
        if(cur_node->pageNum == pageNum) {
            //if already tail do nothing 
            if(pq->tail == cur_node) {
                //should return depth 0 since it's the most recently used
                return depth;
            }
            //otherwise move to tail 
            else {
                //were going backwards so we need to calc depth from head
                deleteElementLinkedList(pq, pq->size - depth - 1);
                insertElementLinkedList(pq, pq->size, pageNum);
                return depth;
            }

        }
        depth++;
        cur_node = cur_node->prev;
    }

    if(pq->size >= pq->maxSize) {
        deleteElementLinkedList(pq, 0);
    }
    insertElementLinkedList(pq, pq->size, pageNum);
    return -1;

    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    PqNode *p = pq->head;
    while(p) {
        PqNode *next = p->next;
        free(p);
        p = next;
    }
    free(pq);
    // TODO:; Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    printLinkedList(pq);
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
