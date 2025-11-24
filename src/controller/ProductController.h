#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/Product.h"
#include <algorithm>
using namespace std;

class ProductController {
public:
    vector<Product> products;

void loadProducts() {
    products.clear();
    ifstream fin("src/data/products.csv");
    if(!fin.is_open()){
        cout << "ERROR: Could not open products.csv\n";
        return;
    }

    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        string id, name, price, stock;
        getline(ss, id, ','); getline(ss, name, ',');
        getline(ss, price, ','); getline(ss, stock, ',');

        trim(id); trim(name); trim(price); trim(stock); // <- trimming applied

        products.push_back(Product(stoi(id), name, stod(price), stoi(stock)));
    }
    fin.close();

    cout << "DEBUG: Loaded " << products.size() << " products.\n"; // optional
}

    void saveProducts() {
        ofstream fout("src/data/products.csv");
        for(auto &p : products)
            fout << p.productId << "," << p.name << "," << p.price << "," << p.stock << "\n";
        fout.close();
    }

    void addProduct(Product p) {
        products.push_back(p);
        saveProducts();
    }

    // Add removeProduct function for admin
void removeProduct(int id){
    auto it = find_if(products.begin(), products.end(),
                      [id](Product &p){ return p.productId == id; });
    if(it != products.end()){
        products.erase(it);
        saveProducts();
        cout << "Product removed successfully!\n";
    } else cout << "Product not found!\n";
}

};
