#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <queue>
#include <map>


class MyDataStore : public DataStore {
    public:
        MyDataStore();
        ~MyDataStore();
        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p);

        /**
         * Adds a user to the data store
         */
        void addUser(User* u);

        void addToCart(const std::string& username, size_t hit_result_index);

        void viewCart(const std::string& username);

        void buyCart(const std::string& username);

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile);

    private:
        std::vector<Product*> products_;
        std::map<std::string, User*> users_;
        std::vector<Product*> searchResults_;
        std::map<std::string, std::queue<Product*>> userCarts_;

};
#endif