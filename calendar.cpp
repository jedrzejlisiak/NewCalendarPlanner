#include <ncurses.h>
#include <string>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "calendar.hpp"

Calendar::Calendar(){
    x = 1;
    y = 2;
    is_saved = "YES";
}

void Calendar::up(){
    if(y > 1)y--;
    this->redraw();
}

void Calendar::right(){
    if(x < col - 2)x++;
    this->redraw();
}

void Calendar::left(){
    if(x > 2)x--;
    this->redraw();
}

void Calendar::down(){
    if(y < row - 2)y++;
    this->redraw();
}

void Calendar::redraw(){
    getmaxyx(stdscr, row, col);
    move(y, x);
    //this->clear();
    move(y, x);
    refresh();
}

void Calendar::setEntry(string field, string value){
    if(field == "KEY"){
        key = value;
    }
    else if(field == "PARAMETR"){
        parametr = value;
    }
    else if(field == "NAMEE"){
        name = value;
    }
    else if(field == "DATE"){
        date = value;
    }
}
string Calendar::getEntry(string field){
    if(field == "IS_SAVED"){
        return is_saved;
    }
    return NULL;
}


void Calendar::addE(){
    this->middle();
    move(y, x);
    string event;
    event = parametr;
    istringstream ss(event);
    string token;
    char tab[10][50];
    char tab1[10][50];
    int j = 0;
    while(getline(ss, token, ':')){
        strcpy(tab[0], token.c_str());
        break;
        
    }
    while(getline(ss, token, '-')){
        strcpy(tab1[j], token.c_str());
        j++;
    }
    istringstream vv(tab1[2]);
    string score;
    while(getline(vv, score, '_')){
        strcpy(sday, score.c_str());
        break;
    }
    //wczytywanie godziny format hh:mm-hh:mm
    istringstream zz(event);
    char tablica[10][50];
    string score3;
    int i=0;
    while(getline(zz, score3, '_')){
        strcpy(tablica[i], score3.c_str());
        i++;
    }
    //move(10,10);
    //printw("Tablica: %s", tablica[1]);
    //name
    strcpy(sname, tab[0]);
    //year
    strcpy(syear, tab1[0]);
    int xyear;
    xyear = std::stoi(syear);
    year = abs(2020 - xyear); //main year
    //month
    strcpy(smonth, tab1[1]);
    xmonth = std::stoi(smonth);
    xday = std::stoi(sday);
    year = abs(2020 - xyear);
    strcpy(hours[year][xmonth][xday], tablica[1]);
    strcpy(name_layer[year][xmonth][xday],sname);
    char detail[50];
    getmaxyx(stdscr, row, col);
    move(row/2,col/2);
    printw("Type details:");
    getstr(detail);
    //this->clear();
    move(y, x);
    printw("Input format: %s", parametr.c_str());
    move(y+1, x);
    //layer name
    printw("Layer name: %s", name_layer[year][xmonth][xday]);
    strcpy(layer[year][xmonth][xday], detail);
    move(y+2,x);
    //event details
    printw("Details: %s", layer[year][xmonth][xday]);
    move(y+3,x);
    //event hours
    printw("Godziny: %s", hours[year][xmonth][xday]);
    pozycjay[year][xmonth][xday] = y;
    
    
}


void Calendar::apply(int year, int xmonth, int xday){
    this->middle();
    string lname;
    lname = name;
    int check = 0;
    for(int i =0; i<100;i++)
    {
        for(int j=1; j<13;j++)
        {
            for(int k=1; k<32;k++)
            {
                if(lname == name_layer[i][j][k])
                {
                    applied[i][j][k] = 1;
                    getmaxyx(stdscr, row, col);
                    move(row/2, col/2);
                    printw("Succesfuly confirmed!");
                    move((row/2)+1, col/2);
                    printw("Layer name: %s", name_layer[i][j][k]);
                    check = 1;
                    break;
                }
                else{
                    continue;
                    
                }
            }
        }
    }
    if(check==0){
        getmaxyx(stdscr, row, col);
        move(row/2, col/2);
        //printw("Tu: %d %d %d", year, xmonth, xday);
        //move((row/2)+1, (col/2)+1);
        printw("Error ocurred! Such a layer name doesn't exist!");
    }
}

void Calendar::hide(){
    this->middle();
    string kname;
    kname = name;
    int check = 0;
    for(int i =0; i<100;i++)
    {
        for(int j=1; j<13;j++)
        {
            for(int k=1; k<32;k++)
            {
                if(kname == name_layer[i][j][k])
                {
                    check = 1;
                    position = pozycjay[i][j][k];
                    this->deleteScreen();
                    getmaxyx(stdscr, row, col);
                    move(row/2, col/2);
                    printw("Succesfully hidden!");
                    move((row/2)+1, col/2);
                    printw("Layer name: %s", name_layer[i][j][k]);
                    break;
                }
                else{
                    continue;
                    
                }
            }
        }
    }
    if(check==0){
        move(row/2, col/2);
        printw("Such a layer name doesn't exist!");
    }

}

void Calendar::deleteEvent(int year, int xmonth, int xday){
    this->middle();
    if((strlen(name_layer[year][xmonth][xday]) > 0) && (year >= 0) && (xmonth > 0) && (xday > 0) ){
        strcpy(name_layer[year][xmonth][xday], "");
        strcpy(layer[year][xmonth][xday], "");
        strcpy(hours[year][xmonth][xday], "");
        position = pozycjay[year][xmonth][xday];
        this->deleteScreen();
        year = 0;
        xmonth = 0;
        xday = 0;
        move(row/2, col/2);
        printw("Event has been deleted succesfully!");
    }
    else{
        move(row/2, col/2);
        printw("Event doesn't exist!");
    }
    
}

void Calendar::jump(){
    this->middle(); //date format: year-month-day
    move(y, x);
    string param;
    param = date;
    istringstream xx(param);
    string val;
    char tab[10][50];
    int j = 0;
    while(getline(xx, val, '-')){
        strcpy(tab[j], val.c_str());
        //move((row/2)+j, (col/2)+j);
        //printw("[%d] %s", j, tab[j]);
        j++;
    }
    int jumpYear2;
    jumpYear2 = std::stoi(tab[0]);
    int jumpYear;
    jumpYear = abs(2020-jumpYear2);
    int jumpMonth;
    jumpMonth = std::stoi(tab[1]);
    int jumpDay;
    jumpDay = std::stoi(tab[2]);
    if(applied[jumpYear][jumpMonth][jumpDay] == 1 && strlen(layer[jumpYear][jumpMonth][jumpDay]) > 0 && strlen(name_layer[jumpYear][jumpMonth][jumpDay]) > 0 && strlen(hours[jumpYear][jumpMonth][jumpDay]) > 0)
    {
        move(row/2,col/2);
        printw("Layer name: %s", name_layer[jumpYear][jumpMonth][jumpDay]);
        move((row/2)+1,col/2);
        printw("Date: %d-%d-%d", 2020 + jumpYear, jumpMonth, jumpDay);
        move((row/2)+2,col/2);
        printw("Hours: %s", hours[jumpYear][jumpMonth][jumpDay]);
        move((row/2)+3,col/2);
        printw("Details: %s", layer[jumpYear][jumpMonth][jumpDay]);
    }
    else
    {
        move(row/2,(col/2) - 20);
        printw("Schedule layer wasn't applied or such a date wasn't connected with any event!");
    }
    

}

void Calendar::clear(){
    for(int i=1; i<row - 1; i++){
        move(i, 0);
        clrtoeol();
    }
}

void Calendar::middle(){
    for(int i=row/2 - 4; i< row/2 + 6; i++){
        for(int j=col/2 - 10; j< col/2 + 4; j++)
        {
            move(i, j);
            clrtoeol();
        }
            
    }
}

void Calendar::deleteScreen(){
    for(int i=position; i< position + 4; i++){
        move(i, 0);
        clrtoeol();
    }
}


void Calendar::init(){
    backend->bind("#nano#<LARROW>%Move left",[&](){left();}, "Go left");
    backend->bind("#nano#<RARROW>%Move right",[&](){right();}, "Go right");
    backend->bind("#nano#<UARROW>%Move up",[&](){up();}, "Go up");
    backend->bind("#nano#<DARROW>%Move left",[&](){down();}, "Go down");
    backend->bind("#nano#<F2>%Add event!Type parameter:${PARAMETR}", [&](){addE();}, "Add event to the given schedule layer");
    backend->bind("#nano#<F4>%Apply schedule!Type layer name:${NAMEE}",[&](){apply(year, xmonth, xday);}, "Apply schedule by its name");
    backend->bind("#nano#<F6>%Delete event!", [&](){deleteEvent(year, xmonth, xday);}, "Delete currently highlighted event");
    backend->bind("#nano#<F7>%Jump to given date!Type date:${DATE}", [&](){jump();}, "Jump to given date");
    backend->bind("#nano#<F8>%Hide schedule!Type layer name:${NAMEE}",[&](){hide();}, "Hide schedule by its name");
}