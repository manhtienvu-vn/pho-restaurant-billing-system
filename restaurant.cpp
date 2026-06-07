#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>

enum TableStatus {
    AVAILABLE = 0,
    OCCUPIED
};

class MenuItem {
    private:
        int id;
        std::string name;
        float price;
    public:
        MenuItem (int ID, std::string n, float pr): id(ID), name(n), price(pr){};
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
        std::shared_ptr<MenuItem> item;
        int quantity;
    public:
        OrderItem(int id, int quantity){
            item = std::make_shared<MenuItem>(id, quantity);
        };
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
        void addItem(int id, int quantity)
        {
            std::unique_ptr<OrderItem> new_order = std::make_unique <OrderItem>(id, quantity);
        }
        void removeItem(int id)
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
        void printBill()
        {
            float totalPrice = calculateTotal();
            for (auto &v: items){
                std::cout << "Item Name: " << v.getName() << " | Quantity: " << v.getQuantity() << "\n"; 
            }
            std::cout << "Total Price: " << totalPrice << "\n";
        }
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
            status = OCCUPIED;
        }
        bool isAvailable()
        {
            return status == AVAILABLE;
        }

};

class Restaurant 
{
    private:
        std::vector <Table> tables;    
        Menu menu;
        std::vector <Order> orders;
    public:
        Restaurant(){};
        void openTable(int table_id)
        {
            Table table(table_id);
            tables.push_back(table);
            tables[table_id].open();
            std::cout << "[SUCCESS] Add new table with ID: "  << table_id <<  "\n";
        }
        void addOrder(int table_id)
        {
            
        }
        void checkOut(int table_id)
        {

        }
        void showRevenue()
        {

        }
};