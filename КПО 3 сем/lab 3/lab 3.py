
import string

def main():
    try:
        str1 = input("введите первую строку : ")
        if len(str1)<= 0:
            raise ValueError('Длина строки должна быть строго больше нуля')

        str2 = input("введите вторую строку : ")
        
        if len(str2)<= 0:
            raise ValueError('Длина строки должна быть строго больше нуля')

        
        print(f'\nПервая строка: {str1}')
        print(f'Вторая строка: {str2}')

        count_1 = int(input('\nВведите количество первых символов первой строки: '))
        if count_1 <= 0 or count_1 > len(str1):
            raise ValueError('Количество символов должно быть больше нуля и меньше длины строки')

        count_2 = int(input('Введите количество последних символов второй строки: '))
        if count_2 <= 0 or count_2 > len(str2):
            raise ValueError('Количество символов должно быть больше нуля и меньше длины строки')

        result = str1[:count_1]
        result += str2[len(str2) - count_2:]

        print(f'\nРезультат: {result}')
    except ValueError as error:
        print(f'\nНекорректный ввод!!!\n{error}')
        
if __name__ == '__main__':
    main()