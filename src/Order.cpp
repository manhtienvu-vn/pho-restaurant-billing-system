#include <Order.h>

Order::Order(){};

void Order::addItemToOrder(std::shared_ptr<MenuItem> item, int quantity)
{
    OrderItem order_item(item, quantity);
    items.push_back(order_item);
}

void Order::removeItemFromOrder(int id)
{

}

float Order::calculateTotal()
{
    float total = 0.0f;
    for (auto &i: items){
        total += static_cast<float>(i.calculateTotal());
    }
    return total;
}

void Order::showBill(){
    for (auto &v: items){
            std::cout << "Item Name: " << v.getName() << " | Quantity: " << v.getQuantity() << "\n"; 
    }
}

