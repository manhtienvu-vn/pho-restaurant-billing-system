#include <Order.h>

Order::Order(){};

void Order::addItemToOrder(std::shared_ptr<MenuItem> item, int quantity)
{
    OrderItem order_item(item, quantity);
    items.push_back(order_item);
}

void Order::removeItemFromOrder(int id)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->getItemId() == id)
        {
            items.erase(it);
            std::cout << "[SUCCESS] Removed item with ID: " << id << " from the order.\n";
            return;
        }
    }
    std::cout << "[WARNING] Item with ID: " << id << " was not found in the order.\n";
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

