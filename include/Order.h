#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <memory>
#include <OrderItem.h>
#include <MenuItem.h>

class Order {
    private:
        int order_id;
        std::vector <OrderItem> items;
        std::string created_time;

    public:
        Order();
        void addItemToOrder(std::shared_ptr<MenuItem> item, int quantity);
        void removeItemFromOrder(int id);
        float calculateTotal();
        void showBill();
};

#endif