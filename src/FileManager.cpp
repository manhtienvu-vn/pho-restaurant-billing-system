#include "FileManager.hpp"
#include "Payment.hpp"

// Include the Menu header
// #include "Menu.hpp" 

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

FileManager::FileManager(const std::string& mFile, const std::string& oFile) 
    : menuFile(mFile), orderFile(oFile) {}

void FileManager::loadMenu(Menu& menu) {
    std::ifstream file(menuFile);
    
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open " << menuFile << ". File missing or unreadable.\n";
        return; 
    }

    std::string line;
    // Skip the header row (id,name,price)
    if (std::getline(file, line)) {
        // Header skipped successfully
    }

    int loadedCount = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, priceStr;

        try {
            // Read comma-separated values
            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, priceStr, ',')) {

                int id = std::stoi(idStr);
                float price = std::stof(priceStr);
                
                menu.addItemToMenu(id, name, price);
                loadedCount++;
            }
        } catch (const std::exception& e) {
            std::cerr << "[WARNING] Failed to parse line: " << line << " | Exception: " << e.what() << "\n";
        }
    }
    file.close();
    std::cout << "[SUCCESS] Loaded " << loadedCount << " items from " << menuFile << "\n";
}

void FileManager::saveCheckout(float totalAmount, const std::shared_ptr<Payment>& payment) {
    // Open in append mode so previous checkouts aren't overwritten
    std::ofstream file(orderFile, std::ios::app);
    
    try {
        if (!file.is_open()) {
            throw std::ios_base::failure("Cannot open checkout file for writing.");
        }

        // Write header if the file is completely new/empty
        file.seekp(0, std::ios::end);
        if (file.tellp() == 0) {
            file << "Total Price,Payment Method,Status\n";
        }

        // Log the checkout record
        file << totalAmount << "," << payment->getPaymentMethodName() << ",";
        
        if (payment->process()) {
            file << "Completed\n";
        } else {
            file << "Failed\n";
        }

        file.close();
        std::cout << "[SUCCESS] Checkout data securely saved to " << orderFile << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL ERROR] File I/O Exception during checkout: " << e.what() << "\n";
    }
}
