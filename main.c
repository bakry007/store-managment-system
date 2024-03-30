#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

typedef struct {
    char name[50];
    float price;
    int quantity;
    char category[50];
} Product;

typedef struct {
    char name[50];
} Category;

COORD coord = {0, 0};

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void addCategory(Category categories[], int *categoryCount) {
    system("cls");
    printf("Enter the name of the category: ");
    scanf("%s", categories[*categoryCount].name);
    (*categoryCount)++;
    printf("Category added successfully.\n");
    system("pause");
}

void addProduct(Product products[], int *productCount, Category categories[], int categoryCount) {
    system("cls");

    if (categoryCount == 0) {
        printf("Error: No categories available. Please add a category first.\n");
        system("pause");
        return;
    }

    printf("Enter the name of the product: ");
    scanf("%s", products[*productCount].name);

    printf("Enter the price of the product: ");
    scanf("%f", &products[*productCount].price);

    printf("Enter the quantity of the product (must be greater than 0): ");
    scanf("%d", &products[*productCount].quantity);

    while (products[*productCount].quantity <= 0) {
        printf("Invalid quantity. Please enter a quantity greater than 0: ");
        scanf("%d", &products[*productCount].quantity);
    }

    printf("Enter the category of the product: ");
    char productCategory[50];
    scanf("%s", productCategory);

    int categoryIndex = -1;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].name, productCategory) == 0) {
            categoryIndex = i;
            break;
        }
    }

    if (categoryIndex == -1) {
        printf("Error: The specified category does not exist. Please choose a valid category.\n");
        system("pause");
        return;
    }

    strcpy(products[*productCount].category, productCategory);

    (*productCount)++;
    printf("Product added successfully.\n");
    system("pause");
}


void showCategories(Category categories[], int categoryCount) {
    system("cls");
    printf("Categories:\n");

    if (categoryCount == 0) {
        printf("No categories available.\n");
    } else {
        for (int i = 0; i < categoryCount; i++) {
            printf("%s\n", categories[i].name);
        }
    }

    system("pause");
}

void showProducts(Product products[], int productCount) {
    system("cls");
    printf("Products:\n");

    if (productCount == 0) {
        printf("No products available.\n");
    } else {
        for (int i = 0; i < productCount; i++) {
            printf("Name: %s, Price: %.2f, Quantity: %d, Category: %s\n",
                   products[i].name, products[i].price, products[i].quantity, products[i].category);
        }
    }

    system("pause");
}

void moveProduct(Product products[], int productCount, Category categories[], int categoryCount) {
    system("cls");

    if (productCount == 0) {
        printf("Error: No products available. Please add a product first.\n");
        system("pause");
        return;
    }

    if (categoryCount < 2) {
        printf("Error: You need at least two categories to move a product between categories. Please add more categories.\n");
        system("pause");
        return;
    }

    printf("Enter the name of the product to move: ");
    char productName[50];
    scanf("%s", productName);

    int productIndex = -1;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("Error: Product not found.\n");
        system("pause");
        return;
    }

    printf("Enter the new category for the product: ");
    char newCategory[50];
    scanf("%s", newCategory);

    int newCategoryIndex = -1;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].name, newCategory) == 0) {
            newCategoryIndex = i;
            break;
        }
    }

    if (newCategoryIndex == -1) {
        printf("Error: The specified category does not exist. Please choose a valid category.\n");
        system("pause");
        return;
    }

    strcpy(products[productIndex].category, newCategory);

    printf("Product moved successfully.\n");
    system("pause");
}


void sellProduct(Product products[], int productCount) {
    system("cls");

    if (productCount == 0) {
        printf("Error: No products available. Please add a product first.\n");
        system("pause");
        return;
    }

    printf("Enter the name of the product to sell: ");
    char productName[50];
    scanf("%s", productName);

    int productIndex = -1;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("Error: Product not found.\n");
        system("pause");
        return;
    }

    int quantityToSell;
    printf("Enter the quantity to sell: ");
    scanf("%d", &quantityToSell);

    if (quantityToSell <= 0 || quantityToSell > products[productIndex].quantity) {
        printf("Error: Invalid quantity to sell.\n");
        system("pause");
        return;
    }

    products[productIndex].quantity -= quantityToSell;

    printf("Product sold successfully.\n");
    system("pause");
}

int main() {
    int choice = 1;
    int maxChoice = 7;
    int ch;

    Category categories[100];
    int categoryCount = 0;

    Product products[100];
    int productCount = 0;

    while (1) {
        system("cls");

        gotoxy(30, 5);
        SetColor(14);
        printf("Simple System For Store Management");
        SetColor(15);

        char *menuOptions[] = {
            "Add Category",
            "Add Product",
            "Show Categories",
            "Show Products",
            "Move Product",
            "Sell Product",
            "Exit"
        };

        for (int i = 1; i <= maxChoice; i++) {
            gotoxy(30, 6 + i);
            if (i == choice) {
                SetColor(12);
            } else {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);
            printf("%s", menuOptions[i - 1]);
        }

        gotoxy(30, 14);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch) {
            case 72:
                if (choice > 1) {
                    choice--;
                }
                break;
            case 80:
                if (choice < maxChoice) {
                    choice++;
                }
                break;
            case 13:
                switch (choice) {
                    case 1:
                        addCategory(categories, &categoryCount);
                        break;
                    case 2:
                        addProduct(products, &productCount, categories, categoryCount);
                        break;
                    case 3:
                        showCategories(categories, categoryCount);
                        break;
                    case 4:
                        showProducts(products, productCount);
                        break;
                    case 5:
                        moveProduct(products, productCount, categories, categoryCount);
                        break;
                    case 6:
                        sellProduct(products, productCount);
                        break;
                    case 7:
                        exit(0);
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    return 0;
}
