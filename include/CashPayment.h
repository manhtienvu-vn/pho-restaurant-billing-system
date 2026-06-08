#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H

#include <Payment.h>

class CashPayment : public Payment 
{
    CashPayment();
    void processPayment(float amount) override;
};

#endif 