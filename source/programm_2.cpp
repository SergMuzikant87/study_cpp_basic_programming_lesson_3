#include <iostream>
#include <string>
#include <clocale>
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    1. Счётчик
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UINT32_HIGEST_BIT_MASK (((uint32_t)1) << 31)

typedef enum : bool
{
    OK = 0,
    COUNTER_OVERFLOW = !OK,
}status_t;

class Counter
{
    private:
        uint32_t __cnt;

    public:
        Counter(uint32_t cnt = 1): __cnt {cnt} {}; 
        
        uint32_t get(void) const;
        void set(uint32_t cnt);
        status_t inc(void);
        status_t dec(void);
};

uint32_t Counter::get(void) const 
{
    return __cnt;
}

void Counter::set(uint32_t cnt)
{
    __cnt = cnt;
}

status_t Counter::inc(void)
{
    uint32_t cnt_prev = __cnt;
    __cnt++;
    return static_cast<status_t>((!(__cnt & UINT32_HIGEST_BIT_MASK)) && (cnt_prev & UINT32_HIGEST_BIT_MASK));
}

status_t Counter::dec(void)
{
    uint32_t cnt_prev = __cnt;
    __cnt--;
    return static_cast<status_t>((__cnt & UINT32_HIGEST_BIT_MASK) && (!(cnt_prev & UINT32_HIGEST_BIT_MASK)));
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    2. Команды пользоватяля
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum : char
{
    INC = '+',
    DEC = '-',
    READ = '=',
    STOP = 'x',
    UNKNOWN = '?'
}command_t;

struct Command
{
    Counter * __counter = nullptr;
    
    Command(void);
    ~Command(void);
    Command(const Command & command);
    Command & operator= (const Command & command);

    void run(void);
};

Command::Command(void)
{
    std::string input_text;
    std::cout << "Вы хотите указать начальное значение счётчика? Введите \'да\' или \'нет\': ";
    std::cin >> input_text;
    
    if(input_text == "да")
    {
        uint32_t cnt_default {};
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> cnt_default;
        __counter = new Counter(cnt_default);
    }
    else
    {   if(input_text != "нет")
        {
            std::cout << "Введён некорректный текст. Для счётчика оставляем значение по умолчанию: ";
        }
        __counter = new Counter();
    } 
}

Command::~Command(void)
{
    delete __counter;
}

Command::Command(const Command & command)
{
    __counter = new Counter(command.__counter->get());
}

Command & Command::operator= (const Command & command)
{
    if((&command) != this)
    {
        __counter->set(command.__counter->get());
    }
    return *this;
}

void Command::run(void)
{
    char command {UNKNOWN};
    while(command != STOP)
    {
        std::cout << "Введите команду: ( \'" << INC << "\', \'" << DEC << "\', \'" << READ << "\', \'" << STOP << "\'): ";
        std::cin >> command;
        switch(command)
        {
            case INC: 
                if(__counter->inc() == COUNTER_OVERFLOW)
                {
                    std::cout << "Счётчик переполнился.\n";
                } 
                break;
            case DEC: 
                if(__counter->dec() == COUNTER_OVERFLOW)
                {
                    std::cout << "Счётчик переполнился.\n";
                } 
                break;
            case READ: 
                std::cout << __counter->get() << std::endl; 
                break;
            case STOP: 
                std::cout << "До свидания!" << std::endl; 
                break;

            default: 
                std::cout << "Введена некорректная команда." << std::endl;
                command = UNKNOWN;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    3. Пример использования.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "Russian");

    Command command;
    command.run();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
