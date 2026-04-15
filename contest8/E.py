import sys


def get_data():
    input_data = sys.stdin.read().split()
    return input_data


def build_edges(n, data):
    edges = []
    idx = 1
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            w = int(data[idx])
            if w != 100000:
                edges.append((i, j, w))
            idx += 1
    return edges


def solve():
    data = get_data()
    n = int(data[0])
    edges = build_edges(n, data)
    dist = [0] * (n + 1)
    parent = [-1] * (n + 1)

    last_update = -1
    for _ in range(n):
        last_update = -1
        for u, v, w in edges:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                parent[v] = u
                last_update = v

    if last_update == -1:
        print("NO")
        return

    print("YES")
    curr = last_update
    for _ in range(n):
        curr = parent[curr]

    cycle = []
    start = curr
    cycle.append(start)
    curr = parent[start]

    while curr != start:
        cycle.append(curr)
        curr = parent[curr]

    cycle.append(start)
    cycle.reverse()

    print(len(cycle))
    print(" ".join(map(str, cycle)))


solve()
