#Список множеств элементов, которые дают одинаковый остаток при делении на положительное число m, из списка целых чисел L. 
# Например, L=[1,3,4,7,9],m=3 → [{3,9}, {1,4,7}].
import random
a = input()
list = [random.randint(0, 10) for number in range(10)]
new_list = [{number for number in list if not number % int(a)}]
new1_list ={number for number in list if (number % int(a)==1 and number % int(a)>0)}
new2_list ={number for number in list if (number % int(a)==2 and number % int(a)>1)}
print (list)
print(new_list)
print(new1_list)
print (new2_list)
