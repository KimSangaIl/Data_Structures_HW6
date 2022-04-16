/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제*/
	/* headNode도 해제되어야 함.*/
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

/* list 처음에 key에 대한 노드하나를 추가*/
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//동적 할당으로 노드 생성
	node->key = key;	//생성된 노드의 키 값에 입력 받은 키 값을 저장

	if (h->first == NULL) {	//리스트가 공백일 경우
		h->first = node;	//헤더 노드를 생성된 노드로 초기화
		node->link = NULL;	//생성한 노드가 처음이자 마지막 노드이므로 링크를 NULL로 초기화
	}

	else {
		listNode* back = h->first;
		listNode* front = h->first;		//리스트의 노드를 임시로 저장할 노드 2개를 선언하고 헤더 노드로 초기화
		while (back != NULL) {			//임시 노드가 마지막 노드가 될때까지 반복
			if (back->key > key) {		//임시 노드의 키 값이 입력 받은 키 값보다 큰 경우
				if(back == h->first) {	//임시 노드가 헤더 노드인 경우 즉 리스트 맨 앞에 생성한 노드를 삽입하는 경우
					h->first = node;	//헤더 노드를 생성한 노드로 초기화
					node->link = back;	//생성한 노드의 링크를 원래 헤더 노드였던 노드에 연결
				}
				else {					//임시 노드가 헤더 노드가 아닌경우 즉 리스트 중간에 생성한 노드를 삽입하는 경우
					node->link = back;	//생성한 노드의 링크를 임시 노드와 연결
					front->link = node;	//큰 키 값을 가진 노드의 앞 노드의 링크를 생성한 노드에 연결
				}
				return 0;		//노드를 삽입했다면 함수를 종료
			}
			front = back;		//front노드를 back노드로 초기화 하고 back노드는 자신이 링크한 노드로 이동함
			back = back->link;	//front노드의 링크는 back노드와 연결됨
		}					//입력 받은 키 값보다 큰 값이 없어서 반복문 종료
		front->link = node;	//front노드의 링크를 생성한 노드에 연결
		node->link = NULL;	//생성한 노드가 마지막 노드이므로 링크를 NULL로 초기화
	}
	
	return 0;
}

/* list에 key에 대한 노드하나를 추가*/
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//동적 할당으로 노드 생성
	node->key = key;	//생성된 노드의 키 값을 입력 받은 키 값으로 초기화
	node->link = NULL;	//생성된 노드가 마지막 노드이므로 링크 값을 NULL로 초기화

	listNode* temp = h->first;		//리스트의 노드를 임시로 저장할 노드 선언 및 헤더 노드로 초기화
	while (temp->link != NULL) {	//임시 노드를 한칸씩 뒤로 옮기면서 마지막 노드가 될때까지 반복
		temp = temp->link;
	}
	temp->link = node;	//마지막 노드의 링크를 생성한 노드에 연결
	return 0;
}

/* list의 첫번째 노드 삭제*/
int deleteFirst(headNode* h) {

	if (h->first == NULL) printf("Nothing to Delete\n");	//공백 리스트라면 경고 메시지 출력
	
	else {
		listNode* temp = h->first;	//임시 노드 선언 및 헤더 노드로 초기화
		h->first = temp->link;		//헤더 노드를 삭제할 노드가 링크한 노드와 연결
		free(temp);					//temp노드의 메모리를 해제해서 노드를 삭제
	}
	return 0;
}

/* list에서 key에 대한 노드 삭제*/
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) printf("Nothing to Delete\n");	//공백 리스트라면 경고 메시지 출력

	else {							//공백 리스트가 아닐 경우
		listNode* back = h->first;	//임시 노드 선언 및 헤더 노드로 초기화
		listNode* front = NULL;		//임시 노드 선언 및 NULL로 초기화

		while (back != NULL) {					//임시 노드가 마지막 노드가 될때까지 반복
			if (back->key == key) {				//입력 받은 키 값과 같은 키 값을 가진 노드를 찾았을때
				if (back == h->first) {			//찾은 노드가 헤더 노드일 경우
					h->first = back->link;		//헤더 노드를 삭제할 노드가 링크한 노드와 연결
				}
				else {							//찾은 노드가 리스트의 중간 노드일 경우
					front->link = back->link;	//삭제할 노드 앞 노드의 링크를 삭제할 노드가 링크한 노드와 연결
				}
				free(back);		//back노드의 메모리를 해제해서 노드를 삭제
				return 0;
			}
			front = back;		//front노드를 back노드로 초기화 하고 back노드는 자신이 링크한 노드로 이동함
			back = back->link;	//front노드의 링크는 back노드와 연결됨
		}
		printf("Cannot search the node for key = %d\n", key);	//입력 받은 키 값과 같은 키 값을 가진 노드를 찾지 못하면 경고 메시지 출력
	}
	return 0;
}

/* list의 마지막 노드 삭제*/
int deleteLast(headNode* h) {

	if (h->first == NULL) printf("Nothing to Delete\n");	//공백 리스트라면 경고 메시지 출력

	else {							//공백 리스트가 아닐 경우
		listNode* back = h->first;	//임시 노드 선언 및 헤더 노드로 초기화
		listNode* front = NULL;		//임시 노드 선언 및 NULL로 초기화

		if (back->link == NULL) {	//마지막 노드가 첫번째 노드인 경우
			h->first = NULL;		//헤더 노드가 마지막 노드이므로 NULL로 초기화
			free(back);				//back노드의 메모리를 해제해서 노드를 삭제
		}
		else {								//노드가 2개 이상인 경우 즉 마지막 노드가 첫번째 노드가 아닌 경우
			while (back->link != NULL) {	//back노드가 마지막 노드가 될때까지 반복
				front = back;				//front노드를 back노드로 초기화 하고 back노드는 자신이 링크한 노드로 이동함
				back = back->link;			//front노드의 링크는 back노드와 연결됨
			}								//반복문이 종료되면 back노드는 마지막 노드 front노드는 끝에서 두번째 노드가 됨
			front->link = NULL;				//front노드가 마지막 노드가 되야하므로 링크를 NULL로 초기화
			free(back);						//back노드의 메모리를 해제해서 노드를 삭제
		}
	}
	return 0;
}

/* 리스트의 링크를 역순으로 재 배치*/
int invertList(headNode* h) {

	if (h->first == NULL) printf("Nothing to Delete\n");	//공백 리스트라면 경고 메시지 출력

	else {						//공백 리스트가 아닌 경우
		listNode* a = h->first;	//임시 노드 선언 및 헤더 노드로 초기화
		listNode* b = NULL;
		listNode* c = NULL;		//임시 노드 선언 및 NULL로 초기화

		while (a != NULL) {		//a노드가 마지막 노드가 될때까지 반복
			c = b;				//c노드를 b노드로 초기화
			b = a;				//b노드를 a노드로 초기화
			a = a->link;		//a노드를 a노드가 연결된 노드로 초기화
			b->link = c;		//b노드의 링크를 c노드로 초기화 즉 링크의 방향을 바꾼다
		}	//반복문이 한번 반복될때 마다 a노드는 리스트를 따라서 한칸씩 앞으로 가고 b와 c도 한칸씩 앞으로 가면서 링크의 방향을 바꾼다
		h->first = b;			//헤더 노드를 b노드로 초기화 즉 마지막 노드를 헤더 노드로 바꾸면서 리스트가 역순이 된다
	}
	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

