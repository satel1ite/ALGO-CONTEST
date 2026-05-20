import sys


data = sys.stdin.read().split()
idx = 0
n = int(data[idx])
idx += 1
k = int(data[idx])
idx += 1

graph = [[] for _ in range(n + 1)]
for i in range(1, n + 1):
    while True:
        v = int(data[idx])
        idx += 1
        if v == 0:
            break
        graph[i].append(v)

match = [-1] * (k + 1)
visited = [False] * (n + 1)


def dfs(u):
    if visited[u]:
        return False
    visited[u] = True
    for v in graph[u]:
        if match[v] == -1 or dfs(match[v]):
            match[v] = u
            return True
    return False


for i in range(1, n + 1):
    for j in range(n + 1):
        visited[j] = False
    dfs(i)

pairs = [(match[v], v) for v in range(1, k + 1) if match[v] != -1]
out = [str(len(pairs))]
for u, v in pairs:
    out.append(f"{u} {v}")
sys.stdout.write("\n".join(out) + "\n")
