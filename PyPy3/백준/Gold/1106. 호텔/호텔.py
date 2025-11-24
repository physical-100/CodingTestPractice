
N, M = map(int, input().split())
arr = []
for _ in range(M):
    arr.append(list(map(int, input().split())))
arr = sorted (arr,key=lambda x:(x[1]/x[0]))
max_profit = arr[-1][1]
a = 0
while a<N:
    a+=max_profit
dp = [100001]*1101
dp[0] = 0

for i in range(M):
    for j in range(arr[i][1],a+1):
        if dp[j-arr[i][1]]!= 100001:
            dp[j] = min(dp[j],dp[j-arr[i][1]]+arr[i][0])
ans  = min(dp[N:a+1])
print(ans)