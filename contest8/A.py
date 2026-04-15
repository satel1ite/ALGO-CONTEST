import sys
import heapq


def build_graph(n, edges):
    graph = [[] for _ in range(n)]
    for u, v, w in edges:
        graph[u].append((v, w))
        graph[v].append((u, w))
    return graph


def dijkstra(n, graph, start):
    dist = [2009000999] * n
    dist[start] = 0
    pq = [(0, start)]

    while pq:
        current_dist, u = heapq.heappop(pq)

        if current_dist > dist[u]:
            continue

        for v, weight in graph[u]:
            distance = current_dist + weight

            if distance < dist[v]:
                dist[v] = distance
                heapq.heappush(pq, (distance, v))

    return dist


input_data = sys.stdin.read().split()
t = int(input_data[0])
idx = 1

results = []

for _ in range(t):
    n = int(input_data[idx])
    m = int(input_data[idx + 1])
    idx += 2

    edges = []
    for _ in range(m):
        u = int(input_data[idx])
        v = int(input_data[idx + 1])
        w = int(input_data[idx + 2])
        edges.append((u, v, w))
        idx += 3

    s = int(input_data[idx])
    idx += 1

    graph = build_graph(n, edges)
    distances = dijkstra(n, graph, s)

    results.append(" ".join(map(str, distances)))

sys.stdout.write("\n".join(results) + "\n")
