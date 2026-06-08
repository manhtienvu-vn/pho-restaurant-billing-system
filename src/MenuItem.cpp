#include <MenuItem.h>

MenuItem::MenuItem (int ID, std::string n, float pr): id(ID), name(n), price(pr){
    std::cout << "[SUCCESS] Created new menu item: Name: " << name << " | ID: " << id << " | Price: " << price << "\n";
}

float MenuItem::getPrice()
{
    return price;
}
std::string MenuItem::getName()
{
    return name;
}
int MenuItem::getId()
{
    return id;
}
void MenuItem::showItem()
{
    std::cout << "[INFO] ID: " << id << " | Name: " << name << " | Price: " << price << "\n";
}
