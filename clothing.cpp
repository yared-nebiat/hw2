#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
    const std::string brand, const std::string size) : 
        Product(category, name, price, qty),
        brand_(brand),
        size_(size)
        {

        }

std::set<std::string> Clothing::keywords() const {

    std::set<std::string> keyWords;
    std::set<std::string> temp;

    keyWords = parseStringToWords(name_);
    temp = parseStringToWords(brand_);
    keyWords.insert(temp.begin(), temp.end());

    return keyWords;

}

/**
 * Returns a string to display the book info for hits of the search
 */

std::string Clothing::displayString() const {
    std::string clothingInfo;
    std::stringstream myStream;
    clothingInfo += name_ + "\n";
    clothingInfo += "Size: " + size_ + " ";
    clothingInfo += "Brand: " + brand_ + "\n";
    myStream << std::fixed << std::setprecision(2) << price_;
    clothingInfo += myStream.str() + " " + std::__cxx11::to_string(qty_) + " left.";

    return clothingInfo;
}

void Clothing::dump(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    os << category_   << std::endl;
    os << name_       << std::endl;
    os << price_      << std::endl;
    os << qty_        << std::endl;
    os << size_       << std::endl;
    os << brand_      << std::endl;
}
