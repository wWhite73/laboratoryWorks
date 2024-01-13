#Список четных элементов списка L. Например, ['a',1,-2,1.2]→[-2].

import random
list = [random.randint(-100, 100) for num in range(10)]
new_list = [ num for num in list if num % 2 == 0]
print (list)
print (new_list) 

