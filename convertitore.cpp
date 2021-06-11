#include "widget.h"

#include <iostream>
#include <math.h>
#include <string>
/*
    Conversioni DEC-BIN BIN-DEC con la virgola
    Moraru Liviu 3C-i
*/

int string_to_int(std::string &str);
std::string int_to_string(int x);
std::string double_to_string(double x);

//--------------------------------------------------------------
struct esponente
{
    std::string esponente_dec;
    std::string esponente_bin;
    bool is_positive = true;
};
void Esponente_Dec_to_Bin();
void Esponente_Bin_to_Dec();

//--------------------------------------------------------------
struct mantissa
{
    std::string mantissa_dec;
    std::string mantissa_bin;
    int precisione = 22;
};
void Mantissa_Dec_to_Bin();
void Mantissa_Bin_to_Dec();

//--------------------------------------------------------------
struct Convertitore
{
    esponente DB_esponente;
    mantissa DB_mantissa;
};
//--------------------------------------------------------------

Convertitore DB;

void cleanDB(void)
{
    DB.DB_esponente.esponente_bin.clear();
    DB.DB_esponente.esponente_dec.clear();
    DB.DB_esponente.is_positive = true;

    DB.DB_mantissa.mantissa_bin.clear();
    DB.DB_mantissa.mantissa_dec.clear();
}

const std::string Widget::Convertitore_start_DecBin(std::string str)
{
    if(Convertitore_Leggi_Input_Dec_Bin(str))
    {
        return "Ivalid input DEC-BIN";
    }
    Esponente_Dec_to_Bin();
    Mantissa_Dec_to_Bin();

    std::string result;

    if (DB.DB_esponente.is_positive)
    {
        result = "(0)" + DB.DB_esponente.esponente_bin + '.' + DB.DB_mantissa.mantissa_bin;
    }
    else // 0 per positivo, 1 per negativo
    {
        result = "(1)" + DB.DB_esponente.esponente_bin + '.' + DB.DB_mantissa.mantissa_bin;
    }

    return result;
}

const std::string Widget::Convertitore_start_BinDec(std::string str)
{
    if(Convertitore_Leggi_Input_Bin_Dec(str))
    {
        return "Invalid input BIN-DEC";
    }
    Esponente_Bin_to_Dec();
    Mantissa_Bin_to_Dec();

    if (DB.DB_esponente.is_positive == false)
    {
        DB.DB_esponente.esponente_dec.insert(DB.DB_esponente.esponente_dec.begin(), '-');
    }

    return DB.DB_esponente.esponente_dec + '.' + DB.DB_mantissa.mantissa_dec;
}

bool Widget::Convertitore_Leggi_Input_Dec_Bin(std::string str)
{
    if(str[0] == '0')
    {
        return true;
    }

    if (str[0] == '-')
    {
        DB.DB_esponente.is_positive = false;
        str.erase(str.begin());
    }

    int i;
    for (i = 0; (str[i] != '.') && (i < static_cast<int>(str.size())); ++i)
    {
        DB.DB_esponente.esponente_dec.push_back(str[i]);
    }
    ++i; // eliminare la virgola
    for (; i < static_cast<int>(str.size()); ++i)
    {
        DB.DB_mantissa.mantissa_dec.push_back(str[i]);
    }

    return false;
}

bool Widget::Convertitore_Leggi_Input_Bin_Dec(std::string str)
{
    for (auto i : str)
    {
        if (i != '1' && i != '0' && i != '.')
        {
            std::cout << std::endl << "input non valido";
            return true;
        }
    }

    int i = 0;
    for (i = 0; i < static_cast<int>(str.size()) && str[i] != '.'; ++i)
    {
        DB.DB_esponente.esponente_bin.push_back(str[i]);
    }
    ++i; // eliminare la virgola
    for (; i < static_cast<int>(str.size()); ++i)
    {
        DB.DB_mantissa.mantissa_bin.push_back(str[i]);
    }

    if (str[0] == '1')
    {
        DB.DB_esponente.is_positive = false;
    }

    return false;
}

void Esponente_Dec_to_Bin()
{
    int esponente_dec = string_to_int(DB.DB_esponente.esponente_dec);

    int resto;
    while (esponente_dec)
    {
        resto = esponente_dec % 2;
        esponente_dec /= 2;
        DB.DB_esponente.esponente_bin.insert(DB.DB_esponente.esponente_bin.begin(), (resto + '0'));
    }
}

void Esponente_Bin_to_Dec()
{
    int result = 0;

    int i = 0;
    if (!DB.DB_esponente.is_positive)
    {
        i = 1;
    }

    for (; i < static_cast<int>(DB.DB_esponente.esponente_bin.size()); ++i)
    {
        if (DB.DB_esponente.esponente_bin[i] == '1')
        {
            result += 1 * static_cast<int>(
                              pow(2, DB.DB_esponente.esponente_bin.size() - i - 1)); // 1 * 2^string_size - i
        }
    }

    DB.DB_esponente.esponente_dec = int_to_string(result);
}

void Mantissa_Dec_to_Bin()
{
    double mantissa_dec = string_to_int(DB.DB_mantissa.mantissa_dec);

    size_t i = DB.DB_mantissa.mantissa_dec.size(); // il compilatore mi dava dei warnings
    while (i)
    {
        --i;
        mantissa_dec *= 0.1; // se la mantissa = 67 -> 0,67
    }
    // std::cout << mantissa_dec;

    int precisione = DB.DB_mantissa.precisione;
    while (precisione) // precisione default = 10
    {
        precisione--;
        mantissa_dec *= 2;
        if (mantissa_dec > 1)
        {
            DB.DB_mantissa.mantissa_bin.push_back('1');
            mantissa_dec -= 1;
        }
        else
        {
            DB.DB_mantissa.mantissa_bin.push_back('0');
        }
    }
}

void Mantissa_Bin_to_Dec()
{
    double result = 0;

    for (int i = 0; i < static_cast<int>(DB.DB_mantissa.mantissa_bin.size()); ++i)
    {
        if (DB.DB_mantissa.mantissa_bin[i] == '1')
        {
            result += 1 * pow(2, (i + 1) * (-1));
        }
    }
    //std::cout << result << std::endl;
    DB.DB_mantissa.mantissa_dec = double_to_string(result);
}

int string_to_int(std::string &str)
{
    int result = 0, t = 1;
    for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i)
    {
        result += (str[i] - '0') * t;
        t *= 10;
    }
    return result;
}

std::string int_to_string(int x)
{
    int res = 0;
    std::string str;
    while (x)
    {
        res = x % 10;
        x /= 10;
        str.insert(str.begin(), (res + '0'));
    }
    return str;
}
std::string double_to_string(double x)
{
    int res;
    //double t = 0;
    std::string str;

    for (int i = 0; i < DB.DB_mantissa.precisione; ++i) //precisione default = 10
    {
        res = static_cast<int>(x * 10);
        x = x * 10;
        x = x - res;
        str.push_back(res + '0');
    }
    return str;
}
