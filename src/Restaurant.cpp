#include "Restaurant.hpp"

// ================= OrderItem =================
OrderItem::OrderItem(std::shared_ptr<MenuItem> item, int quantity) 
    : item(item), quantity(quantity) {}

int OrderItem::getQuantity() const { return quantity; }
void OrderItem::setQuantity(int q) { quantity = q; }
std::string OrderItem::getName() const { return item->getName(); }
float OrderItem::calculateTotal() const { return quantity * item->getPrice(); }

// ================= Order =================
Order::Order() {}

void Order::addItem(std::shared_ptr<MenuItem> item, int quantity) {
    items.push_back(OrderItem(item, quantity));
}

float Order::calculateTotal() const {
    float total = 0.0f;
    for (const auto& i : items) {
        total += i.calculateTotal();
    }
    return total;
}

void Order::printBill() const {
    for (const auto& v : items) {
        std::cout << "Item: " << v.getName() << " | Quantity: " << v.getQuantity() 
                  << " | Subtotal: " << v.calculateTotal() << "\n"; 
    }
    std::cout << "Total Price: " << calculateTotal() << "\n";
}

// ================= Table =================
Table::Table(int id) : table_id(id), status(AVAILABLE) {
    current_order = nullptr;
}

void Table::open() {
    status = OCCUPIED;
    current_order = std::make_unique<Order>();
}

void Table::close() {
    status = AVAILABLE;
    current_order.reset();
}

bool Table::isAvailable() const {
    return status == AVAILABLE;
}

void Table::addOrderItem(std::shared_ptr<MenuItem> item, int quantity) {
    if (current_order) {
        current_order->addItem(item, quantity);
    }
}

float Table::getTotal() const {
    return current_order ? current_order->calculateTotal() : 0.0f;
}

void Table::printBill() const {
    if (current_order) {
        current_order->printBill();
    }
}

// ================= Restaurant =================
Restaurant::Restaurant(int n) : num_of_table(n) {
    // Initialize tables
    for (int i = 1; i <= n; i++) {
        tables.push_back(Table(i));
    }
    
    // Automatically load the menu from menu.csv upon booting the restaurant
    fileManager.loadMenu(menu);
    std::cout << "[SUCCESS] Restaurant initialized with " << num_of_table << " tables.\n";
}

void Restaurant::showMenu() {
    menu.showMenu();
}

void Restaurant::openTable(int table_id) {
    if (table_id < 1 || table_id > num_of_table) return;
    
    tables[table_id - 1].open();
    std::cout << "[SUCCESS] Table " << table_id << " is now opened for service.\n";
}

void Restaurant::addOrder(int table_id, int item_id, int quantity) {
    if (table_id < 1 || table_id > num_of_table || tables[table_id - 1].isAvailable()) {
        std::cout << "[ERROR] Table " << table_id << " is closed or invalid.\n";
        return;
    }

    try {
        std::shared_ptr<MenuItem> item = menu.findItemInMenu(item_id);
        tables[table_id - 1].addOrderItem(item, quantity);
        std::cout << "[SUCCESS] Added " << quantity << "x '" << item->getName() 
                  << "' to Table " << table_id << ".\n";
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Item ID " << item_id << " not found in menu.\n";
    }
}

void Restaurant::checkOut(int table_id, const std::shared_ptr<Payment>& payment) {
    if (table_id < 1 || table_id > num_of_table || tables[table_id - 1].isAvailable()) {
        std::cout << "[ERROR] Cannot checkout. Table " << table_id << " is already closed.\n";
        return;
    }

    float totalAmount = tables[table_id - 1].getTotal();
    
    std::cout << "\n--- BILL FOR TABLE " << table_id << " ---\n";
    tables[table_id - 1].printBill();
    std::cout << "-----------------------\n";

    // Write to checkout.csv via FileManager
    fileManager.saveCheckout(totalAmount, payment);

    // Free memory and reset status
    tables[table_id - 1].close();
    std::cout << "[SUCCESS] Table " << table_id << " checked out and closed.\n";
}
