import sys


n, m = map(int, sys.stdin.readline().split())

weights = list(map(int, sys.stdin.readline().split()))
costs = list(map(int, sys.stdin.readline().split()))

dp = [[0] * (m + 1) for _ in range(n + 1)]

for i in range(1, n + 1):
    cur_w = weights[i - 1]
    cur_c = costs[i - 1]
    for j in range(m + 1):
        if j >= cur_w:
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cur_w] + cur_c)
        else:
            dp[i][j] = dp[i - 1][j]

res_indices = []
curr_w = m
for i in range(n, 0, -1):
    if dp[i][curr_w] != dp[i - 1][curr_w]:
        res_indices.append(i)
        curr_w -= weights[i - 1]

for idx in reversed(res_indices):
    print(idx)
