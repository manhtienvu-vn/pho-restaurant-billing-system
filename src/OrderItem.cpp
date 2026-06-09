#include <OrderItem.h>

OrderItem::OrderItem(std::shared_ptr<MenuItem> item, int quantity){
    this->item = item;
    this->quantity = quantity;
}

int OrderItem::getQuantity()
{
    return this->quantity;
}

void OrderItem::setQuantity(int quantity)
{
    this->quantity = quantity;
}

std::string OrderItem::getName()
{
    return item->getName();
}

int OrderItem::getItemId()
{
    return item->getId();
}

float OrderItem::calculateTotal()
{
    return static_cast<float>(quantity * item->getPrice());
}
