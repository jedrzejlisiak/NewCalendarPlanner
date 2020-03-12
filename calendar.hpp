#ifndef CALENDAR_HPP
#define CALENDAR_HPP
#include "shared.hpp"

using namespace std;

class Calendar : public Tool{
public:
    void setEntry(string field, string value);
    string getEntry(string field);
    void init();
    void redraw();
    Backend* backend;
    Calendar();
    void right();
    void left();
    void up();
    void down();
    void apply(int year, int xmonth, int xday);
    void hide();
    void deleteEvent(int year, int xmonth, int xday);
    void deleteScreen();
    void jump();
    void addE();
    void clear();
    void middle();
private:
    int year, xmonth, xday, position;
    char sname[50];
    char layer[100][13][32][50];
    char name_layer[100][13][32][50];
    char hours[100][13][32][50];
    int applied[100][13][32];
    int pozycjay[100][13][32];
    int x, y, num, row, col;
    char smonth[50], syear[50], sday[50], temp[50],detail[50];
    string key, parametr, name, date, is_saved;
};

#endif