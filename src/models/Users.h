#pragma once
#include <string>
using namespace std;

class User {
public:
    int userId;
    string name;
    string email;
    string password;
    bool isAdmin;

    User() {}
    User(int id, string n, string e, string p, bool admin=false)
        : userId(id), name(n), email(e), password(p), isAdmin(admin) {}
};
