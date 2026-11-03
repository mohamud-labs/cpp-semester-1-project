
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Enum for car categories 
enum CarType { ECONOMY = 1, COMFORT, LUXURY, SUV };

// Car structure */
struct Car {
    int id, year;
    string brand, model;
    CarType type;
    double price;
    bool available;
};

// Customer structure 
struct Customer {
    int id;
    string name, phone;
};

// Rental structure 
struct Rental {
    int id, carId, customerId, days;
    bool active;
};

//Global storage 
vector<Car> cars;
vector<Customer> customers;
vector<Rental> rentals;

//Auto IDs */
int carID = 1, custID = 1, rentID = 1;

// Convert car type to string 
string typeName(CarType t) {
    string names[] = { "", "Economy", "Comfort", "Luxury", "SUV" };
    return names[t];
}

// Load cars 
void loadCars() {
    cars.push_back({ carID++, 2023, "Toyota", "Corolla", ECONOMY, 45, true });
    cars.push_back({ carID++, 2024, "Honda", "Civic", COMFORT, 55, true });
    cars.push_back({ carID++, 2023, "BMW", "5 Series", LUXURY, 120, true });
    cars.push_back({ carID++, 2024, "Toyota", "Fortuner", SUV, 90, true }); // Extra car
}

//Show cars 
void showCars(bool onlyAvailable = false) {
    cout << "\n--- Cars ---\n";
    for (auto& c : cars) {
        if (!onlyAvailable || c.available) {
            cout << c.id << ". "
                << c.brand << " " << c.model
                << " | " << typeName(c.type)
                << " | $" << c.price << "/day "
                << (c.available ? "[Available]" : "[Rented]") << endl;
        }
    }
}

// Rent a car 
void rentCar() {
    showCars(true);

    int cid, days;
    cout << "\nEnter Car ID: ";
    cin >> cid;

    cout << "Number of days: ";
    cin >> days;

    Car* selectedCar = nullptr;
    for (auto& c : cars) {
        if (c.id == cid && c.available) {
            selectedCar = &c;
            break;
        }
    }

    if (!selectedCar) {
        cout << "Invalid or unavailable car!\n";
        return;
    }

    Customer cu;
    cu.id = custID++;
    cin.ignore();
    cout << "Customer Name: ";
    getline(cin, cu.name);
    cout << "Phone: ";
    getline(cin, cu.phone);

    customers.push_back(cu);

    rentals.push_back({ rentID++, cid, cu.id, days, true });
    selectedCar->available = false;

    cout << "Car rented successfully!\n";
}

// Return car USING CAR ID (FIXED) 
void returnCar() {
    int carId;
    cout << "\nEnter Car ID to return: ";
    cin >> carId;

    for (auto& r : rentals) {
        if (r.carId == carId && r.active) {

            for (auto& c : cars) {
                if (c.id == carId) {
                    c.available = true;
                    break;
                }
            }

            r.active = false;
            cout << "Car returned successfully!\n";
            return;
        }
    }

    cout << "This car is not currently rented!\n";
}

// Main menu 
int main() {
    loadCars();
    int choice;

    do {
        cout << "\n===== CAR RENTAL SYSTEM =====";
        cout << "\n1. View All Cars";
        cout << "\n2. View Available Cars";
        cout << "\n3. Rent a Car";
        cout << "\n4. Return a Car";
        cout << "\n0. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: showCars(); break;
        case 2: showCars(true); break;
        case 3: rentCar(); break;
        case 4: returnCar(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
