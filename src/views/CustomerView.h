#pragma once
#include <iostream>
#include <vector>
#include "../models/Product.h"
#include "../models/Order.h"
using namespace std;

class CustomerView {
public:
    void displayProducts(const vector<Product>& products) {
        cout << "\nID\tName\tPrice\tStock\n";
        for(auto &p : products)
            cout << p.productId << "\t" << p.name << "\t" << p.price << "\t" << p.stock << "\n";
    }

    void displayOrder(const Order& o) {
        cout << "\nYour Order (ID: " << o.orderId << ")\n";
        cout << "Product\tQty\tPrice\n";
        for(auto &p : o.products)
            cout << p.name << "\t" << p.stock << "\t" << p.price << "\n";
        cout << "Total Amount: " << o.totalAmount << "\n";
        cout << "Paid: " << (o.isPaid?"Yes":"No") << "\n";
    }

    void fileReturnOrExchange(int orderId) {
    int choice;
    cout << "\n1. Return\n2. Exchange\nChoice: "; cin >> choice;
    string type = (choice == 1) ? "Return" : "Exchange";
    cout << type << " request submitted for Order ID " << orderId << "\n";
}

};
