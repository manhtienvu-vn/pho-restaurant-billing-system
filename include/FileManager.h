#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>

class Menu;

class FileManager
{
private:
    std::string menuFile;
    std::string orderFile;

public:
    FileManager(const std::string& mFile, const std::string& oFile);

    void loadMenu(Menu& menu);

    void saveCheckout(float totalAmount, const std::string& paymentMethod);

    void showHistory();

    void showRevenue();
};

#endif