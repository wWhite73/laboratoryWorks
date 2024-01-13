import math

def evaluate_equation(x):
    if x == 1 or x == -1:
        raise ZeroDivisionError(f'Ошибка деления на 0! math.sqrt({x} * {x} - 1) = 0!!!')
    if -1 < x < 1:
        raise ValueError('Значения числа должны быть < -1 и > 1')

    return 1 / math.sqrt(x * x - 1)


def print_equation(value, result):
    print(f'1 / sqrt({str(value)} * {str(value)} - 1) = {str(result)}')


def task1():
    for i in range(100):
        try:
            value = float(input('Введите x: '))
            print_equation(value, evaluate_equation(value))
        except ValueError as value_error:
            print('Введено некорректное число')
            print(value_error)
        except ZeroDivisionError as zero_division_error:
            print(zero_division_error)
        except OverflowError as overflow_error:
            print(overflow_error)
            print('Число слишком велико')
        except KeyboardInterrupt:
            print(f'\nВы рано сдались! Оставалось ввести чисел: {str(100 - i)}')
            return


def number_of_divisors(x):
    count = 0
    for i in range(x):
        if x % (i + 1) == 0:
            count += 1
    return count


def task2():
    with open('data.txt', 'w') as f:
        for i in range(1, 1000001):
            f.write(str(i) + " : " + str(number_of_divisors(i)) + '\n')
    print('yes')
    return


def main():
    tasks = ['1 - Задание с исключениями', '2 - Задание с менеджерами контекста']
    is_correct = False
    while not is_correct:
        for task in tasks:
            print(task)
        user_task = input('Введите номер задания: ')

        if user_task == '1':
            is_correct = True
            print('\n')
            print('Ну ладно ')
            task1()
            return
        if user_task == '2':
            is_correct = True
            print('\n')
            print('Вывелось в data.txt')
            task2()
            return

        print('Некорректно указан номер задания, повторите попытку')


if __name__ == '__main__':
    main()