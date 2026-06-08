#include <Menu.h>

Menu::Menu(){};

void Menu::addItemToMenu(int id, std::string name, float price)
{
    std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>(id, name, price);
    items.insert({id, item});
}

std::shared_ptr<MenuItem> Menu::findItemInMenu(int id)
{
    auto it = items.at(id);
    return it;
}

void Menu::showMenu()
{
    int count = 1;
    std::cout << "--------RESTAURANT MENU--------" << "\n";
    for (const auto &pair : items){
        std::cout << "1. Item ID: " << pair.first << " | ";
        pair.second->showItem();
    }
}
