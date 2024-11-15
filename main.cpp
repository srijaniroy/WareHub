#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class Product
{
public:
    int id;
    string name;
    int quantity;
    double price;

    Product(int _id, string _name, int _quantity, double _price)
    {
        id = _id;
        name = _name;
        quantity = _quantity;
        price = _price;
    }

    void displayProduct()
    {
        cout << "ID: " << id << ", Name: " << name
             << ", Quantity: " << quantity << ", Price: Rs. " << price << endl;
    }
};

class Supplier
{
public:
    int id;
    string name;
    string contact;

    Supplier(int _id, string _name, string _contact)
    {
        id = _id;
        name = _name;
        contact = _contact;
    }

    void displaySupplier()
    {
        cout << "Supplier ID: " << id << ", Name: " << name
             << ", Contact: " << contact << endl;
    }
};

class Order
{
public:
    int orderId;
    Supplier supplier;
    vector<Product> productsOrdered;
    string status;

    Order(int _orderId, Supplier _supplier, vector<Product> _productsOrdered)
        : orderId(_orderId), supplier(_supplier), productsOrdered(_productsOrdered), status("Pending") {}

    double calculateTotal()
    {
        double total = 0.0;
        for (const Product &product : productsOrdered)
        {
            total += product.price * product.quantity;
        }
        return total;
    }

    void displayOrder()
    {
        cout << "\n--- Order ID: " << orderId << " ---\n";
        supplier.displaySupplier();
        cout << "Status: " << status << endl;
        cout << "Products in this order:" << endl;
        for (Product &product : productsOrdered)
        {
            product.displayProduct();
        }
        cout << "Total Amount: Rs. " << calculateTotal() << endl;
    }
};

class Inventory
{
private:
    vector<Product> products;
    vector<Supplier> suppliers;
    vector<Order> orders;

public:
    int getValidInteger()
    {
        int value;
        while (true)
        {
            cin >> value;
            if (cin.fail() || value < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer: ";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    double getValidDouble()
    {
        double value;
        while (true)
        {
            cin >> value;
            if (cin.fail() || value < 0.0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number: ";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    template <typename T>
    bool isIdUnique(int id, const vector<T> &items) const
    {
        for (const auto &item : items)
        {
            if (item.id == id)
            {
                return false;
            }
        }
        return true;
    }

    void addProduct()
    {
        int id, quantity;
        string name;
        double price;

        cout << "Enter product ID: ";
        cin >> id;
        while (!isIdUnique(id, products))
        {
            cout << "Product ID already exists. Enter a unique ID: ";
            cin >> id;
        }
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter product quantity: ";
        quantity = getValidInteger();
        cout << "Enter product price: ";
        price = getValidDouble();

        products.push_back(Product(id, name, quantity, price));
        cout << "Product added successfully!" << endl;
    }

    bool isValidContact(string contact)
    {
        if (contact.length() != 10)
            return false;
        for (char c : contact)
        {
            if (!isdigit(c))
                return false;
        }
        return true;
    }

    void addSupplier()
    {
        int id;
        string name, contact;

        cout << "Enter supplier ID: ";
        cin >> id;
        while (!isIdUnique(id, suppliers))
        {
            cout << "Supplier ID already exists. Enter a unique ID: ";
            cin >> id;
        }
        cout << "Enter supplier name: ";
        cin.ignore();
        getline(cin, name);
        while (true)
        {
            cout << "Enter supplier contact (10 digits): ";
            getline(cin, contact);
            if (isValidContact(contact))
            {
                break;
            }
            else
            {
                cout << "Invalid contact number. Please enter exactly 10 digits." << endl;
            }
        }

        suppliers.push_back(Supplier(id, name, contact));
        cout << "Supplier added successfully!" << endl;
    }

    void updateSupplier()
    {
        int id;
        cout << "Enter supplier ID to update: ";
        cin >> id;

        for (Supplier &supplier : suppliers)
        {
            if (supplier.id == id)
            {
                cout << "Enter new supplier name: ";
                cin.ignore();
                getline(cin, supplier.name);
                cout << "Enter new supplier contact: ";
                getline(cin, supplier.contact);
                cout << "Supplier details updated successfully!" << endl;
                return;
            }
        }
        cout << "Supplier with ID " << id << " not found." << endl;
    }

    void removeSupplier()
    {
        int id;
        cout << "Enter supplier ID to remove: ";
        cin >> id;

        for (auto it = suppliers.begin(); it != suppliers.end(); ++it)
        {
            if (it->id == id)
            {
                suppliers.erase(it);
                cout << "Supplier removed successfully!" << endl;
                return;
            }
        }
        cout << "Supplier with ID " << id << " not found." << endl;
    }

    void placeOrder()
    {
        int supplierId, orderId, productId, quantity;
        vector<Product> orderProducts;
        Supplier orderSupplier(0, "", "");

        cout << "Enter supplier ID for the order: ";
        cin >> supplierId;

        bool supplierFound = false;
        for (Supplier &supplier : suppliers)
        {
            if (supplier.id == supplierId)
            {
                orderSupplier = supplier;
                supplierFound = true;
                break;
            }
        }

        if (!supplierFound)
        {
            cout << "Supplier not found!" << endl;
            return;
        }

        cout << "Enter order ID: ";
        cin >> orderId;

        char choice;
        do
        {
            cout << "Enter product ID to order: ";
            cin >> productId;
            cout << "Enter quantity to order: ";
            cin >> quantity;

            bool productFound = false;
            for (Product &product : products)
            {
                if (product.id == productId)
                {

                    if (product.quantity >= quantity)
                    {
                        product.quantity -= quantity;
                        orderProducts.push_back(Product(productId, product.name, quantity, product.price));
                        cout << "Product added to the order." << endl;
                    }
                    else
                    {
                        cout << "Insufficient quantity in stock!" << endl;
                    }
                    productFound = true;
                    break;
                }
            }

            if (!productFound)
            {
                cout << "Product not found!" << endl;
            }

            cout << "Do you want to add more products to the order? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        orders.push_back(Order(orderId, orderSupplier, orderProducts));
        double totalAmount = orders.back().calculateTotal();
        cout << "Order placed successfully!" << endl;
        cout << "Total Amount: Rs. " << totalAmount << endl;
    }

    void completeOrder()
    {
        int orderId;
        cout << "Enter order ID to mark as completed: ";
        cin >> orderId;

        for (Order &order : orders)
        {
            if (order.orderId == orderId)
            {
                if (order.status == "Pending")
                {
                    order.status = "Completed";
                    cout << "Order marked as completed successfully!" << endl;
                }
                else
                {
                    cout << "Order is already completed." << endl;
                }
                return;
            }
        }
        cout << "Order with ID " << orderId << " not found." << endl;
    }

    void removeProduct()
    {
        int id;
        cout << "Enter product ID to remove: ";
        cin >> id;

        for (auto it = products.begin(); it != products.end(); ++it)
        {
            if (it->id == id)
            {
                products.erase(it);
                cout << "Product removed successfully!" << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void updateProductDetails()
    {
        int id;
        cout << "Enter product ID to update: ";
        cin >> id;

        for (Product &product : products)
        {
            if (product.id == id)
            {
                double newPrice;
                int newQuantity;

                cout << "Current Price: Rs. " << product.price << endl;
                cout << "Enter new price: ";
                cin >> newPrice;

                cout << "Current Quantity: " << product.quantity << endl;
                cout << "Enter new quantity: ";
                cin >> newQuantity;

                product.price = newPrice;
                product.quantity = newQuantity;

                cout << "Product details updated successfully!" << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void displayInventory()
    {
        if (products.empty())
        {
            cout << "Inventory is empty." << endl;
            return;
        }

        cout << "\nCurrent Inventory:" << endl;
        for (Product &product : products)
        {
            product.displayProduct();
        }
    }

    void displaySuppliers()
    {
        if (suppliers.empty())
        {
            cout << "No suppliers found." << endl;
            return;
        }

        cout << "\n--- All Suppliers ---" << endl;
        for (Supplier &supplier : suppliers)
        {
            supplier.displaySupplier();
        }
    }

    void displayPendingOrders()
    {
        bool hasPendingOrders = false;

        cout << "\n--- Pending Orders ---" << endl;
        for (Order &order : orders)
        {
            if (order.status == "Pending")
            {
                order.displayOrder();
                hasPendingOrders = true;
            }
        }

        if (!hasPendingOrders)
        {
            cout << "No pending orders." << endl;
        }
    }

    void displayCompletedOrders()
    {
        bool hasCompletedOrders = false;

        cout << "\n--- Completed Orders ---" << endl;
        for (Order &order : orders)
        {
            if (order.status == "Completed")
            {
                order.displayOrder();
                hasCompletedOrders = true;
            }
        }

        if (!hasCompletedOrders)
        {
            cout << "No completed orders." << endl;
        }
    }
};

int main()
{
    Inventory inventory;
    int choice;

    while (true)
    {
        cout << "\n--- Inventory Management System ---\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Update Product Details\n";
        cout << "4. Display Inventory\n";
        cout << "5. Add Supplier\n";
        cout << "6. Remove Supplier\n";
        cout << "7. Update Supplier Details\n";
        cout << "8. Display Suppliers\n";
        cout << "9. Place Order\n";
        cout << "10. Complete Order\n";
        cout << "11. Display Pending Orders\n";
        cout << "12. Display Completed Orders\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 13." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            inventory.addProduct();
            break;
        case 2:
            inventory.removeProduct();
            break;
        case 3:
            inventory.updateProductDetails();
            break;
        case 4:
            inventory.displayInventory();
            break;
        case 5:
            inventory.addSupplier();
            break;
        case 6:
            inventory.removeSupplier();
            break;
        case 7:
            inventory.updateSupplier();
            break;
        case 8:
            inventory.displaySuppliers();
            break;
        case 9:
            inventory.placeOrder();
            break;
        case 10:
            inventory.completeOrder();
            break;
        case 11:
            inventory.displayPendingOrders();
            break;
        case 12:
            inventory.displayCompletedOrders();
            break;
        case 13:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}