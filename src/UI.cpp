#include "UI.h"
#include <iostream>
#include "Payment.h"
#include "CashPayment.h"
#include "QRPayment.h"
#include "FileManager.h"

UI::UI(Restaurant& restaurant) : restaurant(restaurant){}

int UI::getUserInput(int from, int to)
{
    int selection;
    std::cout << "[USER] Type in your selection from 1 to 4: ";
    std::cin >> selection;
    while (selection < from || selection > to)
    {
        std::cout << "[ERROR] Invalid selection. Try again!\n";
        std::cout << "[USER] Type in your selection from 1 to 4: ";
        std::cin >> selection;
    }
    return selection;
}

void UI::showMainPage()
{   
    std::cout << "\n";
    std::cout << "======== WELCOME TO PHO ANH HAI RESTAURANT ========\n";
    std::cout << "***************************************************\n";
    std::cout << "[0] Exit\n";
    std::cout << "[1] Open Table\n";
    std::cout << "[2] Add Order\n";
    std::cout << "[3] Payment & Checkout\n";
    std::cout << "[4] View History\n";
}
int UI::getTableID()
{
    int table_id;
    std::cout << "[USER] Type in the table ID to order: ";
    std::cin >> table_id;

    while (table_id < 0 || table_id > restaurant.getNumberOfTable()){
        std::cout << "[ERROR] Invalid table ID input. Try again!\n";
        std::cout << "[USER] Type in the table ID to order: ";
        std::cin >> table_id;
    }
    return table_id;
}

int UI::getItemID(){
    int item_id;
    std::cout << "[USER] Type in the item ID to order: ";
    std::cin >> item_id;
    return item_id;
}

int UI::getItemQuantity()
{
    int quantity;
    std::cout << "[USER] Type in quantity to order: ";
    std::cin >> quantity;
    while (quantity <= 0){
        std::cout << "[ERROR] Invalid quantity input. Try again!\n";
        std::cout << "[USER] Type in quantity to order: ";
        std::cin >> quantity;
    }
    return quantity;
}

void UI::showOrderPage()
{
    std::cout << "\n";
    std::cout << "======== ORDER PAGE ========\n";
    restaurant.showMenu();
}

int UI::showOpenTablePage()
{
    std::cout << "\n";
    std::cout << "======== TABLE MANAGEMENT PAGE ========\n";
    std::cout << "[USER] Type in the Table ID to OPEN for service: ";
    int selection;
    std::cin >> selection;
    return selection;
}

void UI::showPaymentPage(){
    std::cout << "\n";
    std::cout << "======== PAYMENT & CHECKOUT PAGE ========\n";
    std::cout << "[USER] Type in the Table ID to CHECKOUT: ";
    int table_id;
    std::cin >> table_id;

    while (table_id < 0 || table_id > restaurant.getNumberOfTable()){
        std::cout << "[ERROR] Invalid table ID input. Try again!\n";
        std::cout << "[USER] Type in the Table ID to CHECKOUT: ";
        std::cin >> table_id;
    }
    std::cout << "======== SELECT PAYMENT METHOD ========\n";
    std::cout << "***************************************************\n";
    std::cout << "[1] Cash\n";
    std::cout << "[2] QR Code\n";

    int selection = UI::getUserInput(1, 2);
    Payment *payment = nullptr;

    std::string paymentMethod;

    switch(selection){
        case 1:
        {
            payment = new CashPayment();
            paymentMethod = "Cash";

            float total_fees = restaurant.getTotalFees(table_id);
            payment->processPayment(total_fees);

            FileManager fileManager("data/menu.csv", "data/orders.csv");
            fileManager.saveCheckout(total_fees, paymentMethod);

            break;
        }
        case 2:
        {
            payment = new QRPayment();
            paymentMethod = "QR Code";

            float total_fees = restaurant.getTotalFees(table_id);
            payment->processPayment(total_fees);

            FileManager fileManager("data/menu.csv", "data/orders.csv");
            fileManager.saveCheckout(total_fees, paymentMethod);

            break;
        }
    }

    delete payment;
    payment = nullptr;

    restaurant.checkOut(table_id);
    std::cout << "[SUCCESS] Successfully checked out for table with ID: " << table_id << "\n";
    std::cout << "[INFO] Table with ID: " << table_id << " is closed!\n";
}

void UI::showHistoryPage()
{
    std::cout << "\n";
    std::cout << "======== ORDER HISTORY ========\n";
    std::cout << "[1] Show Checkout History\n";
    std::cout << "[2] Show Total Revenue\n";

    int selection = UI::getUserInput(1, 2);

    switch(selection){
        case 1:
        {
            restaurant.showHistory();
            break;
        }
        case 2:
        {
            restaurant.showRevenue();
            break;
        }
    }
}
void UI::run()
{
    bool state = true;

    while (state){
        int selection;
        UI::showMainPage();
        selection = UI::getUserInput(1, 4);

        switch (selection){
            case 0:
            {
                state = false;
                break;
            }
            case 1:
            {
                int table_id = UI::showOpenTablePage();
                if (restaurant.openTable(table_id)){
                    std::cout << "[SUCCESS] Table with ID: "  << table_id << " is now opened for service!" << "\n";
                } else {
                    std::cout << "[WARNING] Table with ID: " << table_id << " is already opened!\n";
                }
                break;
            }
            case 2:
            {
                UI::showOrderPage();
                int table_id = UI::getTableID();
                int item_id = UI::getItemID();
                int item_quantity = UI::getItemQuantity();
                restaurant.addOrder(table_id, item_id, item_quantity);
                break;
            }
            case 3:
            {    
                UI::showPaymentPage();
                break;
            }
            case 4:
            { 
                FileManager fileManager("data/menu.csv", "data/orders.csv");
                fileManager.showHistory();
                fileManager.showRevenue();
                break;
            }
        }
    }
}
