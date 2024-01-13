def main():
    result = input('Введите начальную строку: ')
    str1 = input('Введите то, что нужно заменить: ')
    str2 = input('Введите то, на что нужно заменить: ')

    result = result.replace(str1, str2)

    print(f'Результирующая строка: {result}')


if __name__ == '__main__':
    main()