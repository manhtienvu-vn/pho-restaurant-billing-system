#include "CashPayment.h"
#include <iostream>

CashPayment::CashPayment(){
    std::cout << "[INFO] Cash Payment selected!" << "\n";
}

void CashPayment::processPayment(float amount)
{
    std::cout << "======== CASH PAYMENT ========\n";
    std::cout << "[INFO] Amount: " << amount << "\n";
    std::cout << "[SUCCESS] Payment completed! \n";
}