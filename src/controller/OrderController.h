#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/Order.h"
#include "../models/Product.h"
#include <algorithm>
using namespace std;

class OrderController {
public:
    vector<Order> orders;
    int nextOrderId = 1;

void loadOrders() {
    orders.clear();
    ifstream fin("src/data/orders.csv");
    if(!fin.is_open()){
        cout << "ERROR: Could not open orders.csv\n";
        return;
    }

    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        string orderId, userId, totalAmount, isPaid;
        getline(ss, orderId, ','); getline(ss, userId, ',');
        getline(ss, totalAmount, ','); getline(ss, isPaid, ',');

        trim(orderId); trim(userId); trim(totalAmount); trim(isPaid); // <- trimming applied

        Order o;
        o.orderId = stoi(orderId);
        o.userId = stoi(userId);
        o.totalAmount = stod(totalAmount);
        o.isPaid = isPaid=="1";
        orders.push_back(o);
        if(o.orderId >= nextOrderId) nextOrderId = o.orderId + 1;
    }
    fin.close();

    cout << "DEBUG: Loaded " << orders.size() << " orders.\n"; // optional
}


    void saveOrders() {
        ofstream fout("src/data/orders.csv");
        for(auto &o : orders)
            fout << o.orderId << "," << o.userId << "," << o.totalAmount << "," << o.isPaid << "\n";
        fout.close();
    }

    Order createOrder(int userId, vector<Product>& inventory) {
        Order o;
        o.orderId = nextOrderId++;
        o.userId = userId;
        o.totalAmount = 0;
        o.isPaid = false;

        int choice;
        do {
            cout << "\nEnter Product ID to buy (0 to finish): ";
            cin >> choice;
            if(choice == 0) break;

            auto it = find_if(inventory.begin(), inventory.end(),
                              [choice](Product &p){ return p.productId == choice; });
            if(it != inventory.end()){
                int qty;
                cout << "Enter quantity: ";
                cin >> qty;
                if(qty <= it->stock){
                    Product temp = *it;
                    temp.stock = qty;
                    o.products.push_back(temp);
                    o.totalAmount += temp.price * qty;
                    it->stock -= qty;  // Update inventory
                    cout << "Added " << qty << " of " << it->name << "\n";
                } else {
                    cout << "Not enough stock!\n";
                }
            } else cout << "Product not found!\n";
        } while(choice != 0);

        orders.push_back(o);
        saveOrders();
        return o;
    }

    void payOrder(Order &o) {
        cout << "\nTotal Amount: " << o.totalAmount << "\n";
        cout << "Enter payment method (Cash/Card/UPI): ";
        string method; cin >> method;
        o.isPaid = true;
        saveOrders();
        cout << "Payment successful!\n";
    }
};
