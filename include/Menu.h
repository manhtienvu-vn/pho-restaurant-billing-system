#ifndef MENU_H
#define MENU_H

#include <map>
#include <memory>
#include <iostream>
#include <MenuItem.h>

class Menu {
    private:
        std::map<int, std::shared_ptr<MenuItem>> items;

    public:
        Menu();
        void addItemToMenu(int id, std::string name, float price);
        std::shared_ptr<MenuItem> findItemInMenu(int id);
        void showMenu();
};

#endif