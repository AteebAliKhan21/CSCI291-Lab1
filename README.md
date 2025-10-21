/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h> // Defining constants
#include <stdlib.h>
#define MIN_A 3
#define MIN_B 3
#define MIN_C 3
#define MAX_A 20                   
#define MAX_B 20
#define MAX_C 20

float price_A = 3.5; //Setting prices of each item
float price_B = 4.5;                    
float price_C = 5.5;

int qty_A = 10;
int qty_B = 10;
int qty_C = 10; // Setting quantity of each item

int password = 12345;             
float total = 0.0; // For admin mode 
 
void purchase_product();
void admin_mode();                                 

int main() {
    int choice;
    printf("VENDING MACHINE\n"); //Display each choice that gets displayed on the vending machine
    printf("1 - PURCHASE A PRODUCT\n"); //Admin mode for replenishing stocks etc
    printf("2 - ADMIN MODE\n");                 
    printf("3 - EXIT\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch(choice){ //switch statement used on choice to perform each function i.e, purchasing and admin mode 
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
            return 0;
    }
}

void purchase_product() { //The function is if the user has selected to purchase a product
    int type;
    float price;
    float paid=0.0;
    float coins; //For the payment and for admin mode
   
    printf("------PRODUCTS AVAILABLE------\n");
    printf("1 - Coffee | PRICE: %.2f | QTY: %d\n", price_A, qty_A);
    printf("2 - Water | PRICE: %.2f | QTY: %d\n", price_B, qty_B);
    printf("3 - Panadol | PRICE: %.2f | QTY: %d\n", price_C, qty_C);
    printf("0 - CANCEL\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &type); //displays the products on display and their price

    switch(type){
        case 1:
            price = price_A;
            printf("YOU SELECTED Coffee(%.2f AED)\n", price_A);
            break;
        case 2:
            price = price_B;
            printf("YOU SELECTED Water (%.2f AED)\n", price_B);
            break;
        case 3:
            price = price_C;
            printf("YOU SELECTED Panadol (%.2f AED)\n", price_C);
            break;
        case 0:
            printf("PURCHASE CANCELLED\n");
            return;
        default:
            printf("INVALID SELECTION\n");
            return; //Displays what the user has selected as the item and also their price for them to pay
    }

    while (paid < price) {         
        printf("AMOUNT DUE: %.2f\n", price - paid);
        printf("INSERT COINS - AED 1, AED 0.5, OR AED 0.25: ");
        scanf("%f", &coins);
        if (coins == 1.0 || coins == 0.5 || coins == 0.25)
            paid += coins;
        else
            printf("INVALID COIN! ACCEPTED: 1, 0.5, 0.25\n");
    } //while loop is used for the user to keep entering the coins until the price is paid for or more than paid for

    if (paid > price)
        printf("THE CHANGE IS: %.2f\n", paid - price);
    else//handles the change 
        printf("PAID EXACT AMOUNT. THANK YOU!\n");

    total += price;
    //increments the total for admin mode display
    if (type == 1)qty_A--;
    else if (type == 2) qty_B--;
    else if (type == 3) qty_C--;
    //accounts for the change in product quantity when a user has purchased,user post decrement for accuracy
    printf("DISPENSING PRODUCT...\n");
    printf("THANK YOU FOR YOUR PURCHASE!\n\n");
}
    
    
void admin_mode() { //admin mode code starts here 
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
            case 1:   //randomly restocks the items from 1-20
                qty_A+=(rand()%20)+1;
                qty_B+=(rand()%20)+1;
                qty_C+=(rand()%20)+1;
                printf("All items are restocked ");
                break;

            case 2: 
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
                    char money_reset;
                    printf("THE TOTAL SALES ARE: %.2f\n", total);
                    printf("RESET THE MONEY TO ZERO AND COLLECT THE MONEY? (Y/N): ");
                    scanf(" %c", &money_reset); // Added space before %c to handle newline
                    if (money_reset=='Y' || money_reset=='y'){
                        total=0;
                        printf("DONE - COLLECT MONEY\n");
                    } else
                        printf("DONE\n");
                }
                break;
        
            case 4:    
                printf("------ITEM DISPLAY------\n");   //displays price and quantity
                printf("Coffee | PRICE: %.2f | QTY: %d\n", price_A, qty_A);
                printf("Water | PRICE: %.2f | QTY: %d\n", price_B, qty_B);
                printf("Panadol | PRICE: %.2f | QTY: %d\n", price_C, qty_C);
                break;

            default:
                printf("INVALID ADMIN OPTION\n");
        }
    }    
    else {
        printf("ACCESS DENIED! WRONG PASSWORD\n");
    }
}
