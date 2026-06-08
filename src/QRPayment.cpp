#include "QRPayment.h"
#include <iostream>

void QRPayment::processPayment(float amount)
{
    std::cout << "======== QR PAYMENT ========\n";
    std::cout << "Amount : " << amount << " VND\n";
    std::cout << "[QR CODE HERE:]\n";
    std::cout << "Payment completed!\n";
}