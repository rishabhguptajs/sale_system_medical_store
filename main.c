#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Admin {
    char name[20];
    char username[20];
    char password[20];
    char contactInfo[50];
    char permissions[100];
};


struct Staff {
    int staffID;
    char name[50];
    char username[20];
    char password[20];
    char contactInfo[50];
    char permissions[100];
    struct Staff *next;
};

struct Customer {
    int customerID;
    char name[50];
    char username[20];
    char password[20];
    char contactInfo[50];
    struct Customer *next;};

struct Medicine {
    int medicineID;
    char name[50];
    char manufacturer[50];
    int quantity;
    float price;
    struct Medicine *next;
};

struct Admin admin = {
        .name = "Rishabh",
        .username = "rishabhguptajs",
        .password = "RG@&05",
        .contactInfo = "9889069688",
        .permissions = "Full Control"
};

void addStaff(struct Staff **staffList, int *staffCount);
void addCustomer(struct Customer **customerList, int *customerCount);
void displayAdmins(const struct Admin *adminList);
void displayStaff(const struct Staff *staffList);
void displayCustomers(const struct Customer *customerList);
int validateAdminLogin(struct Admin *admin, const char *enteredUsername, const char *enteredPassword);
void addAdmin(struct Admin **adminList, int *adminCount, const char *name, const char *username, const char *password, const char *contactInfo);
void manageStaff(struct Staff **staffList, int *staffCount);
void manageCustomers(struct Customer **customerList, int *customerCount);
void manageInventory(struct Medicine **medicineList, int *medicineCount);
void addMedicine(struct Medicine **medicineList, int *medicineCount);
void deleteMedicine(struct Medicine **medicineList);

int main() {
    struct Admin *adminList = NULL;
    struct Staff *staffList = NULL;
    struct Customer *customerList = NULL;
    struct Medicine *medicineList = NULL;
    int loggedInAsAdmin = 0;
    int staffCount = 0;
    int customerCount = 0;
    int medicineCount = 0;

    int choice;

    printf("Welcome to the Sales System for a Medical Store\n");

    while (1) {
        printf("\nMain Menu:\n");
        if (!loggedInAsAdmin) {
            printf("-> Login as Admin\n");
        } else {
            printf("-> Logout\n");
            printf("-> Access Admin Panel\n");
        }
        printf("-> Login as Staff\n");
        printf("-> Login as Customer\n");
        printf("-> Exit - Enter 6 to exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (!loggedInAsAdmin) {
                    char enteredUsername[20];
                    char enteredPassword[20];
                    printf("Enter username: ");
                    scanf("%s", enteredUsername);
                    printf("Enter password: ");
                    scanf("%s", enteredPassword);

                    if (validateAdminLogin(&admin, enteredUsername, enteredPassword)) {
                        printf("Admin logged in successfully.\n");
                        loggedInAsAdmin = 1;
                    } else {
                        printf("Invalid username or password.\n");
                    }
                } else {
                    loggedInAsAdmin = 0;
                    printf("Admin logged out.\n");
                }
                break;
            case 2:
                if (loggedInAsAdmin) {
                    int adminChoice;
                    printf("Admin Panel\n");
                    printf("1. Manage Staff\n");
                    printf("2. Manage Customers\n");
                    printf("3. Manage Inventory\n");
                    printf("4. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);

                    switch (adminChoice) {
                        case 1:
                            manageStaff(&staffList, &staffCount);
                            break;
                        case 2:
                            manageCustomers(&customerList, &customerCount);
                            break;
                        case 3:
                            manageInventory(&medicineList, &medicineCount);
                            break;
                        case 4:
                            // Logout
                            loggedInAsAdmin = 0;
                            printf("Admin logged out.\n");
                            break;
                        default:
                            printf("Invalid choice. Please select a valid option.\n");
                    }
                } else {
                    printf("You must be logged in as an admin to access the admin panel.\n");
                }
                break;
            case 3:
                if (loggedInAsAdmin) {
                    manageStaff(&staffList, &staffCount);
                } else {
                    printf("You must be logged in as admin to manage staff.\n");
                }
                break;
            case 4:
                if (loggedInAsAdmin) {
                    manageCustomers(&customerList, &customerCount);
                } else {
                    printf("You must be logged in as admin to manage customers.\n");
                }
                break;
            case 5:
                if (loggedInAsAdmin) {
                    manageInventory(&medicineList, &medicineCount);
                } else {
                    printf("You must be logged in as admin to manage inventory.\n");
                }
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}

void manageStaff(struct Staff **staffList, int *staffCount) {
    int staffChoice;
    printf("Manage Staff:\n");
    printf("1. Add Staff\n");
    printf("2. Display Staff\n");
    printf("Enter your choice: ");
    scanf("%d", &staffChoice);

    switch (staffChoice) {
        case 1:
            addStaff(staffList, staffCount);
            break;
        case 2:
            displayStaff(*staffList);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void manageCustomers(struct Customer **customerList, int *customerCount) {
    int customerChoice;
    printf("Manage Customers:\n");
    printf("1. Add Customer\n");
    printf("2. Display Customers\n");
    printf("Enter your choice: ");
    scanf("%d", &customerChoice);

    switch (customerChoice) {
        case 1:
            addCustomer(customerList, customerCount);
            break;
        case 2:
            displayCustomers(*customerList);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void manageInventory(struct Medicine **medicineList, int *medicineCount) {
    int inventoryChoice;

    printf("\nInventory Menu:\n");
    printf("1. Add Medicine\n");
    printf("2. Delete Medicine\n");
    printf("3. Display Medicines\n");
    printf("4. Go Back to Main Menu\n");

    printf("Enter your choice: ");
    scanf("%d", &inventoryChoice);

    switch (inventoryChoice) {
        case 1:
            addMedicine(medicineList, medicineCount);
            break;
        case 2:
            deleteMedicine(medicineList);
            break;
        case 3:
            displayMedicines(*medicineList);
            break;
        case 4:
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// existing code...

void addStaff(struct Staff **staffList, int *staffCount) {
    struct Staff *newStaff = (struct Staff *)malloc(sizeof(struct Staff));
    if (newStaff == NULL) {
        printf("Memory allocation failed for staff.\n");
        return;
    }

    newStaff->staffID = ++(*staffCount);

    printf("Username: ");
    scanf(" %[^\n]", newStaff->username);

    printf("Password: ");
    scanf(" %[^\n]", newStaff->password);

    printf("Contact Info: ");
    scanf(" %[^\n]", newStaff->contactInfo);

    printf("Permissions: ");
    scanf(" %[^\n]", newStaff->permissions);

    newStaff->next = *staffList;
    *staffList = newStaff;

    printf("Staff member added successfully.\n");
}

void addCustomer(struct Customer **customerList, int *customerCount) {
    struct Customer *newCustomer = (struct Customer *)malloc(sizeof(struct Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed for customer.\n");
        return;
    }

    newCustomer->customerID = ++(*customerCount);

    printf("Enter customer details:\n");
    printf("Name: ");
    scanf("%s", newCustomer->name);
    printf("Username: ");
    scanf("%s", newCustomer->username);
    printf("Password: ");
    scanf("%s", newCustomer->password);
    printf("Contact Info: ");
    scanf("%s", newCustomer->contactInfo);

    newCustomer->next = *customerList;
    *customerList = newCustomer;

    printf("Customer added successfully.\n");
}

void displayStaff(const struct Staff *staffList) {
    printf("\nStaff Members:\n");
    while (staffList != NULL) {
        printf("Staff ID: %d\n", staffList->staffID);
        printf("Name: %s\n", staffList->name);
        printf("Username: %s\n", staffList->username);
        printf("Contact Info: %s\n", staffList->contactInfo);
        printf("Permissions: %s\n", staffList->permissions);
        printf("\n");
        staffList = staffList->next;
    }
}

void displayCustomers(const struct Customer *customerList) {
    printf("\nCustomers:\n");
    while (customerList != NULL) {
        printf("Customer ID: %d\n", customerList->customerID);
        printf("Name: %s\n", customerList->name);
        printf("Username: %s\n", customerList->username);
        printf("Contact Info: %s\n", customerList->contactInfo);
        printf("\n");
        customerList = customerList->next;
    }
}

void addMedicine(struct Medicine **medicineList, int *medicineCount) {
    struct Medicine *newMedicine = (struct Medicine *)malloc(sizeof(struct Medicine));
    if (newMedicine == NULL) {
        printf("Memory allocation failed for the new medicine.\n");
        return;
    }

    newMedicine->medicineID = ++(*medicineCount);

    printf("Enter medicine details:\n");
    printf("Name: ");
    scanf("%s", newMedicine->name);
    printf("Manufacturer: ");
    scanf("%s", newMedicine->manufacturer);
    printf("Quantity: ");
    scanf("%d", &newMedicine->quantity);
    printf("Price: ");
    scanf("%f", &newMedicine->price);

    newMedicine->next = *medicineList;
    *medicineList = newMedicine;

    printf("Medicine added to inventory.\n");
}

void displayMedicines(const struct Medicine *medicineList) {
    printf("\nMedicine Inventory:\n");
    while (medicineList != NULL) {
        printf("Medicine ID: %d\n", medicineList->medicineID);
        printf("Name: %s\n", medicineList->name);
        printf("Manufacturer: %s\n", medicineList->manufacturer);
        printf("Quantity: %d\n", medicineList->quantity);
        printf("Price: %.2f\n", medicineList->price);
        printf("\n");
        medicineList = medicineList->next;
    }
}
void deleteMedicine(struct Medicine **medicineList) {
    if (*medicineList == NULL) {
        printf("Inventory is empty. No medicine to delete.\n");
        return;
    }

    int medicineID;
    printf("Enter the ID of the medicine to delete: ");
    scanf("%d", &medicineID);

    struct Medicine *currentMedicine = *medicineList;
    struct Medicine *prevMedicine = NULL;

    while (currentMedicine != NULL && currentMedicine->medicineID != medicineID) {
        prevMedicine = currentMedicine;
        currentMedicine = currentMedicine->next;
    }

    if (currentMedicine == NULL) {
        printf("Medicine with ID %d not found in inventory.\n", medicineID);
        return;
    }

    if (prevMedicine == NULL) {
        // Deleting the first node
        *medicineList = currentMedicine->next;
    } else {
        prevMedicine->next = currentMedicine->next;
    }

    free(currentMedicine);
    printf("Medicine with ID %d deleted from inventory.\n", medicineID);
}
int validateAdminLogin(struct Admin *admin, const char *enteredUsername, const char *enteredPassword) {
    if (strcmp(enteredUsername, admin->username) == 0 && strcmp(enteredPassword, admin->password) == 0) {
        return 1;
    }
    return 0;
}
