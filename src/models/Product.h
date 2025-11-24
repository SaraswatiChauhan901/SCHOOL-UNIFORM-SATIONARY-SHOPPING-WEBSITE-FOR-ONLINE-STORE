#pragma once
#include <string>
using namespace std;

class Product {
public:
    int productId;
    string name;
    double price;
    int stock;

    Product() {}
    Product(int id, string n, double p, int s)
        : productId(id), name(n), price(p), stock(s) {}
};
