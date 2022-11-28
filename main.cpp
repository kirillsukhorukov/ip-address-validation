#include <iostream>
#include <string>

//Функция нахождения октета по номеру

std::string find_octet (std::string str, int number)
{
    std::string octet;
    int dotNumber = 0;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] != '.')
        {
            if (dotNumber == number)
            {
                octet += str[i];
            }
        }
        else
        {
            dotNumber++;
        }
        if (dotNumber > number)
        {
            return octet;
        }
    }
    return octet;
}

// Функция проверки строки по словарю
bool find_bad_char (std::string str, std::string dictionary)
{
    for (int i=0; i<str.length(); i++)
    {
        int goodChar = dictionary.find(str[i]);
        if (goodChar<0) return true;
    }
    return false;
}

// Функция проверки правильности использования точек
bool dot_incorrect (std::string str)
{
    int doubleDot = int (str.find(".."));
    int dotCount = 0;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] == '.') dotCount++;
    }
    if (str[0] == '.' || str[str.length()-1] == '.' || doubleDot >= 0 || dotCount != 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Функция проверки октетов
bool octet_incorrect (std::string str)
{
    // Получение октета
    for (int i=0; i<4; i++)
    {
        std::string octet = find_octet(str, i);
        // Проверка на длину октета
        if (octet.length()>3)
        {
            return true;
        }
        else
        {
            // Преобразуем октет в число
            int number = 0;
            for (int c=0; c<octet.length(); c++)
            {
                number = number*10 + int (octet[c]-'0');
                // Проверяем полученное число (не более 255)
                if (number > 255)
                {
                    return true;
                }
            }
            // Преобразуем число в контрольную строку (без нулей)
            std::string control = std::to_string(number);
            // Если исходный октет не совпадает с октетом из числа,
            // то в исходном октете есть лишние нули
            if (octet != control)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    while (true)
    {
        // Ввод строки с адресом электронной почты
        std::string ipAddress;
        std::cout << "Enter your IP-address: ";
        std::cin >> ipAddress;

        // Выход из цикла
        if (ipAddress == "exit")
        {
            std::cout << "Program stopped!" << std::endl;
            break;
        }

        // Задание строки-словаря для проверки корректности символов IP-адреса
        std::string dictionary = ".0123456789";

        // Вывод результата проверки
        if (find_bad_char(ipAddress,dictionary) || dot_incorrect(ipAddress) || octet_incorrect(ipAddress))
        {
            std::cout << "Your IP-address is invalid!" << std::endl;
        }
        else
        {
            std::cout << "Your IP-address is valid." << std::endl;
        }

    }

    return 0;
}