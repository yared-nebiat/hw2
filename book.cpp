#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty,
    const std::string author, const std::string isbn) : 
        Product(category, name, price, qty),
        author_(author),
        isbn_(isbn)
        {

        }

std::set<std::string> Book::keywords() const {

    std::set<std::string> keyWords;
    std::set<std::string> temp;

    keyWords = parseStringToWords(name_);
    temp = parseStringToWords(author_);
    keyWords.insert(temp.begin(), temp.end());
    keyWords.insert(isbn_);

    return keyWords;

}

/**
 * Returns a string to display the book info for hits of the search
 */
std::string Book::displayString() const {
    std::string bookInfo;
    std::stringstream myStream;
    bookInfo += name_ + "\n";
    bookInfo += "Author: " + author_ + " ";
    bookInfo += "ISBN: " + isbn_ + "\n";
    myStream << std::fixed << std::setprecision(2) << price_;
    bookInfo += myStream.str() + " " + std::__cxx11::to_string(qty_) + " left.";

    return bookInfo;
}

void Book::dump(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    os << category_ << std::endl;
    os << name_     << std::endl;
    os << price_    << std::endl;
    os << qty_      << std::endl;
    os << isbn_     << std::endl;
    os << author_   << std::endl;
}
