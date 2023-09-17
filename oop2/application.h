#ifndef APPLICATION_H
#define APPLICATION_H

#include "matrix.h"

class Application
{
public:
    Application();
    int exec();

private:
    Matrix mat;

    void menu();
};

#endif // APPLICATION_H
