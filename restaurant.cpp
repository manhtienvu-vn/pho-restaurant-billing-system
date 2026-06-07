#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>

enum TableStatus {
    AVAILABLE = 0,
    RESERVED
};

class MenuItem {
    private:
        int id;
        std::string name;
        float price;
    public:
        MenuItem (int ID, std::string n, float pr): id(ID), name(n), price(pr){};
        void showItem()
        {
            std::cout << "Name: " << name << " | Price: " << price << "\n";
        }
};

class Menu {
    private:
        std::map<int, std::shared_ptr<MenuItem>> items;
    public:
        Menu(){};
        void addItem(int id, std::string name, float price)
        {
            std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>(id, name, price);
            items.insert({id, item});
        }
        std::shared_ptr<MenuItem> findItem(int id)
        {
            auto it = items.at(id);
            return it;
        }
        void showMenu()
        {
            int count = 1;
            for (const auto &pair : items){
                std::cout << "1. Item ID: " << pair.first << " | ";
                pair.second->showItem();
            }
        }
};

class OrderItem {
    private:
        std::shared_ptr<MenuItem> item = std::make_unique<MenuItem>();
        int quantity;
    public:
        OrderItem(int id){};
        int getQuantity()
        {
            return quantity;
        }
        void setQuantity(int q)
        {
            quantity = q;
        }
        float calculateTotal()
        {
            return static_cast<float>(quantity * p->price);
        }
};

class Order {
    private:
        int order_id;
        std::vector <OrderItem> items;
        std::string created_time;
};

class Table {
    private:
        int table_id;
        TableStatus status;
        std::unique_ptr <Order> current_order = std::make_unique <Order>();
    public:
        Table (int id): table_id(id), status(AVAILABLE) {};
        void open()
        {
            status = AVAILABLE;
        }
        void close()
        {
            status = RESERVED;
        }
        bool isAvailable()
        {
            return status == AVAILABLE;
        }

};

class Restaurant 
{
    private:
        std::vector <Table> tables[10];    
        Menu menu;
        std::vector <Order> orders;
    public:
        void openTable(int table_id)
        {
            tables[table_id].open();
        }

};