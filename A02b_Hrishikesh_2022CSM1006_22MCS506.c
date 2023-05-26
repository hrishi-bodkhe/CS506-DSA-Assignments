#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *link;
} Node;

void multiply(Node **headptr, int j);

void display(Node *node);

Node *makeNode(int data);

void insertAtEnd(Node **headptr, int data);

void freeMemory(Node **headptr);

void reverse(Node **headptr);

void update(Node *head, Node *node, int data);

void countEndZeroes(Node *headptr);

void pattern(Node *head, char q[3]);

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        int N;
        char q[3];
        scanf("%d", &N);
        scanf("%s", q);

        Node *head = makeNode(1);

        for (int j = 2; j <= N; ++j) {
            int k = j;

            while (k > 0) {
                multiply(&head, j);
                --k;
            }
        }

        countEndZeroes(head);
        reverse(&head);
        pattern(head, q);
        display(head);
        freeMemory(&head);
    }

    return 0;
}

void pattern(Node *head, char q[]) {
    int i = 0;
    int qsize = 0;

    while (q[i] != '\0') {
        ++qsize;
        ++i;
    }

    i = 0;
    int l = 0, count = 0;
    Node *temp = head;
    Node *start;
    while (temp != NULL) {
        while (temp != NULL && (temp->val != (q[i] - '0')))
            temp = temp->link;

        if (temp == NULL)
            break;
        start = temp->link;

        while (i < qsize && temp != NULL) {
            if (temp->val == (q[i] - '0')) {
                temp = temp->link;
                ++l;
                ++i;
            } else {
                i = 0;
                break;
            }

            if (l == qsize) {
                i = 0;
                break;
            }
        }

        if (l == qsize)
            ++count;
        l = 0;
        temp = start;
    }

    printf("%d ", count);
}

void countEndZeroes(Node *head) {
    int count = 0;

    while (head != NULL) {
        if (head->val == 0)
            ++count;
        else {
            printf("%d ", count);
            return;
        }
        head = head->link;
    }
}

void multiply(Node **headptr, int j) {
    Node *temp = *headptr;
    int carry = 0;

    if (temp->link == NULL) {                               //if there is only one node
        int mul = temp->val * j + carry;
        update(*headptr, temp, mul % 10);
        carry = mul / 10;

        if (carry == 0)
            return;
        insertAtEnd(headptr, carry);
        return;
    }

    while (temp->link != NULL) {                            //traverse till last node
        int mul = temp->val * j + carry;
        update(*headptr, temp, mul % 10);
        carry = mul / 10;
        temp = temp->link;
    }

    int mul = temp->val * j + carry;                        //update last node
    update(*headptr, temp, mul % 10);
    carry = mul / 10;
    if (carry == 0)
        return;

    while (carry != 0) {                                    //if carry = 234, 199, 12, 8,etc.
        insertAtEnd(headptr, carry % 10);
        carry /= 10;
    }
}

void display(Node *node) {
    if (node == NULL) {
        printf("E ");
        return;
    }
    while (node != NULL) {
        printf("%d", node->val);
        node = node->link;
    }
    printf("\n");
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

void freeMemory(Node **headptr) {
    if (*headptr == NULL)
        return;

    Node *temp = *headptr;

    while (*headptr != NULL) {
        *headptr = (*headptr)->link;
        temp->link = NULL;
        free(temp);
        temp = *headptr;
    }
}

void reverse(Node **headptr) {
    Node *curr, *prev, *next;
    curr = *headptr;
    prev = next = NULL;

    while (curr != NULL) {
        next = curr->link;
        curr->link = prev;
        prev = curr;
        curr = next;
    }

    *headptr = prev;
}

void update(Node *head, Node *node, int data) {
    while (head != node)
        head = head->link;

    head->val = data;
}