print('Введите размерность n матрицы смежности')
n = int(input())
adj_matrix = []
for i in range(n):
    adj_matrix.append([])
    for v in range(n):
        adj_matrix[i].append([])
for i in range(n):
        adj_matrix[i] =input().split()

pairs = []
for i in range(n):
    for v in range(n):
        if int(adj_matrix[i][v]) == 1:
            pairs.append(str(i+1) + '-' + str(v+1))

print()

for i in pairs:
    print(i)