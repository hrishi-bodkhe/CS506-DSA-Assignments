#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * This code does not contain the implementation of AVL Tree.
 * AVL Tree test cases will not work for this code.
 */

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct lNode {
    int val;
    struct lNode *link;
} lNode;

typedef struct Queue {
    Node *nodet;
    struct Queue *link;
} queue;

void deque();

bool isqEmpty();

int qsize();

void enque(Node *qnode);

queue *makeqNode(Node *qnode);

Node *makeNode(int val);

Node *findPosition(Node *root, int val);

Node *insertBST(Node *root, int val);

bool find(Node *root, int val);

void preorder(Node *root);

void inorder(Node *root);

void postorder(Node *root);

int height(Node *root);

int totalNodes(Node *root);

int totalLeaves(Node *root);

int checkPathExist(Node *root, int s, int d);

void route(Node *root, int s, int d);

Node *deleteBST(Node *root, int val);

int levelwidth(Node *root);

int lca(Node *root, int i, int j);

int lcaHelper(Node *root, int i, int j);

int diameter(Node *root);

int diameterHelper(Node *root, int *maxDiameter);

void clockwiseBoundaryTraversal(Node *root);

void rightBoundary(Node *root, lNode **head, int *sum);

void leaves(Node *root, lNode **head, int *sum);

void leftBoundary(Node *root, lNode **head, int *sum);

lNode *makelNode(int data);

void insertAtEnd(lNode **headptr, int data);

void display(lNode *node);

void levelOrder(Node *root);

int main() {
    int Z;
    scanf("%d", &Z);

    Node *root = NULL;
    for (int i = 0; i < Z; ++i) {

        char c;
        scanf(" %c", &c);

        if (c == 'T') {
            root = NULL;
            int x;
            do {
                scanf("%d", &x);
                if (x > 0 && !find(root, x))
                    root = insertBST(root, x);
                else if (x < 0) {
                    x = x * -1;
                    root = deleteBST(root, x);
                }
            } while (getchar() != '\n');

        } else if (c == 'A') {
            int x;
            do {
                scanf("%d", &x);
                if (x > 0 && !find(root, x))
                    root = insertBST(root, x);
            } while (getchar() != '\n');
        } else if (c == 'U') {
            int x;
            do {
                scanf("%d", &x);
                deleteBST(root, x);
            } while (getchar() != '\n');
        } else if (c == 'F') {          //find x
            int x;
            scanf("%d", &x);
            if (find(root, x))
                printf("Yes\n");
            else
                printf("No\n");
        } else if (c == 'Q') {      //#leaves
            printf("%d\n", totalLeaves(root));
        } else if (c == 'N') {      //#nodes
            printf("%d\n", totalNodes(root));
        } else if (c == 'P') {      //preorder
            preorder(root);
            printf("\n");
        } else if (c == 'I') {      //inorder
            inorder(root);
            printf("\n");
        } else if (c == 'S') {      //postorder
            postorder(root);
            printf("\n");
        } else if (c == 'L') {      //levelorder
            levelOrder(root);
            printf("\n");
        } else if (c == 'D') {      //height/depth
            printf("%d\n", height(root));
        } else if (c == 'W') {      //width
            printf("%d\n", levelwidth(root));
        } else if (c == 'C') {      //lowestCommonAncestor
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", lca(root, x, y));
        } else if (c == 'R') {      //route
            int x, y;
            scanf("%d %d", &x, &y);
            route(root, x, y);
        } else if (c == 'X') {      //diameter
            printf("%d\n", diameter(root) + 1);
        } else if (c == 'Y') {      //Perimeter / boundaryTraversal
            clockwiseBoundaryTraversal(root);
        } else
            continue;
    }

    return 0;
}

queue *front = NULL, *rear = NULL;

void levelOrder(Node *root) {
    if (root == NULL)
        return;

    enque(root);
    while (!isqEmpty()) {
        printf("%d ", front->nodet->val);
        if (front->nodet->left)
            enque(front->nodet->left);
        if (front->nodet->right)
            enque(front->nodet->right);
        deque();
    }
}

int qsize() {
    if (front == NULL)
        return 0;

    queue *temp = front;
    queue *temp2 = rear;
    int count = 0;
    while (temp != temp2) {
        ++count;
        temp = temp->link;
    }
    ++count;

    return count;
}

int levelwidth(Node *root) {
    if (root == NULL)
        return 0;

    int width = 1;

    enque(root);
    while (!isqEmpty()) {
        int currsize = qsize();
        width = currsize > width ? currsize : width;

        while (currsize != 0) {
            if (front->nodet->left)
                enque(front->nodet->left);
            if (front->nodet->right)
                enque(front->nodet->right);
            deque();
            --currsize;
        }
    }
    return width;
}

queue *makeqNode(Node *qnode) {
    queue *ele = (queue *) malloc(sizeof(queue));
    ele->nodet = qnode;
    ele->link = NULL;

    return ele;
}

bool isqEmpty() {
    if (front == NULL && rear == NULL)
        return true;
    return false;
}

void enque(Node *qnode) {
    if (rear == NULL) {
        rear = makeqNode(qnode);
        front = rear;
    } else {
        queue *temp = makeqNode(qnode);
        rear->link = temp;
        rear = temp;
    }
}

void deque() {
    if (front == NULL)
        return;

    queue *temp = front;
    if (front->link != NULL) {
        front = front->link;
        temp->link = NULL;
        free(temp);
    } else {
        front = NULL;
        rear = NULL;
        temp->link = NULL;
        free(temp);
    }
}

void clockwiseBoundaryTraversal(Node *root) {
    if (root == NULL)
        return;

    lNode *head = makelNode(root->val);
    int sum = 0;
    sum += root->val;

    rightBoundary(root->right, &head, &sum);

    leaves(root->right, &head, &sum);
    leaves(root->left, &head, &sum);

    leftBoundary(root->left, &head, &sum);

    printf("%d ", sum);
    display(head);
    printf("\n");
}

void leftBoundary(Node *root, lNode **head, int *sum) {
    if (root == NULL)
        return;

    if (root->left != NULL) {
        leftBoundary(root->left, head, sum);
        *sum += root->val;
        insertAtEnd(head, root->val);
    } else if (root->right != NULL) {
        leftBoundary(root->right, head, sum);
        *sum += root->val;
        insertAtEnd(head, root->val);
    }

}

void leaves(Node *root, lNode **head, int *sum) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        insertAtEnd(head, root->val);
        *sum += root->val;
    }

    leaves(root->right, head, sum);
    leaves(root->left, head, sum);
}

void rightBoundary(Node *root, lNode **head, int *sum) {
    if (root == NULL)
        return;

    if (root->right != NULL) {
        insertAtEnd(head, root->val);
        *sum += root->val;
        rightBoundary(root->right, head, sum);
    } else if (root->left != NULL) {
        insertAtEnd(head, root->val);
        *sum += root->val;
        rightBoundary(root->left, head, sum);
    }

}


//Reference: https://takeuforward.org/data-structure/calculate-the-diameter-of-a-binary-tree/
int diameter(Node *root) {
    if (root == NULL)
        return 0;

    int maxDiameter = 0;
    diameterHelper(root, &maxDiameter);
    return maxDiameter;
}

//Reference: https://takeuforward.org/data-structure/calculate-the-diameter-of-a-binary-tree/
int diameterHelper(Node *root, int *maxDiameter) {
    if (root == NULL)
        return 0;

    int lheight = diameterHelper(root->left, maxDiameter);
    int rheight = diameterHelper(root->right, maxDiameter);

    int diam = lheight + rheight;
    *maxDiameter = diam > *maxDiameter ? diam : *maxDiameter;

    return 1 + (lheight > rheight ? lheight : rheight);
}

int lca(Node *root, int i, int j) {
    if (root == NULL || !find(root, i) || !find(root, j))
        return -1;

    if (i == j)
        return i;

    return lcaHelper(root, i, j);
}

int lcaHelper(Node *root, int i, int j) {
    if (root->val > i && root->val > j)
        return lcaHelper(root->left, i, j);
    else if (root->val < i && root->val < j)
        return lcaHelper(root->right, i, j);
    return root->val;
}

Node *makeNode(int val) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*Node *findPosition(Node *root, int val) {
    if (root == NULL)
        return root;

    Node *temp = root;
    Node *parent;
    while (temp != NULL) {
        parent = temp;
        if (val <= temp->val) {
            temp = temp->left;
        } else
            temp = temp->right;
    }

    return parent;
}*/

Node *insertBST(Node *root, int val) {
    if (root == NULL)
        return makeNode(val);

    if (val <= root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}

bool find(Node *root, int val) {
    if (root == NULL || val < 0)
        return false;

    while (root != NULL) {
        if (root->val > val)
            root = root->left;
        else if (root->val < val)
            root = root->right;
        else
            return true;
    }

    return false;
}

//Reference: https://www.geeksforgeeks.org/morris-traversal-for-preorder/
void preorder(Node *root) {
    if (root == NULL)
        return;

    while (root != NULL) {
        if (root->left == NULL) {
            printf("%d ", root->val);
            root = root->right;
        } else {
            Node *curr = root->left;
            while (curr->right != NULL && curr->right != root) {
                curr = curr->right;
            }

            if (curr->right == NULL) {
                printf("%d ", root->val);
                curr->right = root;
                root = root->left;
            } else {
                curr->right = NULL;
                root = root->right;
            }
        }
    }
}

void inorder(Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int height(Node *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    return 1 + (l > r ? l : r);
}

int totalNodes(Node *root) {
    if (root == NULL)
        return 0;

    int l = totalNodes(root->left);
    int r = totalNodes(root->right);

    return 1 + l + r;
}

int totalLeaves(Node *root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return totalLeaves(root->left) + totalLeaves(root->right);
}

int checkPathExist(Node *root, int s, int d) {
    if (!find(root, s)) {
        printf("Source does not exist\n");
        return 0;
    } else if (!find(root, d)) {
        printf("Destination does not exist\n");
        return 0;
    } else {
        while (root != NULL && root->val != s) {
            if (root->val < s)
                root = root->right;
            else
                root = root->left;
        }

        if (root == NULL) {
            printf("Unreachable\n");
            return 0;
        }

        while (root != NULL && root->val != d) {
            if (root->val < d)
                root = root->right;
            else
                root = root->left;
        }

        if (root == NULL) {
            printf("Unreachable\n");
            return 0;
        }
    }
    return 1;
}

void route(Node *root, int s, int d) {
    if (s == d) {
        printf("%d\n", s);
        return;
    }

    if (!checkPathExist(root, s, d))
        return;
    else {
        while (root != NULL && root->val != s) {
            if (root->val < s)
                root = root->right;
            else
                root = root->left;
        }

        while (root != NULL && root->val != d) {
            if (root->val < d) {
                printf("%d R ", root->val);
                root = root->right;
            } else {
                printf("%d L ", root->val);
                root = root->left;
            }
        }
        printf("%d\n", root->val);
    }
}

Node *deleteBST(Node *root, int val) {
    if (root == NULL) {
        printf("E\n");
        return root;
    }

    if (!find(root, val)) {
        printf("Node not present\n");
        return root;
    }

    if (root->val == val) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL && root->right != NULL) {
            Node *temp = root;
            root = root->right;
            free(temp);
            return root;
        } else if (root->left != NULL && root->right == NULL) {
            Node *temp = root;
            root = root->left;
            free(temp);
            return root;
        } else {
            Node *prev = NULL;
            Node *predecessor = root->left;
            while (predecessor->right) {
                prev = predecessor;
                predecessor = predecessor->right;
            }
            if (prev != NULL) {
                prev->right = predecessor->left;
                root->val = predecessor->val;
                free(predecessor);
            } else {
                root->left = predecessor->left;
                root->val = predecessor->val;
                free(predecessor);
            }
            return root;
        }
    }

    Node *prev = NULL;
    Node *temp = root;

    while (temp->val != val) {
        prev = temp;
        if (val < temp->val)
            temp = temp->left;
        else if (val > temp->val)
            temp = temp->right;
    }

    if (temp->left == NULL && temp->right == NULL) {      //leaf case
        if (prev->left == temp)
            prev->left = NULL;
        else
            prev->right = NULL;

        free(temp);
    } else if (temp->left == NULL && temp->right != NULL) {     //non leaf with one child
        if (prev->left == temp)
            prev->left = temp->right;
        else
            prev->right = temp->right;

        free(temp);
    } else if (temp->left != NULL && temp->right == NULL) {     //non leaf with one child
        if (prev->left == temp)
            prev->left = temp->left;
        else
            prev->right = temp->left;

        free(temp);
    } else {                                                   //non leaf with two child
        prev = NULL;
        Node *predecessor = temp->left;
        while (predecessor->right) {
            prev = predecessor;
            predecessor = predecessor->right;
        }
        if (prev != NULL)
            prev->right = predecessor->left;
        else
            temp->left = predecessor->left;
        temp->val = predecessor->val;
        free(predecessor);
    }
    return root;
}

lNode *makelNode(int data) {
    lNode *node = (lNode *) malloc(sizeof(lNode));
    node->val = data;
    node->link = NULL;

    return node;
}

void display(lNode *node) {
    if (node == NULL) {
        printf("E\t");
        return;
    }
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->link;
    }
}

void insertAtEnd(lNode **headptr, int data) {
    if (*headptr == NULL) {
        *headptr = makelNode(data);
        return;
    }

    lNode *temp = *headptr;
    while (temp->link != NULL)
        temp = temp->link;

    lNode *node = makelNode(data);
    temp->link = node;
}