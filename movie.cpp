#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty,
    const std::string genre, const std::string rating) : 
        Product(category, name, price, qty),
        genre_(genre),
        rating_(rating)
        {

        }

std::set<std::string> Movie::keywords() const {

    std::set<std::string> keyWords;
    keyWords = parseStringToWords(name_);
    keyWords.insert(convToLower(genre_));

    return keyWords;

}

/**
 * Returns a string to display the book info for hits of the search
 */

std::string Movie::displayString() const {
    std::string movieInfo;
    std::stringstream myStream;
    movieInfo += name_ + "\n";
    movieInfo += "Genre: " + genre_ + " ";
    movieInfo += "Rating: " + rating_ + "\n";
    myStream << std::fixed << std::setprecision(2) << price_;
    movieInfo += myStream.str() + " " + std::__cxx11::to_string(qty_) + " left.";

    return movieInfo;
}

void Movie::dump(std::ostream& os) const {
    os << std::fixed  << std::setprecision(2);
    os << category_   << std::endl;
    os << name_       << std::endl;
    os << price_      << std::endl;
    os << qty_        << std::endl;
    os << genre_      << std::endl;
    os << rating_     << std::endl;
}
