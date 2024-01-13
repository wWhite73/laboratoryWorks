#Список сумм ключей и соответствующих им значений словаря D, в случае если и ключ и значение являются числами. 
# Например, {1:2,'a':3, -1:1, 3:'a'} → [3,0].
import random
dictionary = {random.randint(-10,10): random.randint(-10,10), random.randint(-10,10): random.randint(-10,10), random.randint(-10,10): random.randint(-10,10)}
list = [ sum(dictionary.keys()), sum(dictionary.values())]
print(dictionary)
print(list)
