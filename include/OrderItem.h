#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <memory>
#include <MenuItem.h>

class OrderItem {
    private:
        std::shared_ptr<MenuItem> item;
        int quantity;

    public:
        OrderItem(std::shared_ptr<MenuItem> item, int quantity);
        int getQuantity();
        void setQuantity(int quantity);
        std::string getName();
        int getItemId();
        float calculateTotal();
};

#endif