#include <ncurses.h>
#include <string>
#include <string.h>
#include "calendar.hpp"
#include "nano.hpp"

using namespace std;

int main()
{
    
    Calendar mytool;
    Nano nano;
    nano.tool = &mytool;
    mytool.backend = &nano;
    //nano.bind("<EDITION>", [](){printw("k"); refresh();}, "help");
    //nano.bind("<DEL>%New entry!Write in your entry${E}", [](){printw("J"); refresh();}, "help");
    mytool.init();
    nano.start();
    return 0;
}