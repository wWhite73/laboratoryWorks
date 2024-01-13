#Список положительных элементов списка L. Например, [1,-2,1.2]→[1,1.2].
import random
list = [random.randint(-10, 10) for number in range(10)]
new_list = [ number for number in list if number > 0]
print (list)
print (new_list)

