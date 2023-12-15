#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

class Admin {
public:
    string admin_name;
    string admin_password;

    Admin(string adm_name = "", string adm_pass = "") : admin_name(adm_name), admin_password(adm_pass) {}
};
class Customer;
class Services {
public:
    string service_name;
    int service_cost;
    int service_id;
    Services* next;
    bool hasCustomers;
    Customer* customer_head;

    Services(string ser_name = "", int ser_cost = 0, int ser_id = 0) : service_name(ser_name), service_cost(ser_cost), service_id(ser_id), next(nullptr), hasCustomers(false), customer_head(nullptr) {}

    friend class ServicesFunction;
};


class Customer {
public:
    string customer_name;
    string customer_contact;
    int customer_id;
    Customer* next;

    Customer(int cus_id = 0, string cus_name = "", string cus_contact = "")
        : customer_id(cus_id), customer_name(cus_name), customer_contact(cus_contact), next(nullptr) {}

    friend class ServicesFunction;
};

class ServicesFunction {
public:
    Services* services_head;
    Customer* customer_head;
public:
    ServicesFunction() : services_head(nullptr), customer_head(nullptr) {}

    void Addservice() {
        int ser_id;
        while (true) {
            cout << "Enter Service Id: ";
            cin >> ser_id;
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* current = services_head;
        while (current != nullptr) {
            if (ser_id == current->service_id) {
                cout << "ID already exists!" << endl;
                cout << "Try with a new ID: ";
                cin >> ser_id;
                // Reset the loop to check if the new ID exists
                current = services_head;
            }
            else {
                current = current->next;
            }
        }

        string ser_name;
        int ser_cost;
        cout << "Enter Service Name: ";
        cin.ignore();
        getline(cin, ser_name);

        bool isalphaName = true;
        for (char c : ser_name) {
            if (!isalpha(c) && !isspace(c)) {
                isalphaName = false;
                break;
            }
        }
        if (!isalphaName) {
            cout << "Invalid username! Username should only contain letters." << endl;
            cout << "Enter again:";
            cin.ignore();
            getline(cin, ser_name);
        }
        while (true) {
            cout << "Enter Service cost: ";
            cin >> ser_cost;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* newService = new Services(ser_name, ser_cost, ser_id);
        newService->next = services_head;
        services_head = newService;

        cout << "Service added successfully!" << endl;
    }

    void UpdateService() {
        int update_id;

        while (true) {
            cout << "Enter Service ID to Update: ";
            cin >> update_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }
        Services* current = services_head;
        while (current != nullptr) {
            if (current->service_id == update_id) {
                string ser_name;
                int ser_cost;
                cout << "Enter Updated Service Name: ";
                cin.ignore();
                getline(cin, ser_name);

                bool isAlphaName = true;
                for (char c : ser_name) {
                    if (!isalpha(c) && !isspace(c)) {
                        isAlphaName = false;
                        break;
                    }
                }

                if (!isAlphaName) {
                    cout << "Invalid username! Username should only contain letters." << endl;
                    cout << "Enter Again: ";
                    cin.ignore();
                    getline(cin, ser_name);
                }
                while (true) {
                    cout << "Enter Updated Service Cost: ";
                    cin >> ser_cost;

                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear(); // clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        cout << "Invalid Id! Id should only contain numbers." << endl;
                    }
                    else {
                        // Input is numeric, exit the loop
                        break;
                    }
                }

                current->service_name = ser_name;
                current->service_cost = ser_cost;

                cout << "Service updated successfully!" << endl;
                return;
            }
            current = current->next;
        }

        cout << "Service ID not found!" << endl;
    }

    void SearchService() {
        int search_id;

        while (true) {
            cout << "Enter Service ID to Search: ";
            cin >> search_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* current = services_head;
        while (current != nullptr) {
            if (current->service_id == search_id) {
                cout << "Service ID: " << current->service_id << endl;
                cout << "Service Name: " << current->service_name << endl;
                cout << "Service Cost: " << current->service_cost << endl;
                return;
            }
            current = current->next;
        }

        cout << "Service ID not found!" << endl;
    }

    void DeleteService() {
        int delete_id;
        while (true) {
            cout << "Enter Service ID to Delete: ";
            cin >> delete_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* current = services_head;
        Services* prev = nullptr;

        while (current != nullptr) {
            if (current->service_id == delete_id) {
                if (prev != nullptr) {
                    prev->next = current->next;
                }
                else {
                    services_head = current->next;
                }

                delete current;
                cout << "Service deleted successfully!" << endl;
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Service ID not found!" << endl;
    }

    void DisplayServices() {
        Services* current = services_head;
        cout << "\t\t\t Services List \t\t\t" << endl;
        if (current == nullptr) {
            cout << "No data found!" << endl;
            return;
        }
        while (current != nullptr) {

            cout << "Service ID: " << current->service_id << endl;
            cout << "Service Name: " << current->service_name << endl;
            cout << "Service Cost: " << current->service_cost << endl << endl;
            current = current->next;
        }
    }

    // Inside the ServicesFunction class
    void AddCustomerToService() {
        int entered_service;
        while (true) {
            cout << "Enter the Service ID to add a customer: ";
            cin >> entered_service;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* currentService = services_head;
        while (currentService != nullptr) {
            if (currentService->service_id == entered_service) {
                int cus_id;
                string cus_name, cus_contact;
                // Check if the entered Customer ID already exists
                while (true) {
                    cout << "Enter Customer ID: ";
                    cin >> cus_id;

                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear(); // clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        cout << "Invalid Id! Id should only contain numbers." << endl;
                    }
                    else {
                        // Input is numeric, check if the ID already exists
                        if (CustomerIDExists(currentService->customer_head, cus_id)) {
                            cout << "Customer ID already exists. Please enter a different ID." << endl;
                        }
                        else {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break; // ID is valid and does not exist, exit the loop
                        }
                    }
                }

                cout << "Enter Customer Name: ";
                getline(cin, cus_name);
                bool isAlphaName = true;
                for (char c : cus_name) {
                    if (!isalpha(c) && !isspace(c)) {
                        isAlphaName = false;
                        break;
                    }
                }
                if (!isAlphaName) {
                    cout << "Invalid username! Username should only contain letters." << endl;
                    cout << "Enter Again: ";
                    cin.ignore();
                    getline(cin, cus_name);
                }
                // Check if the entered Customer Contact already exists
                while (true) {
                    cout << "Enter Customer Contact: ";
                    cin.ignore(); // clear the newline character left in the buffer
                    getline(cin, cus_contact);

                    if (CustomerContactExists(currentService->customer_head, cus_contact)) {
                        cout << "Customer Contact already exists. Please enter a different contact." << endl;
                    }
                    else {
                        break; // Contact is valid and does not exist, exit the loop
                    }
                }
                // Create a new customer
                Customer* newCustomer = new Customer(cus_id, cus_name, cus_contact);

                // Add the customer to the beginning of the customer list of the service
                newCustomer->next = currentService->customer_head;
                currentService->customer_head = newCustomer;
                currentService->hasCustomers = true;
                cout << "Customer added to the service successfully!" << endl;
                return;
            }

            currentService = currentService->next;
        }
        cout << "Service ID not found!" << endl;
    }

    // Helper function to check if a Customer ID already exists in the list
    bool CustomerIDExists(Customer* head, int id) {
        Customer* current = head;
        while (current != nullptr) {
            if (current->customer_id == id) {
                return true; // ID already exists
            }
            current = current->next;
        }
        return false; // ID does not exist
    }

    // Helper function to check if a Customer Contact already exists in the list
    bool CustomerContactExists(Customer* head, const string& contact) {
        Customer* current = head;
        while (current != nullptr) {
            if (current->customer_contact == contact) {
                return true; // Contact already exists
            }
            current = current->next;
        }
        return false; // Contact does not exist
    }



    void UpdateCustomer() {
        int update_id;
        while (true) {
            cout << "Enter Customer ID to Update: ";
            cin >> update_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear any remaining newline characters
                break;
            }
        }

        Services* currentService = services_head;
        while (currentService != nullptr) {
            Customer* currentCustomer = currentService->customer_head;
            while (currentCustomer != nullptr) {
                if (currentCustomer->customer_id == update_id) {
                    string cus_name, cus_contact;

                    cout << "Enter Updated Customer Name: ";
                    getline(cin, cus_name);

                    bool isAlphaName = true;
                    for (char c : cus_name) {
                        if (!isalpha(c) && !isspace(c)) {
                            isAlphaName = false;
                            break;
                        }
                    }

                    if (!isAlphaName) {
                        cout << "Invalid username! Username should only contain letters." << endl;
                        cout << "Enter Again: ";
                        getline(cin, cus_name);
                    }

                    cout << "Enter Updated Customer Contact: ";
                    getline(cin, cus_contact);

                    currentCustomer->customer_name = cus_name;
                    currentCustomer->customer_contact = cus_contact;

                    cout << "Customer updated successfully!" << endl;
                    return;
                }
                currentCustomer = currentCustomer->next;
            }
            currentService = currentService->next;
        }

        cout << "Customer ID not found!" << endl;
    }


    void SearchCustomer() {
        int searchcus_id;

        while (true) {
            cout << "Enter Customer ID to Search: ";
            cin >> searchcus_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* currentService = services_head;
        while (currentService != nullptr) {
            Customer* currentCustomer = currentService->customer_head;
            bool found = false;

            while (currentCustomer != nullptr) {
                if (currentCustomer->customer_id == searchcus_id) {
                    cout << "----------------" << endl;
                    cout << "  Customer ID:  " << currentCustomer->customer_id << endl;
                    cout << "  Customer Name: " << currentCustomer->customer_name << endl;
                    cout << "Customer Contact: " << currentCustomer->customer_contact << endl;
                    cout << "----------------" << endl;
                    found = true;
                    break;
                }
                currentCustomer = currentCustomer->next;
            }

            if (found) {
                return;
            }

            currentService = currentService->next;
        }

        cout << "Customer ID not found!" << endl;
    }


    void DeleteCustomer() {
        int deletecus_id;
        while (true) {
            cout << "Enter Customer ID to Delete: ";
            cin >> deletecus_id;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid Id! Id should only contain numbers." << endl;
            }
            else {
                // Input is numeric, exit the loop
                break;
            }
        }

        Services* currentService = services_head;
        while (currentService != nullptr) {
            Customer* currentCustomer = currentService->customer_head;
            Customer* prevCustomer = nullptr;

            while (currentCustomer != nullptr) {
                if (currentCustomer->customer_id == deletecus_id) {
                    if (prevCustomer != nullptr) {
                        prevCustomer->next = currentCustomer->next;
                    }
                    else {
                        currentService->customer_head = currentCustomer->next;
                    }

                    delete currentCustomer;
                    cout << "Customer deleted successfully!" << endl;
                    return;
                }

                prevCustomer = currentCustomer;
                currentCustomer = currentCustomer->next;
            }

            currentService = currentService->next;
        }

        cout << "Customer ID not found!" << endl;
    }

    void DisplayCustomersWithServices() {
        if (services_head == nullptr) {
            cout << "No services available." << endl;
            return;
        }

        cout << "=======================================" << endl;
        cout << "   Customer Data List (selected services)   " << endl;
        cout << "=======================================" << endl;

        Services* currentService = services_head;

        while (currentService != nullptr) {
            if (currentService->hasCustomers) {
                cout << "---------------" << endl;
                cout << "  Service ID:  " << currentService->service_id << endl;
                cout << " Service Name: " << currentService->service_name << endl;
                cout << " Service Cost: " << currentService->service_cost << endl;

                // Display customers for the current service
                Customer* currentCustomer = currentService->customer_head;

                while (currentCustomer != nullptr) {
                    cout << " Customer ID: " << currentCustomer->customer_id << endl;
                    cout << " Customer Name: " << currentCustomer->customer_name << endl;
                    cout << " Customer Contact: " << currentCustomer->customer_contact << endl;
                    cout << "---------------" << endl;
                    currentCustomer = currentCustomer->next;
                }
            }

            currentService = currentService->next;
        }
    }


    void CustomerMenu() {
        int choice;
        do {
            cout << "---------------------------" << endl;
            cout << "        Customer Menu      " << endl;
            cout << "---------------------------" << endl;
            cout << "1: Add Customer to a service" << endl;
            cout << "2: Update Customer" << endl;
            cout << "3: Search Customer" << endl;
            cout << "4: Delete Customer" << endl;
            cout << "5: Display Customers" << endl;
            cout << "6: Back to Menu" << endl;

            while (true) {
                cout << "Enter your choice: ";
                cin >> choice;

                if (cin.fail() || cin.peek() != '\n') {
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                    cout << "Invalid choice! Should only contain numbers." << endl;
                }
                else {
                    // Input is numeric, exit the loop
                    break;
                }
            }

            switch (choice) {
            case 1:
                AddCustomerToService();
                break;
            case 2:
                UpdateCustomer();
                break;
            case 3:
                SearchCustomer();
                break;
            case 4:
                DeleteCustomer();
                break;
            case 5:
                DisplayCustomersWithServices();
                break;
            case 6:
                cout << "Exiting Customer Management!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 6);
    }

    void Menu() {
        int choice;
        do {
            cout << "------------------------" << endl;
            cout << "  Manage Services Menu  " << endl;
            cout << "------------------------" << endl;
            cout << "1: Add Service" << endl;
            cout << "2: Update Service" << endl;
            cout << "3: Search Service" << endl;
            cout << "4: Delete Service" << endl;
            cout << "5: Display Services" << endl;
            cout << "6: Exit" << endl;

            while (true) {
                cout << "Enter your choice: ";
                cin >> choice;

                if (cin.fail() || cin.peek() != '\n') {
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                    cout << "Invalid choice! Should only contain numbers." << endl;
                }
                else {
                    // Input is numeric, exit the loop
                    break;
                }
            }

            switch (choice) {
            case 1:
                Addservice();
                break;
            case 2:
                UpdateService();
                break;
            case 3:
                SearchService();
                break;
            case 4:
                DeleteService();
                break;
            case 5:
                DisplayServices();
                break;
            case 6:
                cout << "Exiting Service Management!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 6);
    }
};

class AdminFunction {
private:
    Admin admin;
    ServicesFunction servicesFunction;

public:
    AdminFunction() {}

    void adminSignup() {
        string adm_name, adm_pass;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, adm_name);

        bool isalphaName = true;
        for (char c : adm_name) {
            if (!isalpha(c) && !isspace(c)) {
                isalphaName = false;
                break;
            }
        }


        if (!isalphaName) {
            cout << "Invalid username! Username should only contain letters!" << endl;
            return;
        }
        bool adminExists = false;
        if (admin.admin_name == adm_name) {
            adminExists = true;
        }

        if (adminExists) {
            cout << "Admin already exists!" << endl;
        }
        else {
            cout << "Enter Password: ";
            cin >> adm_pass;

            admin = Admin(adm_name, adm_pass);
            cout << "Signed up successfully!" << endl;
        }
    }

    void adminSignin() {
        string entered_name, entered_pass;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, entered_name);

        cout << "Enter Password: ";
        cin >> entered_pass;

        if (entered_name == admin.admin_name && entered_pass == admin.admin_password) {
            cout << "Login successful!" << endl;
            AdminMenu(); // Redirect to services menu
        }
        else {
            cout << "Invalid username or password!" << endl;
        }
    }

    void adminMenu() {
        int choice;
        do {
            cout << "========================" << endl;
            cout << "       Admin Menu     " << endl;
            cout << "========================" << endl;
            cout << "1: Admin Sign up " << endl;
            cout << "2: Admin login " << endl;
            cout << "3: Exit" << endl;

            while (true) {
                cout << "Enter your choice: ";
                cin >> choice;

                if (cin.fail() || cin.peek() != '\n') {
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                    cout << "Invalid choice! should only contain numbers." << endl;
                }
                else {
                    // Input is numeric, exit the loop
                    break;
                }
            }
            switch (choice) {
            case 1:
                adminSignup();
                break;

            case 2:
                adminSignin();
                break;

            case 3:
                cout << "Exiting the program!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }
    void AdminMenu() {
        int choice;
        do {
            cout << "-------------------------------" << endl;
            cout << "\t\t\t Travelling Agency \t\t\t" << endl;
            cout << "-------------------------------" << endl;
            cout << "1: Manage Services " << endl;
            cout << "2: Manage Customers " << endl;
            cout << "3: Exit" << endl;

            while (true) {
                cout << "Enter your choice: ";
                cin >> choice;

                if (cin.fail() || cin.peek() != '\n') {
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                    cout << "Invalid choice! Should only contain numbers." << endl;
                }
                else {
                    // Input is numeric, exit the loop
                    break;
                }
            }

            switch (choice) {
            case 1:
                servicesFunction.Menu();
                break;
            case 2:
                servicesFunction.CustomerMenu();
                break;
            case 3:
                cout << "Exiting!" << endl;
                return;
            default:
                cout << "Invalid choice!" << endl;
            }
        } while (true);
    }
};

int main() {
    AdminFunction adminFunction;
    adminFunction.adminMenu();
    return 0;
}