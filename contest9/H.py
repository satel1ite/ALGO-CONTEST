import sys
from collections import deque


class Edge:
    __slots__ = ('fr', 'to', 'cap', 'flow', 'orig', 'rev')

    def __init__(self, fr, to, cap, flow, orig, rev):
        self.fr = fr
        self.to = to
        self.cap = cap
        self.flow = flow
        self.orig = orig
        self.rev = rev


sys.setrecursionlimit(10000)


def add_edge(u, v, c, orig_id):
    eid = len(edges)
    edges.append(Edge(u, v, c, 0, orig_id, eid + 1))
    edges.append(Edge(v, u, 0, 0, -1, eid))
    graph[u].append(eid)
    graph[v].append(eid + 1)


def bfs(delta):
    k = 0
    while k <= n:
        level[k] = -1
        k += 1
    level[1] = 0
    bq = deque()
    bq.append(1)
    while bq:
        u = bq.popleft()
        for eid in graph[u]:
            e = edges[eid]
            w = e.to
            if level[w] == -1 and e.cap - e.flow >= delta:
                level[w] = level[u] + 1
                bq.append(w)
    return level[n] != -1


def dfs(u, min_cap, ptr_arr, delta):
    if u == n:
        return min_cap
    while ptr_arr[u] < len(graph[u]):
        eid = graph[u][ptr_arr[u]]
        e = edges[eid]
        w = e.to
        residual = e.cap - e.flow
        if level[w] != level[u] + 1 or residual < delta:
            ptr_arr[u] += 1
            continue
        new_cap = min_cap if min_cap < residual else residual
        pushed = dfs(w, new_cap, ptr_arr, delta)
        if pushed > 0:
            e.flow += pushed
            edges[e.rev].flow -= pushed
            return pushed
        ptr_arr[u] += 1
    return 0


data = sys.stdin.buffer.read().split()
ptr_in = 0
n = int(data[ptr_in])
ptr_in += 1
m = int(data[ptr_in])
ptr_in += 1

edges = []
graph = [[] for _ in range(n + 1)]

i = 0
while i < m:
    u = int(data[ptr_in])
    ptr_in += 1
    v = int(data[ptr_in])
    ptr_in += 1
    c = int(data[ptr_in])
    ptr_in += 1
    add_edge(u, v, c, i)
    i += 1

level = [-1] * (n + 1)

max_flow = 0
delta = 1 << 30
INF = 1 << 60

while delta > 0:
    while bfs(delta):
        ptr_arr = [0] * (n + 1)
        while True:
            pushed = dfs(1, INF, ptr_arr, delta)
            if pushed == 0:
                break
            max_flow += pushed
    delta >>= 1

ans = [0] * m
for e in edges:
    if e.orig != -1:
        ans[e.orig] = e.flow

out = []
out.append(str(max_flow))
for x in ans:
    out.append(str(x))
sys.stdout.write('\n'.join(out) + '\n')
