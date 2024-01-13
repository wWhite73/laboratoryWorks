def main():
    str1 = input('Введите первую строку: ')
    str2 = input('Введите вторую строку: ')

    result = ''
    for i in zip(str1, str2):
        result += i[0] + i[1]

    if len(str1) < len(str2):
        result += str2[len(str1):]
    elif len(str2) < len(str1):
        result += str1[len(str2):]

    print(f'Исходная строка: {result}')


if __name__ == '__main__':
    main()