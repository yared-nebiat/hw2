#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <iomanip>
#include <sstream>

class Clothing : public Product {
    public:
        Clothing(const std::string category, const std::string name, double price, int qty,
        const std::string brand, const std::string size);
        /**
         * Returns the appropriate keywords that this movie should be associated with
         */
        std::set<std::string> keywords() const;

        /**
         * Returns a string to display the movie info for hits of the search
         */
        std::string displayString() const;

        /**
         * Outputs the movie info in the database format
         */
        void dump(std::ostream& os) const;

    private:
        std::string brand_;
        std::string size_;

};
#endif