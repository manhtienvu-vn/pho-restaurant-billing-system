#include "Restaurant.h"
#include "UI.h"

int main(void)
{
    Restaurant restaurant(10);
    UI ui(restaurant);
    ui.run();
    return 0;
}