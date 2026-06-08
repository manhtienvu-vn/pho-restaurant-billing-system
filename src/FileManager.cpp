#include "FileManager.h"
#include "Menu.h" 

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

    if (std::getline(file, line)) {
        // skip header
    }

    int loadedCount = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, priceStr;

        try {
            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, priceStr, ',')) {

                int id = std::stoi(idStr);
                float price = std::stof(priceStr);
                
                menu.addItemToMenu(id, name, price);
                loadedCount++;
            }
        } catch (const std::exception& e) {
            std::cerr << "[WARNING] Failed to parse line: " 
                      << line << " | Exception: " << e.what() << "\n";
        }
    }

    file.close();

    std::cout << "[SUCCESS] Loaded " << loadedCount 
              << " items from " << menuFile << "\n";
}

void FileManager::saveCheckout(float totalAmount, const std::string& paymentMethod) {
    std::ofstream file(orderFile, std::ios::app);
    
    try {
        if (!file.is_open()) {
            throw std::ios_base::failure("Cannot open checkout file for writing.");
        }

        file.seekp(0, std::ios::end);

        if (file.tellp() == 0) {
            file << "Total Price,Payment Method,Status\n";
        }

        file << totalAmount << "," 
             << paymentMethod << ","
             << "Completed\n";

        file.close();

        std::cout << "[SUCCESS] Checkout data saved to " 
                  << orderFile << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL ERROR] File I/O Exception during checkout: " 
                  << e.what() << "\n";
    }
}

void FileManager::showHistory() {
    std::ifstream file(orderFile);

    if (!file.is_open()) {
        std::cout << "[INFO] No order history file found.\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    std::cout << "\n======== ORDER HISTORY ========\n";

    int count = 1;
    bool hasHistory = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string totalStr, method, status;

        std::getline(ss, totalStr, ',');
        std::getline(ss, method, ',');
        std::getline(ss, status, ',');

        std::cout << "Order #" << count++ << "\n";
        std::cout << "Total Price   : " << totalStr << " VND\n";
        std::cout << "Payment Method: " << method << "\n";
        std::cout << "Status        : " << status << "\n\n";

        hasHistory = true;
    }

    if (!hasHistory) {
        std::cout << "[INFO] No order history found.\n";
    }
}

void FileManager::showRevenue() {
    std::ifstream file(orderFile);

    if (!file.is_open()) {
        std::cout << "[INFO] No order history file found.\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    float totalRevenue = 0.0f;
    int completedOrders = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string totalStr, method, status;

        try {
            std::getline(ss, totalStr, ',');
            std::getline(ss, method, ',');
            std::getline(ss, status, ',');

            if (status == "Completed") {
                totalRevenue += std::stof(totalStr);
                completedOrders++;
            }
        } catch (const std::exception& e) {
            std::cerr << "[WARNING] Failed to parse order line: " 
                      << line << " | Exception: " << e.what() << "\n";
        }
    }

    std::cout << "\n======== REVENUE REPORT ========\n";
    std::cout << "Completed Orders: " << completedOrders << "\n";
    std::cout << "Total Revenue   : " << totalRevenue << " VND\n";
}