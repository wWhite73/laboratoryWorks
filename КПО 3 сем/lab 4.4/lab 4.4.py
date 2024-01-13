def main():
    result = input('Введите начальную строку: ')
    str1 = input('Введите строку для поиска: ')
    str2 = input('Введите то, что нужно вставить после: ')

    result = result.replace(str1, str1 + str2)

    print(f'Результирующая строка: {result}')


if __name__ == '__main__':
    main()