#include <iostream>
#include <string>
#include <vector>

class Property {
public:
    Property(const std::string& address, const std::string& name, double price)
        : address(address), name(name), price(price) {}

    const std::string& getAddress() const {
        return address;
    }

    double getPrice() const {
        return price;
    }

private:
    std::string address;
    std::string name;
    double price;
};

class Owner {
public:
    Owner(int id, const std::string& firstName, const std::string& lastName, double balance)
        : id(id), firstName(firstName), lastName(lastName), balance(balance) {}

    int getID() const {
        return id;
    }

    void addProperty(Property* property) {
        properties.push_back(property);
    }

    void transferProperty(Owner& otherOwner, Property* property, double price) {
        if (balance >= price) {
            balance -= price;
            otherOwner.balance += price;

            // Find and remove the property from the current owner
            for (auto it = properties.begin(); it != properties.end(); ++it) {
                if (*it == property) {
                    properties.erase(it);
                    break;
                }
            }

            // Add the property to the other owner
            otherOwner.addProperty(property);
        }
        else {
            std::cout << "Insufficient balance to transfer property." << std::endl;
        }
    }

    void displayProperties() const {
        std::cout << "Properties owned by Owner " << id << ":\n";
        for (const auto& property : properties) {
            std::cout << "Address: " << property->getAddress() << ", Price: " << property->getPrice() << std::endl;
        }
    }

private:
    int id;
    std::string firstName;
    std::string lastName;
    double balance;
    std::vector<Property*> properties;
};

int main() {
    // Create properties
    Property property1("123 Main St", "Property 1", 100000.0);
    Property property2("456 Elm St", "Property 2", 75000.0);

    // Create owners
    Owner owner1(1, "John", "Doe", 50000.0);
    Owner owner2(2, "Jane", "Smith", 75000.0);

    // Owners acquire properties
    owner1.addProperty(&property1);
    owner2.addProperty(&property2);

    std::cout << "Before transfer:\n";
    owner1.displayProperties();
    owner2.displayProperties();

    // Transfer property from owner1 to owner2
    owner1.transferProperty(owner2, &property1, property1.getPrice());

    std::cout << "\nAfter transfer:\n";
    owner1.displayProperties();
    owner2.displayProperties();

    return 0;
}
