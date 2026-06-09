#include "UI.h"
#include <iostream>
#include <limits>
#include "Payment.h"
#include "CashPayment.h"
#include "QRPayment.h"
#include "FileManager.h"

UI::UI(Restaurant& restaurant) : restaurant(restaurant){}

int UI::getUserInput(int from, int to)
{
    int selection;
    std::cout << "[USER] Type in your selection from " << from << " to " << to << ": ";
    while (!(std::cin >> selection) || selection < from || selection > to)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid selection. Try again!\n";
        std::cout << "[USER] Type in your selection from " << from << " to " << to << ": ";
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
    while (!(std::cin >> table_id) || table_id < 1 || table_id > restaurant.getNumberOfTable()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid table ID input. Try again!\n";
        std::cout << "[USER] Type in the table ID to order: ";
    }
    return table_id;
}

int UI::getItemID(){
    int item_id;
    std::cout << "[USER] Type in the item ID to order: ";
    while (!(std::cin >> item_id)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid item ID input. Try again!\n";
        std::cout << "[USER] Type in the item ID to order: ";
    }
    return item_id;
}

int UI::getItemQuantity()
{
    int quantity;
    std::cout << "[USER] Type in quantity to order: ";
    while (!(std::cin >> quantity) || quantity <= 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid quantity input. Try again!\n";
        std::cout << "[USER] Type in quantity to order: ";
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
    while (!(std::cin >> selection) || selection < 1 || selection > restaurant.getNumberOfTable()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid Table ID. Valid range is 1 to " << restaurant.getNumberOfTable() << ". Try again!\n";
        std::cout << "[USER] Type in the Table ID to OPEN for service: ";
    }
    return selection;
}

void UI::showPaymentPage(){
    std::cout << "\n";
    std::cout << "======== PAYMENT & CHECKOUT PAGE ========\n";
    std::cout << "[USER] Type in the Table ID to CHECKOUT: ";
    int table_id;
    while (!(std::cin >> table_id) || table_id < 1 || table_id > restaurant.getNumberOfTable()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid table ID input. Try again!\n";
        std::cout << "[USER] Type in the Table ID to CHECKOUT: ";
    }

    float total_fees = restaurant.getTotalFees(table_id);
    if (total_fees <= 0.0f) {
        std::cout << "[WARNING] Table " << table_id << " has no open order or zero total. Payment skipped.\n";
        return;
    }

    std::cout << "======== SELECT PAYMENT METHOD ========\n";
    std::cout << "***************************************************\n";
    std::cout << "[1] Cash\n";
    std::cout << "[2] QR Code\n";

    int selection = UI::getUserInput(1, 2);
    Payment *payment = nullptr;

    std::string paymentMethod;

    try {
        switch(selection){
            case 1:
            {
                payment = new CashPayment();
                paymentMethod = "Cash";

                payment->processPayment(total_fees);

                FileManager fileManager("data/menu.csv", "data/orders.csv");
                fileManager.saveCheckout(total_fees, paymentMethod);

                break;
            }
            case 2:
            {
                payment = new QRPayment();
                paymentMethod = "QR Code";

                payment->processPayment(total_fees);

                FileManager fileManager("data/menu.csv", "data/orders.csv");
                fileManager.saveCheckout(total_fees, paymentMethod);

                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Payment failed: " << e.what() << "\n";
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
        selection = UI::getUserInput(0, 4);

        switch (selection){
            case 0:
            {
                state = false;
                std::cout << "[INFO] Exiting Pho Anh Hai Restaurant System. Goodbye!\n";
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
                UI::showHistoryPage();
                break;
            }
        }
    }
}
