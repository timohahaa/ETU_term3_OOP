#include <iostream>
#include "application.h"

Application::Application()
{

}

int Application::exec()
{
    bool exit = false;
    int option = 0;

    std::cout<<"Welcome to my matrix calculator!"<<std::endl;
    std::cout<<"Here are your options:"<<std::endl;
    while (!exit)
    {
        Application::menu();
        std::cin >> option;
        switch(option)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            exit = true;
            break;
        }
    }
    return 0;
}

void Application::menu()
{
    std::cout<<"1) Enter a matrix"<<std::endl;
    std::cout<<"2) Compute determinand"<<std::endl;
    std::cout<<"3) Print transposed matrix"<<std::endl;
    std::cout<<"4) Compute rank"<<std::endl;
    std::cout<<"5) Print current matrix"<<std::endl;
    std::cout<<"6) Exit"<<std::endl;
}
