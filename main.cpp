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
        void addItem(std::shared_ptr<MenuItem> item, int quantity)
        {
            OrderItem order_item(item, quantity);
            items.push_back(order_item);
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
        std::unique_ptr <Order> current_order;
    public:
        Table (int id): table_id(id), status(AVAILABLE) {};
        void open()
        {
            status = OCCUPIED;
            current_order = std::make_unique <Order>();
        }
        void close()
        {
            status = AVAILABLE;
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
        int num_of_table;
    public:
        Restaurant(int n){
            num_of_table = n;
            for (int i = 1; i <= n; i++)
            {
                Table new_table (i);
                tables.push_back(std::move(new_table));
            }
            std::cout << "[SUCCESS] Created a restaurant with " << num_of_table << " tables" << "\n";
        }

        void openTable(int table_id)
        {
            tables[table_id-1].open();
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

int main(void)
{
    Restaurant restaurant(10);
    restaurant.openTable(1);
    return 0;
}