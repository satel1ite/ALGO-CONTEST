import sys


def get_upper_bound(dp, x):
    low, high = 0, len(dp)
    while low < high:
        mid = (low + high) // 2
        if x < dp[mid]:
            high = mid
        else:
            low = mid + 1
    return low


def solve(n, a):
    a.reverse()
    dp = []
    last_idx_at_len = []
    parent = [-1] * n
    for i, x in enumerate(a):
        idx = get_upper_bound(dp, x)
        if idx == len(dp):
            dp.append(x)
            if idx > 0:
                parent[i] = last_idx_at_len[idx - 1]
            last_idx_at_len.append(i)
        else:
            dp[idx] = x
            if idx > 0:
                parent[i] = last_idx_at_len[idx - 1]
            last_idx_at_len[idx] = i
    curr = last_idx_at_len[-1]
    res_indices = []
    while curr != -1:
        res_indices.append(n - curr)
        curr = parent[curr]
    return res_indices


data = sys.stdin.read().split()
n_in = int(data[0])
nums_in = [int(x) for x in data[1:n_in + 1]]
ans = solve(n_in, nums_in)
print(len(ans))
print(*(ans))
