#include <iostream>
#include <string>
#include <vector>
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
    }
};

class Inventory
{
private:
    vector<Product> products;
    vector<Supplier> suppliers;
    vector<Order> orders;

public:
    void addProduct()
    {
        int id, quantity;
        string name;
        double price;

        cout << "Enter product ID: ";
        cin >> id;
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter product quantity: ";
        cin >> quantity;
        cout << "Enter product price: ";
        cin >> price;

        products.push_back(Product(id, name, quantity, price));
        cout << "Product added successfully!" << endl;
    }

    void addSupplier()
    {
        int id;
        string name, contact;

        cout << "Enter supplier ID: ";
        cin >> id;
        cout << "Enter supplier name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter supplier contact: ";
        getline(cin, contact);

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
        cout << "Order placed successfully!" << endl;
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

    void updateProductQuantity()
    {
        int id, newQuantity;
        cout << "Enter product ID to update quantity: ";
        cin >> id;
        cout << "Enter new quantity: ";
        cin >> newQuantity;

        for (Product &product : products)
        {
            if (product.id == id)
            {
                product.quantity = newQuantity;
                cout << "Product quantity updated successfully!" << endl;
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
        cout << "2. Add Supplier\n";
        cout << "3. Place Order\n";
        cout << "4. Remove Product\n";
        cout << "5. Update Product Quantity\n";
        cout << "6. Remove Supplier\n";
        cout << "7. Update Supplier Details\n";
        cout << "8. Display Inventory\n";
        cout << "9. Display Suppliers\n";
        cout << "10. Display Pending Orders\n";
        cout << "11. Display Completed Orders\n";
        cout << "12. Complete Order\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inventory.addProduct();
            break;
        case 2:
            inventory.addSupplier();
            break;
        case 3:
            inventory.placeOrder();
            break;
        case 4:
            inventory.removeProduct();
            break;
        case 5:
            inventory.updateProductQuantity();
            break;
        case 6:
            inventory.removeSupplier();
            break;
        case 7:
            inventory.updateSupplier();
            break;
        case 8:
            inventory.displayInventory();
            break;
        case 9:
            inventory.displaySuppliers();
            break;
        case 10:
            inventory.displayPendingOrders();
            break;
        case 11:
            inventory.displayCompletedOrders();
            break;
        case 12:
            inventory.completeOrder();
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