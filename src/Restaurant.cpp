#include <Restaurant.h>
Restaurant::Restaurant(int n){

    /* Initially, create a vector of 'num_of_table' tables for the restaurant*/
    num_of_table = n;
    for (int i = 1; i <= n; i++)
    {
        /* Create a new table with id 'i' */
        Table new_table (i);
        /* Use std::move() because there exists unique pointer in each Table object */
        tables.push_back(std::move(new_table));
        /* Then we wish to transfer ownership of these objects to the vector elements */
    }
    std::cout << "[SUCCESS] Created a restaurant with " << num_of_table << " tables with ID from 1 to " << num_of_table << "\n";

    /* Create a list of menu item */
    menu.addItemToMenu(1, "Pho Bo", 30000);
    menu.addItemToMenu(2, "Pho Ga", 30000);
    menu.addItemToMenu(3, "Pho Bo Ga", 35000);
}

bool Restaurant::openTable(int table_id)
{
    if(tables[table_id-1].open()){
        return true;
    }
    return false;
}

void Restaurant::addOrder(int table_id, int item_id, int quantity)
{
    if (table_id < 0 || table_id > this->num_of_table){
        std::cout << "[ERROR]: Invalid Table ID. Try again!" << "\n";
        return;
    } else if (!tables[table_id-1].isOpened()){
        std::cout << "[ERROR] Table with ID: " << table_id << " is currently closed!" << "\n";
        return;
    } else if (quantity <= 0)
    {
        std::cout << "[ERROR] Invalid quantity. Try again!" << "\n";
        return;
    }
    std::shared_ptr<MenuItem> item = menu.findItemInMenu(item_id);
    tables[table_id-1].addOrderItem(item, quantity);
    std::cout << "[SUCCESS] Ordered " << quantity << " " << item->getName() << " for Table with ID: " << table_id << "\n";
}

void Restaurant::checkOut(int table_id)
{
    if(!tables[table_id-1].isOpened())
    {
        return;
    }
    tables[table_id-1].printBill();
    tables[table_id-1].close();
}

void Restaurant::showMenu()
{
    this->menu.showMenu();
}

void Restaurant::showRevenue()
{

}

int Restaurant::getNumberOfTable()
{
    return this->num_of_table;
}