#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node *prev, *next; // for LRU doubly linked list
    struct Node *hnext;       // for hash table chaining
} Node;

typedef struct {
    int capacity;
    int size;
    Node **hash;      // hash map (key → node pointer)
    Node *head, *tail; // doubly linked list
} LRUCache;

#define HASH_SIZE 10007 // prime number > possible keys

// Hash function
int hashFunc(int key) {
    return key % HASH_SIZE;
}

// Create new node
Node* createNode(int key, int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    node->hnext = NULL;
    return node;
}

// Create LRU Cache
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->size = 0;
    obj->hash = (Node**)calloc(HASH_SIZE, sizeof(Node*));

    obj->head = createNode(0, 0); // dummy head
    obj->tail = createNode(0, 0); // dummy tail
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;

    return obj;
}

// Remove node from doubly linked list
void removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

// Insert node right after head (most recently used)
void insertAfterHead(LRUCache* obj, Node* node) {
    node->next = obj->head->next;
    node->prev = obj->head;
    obj->head->next->prev = node;
    obj->head->next = node;
}

// Lookup node in hash table
Node* getFromHash(LRUCache* obj, int key) {
    int h = hashFunc(key);
    Node* curr = obj->hash[h];
    while (curr) {
        if (curr->key == key) return curr;
        curr = curr->hnext; // follow hash chain
    }
    return NULL;
}

// Add to hash table
void addToHash(LRUCache* obj, Node* node) {
    int h = hashFunc(node->key);
    node->hnext = obj->hash[h];
    obj->hash[h] = node;
}

// Remove from hash table
void removeFromHash(LRUCache* obj, int key) {
    int h = hashFunc(key);
    Node *curr = obj->hash[h], *prev = NULL;
    while (curr) {
        if (curr->key == key) {
            if (prev) prev->hnext = curr->hnext;
            else obj->hash[h] = curr->hnext;
            return;
        }
        prev = curr;
        curr = curr->hnext;
    }
}

// Get value
int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = getFromHash(obj, key);
    if (!node) return -1;

    // Move to head (most recently used)
    removeNode(node);
    insertAfterHead(obj, node);
    return node->value;
}

// Put key-value
void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = getFromHash(obj, key);
    if (node) {
        node->value = value;
        removeNode(node);
        insertAfterHead(obj, node);
    } else {
        if (obj->size == obj->capacity) {
            // Remove LRU (tail->prev)
            Node* lru = obj->tail->prev;
            removeNode(lru);
            removeFromHash(obj, lru->key);
            free(lru);
            obj->size--;
        }
        Node* newNode = createNode(key, value);
        insertAfterHead(obj, newNode);
        addToHash(obj, newNode);
        obj->size++;
    }
}

// Free cache
void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(obj->hash);
    free(obj);
}
