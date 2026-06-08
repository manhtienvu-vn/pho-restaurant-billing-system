#include <Table.h>

Table::Table (int id): table_id(id), status(AVAILABLE) {
    /* Initially, no memory is allocated for the table since it's not opened */
    current_order = nullptr;
}

bool Table::open()
{
    if (status == OCCUPIED){
        return false;
    }
    status = OCCUPIED;
    /* Only create order when the table is opened for service */
    /* Allocate memory for an exclusive-ownership 'Order' object for this 'Table' */
    current_order = std::make_unique <Order>();
    return true;
}

void Table::close()
{
    status = AVAILABLE;
    this->current_order.reset();
    /* Delete the allocated memory for the exclusive-ownership 'Order' object */
}

bool Table::isOpened()
{
    return status == OCCUPIED;
}

void Table::addOrderItem(std::shared_ptr<MenuItem> item, int quantity)
{
    if (status != OCCUPIED){
        /* Return early if the table is currently closed */
        return;
    }
    current_order->addItemToOrder(item, quantity);
}

void Table::printBill()
{
    float totalFees = current_order->calculateTotal();
    current_order->showBill();
    std::cout << "Total Fees: " << totalFees << "\n";
}
