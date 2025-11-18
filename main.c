#include <stdio.h>

#define MAX 20

// Global arrays for product data
int productID[MAX];
int quantity[MAX];
float price[MAX];
int n = 0;   // number of products

// Function Prototypes
void addProduct();
void searchProduct();
void updateQuantity();
void rackReport();
void stockValueReport();
void displayAll();

// Utility function
int findProduct(int id);

int main() {
    int choice;

    while(1) {
        printf("\n===== SMART WAREHOUSE ANALYTICS SYSTEM =====\n");
        printf("1. Add Product\n");
        printf("2. Search Product\n");
        printf("3. Update Quantity\n");
        printf("4. Generate Rack Report (3x3 Matrix)\n");
        printf("5. Calculate Stock Value for Each Product\n");
        printf("6. Display All Products\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: updateQuantity(); break;
            case 4: rackReport(); break;
            case 5: stockValueReport(); break;
            case 6: displayAll(); break;
            case 7: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Find product index by ID
int findProduct(int id) {
    for(int i = 0; i < n; i++) {
        if(productID[i] == id)
            return i;
    }
    return -1;
}

// 1. Add Product
void addProduct() {
    if(n >= MAX) {
        printf("Warehouse full! Cannot add more.\n");
        return;
    }

    int id, qty;
    float pr;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    // Check duplicate ID
    if(findProduct(id) != -1) {
        printf("Error: Duplicate Product ID!\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &qty);

    printf("Enter Price: ");
    scanf("%f", &pr);

    if(qty <= 0 || pr <= 0) {
        printf("Error: Quantity & Price must be positive!\n");
        return;
    }

    productID[n] = id;
    quantity[n] = qty;
    price[n] = pr;
    n++;

    printf("Product Added Successfully!\n");
}

// 2. Search Product
void searchProduct() {
    int id;
    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);

    int index = findProduct(id);

    if(index == -1) {
        printf("Product Not Found!\n");
    } else {
        printf("\nPRODUCT FOUND:\n");
        printf("ID: %d\n", productID[index]);
        printf("Quantity: %d\n", quantity[index]);
        printf("Price: %.2f\n", price[index]);
    }
}

// 3. Update Quantity
void updateQuantity() {
    int id, choice, amt;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    int index = findProduct(id);
    if(index == -1) {
        printf("Product Not Found!\n");
        return;
    }

    printf("1. Increase Stock\n");
    printf("2. Decrease Stock\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter amount: ");
    scanf("%d", &amt);

    if(choice == 1) {
        quantity[index] += amt;
        printf("Stock increased successfully!\n");
    }
    else if(choice == 2) {
        if(quantity[index] - amt < 0) {
            printf("Error: Quantity cannot be negative!\n");
        } else {
            quantity[index] -= amt;
            printf("Stock decreased successfully!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}

// 4. Rack Report (3x3 Matrix)
void rackReport() {
    int rack[3][3];
    int max = -1, min = 999999;
    int maxR=0, maxC=0, minR=0, minC=0;
    int total = 0;

    printf("\nEnter 3x3 Rack Matrix (numeric stock values):\n");
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            scanf("%d", &rack[i][j]);
            total += rack[i][j];

            if(rack[i][j] > max) {
                max = rack[i][j];
                maxR = i; maxC = j;
            }

            if(rack[i][j] < min) {
                min = rack[i][j];
                minR = i; minC = j;
            }
        }
    }

    printf("\n=== RACK REPORT ===\n");
    printf("Maximum Stock: %d at (%d, %d)\n", max, maxR, maxC);
    printf("Minimum Stock: %d at (%d, %d)\n", min, minR, minC);
    printf("Total Items in Racks: %d\n", total);
}

// 5. Stock Value Analysis
void stockValueReport() {
    if(n == 0) {
        printf("No products available!\n");
        return;
    }

    float stockVal[MAX];
    float max = -1, min = 999999, total=0;
    int maxIndex=0, minIndex=0;

    printf("\nID\tQty\tPrice\tStockValue\n");

    for(int i=0; i<n; i++) {
        stockVal[i] = quantity[i] * price[i];
        printf("%d\t%d\t%.2f\t%.2f\n",
               productID[i], quantity[i], price[i], stockVal[i]);

        if(stockVal[i] > max) {
            max = stockVal[i];
            maxIndex = i;
        }
        if(stockVal[i] < min) {
            min = stockVal[i];
            minIndex = i;
        }

        total += stockVal[i];
    }

    printf("\nHighest Stock Value: %d (%.2f)\n", productID[maxIndex], max);
    printf("Lowest Stock Value: %d (%.2f)\n", productID[minIndex], min);
    printf("Total Warehouse Value: %.2f\n", total);
}

// 6. Display All Products
void displayAll() {
    if(n == 0) {
        printf("No products to display!\n");
        return;
    }

    printf("\nID\tQuantity\tPrice\tStockValue\n");

    for(int i = 0; i < n; i++) {
        float val = quantity[i] * price[i];
        printf("%d\t%d\t\t%.2f\t%.2f\n",
               productID[i], quantity[i], price[i], val);
    }
}

