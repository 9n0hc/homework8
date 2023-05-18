#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key; // ����� ������ ��.
    struct Node* llink; // ���� ��带 ����Ű�� ������.
    struct Node* rlink; // ���� ��带 ����Ű�� ������.
} listNode;

// �Լ� ���� ����.
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
	printf("[----- [������] [2022041043] -----]\n");
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
                initialize(&headnode); // ����Ʈ �ʱ�ȭ.
                break;
            case 'p':
            case 'P':
                printList(headnode); // ����Ʈ ���.
                break;
            case 'i':
            case 'I':
                printf("Your Key = ");
                scanf("%d", &key);
                insertNode(headnode, key); // ��� ����.
                break;
            case 'd':
            case 'D':
                printf("Your Key = ");
                scanf("%d", &key);
                deleteNode(headnode, key); // ��� ����.
                break;
            case 'n':
            case 'N':
                printf("Your Key = ");
                scanf("%d", &key);
                insertLast(headnode, key); // ���� ����Ʈ�� ������ ��� ����.
                break;
            case 'e':
            case 'E':
                deleteLast(headnode); // ���� ����Ʈ�� ������ ��� ����.
                break;
            case 'f':
            case 'F':
                printf("Your Key = ");
                scanf("%d", &key);
                insertFirst(headnode, key); // ���� ����Ʈ�� ù ��°�� ��� ����.
                break;
            case 't':
            case 'T':
                deleteFirst(headnode); // ���� ����Ʈ�� ù ��° ��� ����.
                break;
            case 'r':
            case 'R':
                invertList(headnode); // ���� ����Ʈ�� �������� ��ȯ.
                break;
            case 'q':
            case 'Q':
                freeList(headnode); // ���� ����Ʈ�� �޸� ����.
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

// ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�.
int initialize(listNode** h)
{
    if (*h != NULL)
        freeList(*h);  // ������ �Ҵ�� �޸� ����.

    *h = (listNode*)malloc(sizeof(listNode)); // ��� ��� �޸� �Ҵ�.
    (*h)->rlink = *h; // ��� ����� ���� ��带 �ڱ� �ڽ����� ����.
    (*h)->llink = *h; // ��� ����� ���� ��带 �ڱ� �ڽ����� ����.
    (*h)->key = -9999; // ��� ����� ������ ���� �ǹ� ���� ������ ����.
    return 1;
}

// ���� ����Ʈ�� �޸𸮸� �����ϴ� �Լ�.
int freeList(listNode* h)
{
    listNode* p = h->rlink; // ��� ����� ���� ��带 ����Ű�� ������.
    listNode* prev = NULL; // ���� ��带 ����Ű�� ������.

    while (p != h) { // ��� ��忡 ������ ������ �ݺ�.
        prev = p;  // ���� ��带 ���� ���� ����.
		p = p->rlink; // ���� ���� �̵�.
        free(prev); // ���� ����� �޸� ����.
    }

    free(h); // ��� ��� �޸� ����.

    return 0;
}

// ���� ����Ʈ�� ����ϴ� �Լ�.
void printList(listNode* h)
{
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n"); // ����Ʈ�� ����ִ� ��� ����� ������ ������ �˸�.
        return; 
    }

    p = h->rlink;

    while (p != h) {
        printf("[ [%d]=%d ] ", i, p->key); // ���� ����� �ε����� ������ ���� ���.
        p = p->rlink; // ���� ���� �̵�.
        i++;
    }
    printf("  items = %d\n", i); // ����Ʈ�� ��ü �׸� ���� ���.

    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // ��� ����� ��ũ �ּ� ���.

    i = 0;
    p = h->rlink;
    while (p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // �� ����� �ε���, ������ ��, ��ũ �ּ� ���.
        p = p->rlink;
        i++;
    }
}

// ���� ����Ʈ�� �������� ��带 �����ϴ� �Լ�.
int insertLast(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� ����.
    newNode->key = key; // ���ο� ����� ������ �� ����.

    newNode->rlink = h; // ���ο� ����� ���� ��带 ��� ���� ����.
    newNode->llink = h->llink; // ���ο� ����� ���� ��带 ��� ����� ���� ���� ����.

    h->llink->rlink = newNode; // ��� ����� ���� ����� ���� ��带 ���ο� ���� ����.
    h->llink = newNode; // ��� ����� ���� ��带 ���ο� ���� ����.

    return 1;
}

// ���� ����Ʈ�� �������� ��带 �����ϴ� �Լ�.
int deleteLast(listNode* h)
{
    if (h->rlink == h) // ����Ʈ�� ����ִ� ���.
        return 0;

    listNode* lastNode = h->llink; // ������ ��带 ����Ű�� ������.

    lastNode->llink->rlink = h; // ������ ����� ���� ����� ���� ��带 ��� ���� ����.
    h->llink = lastNode->llink; // ��� ����� ���� ��带 ������ ����� ���� ���� ����.

    free(lastNode); // ������ ����� �޸� ����.

    return 1;
}

// ���� ����Ʈ�� ù ��°�� ��带 �����ϴ� �Լ�.
int insertFirst(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� ����
    newNode->key = key; // ���ο� ����� ������ �� ����.

    newNode->rlink = h->rlink; // ���ο� ����� ���� ��带 ��� ����� ���� ���� ����.
    newNode->llink = h; // ���ο� ����� ���� ��带 ��� ���� ����.

    h->rlink->llink = newNode; // ��� ����� ���� ����� ���� ��带 ���ο� ���� ����.
    h->rlink = newNode; // ��� ����� ���� ��带 ���ο� ���� ����.

    return 1;
}

// ���� ����Ʈ�� ù ��° ��带 �����ϴ� �Լ�.
int deleteFirst(listNode* h)
{
    if (h->rlink == h) // ����Ʈ�� ����ִ� ���.
        return 0;

    listNode* firstNode = h->rlink; // ù ��° ��带 ����Ű�� ������.

    firstNode->rlink->llink = h; // ù ��° ����� ���� ����� ���� ��带 ��� ���� ����.
    h->rlink = firstNode->rlink; // ��� ����� ���� ��带 ù ��° ����� ���� ���� ����.

    free(firstNode); // ù ��° ����� �޸� ����.

    return 1;
}

// ���� ����Ʈ�� �������� ��ȯ�ϴ� �Լ�.
int invertList(listNode* h)
{
    listNode* p = h->rlink;
    listNode* temp;

    h->llink = p; // ��� ����� ���� ��带 ù ��° ���� ����.

    while (p != h) {
        temp = p->rlink;
        p->rlink = p->llink;
        p->llink = temp;
        p = p->llink;
    }

    h->rlink = p->llink; // ��� ����� ���� ��带 �������� ���ĵ� ������ ���� ����.

    return 0;
}

// ���ĵ� ������ ��带 �����ϴ� �Լ�.
int insertNode(listNode* h, int key)
{
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� ����.
    newNode->key = key; // ���ο� ����� ������ �� ����.

    listNode* p = h->rlink;

    while (p != h) {
        if (p->key <= key && key < p->rlink->key) { // ����� ������ ���� ������ ��ġ�� ã�� ���.
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

// Ư�� ���� ��带 �����ϴ� �Լ�.
int deleteNode(listNode* h, int key)
{
    listNode* p = h->rlink;

    while (p != h) {
        if (p->key == key) { // ������ ��带 ã�� ���.
            p->llink->rlink = p->rlink;
            p->rlink->llink = p->llink;
            free(p); // ��� �޸� ����.
            return 1;
        }
        p = p->rlink;
    }

    return 0;
}