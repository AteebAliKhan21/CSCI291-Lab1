/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h> 
#include <stdlib.h>

// Defining constants for minimum and maximum quantities of each item
#define MIN_A 3
#define MIN_B 3
#define MIN_C 3
#define MAX_A 20
#define MAX_B 20
#define MAX_C 20

float price_A = 3.5;  // Setting prices of each item
float price_B = 4.5;
float price_C = 5.5;
int qty_A = 10;
int qty_B = 10;
int qty_C = 10; // Setting quantity of each item
int password = 12345;             
float total = 0.0; // For admin mode total sales tracking

void purchase_product();
void admin_mode();                    

int main() {
    int choice;

    while (1) { // Infinite loop to allow program to run again after each operation
        printf("VENDING MACHINE\n");  // Display the main menu options
        printf("1 - PURCHASE A PRODUCT\n");  // Option to purchase products
        printf("2 - ADMIN MODE\n");  // Admin mode for replenishing stocks etc
        printf("3 - EXIT\n"); 
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);

        switch(choice){  // switch statement used to perform each function based on user choice
            case 1:
                purchase_product();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("GOODBYE\n");
                return 0;
            default:
                printf("INVALID CHOICE\n");
        }

        printf("\n"); // Adds a blank line before the menu appears again
    }
}

void purchase_product() {  // Function executes when user selects to purchase a product
    int type;
    float price;
    float paid=0.0;
    float coins;  // For handling payment input

    printf("------PRODUCTS AVAILABLE------\n");
    printf("1 - Coffee | PRICE: %.2f | QTY: %d\n", price_A, qty_A);
    printf("2 - Water | PRICE: %.2f | QTY: %d\n", price_B, qty_B);
    printf("3 - Panadol | PRICE: %.2f | QTY: %d\n", price_C, qty_C);
    printf("0 - CANCEL\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &type);  // Displays available products and lets user select one

    switch(type){
        case 1:
            // Check if Coffee quantity is below minimum before purchase
            if (qty_A < MIN_A) {
                printf("ERROR: Coffee is below minimum stock level. Please choose another item.\n");
                return;
            }
            price = price_A;
            printf("YOU SELECTED Coffee (%.2f AED)\n", price_A);
            break;

        case 2:
            // Check if Water quantity is below minimum before purchase
            if (qty_B < MIN_B) {
                printf("ERROR: Water is below minimum stock level. Please choose another item.\n");
                return;
            }
            price = price_B;
            printf("YOU SELECTED Water (%.2f AED)\n", price_B);
            break;

        case 3:
            // Check if Panadol quantity is below minimum before purchase
            if (qty_C < MIN_C) {
                printf("ERROR: Panadol is below minimum stock level. Please choose another item.\n");
                return;
            }
            price = price_C;
            printf("YOU SELECTED Panadol (%.2f AED)\n", price_C);
            break;

        case 0:
            printf("PURCHASE CANCELLED\n");
            return;
        default:
            printf("INVALID SELECTION\n");
            return;  // Displays what the user has selected and its price
    }

    // While loop for user to keep inserting coins until amount is covered
    while (paid < price) {         
        printf("AMOUNT DUE: %.2f\n", price - paid);
        printf("INSERT COINS - AED 1, AED 0.5, OR AED 0.25: ");
        scanf("%f", &coins);
        if (coins == 1.0 || coins == 0.5 || coins == 0.25)
            paid += coins;
        else
            printf("INVALID COIN! ACCEPTED: 1, 0.5, 0.25\n");
    }

    // Handle the change or thank user for exact payment
    if (paid > price)
        printf("THE CHANGE IS: %.2f\n", paid - price);
    else
        printf("PAID EXACT AMOUNT. THANK YOU!\n");

    total += price;  // Increments the total for admin mode display

    // Decrease the product quantity after purchase
    if (type == 1) qty_A--;
    else if (type == 2) qty_B--;
    else if (type == 3) qty_C--;

    printf("DISPENSING PRODUCT...\n");
    printf("THANK YOU FOR YOUR PURCHASE!\n\n");
}

void admin_mode() {  // Function for admin access and management
    int admin_pass;
    int choice;
    printf("ENTER THE PASSWORD: ");
    scanf("%d", &admin_pass);

    if (admin_pass == password) {
        printf("ACCESS GRANTED\n");
        printf("SELECT ADMIN OPTION:\n");
        printf("1 - REPLENISH STOCK\n");
        printf("2 - CHANGE PRICE\n");
        printf("3 - DISPLAY TOTAL SALES\n");
        printf("4 - ITEM DISPLAY\n");
        scanf("%d", &choice);
       
        switch(choice){
            case 1:   
                // Randomly replenishes each item up to maximum value
                qty_A += (rand()%20)+1;
                qty_B += (rand()%20)+1;
                qty_C += (rand()%20)+1;
                printf("All items are restocked\n");
                break;

            case 2:  
                // Allows admin to change item prices
                printf("ENTER NEW PRICE FOR Coffee: ");
                scanf("%f", &price_A);
                printf("ENTER NEW PRICE FOR Water: ");
                scanf("%f", &price_B);
                printf("ENTER NEW PRICE FOR Panadol: ");
                scanf("%f", &price_C);
                printf("PRICES UPDATED SUCCESSFULLY\n");
                break;

            case 3:
            {
                // Displays total sales and gives option to reset
                char money_reset;
                printf("THE TOTAL SALES ARE: %.2f\n", total);
                printf("RESET THE MONEY TO ZERO AND COLLECT THE MONEY? (Y/N): ");
                scanf(" %c", &money_reset);
                if (money_reset=='Y' || money_reset=='y'){
                    total=0;
                    printf("DONE - COLLECT MONEY\n");
                } else
                    printf("DONE\n");
            }
            break;

            case 4:
                // Displays all items, their prices, and quantity left
                printf("------ITEM DISPLAY------\n");
                printf("Coffee | PRICE: %.2f | QTY: %d", price_A, qty_A);
                if (qty_A < MIN_A) printf(" [LOW STOCK]");
                printf("\nWater | PRICE: %.2f | QTY: %d", price_B, qty_B);
                if (qty_B < MIN_B) printf(" [LOW STOCK]");
                printf("\nPanadol | PRICE: %.2f | QTY: %d", price_C, qty_C);
                if (qty_C < MIN_C) printf(" [LOW STOCK]");
                printf("\n");
                break;

            default:
                printf("INVALID ADMIN OPTION\n");
        }
    }    
    else {
        printf("ACCESS DENIED! WRONG PASSWORD\n");
    }
}
