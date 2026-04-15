import sys

sys.setrecursionlimit(200000)


def find(i, parent):
    if parent[i] == i:
        return i
    parent[i] = find(parent[i], parent)
    return parent[i]


def union(i, j, parent, rank):
    root_i = find(i, parent)
    root_j = find(j, parent)

    if root_i != root_j:
        if rank[root_i] < rank[root_j]:
            parent[root_i] = root_j
        elif rank[root_i] > rank[root_j]:
            parent[root_j] = root_i
        else:
            parent[root_j] = root_i
            rank[root_i] += 1


def solve():
    input_data = sys.stdin.read().split()

    n = int(input_data[0])
    m = int(input_data[1])

    edges = []
    idx = 2
    for _ in range(m):
        u = int(input_data[idx]) - 1
        v = int(input_data[idx + 1]) - 1
        w = int(input_data[idx + 2])
        edges.append([w, u, v])
        idx += 3

    edges.sort()
    parent = []
    rank = []
    for i in range(n):
        parent.append(i)
        rank.append(0)
    ans = 0
    for edge in edges:
        w = edge[0]
        u = edge[1]
        v = edge[2]
        if find(u, parent) != find(v, parent):
            ans += w
            union(u, v, parent, rank)
    print(ans)


solve()
