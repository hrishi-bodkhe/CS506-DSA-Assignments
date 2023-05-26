#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

vector<vector<int>> adj;

struct Comparator {
    bool operator()(pair<int, int> &a, pair<int, int> &b) {
        return a.second > b.second;
    }
};

typedef struct NodeBino {
    int v;                  //vertex
    int data;               //node value
    NodeBino *parent;       //parent pointer
    NodeBino *lchild;       //left child pointer
    NodeBino *sibling;      //right sibling pointer
    int degree;             //number of children
} NodeBino;

typedef struct NodeFibo {
    int v;                  //vertex
    int data;               //node value
    NodeFibo *parent;       //parent pointer
    NodeFibo *lchild;       //left child pointer
    NodeFibo *lsibling;      //left sibling pointer
    NodeFibo *rsibling;      //right sibling pointer
    int degree;             //number of children
    int marked;             //1 if markded, 0 otherwise
} NodeFibo;

typedef struct FiboHeap {
    NodeFibo *min;
    int n;
} FiboHeap;

FiboHeap *makeFibHeap();

NodeFibo *makeFibNode(int vertex, int data);

FiboHeap *fibHeapInsert(FiboHeap *heap, int v, int data, vector<NodeFibo *> &nodes);

NodeFibo *fibHeapExtractMin(FiboHeap **heap);

void fibHeapLink(FiboHeap *heap, NodeFibo *y, NodeFibo *x);

void consolidate(FiboHeap **heap);

void cut(FiboHeap *heap, NodeFibo *x, NodeFibo *y);

void cascadingCut(FiboHeap *heap, NodeFibo *y);

void fibHeapDecreaseKey(FiboHeap *heap, NodeFibo *x, int k, vector<NodeFibo *> &nodes);

NodeBino *makeBinomialHeap(int data, int v);

void binomialLink(NodeBino *x, NodeBino *y);

NodeBino *binomialHeapMerge(NodeBino *h1, NodeBino *h2);

NodeBino *binomialHeapMeld(NodeBino *h1, NodeBino *h2);

NodeBino *binomialHeapMinimum(NodeBino *head);

NodeBino *binomialHeapInsert(NodeBino **head, int data, int v);

NodeBino *binomialReverseRootList(NodeBino *head);

NodeBino *binomialHeapExtractMin(NodeBino **head);

void binomialHeapDecreaseKey(NodeBino *head, NodeBino *x, int data, vector<NodeBino *> &nodes);

void printAdjMatrix(int N);

void input(int N);

void matrixToList(vector<pair<int, int>> adjList[], int N);

void printAdjList(vector<pair<int, int>> adjList[], int N);

int bellmanFord(vector<vector<int>> edgeMat, int V, int s, vector<int> &d);

void construct_Edge_Matrix(vector<vector<int>> &edgeMat, int N);

void printEdgeMatrix(vector<vector<int>> edgeMat);

void printResD(vector<vector<int>> D);

void dijkstra(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d);

void dijkstraBino(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d);

void dijkstraFibo(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d);

void dijkstraArray(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d);

int main(int argc, char **argv) {
    int T;
    cin >> T;
    int choice;
    choice = atoi(argv[1]);
    for (int t = 0; t < T; ++t) {
        //N - #vertices - 1 indexing
        //D - directed or not
        int N, D;
        cin >> N >> D;
        adj = vector<vector<int> >(N + 1, vector<int>(N + 1, 0));


        //999999 - no edge between vertices or inf

        //TAKING-INPUT-MATRIX
        input(N);
//        printAdjMatrix(N);

        //Converting adjacency Matrix to adjacency List
        vector<pair<int, int>> adjList[N + 1];
        matrixToList(adjList, N + 1);
//        printAdjList(adjList, N + 1);

        //Constructing Edge Matrix
        vector<vector<int>> edgeMat;
        construct_Edge_Matrix(edgeMat, N + 1);
//        printEdgeMatrix(edgeMat);

        vector<int> h;

        clock_t time;
        time = clock();

        if (bellmanFord(edgeMat, N + 1, 0, h) == 1)
            cout << -1 << endl;
        else {
            //h[v] = δ(s,v) is given by bellmanFord

            vector<pair<int, int>> capAdjList[N + 1];
            for (auto &e: edgeMat) {
                int u = e[0];
                int v = e[1];
                int w = e[2];

                int w_cap = w + h[u] - h[v];
                capAdjList[u].push_back(make_pair(v, w_cap));
            }

            //CREATING-D[N X N]-MATRIX
            vector<vector<int>> D(N + 1, vector<int>(N + 1));

            for (int u = 1; u <= N; ++u) {
                vector<int> d_cap;

                //DIJKSTRA
                if (choice == 1)
                    dijkstraArray(N + 1, capAdjList, u, d_cap);
                else if (choice == 2)
                    dijkstra(N + 1, capAdjList, u, d_cap);
                else if (choice == 3)
                    dijkstraBino(N + 1, capAdjList, u, d_cap);
                else
                    dijkstraFibo(N + 1, capAdjList, u, d_cap);

                for (int v = 1; v <= N; ++v) {
                    if (u != v) {
                        D[u][v] = d_cap[v] + h[v] - h[u];
                        if (D[u][v] > 999990)
                            D[u][v] = 999999;
                    }
                }
            }

            //PRINTING-FINAL-MATRIX
            printResD(D);
        }

        time = clock() - time;
        double time_taken = ((double) time) / CLOCKS_PER_SEC;
        cout << time_taken << endl;
    }
    return 0;
}

void dijkstraArray(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d) {
    vector<int> visited;

    //initialize single source
    for (int i = 0; i < N; ++i) {
        d.push_back(999999);
        visited.push_back(0);
    }

    d[s] = 0;

    //dijkstra
    vector<int> arr(N);

    for (int i = 0; i < N; ++i) {
        if (s != i)
            arr[i] = 999999;
    }

    arr[s] = 0;
    int count = 0;

    while (count != N - 1) {
        //find min
        int min = 0;
        for (int i = 0; i < arr.size(); ++i) {
            if (visited[i] != 1 && arr[min] > arr[i])
                min = i;
        }

        int u = min;
        visited[u] = 1;

        for (auto x: adjList[u]) {
            int v = x.first;
            int wt_v = x.second;

            //relax
            if (visited[v] == 0 && d[v] > d[u] + wt_v) {
                d[v] = d[u] + wt_v;
                arr[v] = d[v];
            }
        }

        ++count;
    }
}

void dijkstraFibo(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d) {
    vector<int> visited;

    //initialize single source
    for (int i = 0; i < N; ++i) {
        d.push_back(999999);
        visited.push_back(0);
    }

    d[s] = 0;

    //dijkstra
    FiboHeap *heap = makeFibHeap();
    vector<NodeFibo *> nodes(N, NULL);
    heap = fibHeapInsert(heap, s, 0, nodes);

    for (int i = 0; i < N; ++i) {
        if (s != i)
            heap = fibHeapInsert(heap, i, 999999, nodes);
    }

    while (heap->min != NULL) {
        NodeFibo *min = fibHeapExtractMin(&heap);

        int u = min->v;
        visited[u] = 1;

        for (auto x: adjList[u]) {
            int v = x.first;
            int wt_v = x.second;

            //relax
            if (visited[v] == 0 && d[v] > d[u] + wt_v) {
                d[v] = d[u] + wt_v;
                NodeFibo *y = nodes[v];
                fibHeapDecreaseKey(heap, y, d[v], nodes);
            }
        }
    }

}

void dijkstraBino(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d) {
    vector<int> visited;

    //initialize single source
    for (int i = 0; i < N; ++i) {
        d.push_back(999999);
        visited.push_back(0);
    }

    d[s] = 0;

    //dijkstra
    NodeBino *head = NULL;
    vector<NodeBino *> nodes(N, NULL);
    head = binomialHeapInsert(&head, 0, s);
    nodes[s] = head;

    for (int i = 1; i < N; ++i) {
        if (s != i) {
            nodes[i] = binomialHeapInsert(&head, 999999, i);
        }
    }

    while (head != NULL) {
        NodeBino *min = binomialHeapExtractMin(&head);

        int u = min->v;
        visited[u] = 1;

        for (auto x: adjList[u]) {
            int v = x.first;
            int wt_v = x.second;

            //relax
            if (visited[v] == 0 && d[v] > d[u] + wt_v) {
                d[v] = d[u] + wt_v;
                NodeBino *y = nodes[v];
                binomialHeapDecreaseKey(head, y, d[v], nodes);
            }
        }
    }
}

void dijkstra(int N, vector<pair<int, int>> adjList[], int s, vector<int> &d) {
    vector<int> visited;

    //initialize single source
    for (int i = 0; i < N; ++i) {
        d.push_back(999999);
        visited.push_back(0);
    }
    d[s] = 0;

    //dijkstra
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> pq;
    pair<int, int> source = make_pair(s, 0);
    pq.push(source);

    for (int i = 1; i < N; ++i) {
        if (s != i) {
            pq.push(make_pair(i, 999999));
        }
    }

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();

        int u = p.first;
        int wt_u = p.second;

        visited[u] = 1;

        for (auto x: adjList[u]) {
            int v = x.first;
            int wt_v = x.second;

            //relax
            if (visited[v] == 0 && d[v] > d[u] + wt_v) {
                d[v] = d[u] + wt_v;
                pq.push(make_pair(v, d[v]));
            }
        }

    }
}

void printResD(vector<vector<int>> D) {
    int N = D.size();
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j)
            cout << D[i][j] << " ";
        cout << endl;
    }
}

int bellmanFord(vector<vector<int>> edgeMat, int V, int s, vector<int> &d) {
    //INITIALIZE-SINGLE-SOURCE
    int parent[V];

    for (int i = 0; i < V; ++i) {
        d.push_back(999999);
        parent[i] = -1;
    }

    d[s] = 0;
    //End of INITIALIZE-SINGLE-SOURCE

    //RELAX_|V| - 1_TIMES
    int E = edgeMat.size();
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edgeMat[j][0];
            int v = edgeMat[j][1];
            int w = edgeMat[j][2];

            //RELAX
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                parent[v] = u;
            }
        }
    }
    //End of RELAX_|V| - 1_TIMES

    //DETECT-NEGATIVE-CYCLE
    for (int i = 0; i < E; ++i) {
        int u = edgeMat[i][0];
        int v = edgeMat[i][1];
        int w = edgeMat[i][2];

        if (d[v] > d[u] + w) {
            return 1;
        }
    }
    //End of DETECT-NEGATIVE-CYCLE

    return 0;
}

void printEdgeMatrix(vector<vector<int>> edgeMat) {
    cout << edgeMat.size() << endl;
    for (int i = 0; i < edgeMat.size(); ++i) {
        cout << "Edge: " << i << endl;
        for (int j = 0; j < 3; ++j) {
            cout << edgeMat[i][j] << " ";
        }
        cout << endl;
    }
}

void construct_Edge_Matrix(vector<vector<int>> &edgeMat, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j || adj[i][j] == 999999 || j == 0)
                continue;
            else {
                vector<int> e = {i, j, adj[i][j]};
                edgeMat.push_back(e);
            }
        }
    }
}


void printAdjList(vector<pair<int, int>> adjList[], int N) {
    for (int i = 0; i < N; ++i) {
        cout << i << " -> ";
        for (auto &x: adjList[i]) {
            cout << "(" << x.first << ", " << x.second << ")" << " -> ";
        }
        cout << endl;
    }
}

void matrixToList(vector<pair<int, int>> adjList[], int N) {
    for (int i = 0; i < N; ++i) {
        int u = i;
        for (int j = 0; j < N; ++j) {
            int v = j;
            int wt = adj[u][v];
            if (u != v && wt != 999999)
                adjList[u].push_back(make_pair(v, wt));
        }
    }
}


void input(int N) {
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j)
            cin >> adj[i][j];
    }
}

void printAdjMatrix(int N) {
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < N + 1; ++j)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}

NodeBino *binomialHeapExtractMin(NodeBino **head) {
    NodeBino *x = binomialHeapMinimum(*head);

    //REMOVE-x
    if (*head == x) {
        *head = (*head)->sibling;
    } else {
        NodeBino *temp = *head;

        while (temp->sibling != x)
            temp = temp->sibling;

        temp->sibling = x->sibling;
    }

    x->sibling = NULL;

    //MAKE-PARENT-PTRS-OF-CHILD-OF-x-NULL
    NodeBino *h1 = x->lchild;
    x->lchild = NULL;               //MAKE-CHILD-PTR-OF-x-NULL

    NodeBino *temp1 = h1;
    while (temp1 != NULL) {
        temp1->parent = NULL;
        temp1 = temp1->sibling;
    }

    x->degree = 0;          //MAKE-DEGREE-OF-x-0

    //REVERSE-THE-ORDER-OF-LINKED-LIST-OF-x'S-CHILDREN-AND-SET-h1-POINT-TO-HEAD-OF-LINKED-LIST-FORMED
    h1 = binomialReverseRootList(h1);

    //MELD-BOTH-HEAPS
    *head = binomialHeapMeld(*head, h1);

    return x;
}


void binomialHeapDecreaseKey(NodeBino *head, NodeBino *x, int data, vector<NodeBino *> &nodes) {
    if (data > x->data) {
        cout << "New Key is greater than old key." << endl;
        return;
    }

    x->data = data;
    NodeBino *y = x;
    NodeBino *z = y->parent;

    while (z != NULL && y->data < z->data) {
        //CHANGING-KEYS
        int t = y->data;
        y->data = z->data;
        z->data = t;

        //CHANGING-VERTICES
        int p = y->v;
        y->v = z->v;
        z->v = p;

        //CHANGING-NODE_ARRAY
        NodeBino *temp = nodes[z->v];
        nodes[z->v] = nodes[y->v];
        nodes[y->v] = temp;

        y = z;
        z = y->parent;
    }
}

NodeBino *binomialReverseRootList(NodeBino *head) {
    NodeBino *prev_x = NULL;
    NodeBino *x = head;
    NodeBino *next_x = NULL;

    while (x != NULL) {
        next_x = x->sibling;
        x->sibling = prev_x;
        prev_x = x;
        x = next_x;
    }

    return prev_x;
}

NodeBino *binomialHeapMinimum(NodeBino *head) {
    NodeBino *y = NULL;
    NodeBino *x = head;
    int min = 999999;

    while (x != NULL) {
        if (x->data <= min) {
            min = x->data;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

NodeBino *binomialHeapInsert(NodeBino **head, int data, int v) {
    NodeBino *x = makeBinomialHeap(data, v);
    *head = binomialHeapMeld(*head, x);
    return x;
}

NodeBino *binomialHeapMeld(NodeBino *h1, NodeBino *h2) {
    if (h1 == NULL)
        return h2;

    if (h2 == NULL)
        return h1;

    NodeBino *head = binomialHeapMerge(h1, h2);
    NodeBino *prev_x = NULL;
    NodeBino *x = head;
    NodeBino *next_x = x->sibling;

    while (next_x != NULL) {
        if (x->degree != next_x->degree) {        //CASE 1
            prev_x = x;
            x = next_x;

        } else {                                //x->degree == next_x->degree
            if (next_x->sibling != NULL && next_x->sibling->degree == x->degree) {       //CASE 2
                prev_x = x;
                x = next_x;
            } else if (x->data <= next_x->data) {               //CASE 3
                x->sibling = next_x->sibling;
                binomialLink(next_x, x);
            } else {                   //CASE 4: x->data > next_x->data
                if (prev_x != NULL)
                    prev_x->sibling = next_x;
                else                //prev_x == NULL
                    head = next_x;

                binomialLink(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }

    return head;
}

void binomialLink(NodeBino *x, NodeBino *y) {
    //Makes x as child of y

    x->parent = y;
    x->sibling = y->lchild;
    y->lchild = x;
    y->degree = y->degree + 1;
}

NodeBino *binomialHeapMerge(NodeBino *h1, NodeBino *h2) {
    if (h1 == NULL)
        return h2;

    if (h2 == NULL)
        return h1;

    NodeBino *head = NULL;
    NodeBino *temp = NULL;

    if (h1->degree <= h2->degree) {
        head = h1;
        h1 = h1->sibling;
    } else {
        head = h2;
        h2 = h2->sibling;
    }

    temp = head;

    while (h1 != NULL && h2 != NULL) {
        if (h1->degree <= h2->degree) {
            temp->sibling = h1;
            h1 = h1->sibling;
        } else {
            temp->sibling = h2;
            h2 = h2->sibling;
        }
        temp = temp->sibling;
    }

    if (h1 != NULL) {
        temp->sibling = h1;
    }
    if (h2 != NULL) {
        temp->sibling = h2;
    }

    return head;
}

NodeBino *makeBinomialHeap(int data, int v) {
    NodeBino *node = (NodeBino *) malloc(sizeof(NodeBino));
    node->v = v;
    node->data = data;
    node->parent = NULL;
    node->lchild = NULL;
    node->sibling = NULL;
    node->degree = 0;
    return node;
}

void fibHeapDecreaseKey(FiboHeap *heap, NodeFibo *x, int k, vector<NodeFibo *> &nodes) {
    if (k > x->data) {
        cout << "New Key is greater than old key." << endl;
        return;
    }

    x->data = k;
    NodeFibo *y = x->parent;

    if (y != NULL && x->data < y->data) {
        cut(heap, x, y);
        cascadingCut(heap, y);
    }

    if (x->data < heap->min->data)
        heap->min = x;
}

void cascadingCut(FiboHeap *heap, NodeFibo *y) {
    NodeFibo *z = y->parent;
    if (z != NULL) {
        if (y->marked == 0)
            y->marked = 1;
        else {
            cut(heap, y, z);
            cascadingCut(heap, z);
        }
    }
}

void cut(FiboHeap *heap, NodeFibo *x, NodeFibo *y) {
    //REMOVE-x-FROM-CHILD-LIST-OF-y
    NodeFibo *left = x->lsibling;
    NodeFibo *right = x->rsibling;

    left->rsibling = right;
    right->lsibling = left;

    if (y->lchild == x) {
        if (x->lsibling == x)
            y->lchild = NULL;
        else
            y->lchild = x->rsibling;
    }

    y->degree = y->degree - 1;

    //ADD-x-TO-THE-ROOT-LIST-OF-H
    NodeFibo *min = heap->min;
    if (min->lsibling != min) {
        NodeFibo *temp = min->lsibling;
        x->rsibling = min;
        x->lsibling = temp;
        temp->rsibling = x;
        min->lsibling = x;
    } else {
        x->rsibling = min;
        x->lsibling = min;
        min->lsibling = x;
        min->rsibling = x;
    }


    x->parent = NULL;
    x->marked = 0;
}

NodeFibo *fibHeapExtractMin(FiboHeap **heap) {
    NodeFibo *min = (*heap)->min;

    if (min != NULL) {
        NodeFibo *nodet = min->lchild;

        vector<NodeFibo *> childList;
        if (nodet != NULL) {
            do {
                childList.push_back(nodet);
                nodet = nodet->rsibling;
            } while (nodet != min->lchild);

            for (auto node: childList) {
                if (min->lsibling != min) {
                    NodeFibo *temp = min->lsibling;
                    node->rsibling = min;
                    node->lsibling = temp;
                    temp->rsibling = node;
                    min->lsibling = node;
                } else {
                    node->rsibling = min;
                    node->lsibling = min;
                    min->lsibling = node;
                    min->rsibling = node;
                }

                node->parent = NULL;
            }
        }

        min->lchild = NULL;

        //REMOVE-min-FROM-ROOT-LIST
        NodeFibo *left = min->lsibling;
        NodeFibo *right = min->rsibling;

        left->rsibling = right;
        right->lsibling = left;

        if (min == min->rsibling)
            (*heap)->min = NULL;
        else {
            (*heap)->min = min->rsibling;
            consolidate(heap);
        }

        (*heap)->n = (*heap)->n - 1;
    }

    return min;
}

void consolidate(FiboHeap **heap) {
    //INITIALISING-DEGREE-ARRAY-A
    vector<NodeFibo *> A(log2((*heap)->n) + 2, NULL);
    NodeFibo *min = (*heap)->min;

    //MAKING-ROOT-LIST
    vector<NodeFibo *> rootList;
    NodeFibo *temp = min;
    do {
        rootList.push_back(temp);
        temp = temp->rsibling;
    } while (temp != min);

    for (auto w: rootList) {
        NodeFibo *x = w;
        int d = x->degree;

        while (A[d] != NULL) {
            NodeFibo *y = A[d];

            if (x->data > y->data) {      //EXCHANGE-x-WITH-y
                NodeFibo *dumb = x;
                x = y;
                y = dumb;
            }

            fibHeapLink(*heap, y, x);
            A[d] = NULL;
            d = d + 1;
        }

        A[d] = x;
    }

    //UPDATE-MIN-PTR
    (*heap)->min = NULL;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] != NULL) {
            if ((*heap)->min == NULL)
                (*heap)->min = A[i];
            else {
                if (A[i]->data < (*heap)->min->data)
                    (*heap)->min = A[i];
            }
        }
    }
}

void fibHeapLink(FiboHeap *heap, NodeFibo *y, NodeFibo *x) {
    //REMOVE-y-FROM-ROOT-LIST-OF-HEAP
    y->parent = x;
    NodeFibo *prev_y = y->lsibling;
    NodeFibo *next_y = y->rsibling;

    if (prev_y != y) {
        prev_y->rsibling = next_y;
    }

    if (next_y != y) {
        next_y->lsibling = prev_y;
    }

    //MAKE-y-A-CHILD-OF-x
    if (x->lchild != NULL) {
        NodeFibo *sib = x->lchild;
        NodeFibo *left = sib->lsibling;
        y->rsibling = sib;
        y->lsibling = left;
        sib->lsibling = y;
        left->rsibling = y;
    } else {
        y->rsibling = y;
        y->lsibling = y;
    }

    x->lchild = y;
    x->degree = x->degree + 1;
    y->marked = 0;
}

FiboHeap *fibHeapInsert(FiboHeap *heap, int v, int data, vector<NodeFibo *> &nodes) {
    NodeFibo *node = makeFibNode(v, data);
    nodes[v] = node;
    if (heap->min == NULL) {
        heap->min = node;
        node->lsibling = node;
        node->rsibling = node;
    } else {
        NodeFibo *min = heap->min;
        if (min->lsibling != min) {
            NodeFibo *temp = min->lsibling;
            node->rsibling = min;
            node->lsibling = temp;
            temp->rsibling = node;
            min->lsibling = node;
        } else {
            node->rsibling = min;
            node->lsibling = min;
            min->lsibling = node;
            min->rsibling = node;
        }

        if (node->data < min->data) {
            heap->min = node;
        }
    }

    heap->n = heap->n + 1;
    return heap;
}

FiboHeap *makeFibHeap() {
    FiboHeap *node = (FiboHeap *) malloc(sizeof(FiboHeap));
    node->min = NULL;
    node->n = 0;

    return node;
}

NodeFibo *makeFibNode(int vertex, int data) {
    NodeFibo *node = (NodeFibo *) malloc(sizeof(NodeFibo));
    node->v = vertex;
    node->data = data;
    node->parent = NULL;
    node->lchild = NULL;
    node->lsibling = NULL;
    node->rsibling = NULL;
    node->degree = 0;
    node->marked = 0;
    return node;
}