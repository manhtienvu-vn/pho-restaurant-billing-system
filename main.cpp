#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>

enum TableStatus {
    AVAILABLE = 0,
    OCCUPIED = 1
};

class MenuItem {
    private:
        int id;
        std::string name;
        float price;
    public:
        MenuItem (int ID, std::string n, float pr): id(ID), name(n), price(pr){
            std::cout << "[SUCCESS] Created new menu item: Name: " << name << " | ID: " << id << " | Price: " << price << "\n";
        };
        float getPrice()
        {
            return price;
        }
        std::string getName()
        {
            return name;
        }
        int getId()
        {
            return id;
        }
        void showItem()
        {
            std::cout << "[INFO] ID: " << id << " | Name: " << name << " | Price: " << price << "\n";
        }

};

class Menu {
    private:
        std::map<int, std::shared_ptr<MenuItem>> items;
    public:
        Menu(){};

        void addItemToMenu(int id, std::string name, float price)
        {
            std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>(id, name, price);
            items.insert({id, item});
        }

        std::shared_ptr<MenuItem> findItemInMenu(int id)
        {
            auto it = items.at(id);
            return it;
        }

        void showMenu()
        {
            int count = 1;
            std::cout << "--------RESTAURANT MENU--------" << "\n";
            for (const auto &pair : items){
                std::cout << "1. Item ID: " << pair.first << " | ";
                pair.second->showItem();
            }
        }
};

class OrderItem {
    private:
        std::shared_ptr<MenuItem> item;
        int quantity;

    public:
        OrderItem(std::shared_ptr<MenuItem> item, int quantity){
            this->item = item;
            this->quantity = quantity;
        }

        int getQuantity()
        {
            return this->quantity;
        }

        void setQuantity(int quantity)
        {
            this->quantity = quantity;
        }

        std::string getName()
        {
            return item->getName();
        }

        float calculateTotal()
        {
            return static_cast<float>(quantity * item->getPrice());
        }
};

class Order {
    private:
        int order_id;
        std::vector <OrderItem> items;
        std::string created_time;

    public:
        Order(){};

        void addItemToOrder(std::shared_ptr<MenuItem> item, int quantity)
        {
            OrderItem order_item(item, quantity);
            items.push_back(order_item);
        }

        void removeItemFromOrder(int id)
        {

        }

        float calculateTotal()
        {
            float total = 0.0f;
            for (auto &i: items){
                total += static_cast<float>(i.calculateTotal());
            }
            return total;
        }

        void showBill(){
            for (auto &v: items){
                    std::cout << "Item Name: " << v.getName() << " | Quantity: " << v.getQuantity() << "\n"; 
            }
        }
};


class Table {
    private:
        int table_id;
        TableStatus status;
        std::unique_ptr <Order> current_order;
    public:
        Table (int id): table_id(id), status(AVAILABLE) {
            /* Initially, no memory is allocated for the table since it's not opened */
            current_order = nullptr;
        }
        
        void open()
        {
            status = OCCUPIED;
            /* Only create order when the table is opened for service */
            /* Allocate memory for an exclusive-ownership 'Order' object for this 'Table' */
            current_order = std::make_unique <Order>();
        }

        void close()
        {
            status = AVAILABLE;
            this->current_order.reset();
            /* Delete the allocated memory for the exclusive-ownership 'Order' object */
        }

        bool isOpened()
        {
            return status == OCCUPIED;
        }

        void addOrderItem(std::shared_ptr<MenuItem> item, int quantity)
        {
            if (status != OCCUPIED){
                /* Return early if the table is currently closed */
                return;
            }
            current_order->addItemToOrder(item, quantity);
        }

        void printBill()
        {
            float totalFees = current_order->calculateTotal();
            current_order->showBill();
            std::cout << "Total Fees: " << totalFees << "\n";
        }
};

class Restaurant 
{
    /* Note: One restaurant should have multiple 'tables' with corresponding orders but only 01 'menu' */
    private:
        std::vector <Table> tables;    
        Menu menu;
        std::vector <Order> orders;
        int num_of_table;
    public:
        Restaurant(int n){

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
            std::cout << "[SUCCESS] Created a restaurant with " << num_of_table << " tables" << "\n";

            /* Create a list of menu item */
            menu.addItemToMenu(1, "Pho Bo", 30000);
            menu.addItemToMenu(2, "Pho Ga", 30000);
            menu.addItemToMenu(3, "Pho Bo Ga", 35000);
        }

        void openTable(int table_id)
        {
            tables[table_id-1].open();
            std::cout << "[SUCCESS] Table with ID: "  << table_id << " is now opened for service!" << "\n";
        }

        void addOrder(int table_id, int item_id, int quantity)
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

        void checkOut(int table_id)
        {
            if(!tables[table_id-1].isOpened())
            {
                return;
            }
            tables[table_id-1].printBill();
            tables[table_id-1].close();
        }

        void showRevenue()
        {

        }
};

int main(void)
{
    Restaurant restaurant(10);
    restaurant.openTable(1);
    restaurant.addOrder(1, 1, 2);
    return 0;
}