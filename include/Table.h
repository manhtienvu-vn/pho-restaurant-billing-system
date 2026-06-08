#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include <Order.h>
#include <MenuItem.h>

enum TableStatus {
    AVAILABLE = 0,
    OCCUPIED = 1
};

class Table {
    private:
        int table_id;
        TableStatus status;
        std::unique_ptr <Order> current_order;
    public:
        Table (int id);
        bool open();
        void close();
        bool isOpened();
        void addOrderItem(std::shared_ptr<MenuItem> item, int quantity);
        void printBill();
};

#endif