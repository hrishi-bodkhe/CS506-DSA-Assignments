#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct vertex {
    int label;
    vector<pair<int, int>> incoming;
    vector<pair<int, int>> incomingCopy;
    vector<pair<int, int>> adj;
    vector<pair<int, int>> adjCopy;
} Vertex;

Vertex *arborescence(Vertex *nodes, int r, int N, vector<int> &headRep);

void
dfs(int r, vector<int> &vertices, vector<int> adjList[], int parent[], int color[], int N, vector<int> &cycleNodes,
    int *start,
    int *end, vector<int> &headRep);

int
dfs_visit(vector<int> &vertices, int u, vector<int> adjList[], int color[], int parent[], int N, int *start, int *end,
          vector<int> &headRep);

void dfsAns(int u, vector<int> &ansVertices, int ansParent[], int ansColor[], Vertex *nodes, int N, int *totalCost,
            int cost[]);

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N, M, s;
        cin >> N >> M >> s;

        Vertex nodes[N + 1];
        vector<int> headRep;
        for (int i = 0; i < N + 1; ++i)
            headRep.push_back(i);

        for (int m = 0; m < M; ++m) {
            int u, v, w;
            cin >> u >> v >> w;

            nodes[v].incoming.push_back(make_pair(u, w));
            nodes[v].incomingCopy.push_back(make_pair(u, w));
            nodes[u].adj.push_back(make_pair(v, w));
            nodes[u].adjCopy.push_back(make_pair(v, w));
        }

        for (int i = 0; i < N + 1; ++i)
            nodes[i].label = i;


        arborescence(nodes, s, N, headRep);

        /*for (int i = 1; i < N + 1; ++i) {
            cout << nodes[i].label << endl;
            cout << "incoming: " << endl;
            for (auto x: nodes[i].incoming)
                cout << x.first << " " << x.second << "; ";
            cout << endl;
            cout << "incomingCopy: " << endl;
            for (auto x: nodes[i].incomingCopy)
                cout << x.first << " " << x.second << "; ";
            cout << endl;
            cout << "adj: " << endl;
            for (auto x: nodes[i].adj)
                cout << x.first << " " << x.second << "; ";
            cout << endl;
            cout << "adjCopy: " << endl;
            for (auto x: nodes[i].adjCopy)
                cout << x.first << " " << x.second << "; ";
            cout << endl;
        }*/

        /*for(int i = 0; i < N + 1; ++i)
            cout << i << " " << headRep[i] << endl;
            */

    }
    return 0;
}

Vertex *arborescence(Vertex *nodes, int r, int N, vector<int> &headRep) {

    //finding min cost edge (u, v) entering v
    for (int v = 1; v < N + 1; ++v) {
        if (v == r)
            continue;

        int p = headRep[v];

        int min = 1000000000;
        for (auto &x: nodes[v].incomingCopy) {
            if (headRep[x.first] != headRep[v] && x.second < min)
                min = x.second;
        }

        for (int j = 1; j < N + 1; ++j) {
            if (headRep[j] == p && j != v) {
                for (auto &y: nodes[j].incomingCopy) {
                    if (headRep[y.first] != headRep[j] && y.second < min)
                        min = y.second;
                }
            }
        }

        if (min != 1000000000) {
            for (int j = 1; j < N + 1; ++j) {

                if (headRep[j] == p) {
                    for (auto &x: nodes[j].incomingCopy) {
                        if (headRep[x.first] != headRep[v])
                            x.second -= min;

                        int u = x.first;
                        for (auto &y: nodes[u].adjCopy) {
                            if (headRep[u] != headRep[v] && y.first == j) {
                                y.second -= min;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    /*for (int i = 1; i < N + 1; ++i) {
        cout << nodes[i].label << endl;
        cout << "incomingCopy: " << endl;
        for (auto x: nodes[i].incomingCopy)
            cout << x.first << " " << x.second << "; ";
        cout << endl;
        cout << "adjCopy: " << endl;
        for (auto x: nodes[i].adjCopy)
            cout << x.first << " " << x.second << "; ";
        cout << endl;
    }*/


    vector<int> adjList[N + 1];
    int parent[N + 1];
    int color[N + 1];


    for (int i = 1; i < N + 1; ++i) {
        for (auto &x: nodes[i].adjCopy) {
            if (headRep[i] != headRep[x.first] && x.second == 0) {
                adjList[i].push_back(x.first);
            }
        }
    }


    vector<int> vertices;
    vector<int> cycleNodes;
    int start = -1;
    int end = -1;
    dfs(r, vertices, adjList, parent, color, N, cycleNodes, &start, &end, headRep);

    if (start == -1) {
        int ansParent[N + 1];
        int ansColor[N + 1];
        vector<int> ansVertices;
        int totalCost = 0;
        int cost[N + 1];

        for (int i = 0; i < N + 1; ++i) {
            ansColor[i] = 0;
            ansParent[i] = -1;
        }

        ansParent[r] = 0;

        for (int i = 0; i < N + 1; ++i)
            cost[i] = 0;

        dfsAns(r, ansVertices, ansParent, ansColor, nodes, N, &totalCost, cost);

        cout << totalCost << " ";

        for (int i = 1; i < N + 1; ++i)
            cout << cost[i] << " ";

        cout << "# ";

        for (int i = 1; i < N + 1; ++i)
            cout << ansParent[i] << " ";

        cout << endl;
    } else if (start > 0) {
        //findMinHeadRep
        int minHP = 10000000;
        for (int j: cycleNodes) {
            if (minHP > headRep[j])
                minHP = headRep[j];
        }

        for (int j: cycleNodes) {
            headRep[j] = minHP;
        }

        arborescence(nodes, r, N, headRep);

        /*for (int i = 0; i < headRep.size(); ++i) {
            cout << i << " " << headRep[i] << " ";
            cout << endl;
        }*/
    }
    return nodes;
}

void
dfs(int r, vector<int> &vertices, vector<int> adjList[], int parent[], int color[], int N, vector<int> &cycleNodes,
    int *start,
    int *end, vector<int> &headRep) {
    //0 - WHITE
    //1 - GREY
    //2 - BLACK

    //0 - NIL for parent


    for (int i = 1; i < N + 1; ++i) {
        color[i] = 0;
        parent[i] = 0;
    }

    for (int i = 1; i < N + 1; ++i) {
        if (color[i] == 0 && dfs_visit(vertices, i, adjList, color, parent, N, start, end, headRep)) {
            break;
        }
    }

    if (*start > 0) {
        for (int v = *end; v != *start; v = parent[v])
            cycleNodes.push_back(v);
        cycleNodes.push_back(*start);
        reverse(cycleNodes.begin(), cycleNodes.end());
    }
}

int
dfs_visit(vector<int> &vertices, int u, vector<int> adjList[], int color[], int parent[], int N, int *start, int *end,
          vector<int> &headRep) {
    color[u] = 1;
    vertices.push_back(u);

    for (auto v: adjList[u]) {
        if (color[v] == 0) {
            parent[v] = u;
            if (dfs_visit(vertices, v, adjList, color, parent, N, start, end, headRep))
                return 1;
        } else if (color[v] == 1) {
            *start = v;
            *end = u;
            return 1;
        }
    }

    color[u] = 2;
    return 0;
}

void dfsAns(int u, vector<int> &ansVertices, int ansParent[], int ansColor[], Vertex *nodes, int N, int *totalCost,
            int cost[]) {
    ansColor[u] = 1;
    ansVertices.push_back(u);

    for (auto &x: nodes[u].adjCopy) {
        int v = x.first;
        int wt = x.second;
        if (ansColor[v] == 0 && wt == 0) {
            ansParent[v] = u;

            for (auto &y: nodes[u].adj) {
                if (y.first == v) {
                    cost[v] = cost[u] + y.second;
                    *totalCost += y.second;
                    break;
                } else
                    continue;
            }
            dfsAns(v, ansVertices, ansParent, ansColor, nodes, N, totalCost, cost);
        }
    }
}

