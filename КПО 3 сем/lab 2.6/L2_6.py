#Список таких пар (кортежей из двух элементов) значений из списка чисел L, что первое значение строго меньше второго. 
# Например, [3,4.1,2] → [(3, 4.1), (2, 3), (2, 4.1)].
import random

def main():
        length = int(input("Введите количество элементов массива: "))

        array = []
        for i in range(length):
            array.append(random.randint(0, 100))

        print('\nИсходный массив: ', array)

        new_array = [(array[i], array[j]) for i in range(length) for j in range(length) if array[i] < array[j]]

        print('Новый массив: ', new_array)

if __name__ == '__main__':
    main()
