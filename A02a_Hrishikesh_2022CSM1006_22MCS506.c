#include <stdio.h>
#include <stdlib.h>

#define QSIZE 10000

typedef struct Node {
    int val;
    struct Node *link;
} Node;

void display(Node *node) {
    if (node == NULL) {
        printf("E ");
        return;
    }
    printf("[");
    while (node != NULL) {
        printf("%d", node->val);
        node = node->link;
        if(node != NULL)
            printf("-");
    }
    printf("] ");
}

int size(Node *node) {
    int count = 0;
    if (node == NULL) {
        return 0;
    }
    while (node != NULL) {
        node = node->link;
        ++count;
    }
    return count;
}

Node *makeNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->val = data;
    node->link = NULL;

    return node;
}

void insertAtEnd(Node **headptr, int data) {
    if (*headptr == NULL) {
        *headptr = makeNode(data);
        return;
    }

    Node *temp = *headptr;
    while (temp->link != NULL)
        temp = temp->link;

    Node *node = makeNode(data);
    temp->link = node;
}

void insertInBeg(Node **headptr, int data) {
    if (*headptr == NULL) {
        *headptr = makeNode(data);
        return;
    }

    Node *node = makeNode(data);
    node->link = *headptr;
    *headptr = node;
}

void deleteFirst(Node **headptr) {
    if (*headptr == NULL) {
        printf("E ");
        return;
    } else if ((*headptr)->link == NULL) {
        Node *temp = *headptr;
        *headptr = NULL;
        free(temp);
        return;
    } else {
        Node *temp = *headptr;
        *headptr = (*headptr)->link;
        temp->link = NULL;
        free(temp);
    }
}

void deleteLast(Node **headptr) {
    if (*headptr == NULL) {
        printf("E ");
        return;
    } else if ((*headptr)->link == NULL) {
        Node *temp = *headptr;
        *headptr = NULL;
        free(temp);
        return;
    } else {
        Node *temp = *headptr;

        while (temp->link->link != NULL)
            temp = temp->link;

        Node *temp2 = temp->link;
        temp->link = NULL;
        free(temp2);
    }
}

void findNode(Node *headptr, int val) {
    if (headptr == NULL) {
        printf("E ");
        return;
    } else if ((headptr)->link == NULL) {
        if ((headptr)->val == val) {
        printf("1(0) ");
            return;
        } else {
            printf("N ");
            return;
        }
    } else {
        Node *temp = headptr;
        int count = 1;
        while (temp != NULL && temp->val != val) {
            temp = temp->link;
            ++count;
        }

        if (temp == NULL) {
            printf("N ");
            return;
        } else {
        	printf("%d(%ld) ", count, headptr - temp);
            return;
        }

    }
}

void deleteSpecific(Node **headptr, int val) {
    if (*headptr == NULL) {
        printf("E ");
        return;
    } else if ((*headptr)->val == val) {
        if ((*headptr)->link == NULL) {
            *headptr = NULL;
            free(*headptr);
            return;
        } else {
            Node *temp = *headptr;
            *headptr = (*headptr)->link;
            free(temp);
            return;
        }
    } else {
        Node *temp = *headptr;
        if (temp->link == NULL) {
            printf("N ");
            return;
        } else {
            while (temp->link != NULL && temp->link->val != val) {
                temp = temp->link;
            }

            if (temp->link == NULL) {
                printf("N ");
                return;
            } else {
                Node *temp2 = temp->link;
                temp->link = temp->link->link;
                free(temp2);
            }
        }
    }
}


void freeMemory(Node **headPtr) {
    if (*headPtr == NULL)
        return;

    Node *temp = *headPtr;

    while (*headPtr != NULL) {
        *headPtr = (*headPtr)->link;
        temp->link = NULL;
        free(temp);
        temp = *headPtr;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    int cases[t][QSIZE];                              //number of test cases

    for (int i = 0; i < t; ++i) {
        int N;                                          //number of queries
        scanf("%d", &N);

        int choice;
        int l = 0;
        for (int j = 0; j < N; ++j) {
            scanf("%d", &choice);
            cases[i][l] = choice;
            int val;
            if (choice == 1 || choice == 2 || choice == 5 || choice == 6) {
                ++l;
                scanf("%d", &val);
                cases[i][l] = val;
            }
            ++l;
        }
        cases[i][l] = -32763;
    }

    for (int i = 0; i < t; ++i) {
        printf("#%d ", i + 1);
        int j = 0;
        Node *head = NULL;
        while (cases[i][j] != -32763) {
            int choice = cases[i][j];
            int val;

            if (choice == 1) {
                ++j;
                val = cases[i][j];
                insertInBeg(&head, val);
                ++j;
            } else if (choice == 2) {
                ++j;
                val = cases[i][j];
                insertAtEnd(&head, val);
                ++j;
            } else if (choice == 3) {
                deleteFirst(&head);
                ++j;
            } else if (choice == 4) {
                deleteLast(&head);
                ++j;
            } else if (choice == 5) {
                ++j;
                val = cases[i][j];
                deleteSpecific(&head, val);
                ++j;
            } else if (choice == 6) {
                ++j;
                val = cases[i][j];
                findNode(head, val);
                ++j;
            } else if (choice == 7) {
                printf("%d ", size(head));
                ++j;
            } else if (choice == 8) {
                display(head);
                ++j;
            } 
            else if(choice == 0){
                freeMemory(&head);
                exit(1);
            }
            else {
                printf("W ");
                ++j;
            }
        }
        freeMemory(&head);
        printf("\n");
    }

    return 0;
}
