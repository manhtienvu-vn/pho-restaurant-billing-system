#ifndef UI_H
#define UI_H

#include <Restaurant.h>

class UI
{
    private:
        Restaurant& restaurant;

    public:
        UI(Restaurant& restaurant);
        void run();
        int getUserInput(int from, int to);
        void showMainPage();
        int showOpenTablePage();
        int getTableID();
        int getItemID();
        int getItemQuantity();
        void showOrderPage();
        void showPaymentPage();
        void showHistoryPage();
};

#endif 