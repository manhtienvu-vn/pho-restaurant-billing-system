#include "CashPayment.h"
#include <iostream>

CashPayment::CashPayment(){
    std::cout << "[INFO] Cash Payment selected!" << "\n";
}

void CashPayment::processPayment(float amount)
{
    std::cout << "======== CASH PAYMENT ========\n";
    std::cout << "Amount: " << amount << "\n";
    std::cout << "Payment completed! \n";
}