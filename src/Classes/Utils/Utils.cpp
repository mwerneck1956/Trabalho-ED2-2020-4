#include "./Utils.h"

//https://stackoverflow.com/questions/228617/how-do-i-clear-the-console-in-both-windows-and-linux-using-c

void Utils::ClearScreen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}
