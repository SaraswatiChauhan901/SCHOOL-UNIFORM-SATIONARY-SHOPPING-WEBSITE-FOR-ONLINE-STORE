#pragma once
#include <vector>
#include "./Product.h"
using namespace std;

class Order {
public:
    int orderId;
    int userId;
    vector<Product> products;
    double totalAmount;
    bool isPaid;

    Order() : totalAmount(0), isPaid(false) {}
};
