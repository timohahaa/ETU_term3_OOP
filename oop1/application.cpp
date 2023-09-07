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
        {
            this->mat.edit();
        }
            break;
        case 2:
        {
            number det = this->mat.calcDeterminand();
            std::cout<<"Determinand is: " <<det <<std::endl;
        }
            break;
        case 3:
        {
            Matrix trans = this->mat.transposed();
            trans.printMatrix();
        }
            break;
        case 4:
        {
            int rank = this->mat.calcRank();
            std::cout<<"Rank is: " <<rank <<std::endl;
        }
            break;
        case 5:
        {
            this->mat.printMatrix();
        }
            break;
        case 6:
        {
            exit = true;
            std::cout<<"Goodbye! :)" << std::endl;
        }
            break;
        }
    }
    return 0;
}

void Application::menu()
{
    std::cout<<"____________________________" << std::endl;
    std::cout<<"1) Enter a matrix"<<std::endl;
    std::cout<<"2) Compute determinand"<<std::endl;
    std::cout<<"3) Print transposed matrix"<<std::endl;
    std::cout<<"4) Compute rank"<<std::endl;
    std::cout<<"5) Print current matrix"<<std::endl;
    std::cout<<"6) Exit"<<std::endl;
    std::cout<<"____________________________" << std::endl;
}
