#include <iostream>
#include "controller/UserController.h"
#include "controller/ProductController.h"
#include "controller/OrderController.h"
#include "controller/ComplaintController.h"
#include "views/CustomerView.h"
#include "views/AdminView.h"
using namespace std;

int main() {
    UserController userCtrl;
    ProductController productCtrl;
    OrderController orderCtrl;
    ComplaintController complaintCtrl;
    CustomerView cview;
    AdminView aview;

    userCtrl.loadUsers();
    productCtrl.loadProducts();
    orderCtrl.loadOrders();
    complaintCtrl.loadComplaints();

    string email, password;
    int currentUserId;
    bool isAdmin;

    cout << "Login\nEmail: "; cin >> email;
    cout << "Password: "; cin >> password;
    if(!userCtrl.login(email, password, currentUserId, isAdmin)){
        cout << "Invalid login!\n"; return 0;
    }

    while(true){
        system("cls");
        if(!isAdmin){ // Customer
            cout << "1. Display Products\n2. Place Order\n3. File Return/Exchange\n4. Exit\nChoice: ";
            int ch; cin >> ch;
            if(ch==1) cview.displayProducts(productCtrl.products);
            else if(ch==2){
                Order newOrder = orderCtrl.createOrder(currentUserId, productCtrl.products);
                productCtrl.saveProducts();
                cview.displayOrder(newOrder);
                orderCtrl.payOrder(newOrder);
            }
            else if(ch==3){
                int orderId;
                cout << "Enter Order ID for Return/Exchange: "; cin >> orderId;
                cview.fileReturnOrExchange(orderId);
                complaintCtrl.fileComplaint(orderId, currentUserId, "Return/Exchange");
            }
            else break;
        } else { // Admin
            cout << "1. View Inventory\n2. Add Product\n3. Remove Product\n4. View Orders\n5. View Complaints\n6. Resolve Complaint\n7. Exit\nChoice: ";
            int ch; cin >> ch;
            if(ch==1) aview.displayInventory(productCtrl.products);
            else if(ch==2){
                int id, stock; string name; double price;
                cout << "Enter Product ID, Name, Price, Stock: ";
                cin >> id >> ws; getline(cin, name); cin >> price >> stock;
                productCtrl.addProduct(Product(id, name, price, stock));
            }
            else if(ch==3){
                int id; cout << "Enter Product ID to remove: "; cin >> id;
                productCtrl.removeProduct(id);
            }
            else if(ch==4) aview.displayOrders(orderCtrl.orders);
            else if(ch==5) aview.displayComplaints(complaintCtrl.complaints);
            else if(ch==6){
                int cid; cout << "Enter Complaint ID to resolve: "; cin >> cid;
                complaintCtrl.resolveComplaint(cid);
            }
            else break;
        }
        system("pause");
    }
}
