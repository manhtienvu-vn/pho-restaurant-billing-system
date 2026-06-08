#ifndef MENUITEM_H
#define MENUITEM_H

#include <iostream>
#include <string>

class MenuItem {
    private:
        int id;
        std::string name;
        float price;

    public:
        MenuItem (int ID, std::string n, float pr);
        float getPrice();
        std::string getName();
        int getId();
        void showItem();
};

#endif