import sys
from collections import deque


def parse():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    m = int(data[1])
    cap = [[0] * (n + 1) for _ in range(n + 1)]
    adj = [[] for _ in range(n + 1)]
    edges = []
    pos = 2
    for eid in range(1, m + 1):
        u = int(data[pos])
        v = int(data[pos + 1])
        c = int(data[pos + 2])
        pos += 3
        cap[u][v] += c
        cap[v][u] += c
        adj[u].append(v)
        adj[v].append(u)
        edges.append((u, v, eid))
    return n, cap, adj, edges


def max_flow(n, cap, adj):
    INF = 10 ** 18
    sink = n
    seen = [0] * (n + 1)
    stamp = 0

    def push(u, lim):
        if u == sink:
            return lim
        seen[u] = stamp
        for v in adj[u]:
            if seen[v] != stamp and cap[u][v] > 0:
                got = push(v, min(lim, cap[u][v]))
                if got:
                    cap[u][v] -= got
                    cap[v][u] += got
                    return got
        return 0

    total = 0
    while True:
        stamp += 1
        added = push(1, INF)
        if not added:
            break
        total += added
    return total


def reachable(n, cap, adj):
    side = [False] * (n + 1)
    side[1] = True
    q = deque([1])
    while q:
        u = q.popleft()
        for v in adj[u]:
            if not side[v] and cap[u][v] > 0:
                side[v] = True
                q.append(v)
    return side


def cut_edges(edges, side):
    out = []
    for u, v, eid in edges:
        if side[u] != side[v]:
            out.append(eid)
    out.sort()
    return out


n, cap, adj, edges = parse()
flow = max_flow(n, cap, adj)
side = reachable(n, cap, adj)
ans = cut_edges(edges, side)
sys.stdout.write(f"{len(ans)} {flow}\n")
sys.stdout.write(' '.join(map(str, ans)) + '\n')
