#pragma once
#include <string>
#include <memory>

// Forward declarations to avoid circular dependencies
class Menu; 
class Payment;

class FileManager {
private:
    std::string menuFile;
    std::string orderFile;

public:
    FileManager(const std::string& mFile = "menu.csv", const std::string& oFile = "checkout.csv");

    // Populates the existing Menu object
    void loadMenu(Menu& menu);

    // Saves the completed checkout details
    void saveCheckout(float totalAmount, const std::shared_ptr<Payment>& payment);
};
