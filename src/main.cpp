#include "Restaurant.h"

int main(void)
{
    Restaurant restaurant(10);
    restaurant.openTable(1);
    restaurant.addOrder(1, 1, 2);
    return 0;
}