#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

typedef struct graphNode { //인접리스트의 노드 구조체
	int vertex; //정점
	struct graphNode* link; //다음 노드로의 포인터
}graphNode;

typedef struct Graph { //그래프를 인접리스트로 표현하기 위한 구조체
	int n; //노드의 갯수
	graphNode* list[MAX_VERTEX]; //그래프용 인접리스트 생성
	int Dvisited[MAX_VERTEX]; //DFS용 flag
	int Bvisited[MAX_VERTEX]; //BFS용 flag
}Graph;

typedef struct stack{ //DFS용 스택 구조체
	int data;
	struct stack *link;
}stack;

stack* top;

typedef struct Qnode{ //BFS용 큐 구조체
	int data;
	struct Qnode *link;
}Qnode;

typedef struct {
	Qnode *front;
	Qnode *rear;
}Queue;

/*BFS용*/
Queue *createQ();
void enQueue(Queue *q, int item);
int deQueue(Queue *q);
int QisEmpty(Queue *q);
int BFS(Graph* g, int v);


/*DFS용*/
int isEmpty();
void push(int n);
int pop();
int DFS(Graph* g, int v);


Graph* initialize(Graph* g);
int freeGraph(Graph* g);
int insertVertex(Graph* g);
int insertEdge(Graph* g, int u, int v);
void printGraph(Graph* g);



int main()
{
	int u, v;
	char command;
	Graph* graph=NULL;
	printf("[-------[황슬비] [2018032027] ------");

	do{
		printf("\n----------------------------------------------------------------\n");
		printf("                     Graph Searches                             \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph   = z          \n");
		printf(" Insert Vertex      = v        Insert Edge           = e \n");
		printf(" Depth First Search = d        Breath First Search   = b \n");
		printf(" Print Graph        = p        Quit                  = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout); //이클립스 scanf 오류 해결용
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			graph=initialize(graph);
			break;

		case 'v': case 'V':
			 insertVertex(graph);
			break;

		case 'e': case 'E':
			printf("u = ");
			fflush(stdout);
			scanf("%d", &u);
			printf("v = ");
			fflush(stdout);
			scanf("%d", &v);
			insertEdge(graph, u, v);
			break;

		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &u);
			DFS(graph, u);
			break;

		case 'b': case 'B':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &u);
			BFS(graph, u);
			break;

		case 'p': case 'P':
			printGraph(graph);
			break;

		case 'q': case 'Q':
			freeGraph(graph);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

Graph* initialize(Graph* g){
	/*g가 NULL이 아니면, freeGraph를 호출하여 할당된 메모리 모두 해제*/
	if(g != NULL)
		freeGraph(g);

	/*graph에 대한 배열 메모리 할당하여 리턴*/
	Graph* temp=(Graph *)malloc(sizeof(Graph));
	int v;
	temp->n=0; //정점의 갯수=0으로 설정
	for(v=0; v<MAX_VERTEX; v++){ //그래프리스트 초기화
		temp->list[v]=NULL;
		temp->Dvisited[v]=FALSE;
		temp->Bvisited[v]=FALSE;
	}
	return temp;
}


int freeGraph(Graph* g){
	int v=0;
	graphNode* p = g->list[v];
	graphNode* prev=NULL;
	for(v=0; v<MAX_VERTEX; v++){ //리스트[0]~리스트[9] 반복문 돌며 초기화
		p=g->list[v];
		while(p !=NULL){ //리스트[v]에서 p가 NULL이 될 때까지 prev초기화, loop in loop
				prev=p; //각 리스트별 노드들 메모리 할당 해제
				p=p->link;
				free(prev);
			}
		}
	free(g); //모든 리스트 내용 해제 후 그래프 메모리 해제
	return 0;
}

int isEmpty(){ //스택이 비었는지 확인
	if (top==NULL){ //빈 스택
		return 1;
	}
	else
		return 0;
}

int QisEmpty(Queue *q){
	if(q->front == NULL){ //빈 큐

		return 1;
	}
	else
		return 0;
}


/*Stack용 함수*/
void push(int n){
	stack* temp=(stack *)malloc(sizeof(stack));
	temp->data=n; //스택 메모리 할당해주어 데이터 삽입
	temp->link=top;
	top=temp; //스택포인터 top는 가장 최근에 들어온 메모리를 포인터
}

int pop(){
	int item;
	stack* temp=top;

	if(isEmpty()){ //빈 스택인 경우
		printf("\n Stack is empty!!!!\n");
		return 0;
	}
	else{ //빈 스택이 아닌 경우
		item=temp->data; //item으로 top 부분 데이터 가져오기
		top=temp->link;
		free(temp);
		return item;
	}
}


/*Queue용 함수*/

Queue *createQ(){ //큐 생성
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	q->front=NULL;//초기화
	q->rear=NULL;
	return q;
}
void enQueue(Queue *q, int item){
	Qnode *node=(Qnode *)malloc(sizeof(Qnode));
	node->data=item; //메모리 할당하여 내용 넣기
	node->link=NULL;

	if(q->front==NULL){ //빈 큐인 경우
		q->front=node;
		q->rear=node;
	}
	else{
		q->rear->link=node;
		q->rear=node;
	}
}

int deQueue(Queue *q){
	Qnode *temp=q->front;
	int item;
	if(QisEmpty(q)){ //빈 큐인 경우
		printf("\n Queue is empty!!!!\n");
		return 0;
	}
	else{
		item = temp->data; //item으로 데이터 가져오기
		q->front = q->front->link; //데이터 뺀 후 front 이동
		if(q->front == NULL) //마지막 데이터 뺀 경우
			q->rear=NULL;
		free(temp);
		return item;
	}
}

/*Depth First Search*/
int DFS(Graph* g, int v){
	graphNode* t; //포인터 생성
	top=NULL;
	push(v); //스택에 push
	g->Dvisited[v]=TRUE;//visited flag
	printf("[ %d ]", v);

	while(!isEmpty()){ //스택이 비어있지 않은 경우
		v=pop();
		t=g->list[v];

		while(t){ //포인터가 NULL을 가리키지 않는 경우, 리스트 vertex가 있는 경우
			if(!g->Dvisited[t->vertex]){ //visited flag가 설정되어있지 않은 경우
				if(isEmpty()){ //스택이 비어있으면 스택에 푸쉬
					push(v);
				}
				push(t->vertex);
				g->Dvisited[t->vertex]=TRUE;//visted flag 설정
				printf("[ %d ]", t->vertex);
				v=t->vertex;
				t=g->list[v];
			}
			else //visited flag 설정되어있는 경우 넘어감
				t=t->link;
		}
	}

	return 0;
}


/*Breath First Search*/
int BFS(Graph* g, int v){
	graphNode* t; //노드포인터 생성
	Queue* q; //큐포인터 생성
	q=createQ(); //큐 생성
	g->Bvisited[v]=TRUE; //visited flag
	printf("[ %d ]",v);
	enQueue(q, v); //큐에 삽입

	while(!QisEmpty(q)){ //큐가 비어있지 않은 경우
		v=deQueue(q); //v로 큐 데이터 받아옴

		for(t=g->list[v]; t; t=t->link){
			if(!g->Bvisited[t->vertex]){//visited flag 되어있지 않은 경우
				g->Bvisited[t->vertex] = TRUE; //flag설정해줌
				printf("%d", t->vertex);
				enQueue(q, t->vertex); //큐에 삽입
			}
		}
	}

	return 0;
}

int insertVertex(Graph* g){

	if((g->n)+1>MAX_VERTEX){ //그래프 정점 갯수가 10개를 넘을 시
		printf("!!!!!Exceed the num of vertex!!!!!!\n");
		return 0;
	}
	g->n++; //초과하지 않은 경우 정점 갯수 +1

	return 0;
}

int insertEdge(Graph* g, int u, int v){
	graphNode* unode;
	graphNode* vnode;
	graphNode* ptr;
	graphNode* prev;

	if((g->n)<=u || (g->n)<=v){ //그래프에 없는 정점인 경우
		printf("vertex is not in this graph!!\n");
		return 0;
	}
	ptr=g->list[u];
	while(ptr){//edge가 이미 존재하는지 확인
		if(ptr->vertex==v){
			printf("This edge is already exists!!\n");
			return 0;
		}
		ptr=ptr->link;
	}

	ptr=g->list[u];
	prev=NULL;
	unode = (graphNode *)malloc(sizeof(graphNode)); //정점 생성
	unode->vertex=v;
	if(!ptr||ptr->vertex>v){ //첫번째 노드이거나 기존 vertex보다 작은 경우, 첫번째 노드로 오는 경우
			unode->link=g->list[u];
			g->list[u]=unode;
		}
	else{//오름차순 정렬
		while(ptr){
		if(ptr->vertex<v){ //vertex보다 큰 경우, 순회 돌며 적절한 위치 찾아가서 연결
			prev=ptr;
			ptr=ptr->link;
			}
		else{ //자리 찾으면 반복문 탈출
			break;
		}
		}
		unode->link=prev->link; //노드 연결
		prev->link=unode;
	}


	ptr=g->list[v];
	prev=NULL;
	vnode = (graphNode *)malloc(sizeof(graphNode)); //정점 생성
	vnode->vertex=u; //digraph가 아니므로 (u,v),(v,u)함께 생성
	if(!ptr||ptr->vertex>u){
			vnode->link=g->list[v];
			g->list[v]=vnode;
		}
	else{ //오름차순 정렬
		while(ptr){
		if(ptr->vertex<u){//첫번째 노드이거나 기존 vertex보다 작은 경우, 첫번째 노드로 오는 경우
			prev=ptr; //첫번째 노드로 삽입
			ptr=ptr->link;
			}
		else{ //적절한 위치에서 반복문 탈출
				break;
				}
		}
		vnode->link=prev->link; //노드 연결
		prev->link=vnode;
	}

	return 0;
}

void printGraph(Graph* g){
	int i;
	graphNode* ptr; //포인터 생성
	printf("\n---PRINT\n");

	if(g->n==0){ //vertex가 없는 경우 ,vertex갯수=0인 경우
		printf("Nothing to print....\n");
		return;
	}

	for(i=0; i<g->n; i++){ //리스트 순회돌기
		printf("\n [ %d ]", i);
		ptr=g->list[i];
		while(ptr){ //리스트 별로 노드 순회돌며 출력
			printf("->[ %d ]", ptr->vertex);
			ptr=ptr->link;
		}
	}

}


