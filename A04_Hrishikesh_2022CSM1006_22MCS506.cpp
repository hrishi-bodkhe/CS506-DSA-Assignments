#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int val;
    struct Node *link;
} Node;

struct Comparator {
    bool operator()(pair<int, double> &a, pair<int, double> &b) {
        return a.second > b.second;
    }
};

Node *makeNode(int data);

void display(Node *node);

void insertAtEnd(Node **headptr, int data);

double dijkstra(int N, vector<pair<int, double>> adjList[], int s, int dest);

int bfs(int N, vector<int> adjList[], int s, int dest);

int main() {
    int T;          //#test cases
    cin >> T;
    for (int k = 0; k < T; ++k) {
        int Q;          //query id
        cin >> Q;
        if (Q == 1) {
            int N, M, sx, sy, vx, vy;
            cin >> N >> M >> sx >> sy >> vx >> vy;

            int adj[N][N];
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cin >> adj[i][j];
                }
            }

            vector<pair<int, double>> adjList[N * N];         //Converting adjMatrix to adjList

            if (M == 2) {         //right and down
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        int u = i * N + j;
                        if (i + 1 < N) {                      //down
                            int v = (i + 1) * N + j;
                            double wt = abs(adj[i + 1][j] - adj[i][j]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (j + 1 < N) {
                            int v = i * N + (j + 1);
                            double wt = abs(adj[i][j] - adj[i][j + 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (i == N - 1 && j == N - 1)
                            adjList[u].push_back(make_pair(-1, -1));
                    }
                }

                int s = ((sx - 1) * N) + (sy - 1);
                int dest = ((vx - 1) * N) + (vy - 1);
                double ans;

                if (s != dest)
                    ans = dijkstra(N * N, adjList, s, dest);
                else
                    ans = 0;

                cout << ans << endl;

            } else if (M == 4) {        //up down right left
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        int u = i * N + j;
                        if (i + 1 < N) {                      //down
                            int v = (i + 1) * N + j;
                            double wt = abs(adj[i + 1][j] - adj[i][j]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (j + 1 < N) {                    //right
                            int v = i * N + (j + 1);
                            double wt = abs(adj[i][j] - adj[i][j + 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (i - 1 >= 0) {                     //up
                            int v = (i - 1) * N + j;
                            double wt = abs(adj[i][j] - adj[i - 1][j]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (j - 1 >= 0) {                     //left
                            int v = i * N + (j - 1);
                            double wt = abs(adj[i][j] - adj[i][j - 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (i == N - 1 && j == N - 1)
                            adjList[u].push_back(make_pair(-1, -1));
                    }
                }

                int s = ((sx - 1) * N) + (sy - 1);
                int dest = ((vx - 1) * N) + (vy - 1);
                double ans;

                if (s != dest)
                    ans = dijkstra(N * N, adjList, s, dest);
                else
                    ans = 0;

                cout << ans << endl;

            } else if (M == 6) {        //up down right left /^ \d
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        int u = i * N + j;
                        if (i + 1 < N) {                      //down
                            int v = (i + 1) * N + j;
                            double wt = abs(adj[i + 1][j] - adj[i][j]);
                            adjList[u].push_back(make_pair(v, wt));

                            if (j + 1 < N) {
                                v = (i + 1) * N + (j + 1);
                                wt = abs(adj[i][j] - adj[i + 1][j + 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }
                        }

                        if (j + 1 < N) {                    //right
                            int v = i * N + (j + 1);
                            double wt = abs(adj[i][j] - adj[i][j + 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (i - 1 >= 0) {                     //up
                            int v = (i - 1) * N + j;
                            double wt = abs(adj[i][j] - adj[i - 1][j]);
                            adjList[u].push_back(make_pair(v, wt));

                            if (j + 1 < N) {
                                v = (i - 1) * N + (j + 1);
                                wt = abs(adj[i][j] - adj[i - 1][j + 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }
                        }

                        if (j - 1 >= 0) {                     //left
                            int v = i * N + (j - 1);
                            double wt = abs(adj[i][j] - adj[i][j - 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }


                        if (i == N - 1 && j == N - 1)
                            adjList[u].push_back(make_pair(-1, -1));
                    }
                }

                int s = ((sx - 1) * N) + (sy - 1);
                int dest = ((vx - 1) * N) + (vy - 1);
                double ans;

                if (s != dest)
                    ans = dijkstra(N * N, adjList, s, dest);
                else
                    ans = 0;

                cout << ans << endl;

            } else if (M == 8) {        //all
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        int u = i * N + j;
                        if (i + 1 < N) {                      //down
                            int v = (i + 1) * N + j;
                            double wt = abs(adj[i + 1][j] - adj[i][j]);
                            adjList[u].push_back(make_pair(v, wt));

                            if (j + 1 < N) {
                                v = (i + 1) * N + (j + 1);
                                wt = abs(adj[i][j] - adj[i + 1][j + 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }

                            if (j - 1 < N) {
                                v = (i + 1) * N + (j - 1);
                                wt = abs(adj[i][j] - adj[i + 1][j - 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }
                        }

                        if (j + 1 < N) {                    //right
                            int v = i * N + (j + 1);
                            double wt = abs(adj[i][j] - adj[i][j + 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }

                        if (i - 1 >= 0) {                     //up
                            int v = (i - 1) * N + j;
                            double wt = abs(adj[i][j] - adj[i - 1][j]);
                            adjList[u].push_back(make_pair(v, wt));

                            if (j + 1 < N) {
                                v = (i - 1) * N + (j + 1);
                                wt = abs(adj[i][j] - adj[i - 1][j + 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }

                            if (j - 1 >= 0) {
                                v = (i - 1) * N + (j - 1);
                                wt = abs(adj[i][j] - adj[i - 1][j - 1]) * 1.5;
                                adjList[u].push_back(make_pair(v, wt));
                            }
                        }

                        if (j - 1 >= 0) {                     //left
                            int v = i * N + (j - 1);
                            double wt = abs(adj[i][j] - adj[i][j - 1]);
                            adjList[u].push_back(make_pair(v, wt));
                        }


                        if (i == N - 1 && j == N - 1)
                            adjList[u].push_back(make_pair(-1, -1));
                    }
                }

                int s = ((sx - 1) * N) + (sy - 1);
                int dest = ((vx - 1) * N) + (vy - 1);
                double ans;

                if (s != dest)
                    ans = dijkstra(N * N, adjList, s, dest);
                else
                    ans = 0;

                cout << ans << endl;

            } else                    //no movements
                cout << -1 << endl;

        } else if (Q == 2) {
            int N, d, sx, sy, vx, vy;
            cin >> N >> d >> sx >> sy >> vx >> vy;

            int adj[N][N];
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cin >> adj[i][j];
                }
            }

            vector<int> adjList[N * N];         //Converting adjMatrix to adjList
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    int u = i * N + j;
                    if (i + 1 < N) {              //down
                        int v = (i + 1) * N + j;
                        int diff = abs(adj[i + 1][j] - adj[i][j]);
                        if (diff <= d)
                            adjList[u].push_back(v);
                    }

                    if (i - 1 >= 0) {             //up
                        int v = (i - 1) * N + j;
                        int diff = abs(adj[i - 1][j] - adj[i][j]);
                        if (diff <= d)
                            adjList[u].push_back(v);
                    }

                    if (j + 1 < N) {              //right
                        int v = i * N + (j + 1);
                        int diff = abs(adj[i][j + 1] - adj[i][j]);
                        if (diff <= d)
                            adjList[u].push_back(v);
                    }

                    if (j - 1 >= 0) {             //left
                        int v = i * N + (j - 1);
                        int diff = abs(adj[i][j - 1] + adj[i][j]);
                        if (diff <= d)
                            adjList[u].push_back(v);
                    }
                }
            }

            int s = (sx - 1) * N + (sy - 1);
            int dest = (vx - 1) * N + (vy - 1);
            int ans;

            if (s != dest)
                ans = bfs(N * N, adjList, s, dest);
            else
                ans = 0;

            cout << ans << endl;

        } else if (Q == 3) {
            int N;          //#nodes
            cin >> N;
            int adj[N][N];
            int indegree[N];
            for (int i = 0; i < N; ++i)
                indegree[i] = 0;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cin >> adj[i][j];
                }
            }

            vector<int> adjList[N];         //Converting adjMatrix to adjList
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (adj[i][j] == 1) {
                        adjList[i].push_back(j);
                        ++indegree[j];
                    }
                }
            }

            priority_queue<int, vector<int>, greater<int>> pq;
            for (int i = 0; i < N; ++i) {
                if (indegree[i] == 0) {
                    pq.push(i);
                }
            }

            int count = 0;
            Node *head = NULL;

            while (!pq.empty()) {
                int u = pq.top();
                pq.pop();
                insertAtEnd(&head, u + 1);

                for (auto v: adjList[u]) {
                    --indegree[v];
                    if (indegree[v] == 0) {
                        pq.push(v);
                    }
                }
                ++count;
            }

            if (count != N)
                cout << -1 << endl;
            else
                display(head);
        }
    }
    return 0;
}

int bfs(int N, vector<int> adjList[], int s, int dest) {
    int color[N];
    int parent[N];
    int d[N];

    //0 - WHITE
    //1 - GREY
    //2 - BLACK

    //-1 - NIL for parent

    for (int i = 0; i < N; ++i) {
        color[i] = 0;
        parent[i] = -1;
        d[i] = 1000000;
    }

    color[s] = 1;
    d[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v: adjList[u]) {
            if (color[v] == 0) {
                color[v] = 1;
                d[v] = d[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }

        color[u] = 2;
    }

    if (parent[dest] == -1)
        return -1;
    return d[dest];
}

double dijkstra(int N, vector<pair<int, double>> adjList[], int s, int dest) {
    double d[N];
    int parent[N];

    //initialize single source
    for (int i = 0; i < N; ++i) {
        d[i] = 1000000.0;
        parent[i] = -1;
    }
    d[s] = 0.0;

    //dijkstra
    priority_queue<pair<int, double>, vector<pair<int, double>>, Comparator> pq;
    pair<int, double> source = make_pair(s, 0.0);
    pq.push(source);

    for (int i = 0; i < N; ++i) {
        if (s != i) {
            pq.push(make_pair(0, 1000000.0));
        }
    }

    while (!pq.empty()) {
        pair<int, double> p = pq.top();
        pq.pop();

        int u = p.first;
        double wt_u = p.second;

        if (u == dest)
            break;

        for (auto x: adjList[u]) {
            int v = x.first;
            double wt_v = x.second;

            //relax
            if (d[v] > d[u] + wt_v) {
                d[v] = d[u] + wt_v;
                parent[v] = u;
                pq.push(make_pair(v, d[v]));
            }
        }

    }

    if (parent[dest] == -1)
        return -1.0;
    return d[dest];
}

void display(Node *node) {
    if (node == NULL) {
        printf("E\t");
        return;
    }
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->link;
    }
    cout << endl;
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