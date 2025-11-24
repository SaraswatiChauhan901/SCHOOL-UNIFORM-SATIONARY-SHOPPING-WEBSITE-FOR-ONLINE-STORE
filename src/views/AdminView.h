#pragma once
#include <iostream>
#include <vector>
#include "../models/Product.h"
#include "../models/Order.h"
#include "../models/Complaint.h"
using namespace std;

class AdminView {
public:
    void displayInventory(const vector<Product>& products) {
        cout << "\nInventory Table:\nID\tName\tPrice\tStock\n";
        for(auto &p : products)
            cout << p.productId << "\t" << p.name << "\t" << p.price << "\t" << p.stock << "\n";
    }

    void displayOrders(const vector<Order>& orders) {
        cout << "\nOrders Table:\nOrderID\tUserID\tTotal\tPaid\n";
        for(auto &o : orders)
            cout << o.orderId << "\t" << o.userId << "\t" << o.totalAmount << "\t" << (o.isPaid?"Yes":"No") << "\n";
    }

    void displayComplaints(const vector<Complaint>& complaints){
    cout << "\nComplaints Table:\nID\tOrderID\tUserID\tType\tStatus\n";
    for(auto &c : complaints)
        cout << c.complaintId << "\t" << c.orderId << "\t" << c.userId
             << "\t" << c.type << "\t" << c.status << "\n";
}

};
