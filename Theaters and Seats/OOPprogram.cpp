/*
            Данная программа написана в целях обучения с объектно-ориентировонным программированием, наследием и
            динамическим связыванием. А также для демонстрации навыка работать с этим.
            
            Программа ещё не окончательная и дорабатывается.

            В данной версии программы отсутсвует циклическая версия, в которой пользователь сможет создавать "театры"
            и заказывать в них "билеты" столько, сколько он захочет. Также создается версия с шаблонным "театром", 
            в котором можно выбрать тип номеров сидений, а не только integer (Например: char 'A','B','C' и т. д.).

            Возможно, к тому же, изменение класса Seat. В данной программе, чтобы использовался данный класс, в нём написаны 
            публичные конструкторы, а это нужно для использования ассоциативного контейнера map<,>. В обновленной версии у
            класса Seat не будет публичных переменных и функций вовсе.

            Будут и маленькие исправления с рефакторингом.

            Программу написал и обновляет Иванов Иван
*/
#include "Theater.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

const bool TEST_PROGRAM = true;
const bool CYCLE_PROGRAM = false;

using std::cout;
using std::cin;
using std::string;

using vecIterPtrTh = std::vector<std::unique_ptr<Theater>>::iterator;


int main()
{
    string search;
    auto isNameEqual = [&search](std::unique_ptr<Theater>& t) -> bool {return t->name() == search ? true : false; };

    if (TEST_PROGRAM)
    {
        float wallet = 1000.0f;
        std::vector<std::unique_ptr<Theater>> testTheaters;
        testTheaters.emplace_back(new Theater("Peter's Theater"));
        testTheaters.emplace_back(new Theater("Small Theater", 54));
        testTheaters.emplace_back(new Theater("Big Theater", 197, 8));

        search = "Small Theater";
        auto STh = std::find_if(testTheaters.begin(), testTheaters.end(), isNameEqual);
        if (STh != testTheaters.end())
        {
            cout << "  Checks \"Small Theater\" and order 2 tickets for #45 seat\n";
            (*STh)->check_theater_seats(cout);
            (*STh)->order_ticket("George", wallet, 45);
            order_ticket(**STh, "George", wallet, 45); //Идентичный вызов
        }

        //Создание двух театров
        Theater JohnatanTh("J Cinema", 80, 10);
        Theater JohnTh("John's Theater");

        cout << "\n  Types of seats in \"J Cinema\" and \"John's Theater\"\n" 
            "  (O - Ordinary Seat, V - Vip Seat (With increased price), C - Child Seat (With discount))\n" ;
        JohnatanTh.check_theater_types_of_seats(cout);
        JohnTh.check_theater_types_of_seats(cout);
                
        JohnTh.random_fill(); //Заполнить случайно пустой зал. 

        cout << "\n  Check \"John's Theater\" and check seat #99\n";
        cout << JohnTh; //Вызов функции
        JohnTh.check_seat(99);

        cout << "\n  Reserve seats #1, #2, #3, #44, #45, #46 in \"J Cinema\" and check theater itself\n";
        reserve_seats(JohnatanTh, "Johnatan", { 1, 2, 3, 44, 45, 46 });
        JohnatanTh.check_theater_seats(cout);

        cout << "\n\n\nPress Enter to exit the program...";
        string exit;
        std::getline(cin, exit);
    }

    //Under Development | Разрабатывается
    if (CYCLE_PROGRAM)
    {
        float wallet = {};
        cout << "How much money in your wallet? (This need to order tickets, leave empty if you want infinite money)";
        if (!(cin >> wallet))
            wallet = INFINITY;
        std::vector<std::unique_ptr<Theater>> theaters;
        string command = {};

        cout << "(Type 'help' to see curent commands, or 'exit' to close the program)\n";
        while (command[0] != 'e') {
            cout << "Please, type the command: ";
            cin >> command;
            cout << std::endl;

            command[0] = std::tolower(command[0]);
            std::stringstream ss(command);
            ss >> command;
            switch (command[0])
            {
            case 'c': {
                if (!(ss >> command)) {
                    ss.clear();
                    std::cout << "What theater and number of seat?";
                    cin >> command;
                    ss << command;
                }
                else
                    //...
                      // std::find_if(theaters.begin(), theaters.end(), isNameEqual);
                    ;
                    break;
            }
            case 'e': {
                std::cout << "Exit from program...";
                break;
            }
            case 'h': {
                std::cout << "Curent commands: help, exit, check, build...\n" <<
                    "(You can type one letter for commands, like 'h' for 'help', but names need to write whole)\n\n";
                break;
            }
            case 't': {
                //...
                break;
            }
            case 'b': {
                //build...
                break;
            }
            default: {
                std::cout << "Incorrect command, type 'help' to see commands.\n\n";
                break;
            }
        }

        }

    }

    return 0;
}
