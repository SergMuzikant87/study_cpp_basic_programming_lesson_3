#include <iostream>
#include <string>
#include <clocale>
#include <cmath>

#define NUMBERS_DEFAULT_VALUE (1.0)
#define ZERO_NUM_MAXIMUM_TRESHOLD (0.00000001)
#define ZERO_NUM_MINIMUM_TRESHOLD (-0.00000001)

class Calculyator
{
    private:
        double __num1;
        double __num2;

        static double __not_zero_set(double num)
        {
            if((num >= 0.0) && (num <= ZERO_NUM_MAXIMUM_TRESHOLD))
            {
                return ZERO_NUM_MAXIMUM_TRESHOLD;
            }
            else if((num >= ZERO_NUM_MINIMUM_TRESHOLD) && (num <= -0.0))
            {
                return ZERO_NUM_MINIMUM_TRESHOLD;
            }
            return num;
        }
        
        static bool __is_not_zero(double num)
        {
            return (num >= ZERO_NUM_MAXIMUM_TRESHOLD) || (num <= ZERO_NUM_MINIMUM_TRESHOLD);
        }

    public:
        Calculyator(double num1 = NUMBERS_DEFAULT_VALUE, double num2 = NUMBERS_DEFAULT_VALUE) : __num1{Calculyator::__not_zero_set(num1)}, __num2{Calculyator::__not_zero_set(num2)} {};

        double add(void) const {return __num1 + __num2;};
        double multyply(void) const {return __num1 * __num2;};
        double substruct_1_2(void) const {return __num1 - __num2;};
        double substruct_2_1(void) const {return 0.0 - this->substruct_1_2();};
        double divide_1_2(void) const {return __num1 / __num2;};
        double divide_2_1(void) const {return __num2 / __num1;};

        bool set_num1(double num1)
        {
            if(Calculyator::__is_not_zero(num1))
            {
                __num1 = num1;
                return true;
            }
            return false;
        };

        bool set_num2(double num2)
        {
            if(Calculyator::__is_not_zero(num2))
            {
                __num2 = num2;
                return true;
            }
            return false;
        };
};

int main(int argc, char * argv[])
{
    Calculyator calculyator;

    int inputs_count_maximum {16};
    while(inputs_count_maximum--)
    {
        double num1 {};
        double num2 {};

        std::cout << "------------------------------------------------------------\n";

        std::cout << "Введите \'num1\': ";
        if(!(std::cin >> num1))
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Принудительный выход из программы.\n";
            return 0;
        }

        if(!calculyator.set_num1(num1))
        {
            std::cout << "Неверный ввод!\n";
            continue;
        };

        std::cout << "Введите \'num2\': ";
        if(!(std::cin >> num2))
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Принудительный выход из программы.\n";
            return 0;
        }

        if(!calculyator.set_num2(num2))
        {
            std::cout << "Неверный ввод!\n";
            continue;
        };

        std::cout << "num1 + num2 = " << calculyator.add() << std::endl; 
        std::cout << "num1 * num2 = " << calculyator.multyply() << std::endl;
        std::cout << "num1 - num2 = " << calculyator.substruct_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calculyator.substruct_2_1() << std::endl;
        std::cout << "num1 / num2 = " << calculyator.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calculyator.divide_2_1() << std::endl;     
    }

    std::cout << "Выход из программы про причине превышения максимального количества вводов.\n";
    return 0;
}
