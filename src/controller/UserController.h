#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/Users.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch){ return !std::isspace(ch); }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch){ return !std::isspace(ch) && ch != '\r'; }).base(), s.end());
}


static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

class UserController {
public:
    vector<User> users;

void loadUsers() {
    users.clear();
    ifstream fin("src/data/users.csv");
    if(!fin.is_open()){
        cout << "ERROR: Could not open users.csv\n";
        return;
    }
    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        string id, name, email, password, admin;
        getline(ss, id, ','); getline(ss, name, ',');
        getline(ss, email, ','); getline(ss, password, ',');
        getline(ss, admin, ',');

        trim(id); trim(name); trim(email); trim(password); trim(admin);

        users.push_back(User(stoi(id), name, email, password, admin=="1"));
    }
    fin.close();

    cout << "DEBUG: Loaded " << users.size() << " users.\n"; // confirm
}

    void saveUsers() {
        ofstream fout("src/data/users.csv");
        for(auto &u : users)
            fout << u.userId << "," << u.name << "," << u.email << "," 
                 << u.password << "," << u.isAdmin << "\n";
        fout.close();
    }

bool login(string email, string password, int &userId, bool &isAdmin) {
    trim(email);
    trim(password);

    cout << "DEBUG: Attempting login with:\n";
    cout << "Email entered: '" << email << "'\n";
    cout << "Password entered: '" << password << "'\n";

    for(auto &u : users){
        trim(u.email);
        trim(u.password);

        cout << "DEBUG: Checking against user:\n";
        cout << "Email: '" << u.email << "', Password: '" << u.password << "'\n";

        if(u.email == email && u.password == password){
            cout << "DEBUG: Login successful!\n";
            userId = u.userId;
            isAdmin = u.isAdmin;
            return true;
        } else {
            cout << "DEBUG: No match.\n";
        }
    }

    cout << "DEBUG: Login failed.\n";
    return false;
}


    void addUser(User u) {
        users.push_back(u);
        saveUsers();
    }
};
