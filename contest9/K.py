import sys
from collections import deque


INF = 10 ** 18


def add_edge(graph, edges, u, v, cap, cost):
    idx = len(edges)
    edges.append([u, v, cap, 0, cost, idx + 1])
    edges.append([v, u, 0, 0, -cost, idx])
    graph[u].append(idx)
    graph[v].append(idx + 1)


def spfa(s, t, n_nodes, graph, edges, dist, prev_edge, in_queue):
    for i in range(n_nodes):
        dist[i] = INF
        prev_edge[i] = -1
        in_queue[i] = False
    dist[s] = 0
    q = deque([s])
    in_queue[s] = True
    while q:
        u = q.popleft()
        in_queue[u] = False
        for eid in graph[u]:
            e = edges[eid]
            if e[2] - e[3] <= 0:
                continue
            v = e[1]
            nd = dist[u] + e[4]
            if nd < dist[v]:
                dist[v] = nd
                prev_edge[v] = eid
                if not in_queue[v]:
                    q.append(v)
                    in_queue[v] = True
    return dist[t] < INF


def push_flow(s, t, graph, edges, prev_edge):
    push = INF
    v = t
    while v != s:
        eid = prev_edge[v]
        e = edges[eid]
        push = min(push, e[2] - e[3])
        v = e[0]
    v = t
    while v != s:
        eid = prev_edge[v]
        e = edges[eid]
        e[3] += push
        edges[e[5]][3] -= push
        v = e[0]
    return push


data = sys.stdin.buffer.read().split()
idx = 0
n = int(data[idx])
idx += 1
m = int(data[idx])
idx += 1
graph = [[] for _ in range(n + 1)]
edges = []
for _ in range(m):
    u = int(data[idx])
    idx += 1
    v = int(data[idx])
    idx += 1
    c = int(data[idx])
    idx += 1
    w = int(data[idx])
    idx += 1
    add_edge(graph, edges, u, v, c, w)

source = 1
sink = n
n_nodes = n + 1
dist = [INF] * n_nodes
prev_edge = [-1] * n_nodes
in_queue = [False] * n_nodes
total_cost = 0
while spfa(source, sink, n_nodes, graph, edges, dist, prev_edge, in_queue):
    push = push_flow(source, sink, graph, edges, prev_edge)
    total_cost += push * dist[sink]

sys.stdout.write(str(total_cost) + '\n')
