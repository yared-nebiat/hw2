#include "mydatastore.h"
#include "util.h"


/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u) {
    std::string username = u->getName();
    users_[username] = u;
}


void MyDataStore::addToCart(const std::string& username, size_t hit_result_index) {
    if(users_.find(username) == users_.end() || hit_result_index < 0 || hit_result_index >= searchResults_.size()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    Product* myProd = searchResults_[hit_result_index];
    userCarts_[username].push(myProd);
}

void MyDataStore::viewCart(const std::string& username) {
    if(users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::queue<Product*> userCartCopy = userCarts_[username];
    std::cout << username << "'s Cart" << std::endl;

    int idx = 1;
    while(!userCartCopy.empty()) {
        std::cout << idx << ": " << userCartCopy.front()->displayString() << std::endl;
        userCartCopy.pop();
        idx++;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    if(users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::queue<Product*>& userCart = userCarts_[username];

    for(size_t i=0; i<userCart.size(); i++) {
        Product* item = userCart.front();
        if(item->getQty() > 0 && users_[username]->getBalance() >= item->getPrice()) {
            userCart.pop();
            item->subtractQty(1);
            users_[username]->deductAmount(item->getPrice());
        }
        else {
            userCart.pop();
            userCart.push(item);
        }
    }
}


/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {

    std::set<Product*> termProducts;
    std::set<Product*> searchResults;
    std::vector<Product*> finalResult;

    if(terms.empty()) {
        return finalResult;
    }

    // find products matching the first term
    for(size_t i=0; i<products_.size(); i++) {
        std::set<std::string> prodKeywords = products_[i]->keywords();
        if(prodKeywords.find(terms[0]) != prodKeywords.end()) {
            searchResults.insert(products_[i]);
        }
    }
    // find matching products for each remaining term
    for(size_t i=1; i<terms.size(); i++) {
        for(size_t j=0; j<products_.size(); j++) {
            std::set<std::string> prodKeywords = products_[j]->keywords();
            if(prodKeywords.find(terms[i]) != prodKeywords.end()) {
                termProducts.insert(products_[j]);
            }
        }
        // AND search
        if (type == 0) {
            searchResults = setIntersection(termProducts, searchResults);
        }
        // OR search
        else {
            searchResults = setUnion(termProducts, searchResults);
        }
    }


    std::set<Product*>::iterator it;

    for(it=searchResults.begin(); it != searchResults.end(); ++it) {
        finalResult.push_back(*it);
    }
    searchResults_ = finalResult;

    return finalResult;

}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for(size_t i=0; i<products_.size(); ++i) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    std::map<std::string, User*>::iterator it;
    for(it=users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
    
}



