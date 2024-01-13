#Список элементов списка L с четными индексами. Например, ['a',1,-2,1.2]→['a',-2].
import random
list=(''.join([random.choice(list('123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM')) 
for x in range(10)]))
new_list= list [::2]
print(list)
print(new_list)