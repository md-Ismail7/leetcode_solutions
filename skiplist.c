#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEVEL 16   // enough for 2*10^5 operations

typedef struct Node {
    int val;
    struct Node* forward[MAX_LEVEL];
} Node;

typedef struct {
    Node* head;
    int level;
} Skiplist;

// Create new node
Node* createNode(int val, int level) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    for (int i = 0; i < MAX_LEVEL; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

// Random level generator
int randomLevel() {
    int level = 1;
    while ((rand() &1) && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Constructor
Skiplist* skiplistCreate() {
    Skiplist* list = (Skiplist*)malloc(sizeof(Skiplist));
    list->head = createNode(-1, MAX_LEVEL);
    list->level = 1;
    return list;
}

// Search
bool skiplistSearch(Skiplist* list, int target) {
    Node* cur = list->head;
    for (int i = list->level - 1; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->val < target) {
            cur = cur->forward[i];
        }
    }
    cur = cur->forward[0];
    return (cur && cur->val == target);
}

// Add
void skiplistAdd(Skiplist* list, int num) {
    Node* update[MAX_LEVEL];
    Node* cur = list->head;

    for (int i = list->level - 1; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->val < num) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    int lvl = randomLevel();
    if (lvl > list->level) {
        for (int i = list->level; i < lvl; i++) {
            update[i] = list->head;
        }
        list->level = lvl;
    }

    Node* newNode = createNode(num, lvl);
    for (int i = 0; i < lvl; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

// Erase
bool skiplistErase(Skiplist* list, int num) {
    Node* update[MAX_LEVEL];
    Node* cur = list->head;

    for (int i = list->level - 1; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->val < num) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    cur = cur->forward[0];
    if (!cur || cur->val != num) return false;

    for (int i = 0; i < list->level; i++) {
        if (update[i]->forward[i] != cur) break;
        update[i]->forward[i] = cur->forward[i];
    }
    free(cur);

    while (list->level > 1 && list->head->forward[list->level - 1] == NULL) {
        list->level--;
    }
    return true;
}

// Free memory
void skiplistFree(Skiplist* list) {
    Node* cur = list->head;
    while (cur) {
        Node* next = cur->forward[0];
        free(cur);
        cur = next;
    }
    free(list);
}

/**
 * Your Skiplist struct will be instantiated and called as such:
 * Skiplist* obj = skiplistCreate();
 * bool param_1 = skiplistSearch(obj, target);
 
 * skiplistAdd(obj, num);
 
 * bool param_3 = skiplistErase(obj, num);
 
 * skiplistFree(obj);
*/