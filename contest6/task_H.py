def count_subsets(numbers, target):
    dp = [0] * (target + 1)
    dp[0] = 1
    for num in numbers:
        if num > target:
            continue
        for s in range(target, num - 1, -1):
            dp[s] += dp[s - num]
    return dp[target]


def solve_friends(n):
    total = 0
    for min_val in range(1, n + 1):
        max_val = 2 * min_val
        available_numbers = []
        for num in range(min_val + 1, max_val):
            if num <= n:
                available_numbers.append(num)
        target_sum = n - min_val
        if target_sum < 0:
            continue
        ways = count_subsets(available_numbers, target_sum)
        total += ways
    return total


n = int(input())
answer = solve_friends(n)
print(answer)
