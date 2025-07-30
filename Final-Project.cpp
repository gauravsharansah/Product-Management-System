#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class prod_manage {
public:
    int prod_id;
    string prod_name;
    int prod_stocks;
    float prod_price;

    prod_manage() {}

    prod_manage(int p, string pn, int s, float c) {
        prod_id = p;
        prod_name = pn;
        prod_stocks = s;
        prod_price = c;
    }

    void get_prod_details();
};

class Billing : public prod_manage {
public:
    void generate_bill(const string& cust_name, int id, const string& name, int qty, float price, float total) {
        time_t now = time(0);
        char* dt = ctime(&now);
        fstream sales("sales.txt", ios::app);
        sales << cust_name << '\t' << id << '\t' << name << '\t' << qty << '\t' << price << '\t' << total << '\t' << dt;
        sales.close();
    }
};

void prod_manage::get_prod_details() {
    string sup_name;
    cout << "Enter supplier name: ";
    cin >> sup_name;
    int new_id;
    cout << "Enter product name ";
    cin >> prod_name;
    fstream check("product.txt", ios::in);
    int id, stock, total;
    string name;
    float price;
    bool found = false;
    fstream file("product1.txt", ios::out);
    fstream temp("supplier.txt", ios::app);
    while (check >> id >> name >> stock >> price) {
        if (name == prod_name) {
            cout << "Note: Product name already exists. Thus final stocks will be added up.\n";
            check.close();
            cout << "Enter no of products: ";
            cin >> prod_stocks;
            found = true;
            new_id=id+1;
            file << id << '\t' << prod_name << '\t' << prod_stocks + stock << '\t' << price << '\n';
            total = prod_stocks * price;
            temp << sup_name << '\t' << id << '\t' << prod_name << '\t' << prod_stocks << '\t' << price << '\t' << total << '\n';
            cout << "The details of deal are: \n";
            cout << sup_name << '\t' << id << '\t' << prod_name << '\t' << prod_stocks << '\t' << price << '\t' << total << '\n';
            cout<<"\nThe total cost of product is: " << total << endl ;
        }
        else {
            file << id << '\t' << prod_name << '\t' << stock << '\t' << price << '\n';
        }
    }


    if(!found){
        check.close();
        cout << "Enter no of products: ";
        cin >> prod_stocks;
        cout << "Enter price of product: ";
        cin >> prod_price;
        file << new_id << '\t' << prod_name << '\t' << prod_stocks << '\t' << prod_price << '\n';
        total = prod_stocks * prod_price;
        temp << sup_name << '\t' << new_id << '\t' << prod_name << '\t' << prod_stocks << '\t' << prod_price << '\t' << total << '\n';
        cout << "The details of deal are: \n";
        cout << sup_name << '\t' << new_id << '\t' << prod_name << '\t' << prod_stocks << '\t' << prod_price << '\t' << total << '\n';
        cout<<"\nThe total cost of product is: " << total << endl ;
    }

    file.close();
    temp.close();
    
    remove("product.txt");
    rename("product1.txt", "product.txt");

    cout << "Product added successfully.\n";
}

void display() {
    fstream file("product.txt", ios::in);
    int id, stock;
    string name;
    float price;

    cout << fixed << setprecision(2);
    cout << "All product details:\n";
    cout << "ID\tName\tStocks\tPrice\n";
    while (file >> id >> name >> stock >> price) {
        cout << id << '\t' << name << '\t' << stock << '\t' << price << endl;
    }
    file.close();
}

void display_oneprod() {
	fstream file("product.txt", ios::in);
    int id, stock;
    string name, disp_name;
    float price;

    cout << fixed << setprecision(2);
    cout << "Enter produt name whose details are needed: ";
    cin >> disp_name;
    cout << "All product details:\n";
    cout << "ID\tName\tStocks\tPrice\n";
    while (file >> id >> name >> stock >> price) {
        if(disp_name == name)
        cout << id << '\t' << name << '\t' << stock << '\t' << price << endl;
    }
    file.close();
}

void delet_prod(int del_id) {
    fstream file("product.txt", ios::in);
    fstream temp("temp.txt", ios::out);
    int id, stock;
    string name;
    float price;
    bool found = false;

    while (file >> id >> name >> stock >> price) {
        if (id != del_id) {
            temp << id << '\t' << name << '\t' << stock << '\t' << price << '\n';
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();

    if (found) {
        remove("product.txt");
        rename("temp.txt", "product.txt");
        cout << "Product deleted successfully.\n";
    } else {
        remove("temp.txt");
        cout << "Product ID not found.\n";
    }
}

void delet_prod(string del_name) {
    fstream file("product.txt", ios::in);
    fstream temp("temp.txt", ios::out);
    int id, stock;
    string name;
    float price;
    bool found = false;

    while (file >> id >> name >> stock >> price) {
        if (name != del_name) {
            temp << id << '\t' << name << '\t' << stock << '\t' << price << '\n';
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();

    if (found) {
        remove("product.txt");
        rename("temp.txt", "product.txt");
        cout << "Product deleted successfully.\n";
    } else {
        remove("temp.txt");
        cout << "Product name not found.\n";
    }
 
}

void search_prod(int p_id) {
    fstream file("product.txt", ios::in);
    int id, stock;
    string name;
    float price;

    cout << fixed << setprecision(2);
    while (file >> id >> name >> stock >> price) {
        if (id == p_id) {
            cout << "Product ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Stocks: " << stock << endl;
            cout << "Price: " << price << endl;
            file.close();
            return;
        }
    }

    cout << "No record found.\n";
    file.close();
}

void search_prod(string p_name) {
    fstream file("product.txt", ios::in);
    int id, stock;
    string name;
    float price;

    cout << fixed << setprecision(2);
    while (file >> id >> name >> stock >> price) {
        if (name == p_name) {
            cout << "Product ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Stocks: " << stock << endl;
            cout << "Price: " << price << endl;
            file.close();
            return;
        }
    }

    cout << "No record found.\n";
    file.close();
}

void buy_prod() {
    Billing bill;
    int req_stock, resp = 1;
    string cust_name, req_name;

    cout << "Enter customer name: ";
    cin >> cust_name;

    while (resp == 1) {
        cout << "Enter name of product: ";
        cin >> req_name;

        fstream prod_in("product.txt", ios::in);
        fstream temp("temp.txt", ios::out);

        int id, stock;
        string name;
        float price, total;

        bool product_found = false;

        while (prod_in >> id >> name >> stock >> price) {
            if (name == req_name) {
                product_found = true;
                cout << "Enter how many stocks do you need: ";
                cin >> req_stock;
                if (stock < req_stock) {
                    req_stock = stock;
                    cout << "Stock is reduced to " << req_stock << " due to insufficient stocks.\n";
                }
                float subtotal = req_stock * price;
                float tax = subtotal * 0.13;
                total = subtotal + tax;
                cout << fixed << setprecision(2);
                cout << "Subtotal: " << subtotal << "\nTax (13%): " << tax << "\nTotal amount is: " << total << endl;
                temp << id << '\t' << name << '\t' << stock - req_stock << '\t' << price << '\n';
                bill.generate_bill(cust_name, id, name, req_stock, price, total);
            } else {
                temp << id << '\t' << name << '\t' << stock << '\t' << price << '\n';
            }
        }
        prod_in.close();
        temp.close();
        remove("product.txt");
        rename("temp.txt", "product.txt");

        if (!product_found)
            cout << "No product with the given name found.\n";

        cout << "Enter 1 to continue buying, 0 to exit: ";
        cin >> resp;
    }
}

void low_stocks() {
    fstream file("product.txt", ios::in);
    int id, stock;
    string name;
    float price;

    cout << fixed << setprecision(2);
    cout << "Low stock product details (<20):\n";
    while (file >> id >> name >> stock >> price) {
        if (stock < 20) {
            cout << id << '\t' << name << '\t' << stock << '\t' << price << endl;
        }
    }
    file.close();
}

void add_stocks() {
    int qty;
    string add_name, sup_name;

    display();
    cout << "Enter product name to add stock: ";
    cin >> add_name;

    fstream file("product.txt", ios::in);
    int id, stock;
    string name;
    float price;
    bool found = false;

    while (file >> id >> name >> stock >> price) {
        if (name == add_name) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Enter supplier name: ";
        cin >> sup_name;
        cout << "Enter stock quantity to add: ";
        cin >> qty;

        fstream fin("product.txt", ios::in);
        fstream temp("temp.txt", ios::out);
        fstream fout("supplier.txt", ios::app);

        while (fin >> id >> name >> stock >> price) {
            if (name == add_name) {
                temp << id << '\t' << name << '\t' << stock + qty << '\t' << price << '\n';
            } else {
                temp << id << '\t' << name << '\t' << stock << '\t' << price << '\n';
            }
        }

        fout << sup_name << '\t' << id << '\t' << name << '\t' << qty << '\t' << price << '\t' << price * qty << '\n';

        fin.close();
        temp.close();
        fout.close();

        remove("product.txt");
        rename("temp.txt", "product.txt");

        cout << "Stocks added successfully.\n";
        display();
    } else {
        cout << "Product name not found.\n";
    }
}

void supplier_info() {
    fstream file("supplier.txt", ios::in);
    int id, stock;
    string sup_name, name;
    float price, total;

    cout << fixed << setprecision(2);
    cout << "All supplier details:\n";
    cout << "Supplier\tID\tName\tStock\tPrice\tTotal\n";
    while (file >> sup_name >> id >> name >> stock >> price >> total) {
        cout << sup_name << '\t' << id << '\t' << name << '\t' << stock << '\t' << price << '\t' << total << endl;
    }
    file.close();
}

void sales_info() {
    fstream file("sales.txt", ios::in);
    int id, stock;
    string cust_name, name;
    float price, total;
    string timestamp;

    cout << fixed << setprecision(2);
    cout << "All sales details:\n";
    cout << "Customer\tID\tName\tStock\tPrice\tTotal   \tTimestamp\n";
    while (file >> cust_name >> id >> name >> stock >> price >> total) {
        getline(file, timestamp);
        cout << '\n' << cust_name << '\t' << '\t' << id << '\t' << name << '\t' << stock << '\t' << price << '\t' << total << '\t' << timestamp << endl;
    }
    file.close();
}

void total_revenue() {
    fstream file("sales.txt", ios::in);
    if (!file) {
        cout << "No sales records found.\n";
        return;
    }

    string cust_name, prod_name, timestamp;
    int id, stock;
    float price, total;
    float grand_total = 0;

    while (file >> cust_name >> id >> prod_name >> stock >> price >> total) {
        getline(file, timestamp);
        grand_total += total;
    }
    file.close();

    cout << fixed << setprecision(2);
    cout << "Total revenue generated from all sales: " << grand_total << endl;
}

int main() {
    prod_manage p;
    char ch;
    int input, search_id, delet_id;

    do {
        //clrscr();
        cout << "\033[2J\033[H";
        cout << "\n1---->Add product details\n";
        cout << "2---->Display all product details\n";
        cout << "3---->Search product details\n";
        cout << "4---->Delete product details\n";
        cout << "5---->Buy products\n";
        cout << "6---->Display suppliers info\n";
        cout << "7---->Low stock alerts\n";
        cout << "8---->Add stocks to existing product\n";
        cout << "9---->Display sales info\n";
        cout << "10--->Display total revenue summary\n";
        cout << "11--->Display product details of a particular product\n";
        cout << "Enter your choice: ";
        cin >> input;

        switch (input) {
        case 1:
            p.get_prod_details();
            break;
        case 2:
            display();
            break;
        case 3: {
            int choice;
            cout << "Search by:\n1. Product ID\n2. Product Name\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter product ID to search: ";
                cin >> search_id;
                search_prod(search_id);
            } else if (choice == 2) {
                cout << "Enter product Name to search (no spaces): ";
                string search_name;
                cin >> search_name;
                search_prod(search_name);
            } else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 4:
            int choice;
            cout << "Delete by:\n1. Product ID\n2. Product Name\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter product ID to delete: ";
                cin >> delet_id;
                delet_prod(delet_id);
            } else if (choice == 2) {
                cout << "Enter product Name to delete (no spaces): ";
                string delet_name;
                cin >> delet_name;
                delet_prod(delet_name);
            } else {
                cout << "Invalid choice.\n";
            }
            break;
        case 5:
            buy_prod();
            break;
        case 6:
            supplier_info();
            break;
        case 7:
            low_stocks();
            break;
        case 8:
            add_stocks();
            break;
        case 9:
            sales_info();
            break;
        case 10:
            total_revenue();
            break;
        case 11:
            display_oneprod();
            break;
        default:
            cout << "Invalid entry.\n";
        }

        cout << "Enter Y to continue or N to exit: ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    return 0;
}


