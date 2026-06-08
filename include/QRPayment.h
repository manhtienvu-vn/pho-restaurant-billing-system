#ifndef QRPAYMENT_H
#define QRPAYMENT_H

#include "Payment.h"

class QRPayment : public Payment
{
    QRPayment();
    void processPayment(float amount) override ;
};
#endif