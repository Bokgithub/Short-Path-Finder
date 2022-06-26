
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define NODES 10

static int weighted_adj[10][10] = {
    0,  0,  9, 0,  12, 6,  0, 6,  0, 4, 0, 0,  0,  7, 0, 11, 10, 0, 11, 0,
    9,  0,  0, 0,  4,  13, 0, 12, 0, 6, 0, 7,  0,  0, 0, 5,  6,  0, 13, 0,
    12, 0,  4, 0,  0,  6,  0, 0,  0, 0, 6, 11, 13, 5, 6, 0,  0,  0, 0,  0,
    0,  10, 0, 6,  0,  0,  0, 0,  9, 0, 6, 0,  12, 0, 0, 0,  0,  0, 0,  7,
    0,  11, 0, 13, 0,  0,  9, 0,  0, 0, 4, 0,  6,  0, 0, 0,  0,  7, 0,  0};

void MinimumHopPath(int src, int dest);
void ShortestTimePath(int src, int dest);


// Add your functions and structs



typedef struct _node {
    int value;
    struct _node* next;
} node;

typedef struct _time {
    int vertex;
    int length;
}times;

typedef struct _queue {
    int front;
    int rear;
    int element[20];
} queue;

int minheap_pop(int* short_time, int* check);
int dijkstra(int src,int current, int dest, int* short_time, node** path, int* check);
node* init(int val);
void insert_node(node* head, int idx, int val);
void print_reverse(node* head);
void print_all(node* head);
void append_node(node* head, int val);

queue* q_init();
void Switch(int a, int b, queue* heap, queue* vertex);
void q_enqueue(queue* q, int val);
int q_dequeue(queue* q);
bool q_is_empty(queue* q);
bool q_is_full(queue* q);