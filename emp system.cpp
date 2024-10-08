 #include <stdio.h>
#include <stdlib.h>

// Define the structure for an employee
typedef struct Employee {
    int empID;
    char empName[50];
    float empSalary;
    struct Employee* left;
    struct Employee* right;
} Employee;

// Function to create a new employee node
Employee* createEmployee(int id, char name[], float salary) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    newEmployee->empID = id;
    strcpy(newEmployee->empName, name);
    newEmployee->empSalary = salary;
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee into the BST
Employee* insertEmployee(Employee* root, int id, char name[], float salary) {
    if (root == NULL) {
        return createEmployee(id, name, salary);
    }

    if (id < root->empID) {
        root->left = insertEmployee(root->left, id, name, salary);
    } else if (id > root->empID) {
        root->right = insertEmployee(root->right, id, name, salary);
    }

    return root;
}

// Function to search for an employee by their ID
Employee* searchEmployee(Employee* root, int id) {
    if (root == NULL || root->empID == id) {
        return root;
    }

    if (id < root->empID) {
        return searchEmployee(root->left, id);
    } else {
        return searchEmployee(root->right, id);
    }
}

// Function to find the minimum employee in the BST (used in delete operation)
Employee* findMinEmployee(Employee* node) {
    Employee* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete an employee from the BST
Employee* deleteEmployee(Employee* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->empID) {
        root->left = deleteEmployee(root->left, id);
    } else if (id > root->empID) {
        root->right = deleteEmployee(root->right, id);
    } else {
        if (root->left == NULL) {
            Employee* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Employee* temp = root->left;
            free(root);
            return temp;
        }

        Employee* temp = findMinEmployee(root->right);
        root->empID = temp->empID;
        root->right = deleteEmployee(root->right, temp->empID);
    }

    return root;
}

// Function to display employee details
void displayEmployee(Employee* employee) {
    if (employee != NULL) {
        printf("Employee ID: %d\n", employee->empID);
        printf("Employee Name: %s\n", employee->empName);
        printf("Employee Salary: %.2f\n", employee->empSalary);
    } else {
        printf("Employee not found.\n");
    }
}

// Function to compute salary for an employee (dummy example)
float computeSalary(Employee* employee) {
    // Replace this with your salary computation logic
    // For simplicity, we assume salary is stored in the employee node.
    return employee->empSalary;
}

int main() {
    Employee* root = NULL;
    int choice, id;
    char name[50];
    float salary;

    while (1) {
        printf("\nEmployee Management System Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employee\n");
        printf("5. Compute Salary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Employee Name: ");
                scanf(" %49[^\n]", name);  // Read up to 49 characters for the name
                printf("Enter Employee Salary: ");
                scanf("%f", &salary);
                root = insertEmployee(root, id, name, salary);
                break;

            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                Employee* foundEmployee = searchEmployee(root, id);
                printf("Search Result:\n");
                displayEmployee(foundEmployee);
                break;

            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                root = deleteEmployee(root, id);
                break;

            case 4:
                printf("Enter Employee ID to display: ");
                scanf("%d", &id);
                Employee* employeeToDisplay = searchEmployee(root, id);
                displayEmployee(employeeToDisplay);
                break;

            case 5:
                printf("Enter Employee ID to compute salary: ");
                scanf("%d", &id);
                Employee* employeeToComputeSalary = searchEmployee(root, id);
                float salary = computeSalary(employeeToComputeSalary);
                printf("Computed Salary: %.2f\n", salary);
                break;

            case 6:
                // Exit the program
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
