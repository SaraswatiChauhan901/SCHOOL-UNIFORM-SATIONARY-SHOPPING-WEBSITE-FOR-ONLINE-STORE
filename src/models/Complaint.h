#pragma once
#include <string>
using namespace std;

class Complaint {
public:
    int complaintId;
    int orderId;
    int userId;
    string type; // "Return" or "Exchange"
    string status; // "Pending", "Resolved"

    Complaint() : status("Pending") {}
};
