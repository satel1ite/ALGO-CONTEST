import sys
from collections import deque


def add_edge(graph, edges, u, v, cap, original_id):
    id_direct = len(edges)
    edges.append([u, v, cap, 0, original_id, id_direct + 1])
    edges.append([v, u, 0, 0, -1, id_direct])
    graph[u].append(id_direct)
    graph[v].append(id_direct + 1)


def bfs(n, graph, edges, level, delta):
    for i in range(n + 1):
        level[i] = -1
    level[1] = 0
    q = deque([1])
    while q:
        u = q.popleft()
        for edge_id in graph[u]:
            e = edges[edge_id]
            v = e[1]
            if level[v] == -1 and e[2] - e[3] >= delta:
                level[v] = level[u] + 1
                q.append(v)
    return level[n] != -1


def dfs(u, min_cap, n, graph, edges, level, ptr, delta):
    if u == n:
        return min_cap
    while ptr[u] < len(graph[u]):
        edge_id = graph[u][ptr[u]]
        e = edges[edge_id]
        v = e[1]
        if level[v] != level[u] + 1 or e[2] - e[3] < delta:
            ptr[u] += 1
            continue
        new_cap = min(min_cap, e[2] - e[3])
        pushed = dfs(v, new_cap, n, graph, edges, level, ptr, delta)
        if pushed > 0:
            e[3] += pushed
            edges[e[5]][3] -= pushed
            return pushed
        ptr[u] += 1
    return 0


sys.setrecursionlimit(10000)
data = sys.stdin.buffer.read().split()
idx = 0
n = int(data[idx])
idx += 1
m = int(data[idx])
idx += 1
edges = []
graph = [[] for _ in range(n + 1)]
for i in range(m):
    u = int(data[idx])
    idx += 1
    v = int(data[idx])
    idx += 1
    c = int(data[idx])
    idx += 1
    add_edge(graph, edges, u, v, c, i)

level = [-1] * (n + 1)
max_flow = 0
delta = 1 << 30
INF = float('inf')
while delta > 0:
    while bfs(n, graph, edges, level, delta):
        ptr = [0] * (n + 1)
        while True:
            pushed = dfs(1, INF, n, graph, edges, level, ptr, delta)
            if pushed == 0:
                break
            max_flow += pushed
    delta //= 2

ans = [0] * m
for e in edges:
    if e[4] != -1:
        ans[e[4]] = e[3]

out = [str(max_flow)]
for x in ans:
    out.append(str(x))
sys.stdout.write('\n'.join(out) + '\n')
