#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <Table.h>
#include <Order.h>
#include <Menu.h>

class Restaurant 
{
    /* Note: One restaurant should have multiple 'tables' with corresponding orders but only 01 'menu' */
    private:
        std::vector <Table> tables;    
        Menu menu;
        int num_of_table;
    public:
        Restaurant(int n);
        bool openTable(int table_id);
        void addOrder(int table_id, int item_id, int quantity);
        float getTotalFees(int table_id);
        void checkOut(int table_id);
        void showMenu();
        void showHistory();
        void showRevenue();
        int getNumberOfTable();
};

#endif