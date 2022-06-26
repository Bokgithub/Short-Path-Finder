#include "module.h"
#define Node_number 10 //vertex ������ ��Ÿ���� ��, �ش� ���� �ٲپ vertex ������ �ٸ� ��쿡�� ���� �����ϴ�
#include <limits.h>
#define INF INT_MAX
void MinimumHopPath(int src, int dest) {
    // TODO: 
    // 1. Find the path with minimum # of hops
    // 2. Print the path
    int visit[Node_number] = { 0, }; //vertex �湮(ó��) ����
    queue* q = q_init(); //BFS�� ���� �ӽ� ����� queue ����
    node* Path[Node_number] = { NULL, }; //�� ������ ���� �ִ� path�� ����

    for (int i = 0; i < Node_number; i++) //�ʱ�ȭ
    {
        node* zero = init(i);
        Path[i] = zero;
    }

    int v = src; //v: ���� ó���ϴ� vertex
    visit[src] = 1; // src �湮 ó��
    q_enqueue(q, src);

    while (v != dest)
    {
        v = q_dequeue(q); //dequeue�� ��� �湮
        
        int next = 0;


        for (int ver = 0; ver < Node_number; ver++)
        {

            if (weighted_adj[v][ver] != 0 && visit[ver] != 1) //�湮�� �� ����, ���� ��忡�� �̾����ִ� ����� enqueue�ϰ� path ����
            {
                next = 1;
                q_enqueue(q, ver); 

                if (Path[v]->next != NULL)
                    Path[ver]->next = Path[v]->next;
                insert_node(Path[ver], 1, v); //path�� ���� ��� ���� (path�� ���� path�� �������� ���)
                visit[ver] = 1;

            }
        }

    }

    printf("Minimum hop path: ");

    node* pnt = Path[dest]; //��� ��� �����Ͱ� ����Ű�� ��带 ����Ű�� pnt ����

    int size = 0;   //reverse�Ϸ��� �ϴ� linked list�� ũ�⸦ ��Ÿ���� ���� ���� 
    while (pnt != NULL)
    {
        pnt = pnt->next;//pnt�� �̵���Ű�� ���� ���ο� ��带 ������ ������ node�� �ּҰ����� �Է�
        size++;// linked list�� ũ�� 1 ����
    }
    if (size == 2) //size�� 2���� head->next ��� �� head ���
    {
        node* pnt = Path[dest]->next;
        printf("%d ", pnt->value);
        printf("%d ", Path[dest]->value);
        

    }
    else {
        for (int pntsize = size; pntsize > 0; pntsize--) //size ���� �ٲ�� ���� �ʱ� ���� ������ pntsize ����
        {
            pnt = Path[dest];// pnt�� head ��������ͷ� ���
            for (int j = pntsize; j > 1; j--)//reverse print�� ���� pnt�� �̵��ؾ� ��. �̶� ������ ����� �� �������� �̵���Ŵ(������ ���� �ʱ�ȭ ��)
                pnt = pnt->next;//pnt�� �̵���Ű�� ���� ���ο� ��带 ������ ������ node�� �ּҰ����� �Է�
            printf("%d ", pnt->value);
        }
    }
    printf("\n");//����� ������ �Ǹ� �� �ٲޱ��� ���
    printf("# of hops : %d \n", size-1);

}

void ShortestTimePath(int src, int dest) {
    // TODO: 
    // 1. Find the path with shortest time
    // 2. Print the path
    int short_time[Node_number] = { 0, }; //�ش� ������ ���� �� �ɸ��� �ð�, 0�� ������ �� ������ �ǹ���
    int check[Node_number] = { 0, }; //�ش� ��忡 ���� �ִ� �Ÿ��� Ȯ���Ͽ����� ���θ� ǥ��. 1�̸� �Ϸ���� �ǹ���.
    node* Path[Node_number] = { NULL, };//�� ������ ���� ���� �ִ� ��θ� ǥ��. 0��°���� 0�� ������ ���� �ִܰ�θ� list�� ����
    for (int i = 0; i < Node_number; i++) //�ʱ�ȭ
    {
        node* zero = init(i);
        Path[i] = zero;
    }

    check[src] = 1;

    int current = src; //current�� ���� ó�� ���� ���
    int result = dijkstra(src,src, dest, &short_time, &Path, &check);
    printf("Shortest Time Path: ");
    print_reverse(Path[dest]);
    printf("Total time: ");
    printf("%d\n", result);

}
// Add your functions like enqueue, ...
int dijkstra(int src,int current, int dest, int* short_time, node** path, int* check) {
    int finished = 1; //��� ��带 ó���ϰų� dest�� �����ϸ� finished=1�̰� �˰����� ������

    for (int c = 0; c < Node_number; c++)
    {
        if (*(check + c) == 1)
            finished = 0;
    }
    if (finished == 1 || dest==current)
        return  *(short_time + dest);

    int Append[Node_number] = { 0, };
    node* path_current = *(path + current);

    for (int idx = 0; idx < Node_number; idx++)
    {
        if (weighted_adj[current][idx] != 0) //���� ��忡�� �� �� �ִ� ��忡 ���ؼ� ���
        {
            Append[idx] = *(short_time + current) + weighted_adj[current][idx]; //i ���� ��: ���� ������ �ɸ��� �ִ� �ð�+ ���� ��忡�� i��° ������ �ɸ��� �ð�            
            if ((Append[idx] < *(short_time + idx) || *(short_time + idx) == 0 )&& idx != src) //���� ���� �� �۰ų�, ���� ���� �ʱ�ȭ ���� �� ����
            {
                *(short_time + idx) = Append[idx]; //�ð� ����
                (*(path + idx))->next = path_current->next;//path ����
                insert_node(*(path + idx), 1, current);
            }
        }
    }



    int current_node = minheap_pop(short_time, check); //heap�� �̿��ؼ� ���� �̵��Ÿ��� ª�� ��� ����
    *(check + current_node) = 1;

    //printf("check[%d]= %d\n", current_node, *(check + current_node));
    dijkstra(src, current_node, dest, short_time, path, check);
}


//About minheap

int minheap_pop(int* short_time, int* check) { //�ּҰ��� �������ִ� �Լ�
    queue* heap = q_init();
    queue* vertex_ = q_init();
    for (int i = 0; i < Node_number; i++) {
        if (*(check + i) != 1 && *(short_time + i) != 0)
        {
            q_enqueue(heap, *(short_time + i));
            q_enqueue(vertex_, i);

            int j = heap->rear - 1;
            while (heap->element[j / 2] > heap->element[j])
            {
                Switch(j / 2, j, heap, vertex_);
                j = j / 2;
            }
        }
    }


    int deq = q_dequeue(vertex_);
    return deq;
}
void Switch(int a, int b, queue* heap, queue* vertex) //�־��� index�� ���Ͽ� heap ���� �ٲٴ� �Լ�
{
    int aa = heap->element[a];
    int bb = heap->element[b];
    heap->element[a] = bb;
    heap->element[b] = aa;

    int cc = vertex->element[a];
    int dd = vertex->element[b];
    vertex->element[a] = dd;
    vertex->element[b] = cc;

}
//About linked list
node* init(int val) { //(O(1))

    node* head = (node*)malloc(sizeof(node)); //head node�� �������� �Ҵ�
    head->value = val; //head node�� value�� val �Ҵ�
    head->next = NULL; //head node�� next�� NULL �Ҵ�

    return head; //head node ������ ��ȯ
}
void append_node(node* head, int val) { 
    // O(n)
    node* appends = (node*)malloc(sizeof(node));//��������� appends �Ҵ�
    appends->value = val; //appends�� �Է� value �Ҵ�
    appends->next = NULL; //appends�� next�� ����Ű�� ���� NULL�� ����
    node* temp = head;// temp�� head ��������ͷ� ���(head pointer�� �̵���Ű�� �ʱ� ���� ������ ������ ���)
    while (temp->next != NULL)
        temp = temp->next; //temp�� linked list�� ������ �̵�
    temp->next = appends; //temp�� ���� append node �� ����

}
void insert_node(node* head, int idx, int val)
{  //idx�� 1 �ΰ�� O(1)
    node* new_node = (node*)malloc(sizeof(node)); //������ node�� �����͸� new_node�� ����
    new_node->value = val; //new_node �� value�� val �Ҵ�
    new_node->next = NULL; ///new_node�� next�� NULL �Ҵ�


    if (head->next == NULL)   //1��° node(��� ��尡 ����Ű�� node)�� null�� ���, �� node�� �� ������ 1���� ��� ���ο� ��带 ��� ��� �������� ������.
    {
        if (idx == 1)     // idx�� 1�϶�, �� 1��° ��忡 ���ο� ��带 �����ϰ��� �� ��
            head->next = new_node; //1��° node�� ���ο� ���� ����
        else //1��° ��� �ܿ� ������ ��� out of range�μ� ���� 
        {
            printf("Wrong idx value! Put another value�� \n");
            return;
        }
    }
    else
    {
        node* cop = head; //node�� �� �� �̻��� ���,cop�� head ��������ͷ� ���(head pointer�� �̵���Ű�� �ʱ� ���� ������ ������ ���)
        for (int i = idx - 1; i > 0; i--)
        {
            cop = cop->next; //cop�� idx �� ��带 ����ų ������ linked list�� ���� �̵�

            if (cop->next == NULL && i != 1) //�̵��ϴ� �������� i�� 1�� �ƴ� ����, �� ������ node�� �̵����� ���� �����ε� ���� node�� NULL�̸� ���� ó��
            {
                printf("Wrong idx value! Put another value�� \n");
                return;
            }

        }
        new_node->next = cop->next;//���ο� ����� �ּҰ��� cop�� ����Ű�� ������ node�� �ּҰ����� �Է�
        cop->next = new_node; //���ο� ��带 ������ ������ node�� �ּҰ����� �Է�

    }
}
void print_reverse(node* head) {
    //O(n)

    node* pnt = head; //��� ��� �����Ͱ� ����Ű�� ��带 ����Ű�� pnt ����

    int size = 0;   //reverse�Ϸ��� �ϴ� linked list�� ũ�⸦ ��Ÿ���� ���� ���� 
    while (pnt != NULL)
    {
        pnt = pnt->next;//pnt�� �̵���Ű�� ���� ���ο� ��带 ������ ������ node�� �ּҰ����� �Է�
        size++;// linked list�� ũ�� 1 ����
    }

    if (size == 1) //size�� 1���� head�� value�� ���
        printf("%d ", head->value);

    else if (size == 2) //size�� 2���� head->next ��� �� head ���
    {
        node* pnt = head->next;
        printf("%d ", pnt->value);
        printf("%d ", head->value);
    }
    else {
        for (int pntsize = size; pntsize > 0; pntsize--) //size ���� �ٲ�� ���� �ʱ� ���� ������ pntsize ����
        {
            pnt = head;// pnt�� head ��������ͷ� ���
            for (int j = pntsize; j > 1; j--)//reverse print�� ���� pnt�� �̵��ؾ� ��
                pnt = pnt->next;//pnt�� �̵���Ű�� ���� ���ο� ��带 ������ ������ node�� �ּҰ����� �Է�
            printf("%d ", pnt->value);
        }
    }
    printf("\n");
}
void print_all(node* head)
{ //O(n)
    node* pnt = head;
    while (pnt != NULL)
    {
        printf("%d ", pnt->value);//���� node�� ���� ���
        pnt = pnt->next;//���ο� ��带 ������ ������ node�� �ּҰ����� �Է�
    }
    printf("\n");//����� ������ �Ǹ� �� �ٲޱ��� ���
}


//About Queue
queue* q_init() {
    queue* make = (queue*)malloc(sizeof(queue)); //���ο� queue ����
    make->front = 0;
    make->rear = 0;
    for (int i = 0; i < 20; i++)
        make->element[i] = INF;
    return make;
}

void q_enqueue(queue* q, int val) { //O(1)
    if (q_is_full(q))
    {
        printf("enqueu not allowed\n"); //q�� ��� á�� �� ���� ó��
        return NULL;
    }
    q->element[q->rear] = val; //q�� element�迭�� ������ ����(rear�� ����Ű�� ��)�� val��� ���� �Ҵ�
    q->rear = q->rear + 1; //rear�� ���� ����ִ� ������ ���� ���� ��(�� array) ���� ����
}

int q_dequeue(queue* q) { //(O(1))
    int deq;
    if (q_is_empty(q))
    {
        printf("dequeu not allowed\n"); //q�� ����� �� ���� ó��
        deq = NULL;
    }
    else
    {
        deq = q->element[q->front]; //������� �ϴ� �ڷ�(ť�� front�� ����Ű�� element)�� deq��� ������ �Ҵ�
        q->front = q->front + 1; //ť�� front�� ���� ���� ���� ����

    }
    return deq;
}

bool q_is_empty(queue* q) { //(O(1))
    bool empt = false;
    if ((q->front) == (q->rear)) // Element�� �ڷᰡ �ϳ��� ������ rear�� front�� ����Ű�� �� ����
        empt = true;
    return empt;
}

bool q_is_full(queue* q) { //(O(1))
    //q�� ��� �������� rear�� ��= max_data
    if (q->rear == 20)
        return true;
    return false;
}