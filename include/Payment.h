#ifndef PAYMENT_H
#define PAYMENT_H

class Payment
{
    public:
        virtual void processPayment(float amount) = 0;
        virtual ~Payment() = default;
};

#endif
