#include <stdio.h>
#include <limits.h>
#include <string.h>
// Define the maximum value for an unsigned integer to prevent overflow
const unsigned int value = UINT_MAX;

#define MIN_REQUIRED_LEVEL 3
#define STR_LIMIT 50
#define DB_SIZE 3 


struct Employee {
    char name[50];      // Employee's full name
    short access_lvl;   // Security clearance level (1-10)
    unsigned int id;    // Unique employee identification number
};

// Custom input function to securely parse unsigned integers
int my_scanf(unsigned int *ptr){
    unsigned int total = 0; // Accumulator for the parsed integer
    int c = getchar(); // Read the first character from stdin

    // Loop until End Of File (EOF) is reached
    while (c != EOF ){
        // Check if the character is a digit (0-9)
        if (c >= '0' && c <= '9'){
            c = c - '0'; // Convert ASCII character to integer value
            
            // Overflow protection check:
            // We want to ensure that (total * 10 + c) <= value (UINT_MAX).
            // Rearranging the inequality to avoid overflow during the check itself:
            // total <= (value - c) / 10
            if (total <= (value - c)/10){
                total = (total * 10) + c; // Update total safely
                c = getchar(); // Read the next character
            }
            else{
                // If overflow would occur, warn the user and flush the input buffer
                printf("Overflow detected! Discarding excess input.\n");
                while (c != '\n' && c != EOF) {
                    c = getchar(); // Consume remaining characters on the line
                }
                return 3; // Exit the loop as the input is invalid/complete

            }
        }
        // Handle whitespace: skip spaces and tabs
        else if(c == ' ' || c == '\t'){
            c = getchar();
            continue;
        }
        // If a non-digit, non-whitespace character (like newline) is found, stop parsing
        else if(c == '\n'){
            break;
        }
        else{
            // Invalid character encountered, flush the input buffer
            printf("Invalid character detected! Discarding excess input.\n");
            while (c != '\n' && c != EOF) {
                c = getchar(); // Consume remaining characters on the line
            }
            return 3; // Exit the loop as the input is invalid/complete
        }
    
    }
    *ptr = total; // Store the accumulated result in the provided pointer address
    return 1;
}

// Function to safely read a string from stdin, avoiding buffer overflows and invalid characters
char* get_string_safe(char *buffer){
    int c = getchar(); // Read the first character
    int i = 0; // Index for the buffer

    // Loop until EOF or newline is encountered
    while (c != EOF && c != '\n'){
        if (c == '\t'){
            c = getchar(); // Skip tabs
            continue;
        }
        // Check if the character is a digit (names shouldn't have numbers here)
        else if ((c>='0' && c<='9')){
            printf("Invalid Username\n");
            while (c != '\n' && c != EOF) {
                c = getchar(); // Consume remaining characters on the line
            }
            return NULL;
        }
        else{
            // Check if there is space in the buffer
            if (i < STR_LIMIT - 1){
                buffer[i] = c; // Store the character
                i++;
                c= getchar(); // Read the next character
            }
            else{
                printf("Overflow detected! Discarding excess input.\n");
                while (c != '\n' && c != EOF) {
                    c = getchar(); // Consume remaining characters on the line
                }
                return NULL; // Exit the loop as the input is invalid/complete
            }
        }
    }
    buffer[i] = '\0'; // Null-terminate the string
    // If no characters were read (empty input)
    if (i==0){
        return NULL;
    }
    return buffer;
}

// Function to check if the employee has sufficient privileges
void process_entry(struct Employee *emp){
    printf("\n--- AUTHENTICATING: %s ---\n", emp->name);

    // Compare employee's access level against the minimum required
    if (emp->access_lvl < MIN_REQUIRED_LEVEL){
        printf("[ACCESS DENIED] Clearance Level %d required. \n", MIN_REQUIRED_LEVEL);

    }
    else{
        printf("[ACCESS GRANTED] Welcome, Officer %s.\n", emp->name);
    }

}

int main(){
    // Initialize the database with some dummy employee data
    struct Employee Database[DB_SIZE] = {
        {"Alice Gabriel", 5, 1001 },  
        {"Bob Chen", 1, 1002 },
        {"Charlie Grey", 7, 1003}
    };
    unsigned int id;
    char name[STR_LIMIT];
    short found = 0; // Flag to track if the user is found in the database

    printf("--- SECURE TERMINAL ACTIVE ---\n");
    printf("Enter Name: \n");
    // Read the name securely
    if(get_string_safe(name) == NULL){
        printf("[CRITICAL ERROR] Invalid Input format");
        return 1;
    }

    printf("Enter Employee ID: \n");
    
    // Read the ID securely
    if(my_scanf(&id) == 3){
        printf("[CRITICAL ERROR] Invalid Input format");
        return 1;
    }

    else{
        printf("Checking Database for User credentials\n");

        // Iterate through the database to find a matching record
        for (short i=0; i<DB_SIZE; i++){
            // Check if both name and ID match
            if (strcmp(Database[i].name, name) == 0 && Database[i].id==id){
                printf("MATCH FOUND\n");
                printf("CHECKING ACCESS ENTRY\n");
                process_entry(&Database[i]);
                found = 1; // Mark as found
                break; // Exit the loop
            }
        }

        // If no match was found after checking the entire database
        if (found == 0){
            printf("[LOGIN ERROR] EMPLOYEE NOT FOUND IN DATABASE");
        }

        return 0;

    }

}