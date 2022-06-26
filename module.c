#include "module.h"
#define Node_number 10 //vertex 개수를 나타내는 수, 해당 수를 바꾸어서 vertex 개수가 다른 경우에도 적용 가능하다
#include <limits.h>
#define INF INT_MAX
void MinimumHopPath(int src, int dest) {
    // TODO: 
    // 1. Find the path with minimum # of hops
    // 2. Print the path
    int visit[Node_number] = { 0, }; //vertex 방문(처리) 여부
    queue* q = q_init(); //BFS를 위한 임시 저장소 queue 생성
    node* Path[Node_number] = { NULL, }; //각 노드까지 가는 최단 path를 저장

    for (int i = 0; i < Node_number; i++) //초기화
    {
        node* zero = init(i);
        Path[i] = zero;
    }

    int v = src; //v: 현재 처리하는 vertex
    visit[src] = 1; // src 방문 처리
    q_enqueue(q, src);

    while (v != dest)
    {
        v = q_dequeue(q); //dequeue한 노드 방문
        
        int next = 0;


        for (int ver = 0; ver < Node_number; ver++)
        {

            if (weighted_adj[v][ver] != 0 && visit[ver] != 1) //방문한 적 없고, 현재 노드에서 이어져있는 노드라면 enqueue하고 path 갱신
            {
                next = 1;
                q_enqueue(q, ver); 

                if (Path[v]->next != NULL)
                    Path[ver]->next = Path[v]->next;
                insert_node(Path[ver], 1, v); //path에 현재 노드 삽입 (path는 실제 path의 역순으로 기록)
                visit[ver] = 1;

            }
        }

    }

    printf("Minimum hop path: ");

    node* pnt = Path[dest]; //헤드 노드 포인터가 가르키는 노드를 가르키는 pnt 생성

    int size = 0;   //reverse하려고 하는 linked list의 크기를 나타내는 변수 생성 
    while (pnt != NULL)
    {
        pnt = pnt->next;//pnt를 이동시키기 위해 새로운 노드를 기존의 마지막 node의 주소값으로 입력
        size++;// linked list의 크기 1 증가
    }
    if (size == 2) //size가 2개면 head->next 출력 후 head 출력
    {
        node* pnt = Path[dest]->next;
        printf("%d ", pnt->value);
        printf("%d ", Path[dest]->value);
        

    }
    else {
        for (int pntsize = size; pntsize > 0; pntsize--) //size 값이 바뀌게 하지 않기 위해 복제된 pntsize 생성
        {
            pnt = Path[dest];// pnt를 head 노드포인터로 사용
            for (int j = pntsize; j > 1; j--)//reverse print를 위해 pnt를 이동해야 함. 이때 마지막 노드의 앞 노드까지만 이동시킴(마지막 노드는 초기화 값)
                pnt = pnt->next;//pnt를 이동시키기 위해 새로운 노드를 기존의 마지막 node의 주소값으로 입력
            printf("%d ", pnt->value);
        }
    }
    printf("\n");//출력이 마무리 되면 줄 바꿈까지 출력
    printf("# of hops : %d \n", size-1);

}

void ShortestTimePath(int src, int dest) {
    // TODO: 
    // 1. Find the path with shortest time
    // 2. Print the path
    int short_time[Node_number] = { 0, }; //해당 노드까지 가는 데 걸리는 시간, 0은 도달할 수 없음을 의미함
    int check[Node_number] = { 0, }; //해당 노드에 대한 최단 거리를 확인하였는지 여부를 표현. 1이면 완료됨을 의미함.
    node* Path[Node_number] = { NULL, };//각 노드까지 가는 데의 최단 경로를 표현. 0번째에는 0번 노드까지 가는 최단경로를 list로 연결
    for (int i = 0; i < Node_number; i++) //초기화
    {
        node* zero = init(i);
        Path[i] = zero;
    }

    check[src] = 1;

    int current = src; //current는 현재 처리 중인 노드
    int result = dijkstra(src,src, dest, &short_time, &Path, &check);
    printf("Shortest Time Path: ");
    print_reverse(Path[dest]);
    printf("Total time: ");
    printf("%d\n", result);

}
// Add your functions like enqueue, ...
int dijkstra(int src,int current, int dest, int* short_time, node** path, int* check) {
    int finished = 1; //모든 노드를 처리하거나 dest에 도착하면 finished=1이고 알고리즘을 종료함

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
        if (weighted_adj[current][idx] != 0) //현재 노드에서 갈 수 있는 노드에 대해서 계산
        {
            Append[idx] = *(short_time + current) + weighted_adj[current][idx]; //i 갱신 값: 현재 노드까지 걸리는 최단 시간+ 현재 노드에서 i번째 노드까지 걸리는 시간            
            if ((Append[idx] < *(short_time + idx) || *(short_time + idx) == 0 )&& idx != src) //갱신 값이 더 작거나, 기존 값이 초기화 값일 때 갱신
            {
                *(short_time + idx) = Append[idx]; //시간 갱신
                (*(path + idx))->next = path_current->next;//path 갱신
                insert_node(*(path + idx), 1, current);
            }
        }
    }



    int current_node = minheap_pop(short_time, check); //heap을 이용해서 가장 이동거리가 짧은 노드 구함
    *(check + current_node) = 1;

    //printf("check[%d]= %d\n", current_node, *(check + current_node));
    dijkstra(src, current_node, dest, short_time, path, check);
}


//About minheap

int minheap_pop(int* short_time, int* check) { //최소값을 산출해주는 함수
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
void Switch(int a, int b, queue* heap, queue* vertex) //주어진 index에 대하여 heap 순서 바꾸는 함수
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

    node* head = (node*)malloc(sizeof(node)); //head node에 동적변수 할당
    head->value = val; //head node의 value에 val 할당
    head->next = NULL; //head node의 next에 NULL 할당

    return head; //head node 포인터 반환
}
void append_node(node* head, int val) { 
    // O(n)
    node* appends = (node*)malloc(sizeof(node));//노드포인터 appends 할당
    appends->value = val; //appends에 입력 value 할당
    appends->next = NULL; //appends의 next가 가리키는 것을 NULL로 지정
    node* temp = head;// temp를 head 노드포인터로 사용(head pointer를 이동시키지 않기 위해 복제된 포인터 사용)
    while (temp->next != NULL)
        temp = temp->next; //temp를 linked list의 끝까지 이동
    temp->next = appends; //temp의 끝에 append node 를 연결

}
void insert_node(node* head, int idx, int val)
{  //idx가 1 인경우 O(1)
    node* new_node = (node*)malloc(sizeof(node)); //삽입할 node의 포인터를 new_node로 생성
    new_node->value = val; //new_node 의 value에 val 할당
    new_node->next = NULL; ///new_node의 next에 NULL 할당


    if (head->next == NULL)   //1번째 node(헤드 노드가 가르키는 node)가 null일 경우, 즉 node의 총 개수가 1개일 경우 새로운 노드를 헤드 노드 다음으로 배정함.
    {
        if (idx == 1)     // idx가 1일때, 즉 1번째 노드에 새로운 노드를 삽입하고자 할 때
            head->next = new_node; //1번째 node가 새로운 노드로 삽입
        else //1번째 노드 외에 삽입은 모두 out of range로서 오류 
        {
            printf("Wrong idx value! Put another value… \n");
            return;
        }
    }
    else
    {
        node* cop = head; //node가 두 개 이상인 경우,cop을 head 노드포인터로 사용(head pointer를 이동시키지 않기 위해 복제된 포인터 사용)
        for (int i = idx - 1; i > 0; i--)
        {
            cop = cop->next; //cop이 idx 앞 노드를 가르킬 때까지 linked list를 따라 이동

            if (cop->next == NULL && i != 1) //이동하는 과정에서 i가 1이 아닌 상태, 즉 마지막 node로 이동되지 않은 상태인데 다음 node가 NULL이면 오류 처리
            {
                printf("Wrong idx value! Put another value… \n");
                return;
            }

        }
        new_node->next = cop->next;//새로운 노드의 주소값을 cop이 가르키는 마지막 node의 주소값으로 입력
        cop->next = new_node; //새로운 노드를 기존의 마지막 node의 주소값으로 입력

    }
}
void print_reverse(node* head) {
    //O(n)

    node* pnt = head; //헤드 노드 포인터가 가르키는 노드를 가르키는 pnt 생성

    int size = 0;   //reverse하려고 하는 linked list의 크기를 나타내는 변수 생성 
    while (pnt != NULL)
    {
        pnt = pnt->next;//pnt를 이동시키기 위해 새로운 노드를 기존의 마지막 node의 주소값으로 입력
        size++;// linked list의 크기 1 증가
    }

    if (size == 1) //size가 1개면 head의 value를 출력
        printf("%d ", head->value);

    else if (size == 2) //size가 2개면 head->next 출력 후 head 출력
    {
        node* pnt = head->next;
        printf("%d ", pnt->value);
        printf("%d ", head->value);
    }
    else {
        for (int pntsize = size; pntsize > 0; pntsize--) //size 값이 바뀌게 하지 않기 위해 복제된 pntsize 생성
        {
            pnt = head;// pnt를 head 노드포인터로 사용
            for (int j = pntsize; j > 1; j--)//reverse print를 위해 pnt를 이동해야 함
                pnt = pnt->next;//pnt를 이동시키기 위해 새로운 노드를 기존의 마지막 node의 주소값으로 입력
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
        printf("%d ", pnt->value);//현재 node의 값을 출력
        pnt = pnt->next;//새로운 노드를 기존의 마지막 node의 주소값으로 입력
    }
    printf("\n");//출력이 마무리 되면 줄 바꿈까지 출력
}


//About Queue
queue* q_init() {
    queue* make = (queue*)malloc(sizeof(queue)); //새로운 queue 생성
    make->front = 0;
    make->rear = 0;
    for (int i = 0; i < 20; i++)
        make->element[i] = INF;
    return make;
}

void q_enqueue(queue* q, int val) { //O(1)
    if (q_is_full(q))
    {
        printf("enqueu not allowed\n"); //q가 모두 찼을 때 예외 처리
        return NULL;
    }
    q->element[q->rear] = val; //q의 element배열의 마지막 순서(rear가 가리키는 방)에 val라는 값을 할당
    q->rear = q->rear + 1; //rear는 방이 들어있는 마지막 방의 다음 방(빈 array) 순서 가짐
}

int q_dequeue(queue* q) { //(O(1))
    int deq;
    if (q_is_empty(q))
    {
        printf("dequeu not allowed\n"); //q가 비었을 때 예외 처리
        deq = NULL;
    }
    else
    {
        deq = q->element[q->front]; //지우고자 하는 자료(큐의 front가 가리키는 element)를 deq라는 변수에 할당
        q->front = q->front + 1; //큐의 front가 다음 방을 순서 가짐

    }
    return deq;
}

bool q_is_empty(queue* q) { //(O(1))
    bool empt = false;
    if ((q->front) == (q->rear)) // Element에 자료가 하나도 없으면 rear와 front가 가리키는 값 동일
        empt = true;
    return empt;
}

bool q_is_full(queue* q) { //(O(1))
    //q가 모두 차있으면 rear의 값= max_data
    if (q->rear == 20)
        return true;
    return false;
}