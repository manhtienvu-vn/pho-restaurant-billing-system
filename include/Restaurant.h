#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>


#include "Menu.h"
#include "FileManager.hpp"
#include "Payment.hpp"

enum TableStatus {
    AVAILABLE = 0,
    OCCUPIED = 1
};

class OrderItem {
private:
    std::shared_ptr<MenuItem> item;
    int quantity;
public:
    OrderItem(std::shared_ptr<MenuItem> item, int quantity);
    int getQuantity() const;
    void setQuantity(int q);
    std::string getName() const;
    float calculateTotal() const;
};

class Order {
private:
    int order_id;
    std::vector<OrderItem> items;
    std::string created_time;
public:
    Order();
    void addItem(std::shared_ptr<MenuItem> item, int quantity);
    float calculateTotal() const;
    void printBill() const;
};

class Table {
private:
    int table_id;
    TableStatus status;
    std::unique_ptr<Order> current_order;
public:
    Table(int id);
    void open();
    void close();
    bool isAvailable() const;
    void addOrderItem(std::shared_ptr<MenuItem> item, int quantity);
    float getTotal() const;
    void printBill() const;
};

class Restaurant {
private:
    std::vector<Table> tables;
    Menu menu;
    FileManager fileManager;
    int num_of_table;
public:
    Restaurant(int n);
    void openTable(int table_id);
    void addOrder(int table_id, int item_id, int quantity);
    void checkOut(int table_id, const std::shared_ptr<Payment>& payment);
    void showMenu();
};
