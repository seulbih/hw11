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
	int visited[MAX_VERTEX]; //flag
}Graph;

typedef struct stack{
	int data;
	struct stack *link;
}stack;

stack* top;

Graph* initialize(Graph* g);
int freeGraph(Graph* g);
int insertVertex(Graph* g);
int insertEdge(Graph* g, int u, int v);
int DFS(Graph* g, int v);
int BFS(Graph* g, int v);
int isEmpty();
void push(int n);
int pop();




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
		fflush(stdout);
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
		temp->visited[v]=FALSE;
	}
	return temp;
}


int freeGraph(Graph* g){
	int v=0;
	graphNode* p = g->list[v];
	graphNode* prev=NULL;
	for(v=0; v<MAX_VERTEX; v++){ //리스트[0]~리스트[9] 반복문 돌며 초기화
		p=g->list[v];
		while(p !=NULL){ //리스트[v]에서 p가 NULL이 될 때까지 prev초기화
				prev=p;
				p=p->link;
				free(prev);
			}
		}
	free(g);
	return 0;
}

int isEmpty(){ //스택이 비었는지 확인
	if (top==NULL){
		return 1;
	}
	else
		return 0;
}

void push(int n){
	stack* temp=(stack *)malloc(sizeof(stack));
	temp->data=n;
	temp->link=top;
	top=temp;
}

int pop(){
	int item;
	stack* temp=top;

	if(isEmpty()){
		printf("\n Stack is empty!!!!\n");
		return 0;
	}
	else{
		item=temp->data;
		top=temp->link;
		free(temp);
		return item;
	}
}

int DFS(Graph* g, int v){
	graphNode* t;
	top=NULL;
	push(v);
	g->visited[v]=TRUE;
	printf("[ %d ]", v);

	while(!isEmpty()){
		v=pop();
		t=g->list[v];

		while(t){
			if(!g->visited[t->vertex]){
				if(isEmpty()){
					push(v);
				}
				push(t->vertex);
				g->visited[t->vertex]=TRUE;
				printf("[ %d ]", t->vertex);
				v=t->vertex;
				t=g->list[v];
			}
			else
				t=t->link;
		}
	}

	return 0;
}
int BFS(Graph* g, int v){

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
	if(!ptr||ptr->vertex>v){
			unode->link=g->list[u];
			g->list[u]=unode;
		}
	else{
		while(ptr){
		if(ptr->vertex<v){
			prev=ptr;
			ptr=ptr->link;
			}
		else{
			break;
		}
		}
		unode->link=prev->link;
		prev->link=unode;
	}


	/*vnode = (graphNode *)malloc(sizeof(graphNode)); //정점 생성
	vnode->vertex=u; //digraph가 아니므로 (u,v),(v,u)함께 생성
	vnode->link=g->list[v];
	g->list[v]=vnode;*/

	ptr=g->list[v];
	prev=NULL;
	vnode = (graphNode *)malloc(sizeof(graphNode)); //정점 생성
	vnode->vertex=u; //digraph가 아니므로 (u,v),(v,u)함께 생성
	if(!ptr||ptr->vertex>u){
			vnode->link=g->list[v];
			g->list[v]=vnode;
		}
	else{
		while(ptr){
		if(ptr->vertex<u){
			prev=ptr;
			ptr=ptr->link;
			}
		else{
				break;
				}
		}
		vnode->link=prev->link;
		prev->link=vnode;
	}

	return 0;
}

void printGraph(Graph* g){
	int i;
	graphNode* ptr;
	printf("\n---PRINT\n");

	if(g->n==0){
		printf("Nothing to print....\n");
		return;
	}

	for(i=0; i<g->n; i++){
		printf("\n [ %d ]", i);
		ptr=g->list[i];
		while(ptr){
			printf("->[ %d ]", ptr->vertex);
			ptr=ptr->link;
		}
	}

}


