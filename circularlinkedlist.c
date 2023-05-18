#include<stdio.h>
#include<stdlib.h>


void PrintStudent(){
	char* name = "Kim sieun", id = "2021053007";

	printf("----------[%S][%s]----------", name, id);
}

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	PrintStudent();

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	if(*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // 헤드 포인터가 NULL인 경우 리스트가 비어있으므로 실패를 나타내는 -1을 반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 동적으로 할당
	node->key = key; // 새로운 노드의 key를 주어진 key로 설정
	node->rlink = NULL; // 새로운 노드의 오른쪽 링크를 NULL로 초기화
	node->llink = NULL; // 새로운 노드의 왼쪽 링크를 NULL로 초기화

	if (h->rlink == h)
	{
		// 리스트가 비어있는 경우
		h->rlink = node; // 헤드의 오른쪽 링크를 새로운 노드로 설정
		h->llink = node; // 헤드의 왼쪽 링크를 새로운 노드로 설정
		node->rlink = h; // 새로운 노드의 오른쪽 링크를 헤드로 설정
		node->llink = h; // 새로운 노드의 왼쪽 링크를 헤드로 설정
	} else {
		// 리스트가 비어있지 않은 경우
		h->llink->rlink = node; // 헤드의 왼쪽 노드의 오른쪽 링크를 새로운 노드로 설정
		node->llink = h->llink; // 새로운 노드의 왼쪽 링크를 헤드의 왼쪽 노드로 설정
		h->llink = node; // 헤드의 왼쪽 링크를 새로운 노드로 설정
		node->rlink = h; // 새로운 노드의 오른쪽 링크를 헤드로 설정
	}

	return 1; // 성공을 나타내는 1을 반환
}


int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n"); // 삭제할 노드가 없는 경우 메시지를 출력
		return 1; // 성공을 나타내는 1을 반환
	}

	listNode* nodetoremove = h->llink; // 삭제할 노드를 가리키는 포인터를 설정

	nodetoremove->llink->rlink = h; // 삭제할 노드의 이전 노드의 오른쪽 링크를 헤드로 설정
	h->llink = nodetoremove->llink; // 헤드의 왼쪽 링크를 삭제할 노드의 이전 노드로 설정

	free(nodetoremove); // 삭제할 노드를 해제

	return 1;
}

int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 동적으로 할당
	node->key = key; // 새로운 노드의 key를 주어진 key로 설정
	node->rlink = NULL; // 새로운 노드의 오른쪽 링크를 NULL로 초기화
	node->llink = NULL; // 새로운 노드의 왼쪽 링크를 NULL로 초기화


	node->rlink = h->rlink; // 새로운 노드의 오른쪽 링크를 헤드의 오른쪽 노드로 설정
	h->rlink->llink = node; // 헤드의 오른쪽 노드의 왼쪽 링크를 새로운 노드로 설정
	node->llink = h; // 새로운 노드의 왼쪽 링크를 헤드로 설정
	h->rlink = node; // 헤드의 오른쪽 링크를 새로운 노드로 설정

	return 1; // 성공을 나타내는 1을 반환
}

int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n"); // 삭제할 노드가 없는 경우 메시지를 출력
		return 0; // 실패를 나타내는 0을 반환
	}

	listNode* nodetoremove = h->rlink; // 삭제할 노드를 가리키는 포인터를 설정

	nodetoremove->rlink->llink = h; // 삭제할 노드의 다음 노드의 왼쪽 링크를 헤드로 설정
	h->rlink = nodetoremove->rlink; // 헤드의 오른쪽 링크를 삭제할 노드의 다음 노드로 설정

	free(nodetoremove); // 삭제할 노드를 해제

	return 1; // 성공을 나타내는 1을 반환
}


int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n"); // 뒤집을 노드가 없는 경우 메시지 출력
		return 0; // 실패를 나타내는 0을 반환
	}
	listNode *n = h->rlink; // 현재 노드를 가리키는 포인터
	listNode *trail = h; // 이전 노드를 가리키는 포인터
	listNode *middle = h; // 중간 노드를 가리키는 포인터

	h->llink = h->rlink; // 헤드의 왼쪽 링크를 첫 번째 노드로 설정

	while(n != NULL && n != h){
		trail = middle; // 이전 노드를 갱신
		middle = n; // 중간 노드를 갱신
		n = n->rlink; // 다음 노드로 이동
		middle->rlink = trail; // 중간 노드의 오른쪽 링크를 이전 노드로 설정
		middle->llink = trail->llink; // 중간 노드의 왼쪽 링크를 이전 노드의 왼쪽 링크로 설정
	}

	h->rlink = middle; // 헤드의 오른쪽 링크를 마지막 노드로 설정

	return 0; // 성공을 나타내는 0을 반환
}

int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; // 헤드 포인터가 NULL인 경우 실패를 나타내는 -1을 반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 동적으로 할당
	node->key = key; // 새로운 노드의 key를 주어진 key로 설정
	node->llink = node->rlink = NULL; // 새로운 노드의 링크를 NULL로 초기화

	if (h->rlink == h)
	{
		insertFirst(h, key); // 리스트가 비어있는 경우 첫 번째에 삽입
		return 1; // 성공을 나타내는 1을 반환
	}

	listNode* n = h->rlink; // 현재 노드를 가리키는 포인터

	while(n != NULL && n != h) {
		if(n->key >= key) {
			if(n == h->rlink) {
				insertFirst(h, key); // 첫 번째 노드보다 작은 경우 첫 번째에 삽입
			} else {
				node->rlink = n; // 새로운 노드의 오른쪽 링크를 현재 노드로 설정
				node->llink = n->llink; // 새로운 노드의 왼쪽 링크를 현재 노드의 왼쪽 링크로 설정
				n->llink->rlink = node; // 현재 노드의 왼쪽 링크를 새로운 노드로 설정
				n->llink = node; // 현재 노드의 왼쪽 링크를 새로운 노드로 설정
			}
			return 0; // 성공을 나타내는 0을 반환
		}

		n = n->rlink; // 다음 노드로 이동
	}

	insertLast(h, key); // 모든 노드보다 큰 경우 마지막에 삽입
	return 0; // 성공을 나타내는 0을 반환
}


int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n"); // 삭제할 노드가 없는 경우 메시지 출력
		return 0; // 실패를 나타내는 0을 반환
	}

	listNode* n = h->rlink; // 현재 노드를 가리키는 포인터

	while(n != NULL && n != h) {
		if(n->key == key) { // 삭제할 노드를 찾은 경우
			if(n == h->rlink) {
				deleteFirst(h); // 첫 번째 노드인 경우 첫 번째 노드 삭제 함수 호출
			} else if (n->rlink == h){
				deleteLast(h); // 마지막 노드인 경우 마지막 노드 삭제 함수 호출
			} else {
				n->llink->rlink = n->rlink; // 삭제할 노드의 이전 노드의 오른쪽 링크를 다음 노드로 설정
				n->rlink->llink = n->llink; // 삭제할 노드의 다음 노드의 왼쪽 링크를 이전 노드로 설정
				free(n); // 삭제할 노드 해제
			}
			return 0; // 성공을 나타내는 0을 반환
		}

		n = n->rlink; // 다음 노드로 이동
	}

	printf("cannot find the node for key = %d\n", key); // 해당 키의 노드를 찾지 못한 경우 메시지 출력
	return 0; // 실패를 나타내는 0을 반환
}