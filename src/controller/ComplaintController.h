#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/Complaint.h"
using namespace std;

class ComplaintController {
public:
    vector<Complaint> complaints;
    int nextComplaintId = 1;

void loadComplaints() {
    complaints.clear();
    ifstream fin("src/data/complaints.csv");
    if(!fin.is_open()){
        cout << "ERROR: Could not open complaints.csv\n";
        return;
    }

    string line;
    while(getline(fin, line)){
        stringstream ss(line);
        string id, orderId, userId, type, status;
        getline(ss, id, ','); getline(ss, orderId, ',');
        getline(ss, userId, ','); getline(ss, type, ','); getline(ss, status, ',');

        trim(id); trim(orderId); trim(userId); trim(type); trim(status); // <- trimming applied

        Complaint c;
        c.complaintId = stoi(id);
        c.orderId = stoi(orderId);
        c.userId = stoi(userId);
        c.type = type;
        c.status = status;
        complaints.push_back(c);
        if(c.complaintId >= nextComplaintId) nextComplaintId = c.complaintId + 1;
    }
    fin.close();

    cout << "DEBUG: Loaded " << complaints.size() << " complaints.\n"; // optional
}


    void saveComplaints() {
        ofstream fout("src/data/complaints.csv");
        for(auto &c : complaints)
            fout << c.complaintId << "," << c.orderId << "," << c.userId << "," 
                 << c.type << "," << c.status << "\n";
        fout.close();
    }

    void fileComplaint(int orderId, int userId, string type) {
        Complaint c;
        c.complaintId = nextComplaintId++;
        c.orderId = orderId;
        c.userId = userId;
        c.type = type;
        c.status = "Pending";
        complaints.push_back(c);
        saveComplaints();
        cout << type << " complaint filed successfully!\n";
    }

    void resolveComplaint(int id) {
        for(auto &c : complaints){
            if(c.complaintId == id){
                c.status = "Resolved";
                saveComplaints();
                cout << "Complaint resolved!\n";
                return;
            }
        }
        cout << "Complaint not found!\n";
    }
};
