#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10


typedef struct graphNode { //인접리스트의 노드 구조체
	int vertex; //정점
	struct graphNode* link; //다음 노드로의 포인터
}graphNode;

typedef struct Graph { //그래프를 인접리스트로 표현하기 위한 구조체
	int n; //노드의 갯수
	graphNode* list[MAX_VERTEX]; //그래프용 인접리스트 생성
}Graph;

short int visited[MAX_VERTEX];


Graph* initialize(Graph *g);
int freeGraph(Graph *g);
int insertVertex(Graph *g);
int insertEdge(Graph *g, int u, int v);

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
			printf("u = ");
			fflush(stdout);
			scanf("%d", &v);
			insertEdge(graph, u, v);
			break;

		case 'd': case 'D':

			break;

		case 'b': case 'B':

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

int insertVertex(Graph* g){

	if((g->n)+1>MAX_VERTEX){ //그래프 정점 갯수가 10개를 넘을 시
		printf("!!!!!Exceed the num of vertex!!!!!!\n");
		return 0;
	}
	g->n++; //초과하지 않은 경우 정점 갯수 +1

	return 0;
}

int insertEdge(Graph* g, int u, int v){
	graphNode* node;
	if((g->n)<=u || (g->n)<=v){ //그래프에 없는 정점인 경우
		printf("vertex is not in this graph!!\n");
		return 0;
	}
	node = (graphNode *)malloc(sizeof(graphNode)); //정점 생성
	node->vertex=v;
	node->link=g->list[u];
	g->list[u]=node;

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


