#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key; // 노드의 데이터 값.
    struct Node* llink; // 이전 노드를 가리키는 포인터.
    struct Node* rlink; // 다음 노드를 가리키는 포인터.
} listNode;

// 함수 원형 선언.
int initialize(listNode** h);
int freeList(listNode* h);
void printList(listNode* h);

int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

int main()
{
	printf("[----- [이은총] [2022041043] -----]\n");
    char command;
    int key;
    listNode* headnode = NULL;

    do {
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

        switch (command) {
            case 'z':
            case 'Z':
                initialize(&headnode); // 리스트 초기화.
                break;
            case 'p':
            case 'P':
                printList(headnode); // 리스트 출력.
                break;
            case 'i':
            case 'I':
                printf("Your Key = ");
                scanf("%d", &key);
                insertNode(headnode, key); // 노드 삽입.
                break;
            case 'd':
            case 'D':
                printf("Your Key = ");
                scanf("%d", &key);
                deleteNode(headnode, key); // 노드 삭제.
                break;
            case 'n':
            case 'N':
                printf("Your Key = ");
                scanf("%d", &key);
                insertLast(headnode, key); // 연결 리스트의 마지막 노드 삽입.
                break;
            case 'e':
            case 'E':
                deleteLast(headnode); // 연결 리스트의 마지막 노드 삭제.
                break;
            case 'f':
            case 'F':
                printf("Your Key = ");
                scanf("%d", &key);
                insertFirst(headnode, key); // 연결 리스트의 첫 번째에 노드 삽입.
                break;
            case 't':
            case 'T':
                deleteFirst(headnode); // 연결 리스트의 첫 번째 노드 삭제.
                break;
            case 'r':
            case 'R':
                invertList(headnode); // 연결 리스트를 역순으로 변환.
                break;
            case 'q':
            case 'Q':
                freeList(headnode); // 연결 리스트의 메모리 해제.
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

// 연결 리스트를 초기화하는 함수.
int initialize(listNode** h)
{
    if (*h != NULL)
        freeList(*h);  // 기존에 할당된 메모리 해제.

    *h = (listNode*)malloc(sizeof(listNode)); // 헤드 노드 메모리 할당.
    (*h)->rlink = *h; // 헤드 노드의 다음 노드를 자기 자신으로 설정.
    (*h)->llink = *h; // 헤드 노드의 이전 노드를 자기 자신으로 설정.
    (*h)->key = -9999; // 헤드 노드의 데이터 값은 의미 없는 값으로 설정.
    return 1;
}

// 연결 리스트의 메모리를 해제하는 함수.
int freeList(listNode* h)
{
    listNode* p = h->rlink; // 헤드 노드의 다음 노드를 가리키는 포인터.
    listNode* prev = NULL; // 이전 노드를 가리키는 포인터.

    while (p != h) { // 헤드 노드에 도달할 때까지 반복.
        prev = p;  // 이전 노드를 현재 노드로 설정.
		p = p->rlink; // 다음 노드로 이동.
        free(prev); // 이전 노드의 메모리 해제.
    }

    free(h); // 헤드 노드 메모리 해제.

    return 0;
}

// 연결 리스트를 출력하는 함수.
void printList(listNode* h)
{
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n"); // 리스트가 비어있는 경우 출력할 내용이 없음을 알림.
        return; 
    }

    p = h->rlink;

    while (p != h) {
        printf("[ [%d]=%d ] ", i, p->key); // 현재 노드의 인덱스와 데이터 값을 출력.
        p = p->rlink; // 다음 노드로 이동.
        i++;
    }
    printf("  items = %d\n", i); // 리스트의 전체 항목 개수 출력.

    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // 헤드 노드의 링크 주소 출력.

    i = 0;
    p = h->rlink;
    while (p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // 각 노드의 인덱스, 데이터 값, 링크 주소 출력.
        p = p->rlink;
        i++;
    }
}

// 연결 리스트의 마지막에 노드를 삽입하는 함수.
int insertLast(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성.
    newNode->key = key; // 새로운 노드의 데이터 값 설정.

    newNode->rlink = h; // 새로운 노드의 다음 노드를 헤드 노드로 설정.
    newNode->llink = h->llink; // 새로운 노드의 이전 노드를 헤드 노드의 이전 노드로 설정.

    h->llink->rlink = newNode; // 헤드 노드의 이전 노드의 다음 노드를 새로운 노드로 설정.
    h->llink = newNode; // 헤드 노드의 이전 노드를 새로운 노드로 설정.

    return 1;
}

// 연결 리스트의 마지막에 노드를 삭제하는 함수.
int deleteLast(listNode* h)
{
    if (h->rlink == h) // 리스트가 비어있는 경우.
        return 0;

    listNode* lastNode = h->llink; // 마지막 노드를 가리키는 포인터.

    lastNode->llink->rlink = h; // 마지막 노드의 이전 노드의 다음 노드를 헤드 노드로 설정.
    h->llink = lastNode->llink; // 헤드 노드의 이전 노드를 마지막 노드의 이전 노드로 설정.

    free(lastNode); // 마지막 노드의 메모리 해제.

    return 1;
}

// 연결 리스트의 첫 번째에 노드를 삽입하는 함수.
int insertFirst(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
    newNode->key = key; // 새로운 노드의 데이터 값 설정.

    newNode->rlink = h->rlink; // 새로운 노드의 다음 노드를 헤드 노드의 다음 노드로 설정.
    newNode->llink = h; // 새로운 노드의 이전 노드를 헤드 노드로 설정.

    h->rlink->llink = newNode; // 헤드 노드의 다음 노드의 이전 노드를 새로운 노드로 설정.
    h->rlink = newNode; // 헤드 노드의 다음 노드를 새로운 노드로 설정.

    return 1;
}

// 연결 리스트의 첫 번째 노드를 삭제하는 함수.
int deleteFirst(listNode* h)
{
    if (h->rlink == h) // 리스트가 비어있는 경우.
        return 0;

    listNode* firstNode = h->rlink; // 첫 번째 노드를 가리키는 포인터.

    firstNode->rlink->llink = h; // 첫 번째 노드의 다음 노드의 이전 노드를 헤드 노드로 설정.
    h->rlink = firstNode->rlink; // 헤드 노드의 다음 노드를 첫 번째 노드의 다음 노드로 설정.

    free(firstNode); // 첫 번째 노드의 메모리 해제.

    return 1;
}

// 연결 리스트를 역순으로 변환하는 함수.
int invertList(listNode* h)
{
    listNode* p = h->rlink;
    listNode* temp;

    h->llink = p; // 헤드 노드의 이전 노드를 첫 번째 노드로 설정.

    while (p != h) {
        temp = p->rlink;
        p->rlink = p->llink;
        p->llink = temp;
        p = p->llink;
    }

    h->rlink = p->llink; // 헤드 노드의 다음 노드를 역순으로 정렬된 마지막 노드로 설정.

    return 0;
}

// 정렬된 순서로 노드를 삽입하는 함수.
int insertNode(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성.
    newNode->key = key; // 새로운 노드의 데이터 값 설정.

    listNode* p = h->rlink;

    while (p != h) {
        if (p->key <= key && key < p->rlink->key) { // 노드의 데이터 값이 삽입할 위치를 찾은 경우.
            newNode->rlink = p->rlink;
            newNode->llink = p;
            p->rlink->llink = newNode;
            p->rlink = newNode;
            return 1;
        }
        p = p->rlink;
    }

    newNode->rlink = h;
    newNode->llink = h->llink;
    h->llink->rlink = newNode;
    h->llink = newNode;

    return 1;
}

// 특정 값의 노드를 삭제하는 함수.
int deleteNode(listNode* h, int key)
{
    listNode* p = h->rlink;

    while (p != h) {
        if (p->key == key) { // 삭제할 노드를 찾은 경우.
            p->llink->rlink = p->rlink;
            p->rlink->llink = p->llink;
            free(p); // 노드 메모리 해제.
            return 1;
        }
        p = p->rlink;
    }

    return 0;
}