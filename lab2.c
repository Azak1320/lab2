#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This part just defines the structure to hold part information. It's like a record in memory.
typedef struct {
    int part_number;
    char *part_name;
    float part_size;
    char *part_size_metric;
    float part_cost;
} Part;

Part *database = NULL; // Pointer to the start of our database starts off as empty.
int num_records = 0; // Keeps track of how many records there are.


// Function to resize the memory on our own since we aren't using realloc.
void resize_memory(int new_size) {
    Part *new_database;
    int i;
    
    // Allocating new memory. This will be the new database and its bigger.
    new_database = (Part *)malloc(new_size * sizeof(Part)); 
    
    if (new_database == NULL) {
        printf("memory allocation failed! Exiting \n");
        return; // If memory can't be allocated, we just quit
    }
    
    // Manually copying data from old memory to new memory
    for (i = 0; i < num_records && i < new_size; i++) {
        new_database[i] = database[i]; // Copy each record over
    }
    
    // Free the old memory because we don't need it anymore
    free(database);
    database = new_database; // Now the database points to the new memory.
}

//  adds a new record to the database
void add_record() {
    char temp[100]; // space to hold user input (it is temporarty).
    
    // Resizes memory so we have space for the new record
    resize_memory(num_records + 1);
    
    printf("Enter part number: ");
    scanf("%d", &database[num_records].part_number);
    
    printf("Enter part name: ");
    scanf(" %99[^\n]", temp); // Read input until newline.
    database[num_records].part_name = strdup(temp); // Stores the string this is the allocated memory
    
    printf("Enter part size: ");
    scanf("%f", &database[num_records].part_size);
    
    printf("Enter part size metric (e.g., mm, cm): ");
    scanf(" %99[^\n]", temp); 
    database[num_records].part_size_metric = strdup(temp);
    
    printf("Enter part cost: ");
    scanf("%f", &database[num_records].part_cost);
    
    num_records++; // added a record so add the count.
    printf("Record added \n");
}

// deletes the last record 
void delete_record() {
    if (num_records == 0) {
        printf("No records to delete \n");
        return; // If no records are there it will just return
    }
    
    // Frees memory for the last record's strings
    free(database[num_records - 1].part_name);
    free(database[num_records - 1].part_size_metric);
    
    // Resize memory to make the database smaller. Does that by removing the last record
    if (num_records == 1) {
        free(database);
        database = NULL; // If it’s the last record it will go ahead and free the whole database
    } else {
        resize_memory(num_records - 1);
    }
    num_records--; // decreases the record count
    printf("Last record deleted\n");
}

// prints all stored records
void print_records() {
    int i;
    if (num_records == 0) {
        printf("No records to print Database is empty.\n");
        return; // there is nothing to print if there are no records
    }
    
    // Prints out all records stored in memory
    for (i = 0; i < num_records; i++) {
        printf("Part Number: %d\n", database[i].part_number);
        printf("Part Name: %s\n", database[i].part_name);
        printf("Part Size: %.2f %s\n", database[i].part_size, database[i].part_size_metric);
        printf("Part Cost: $%.2f\n", database[i].part_cost);
        printf("---------------------\n");
    }
}

// prints how many records are stored in the database
void print_num_records() {
    printf("Number of records: %d\n", num_records);
}

// prints the total memory size used by the database
void print_memory_size() {
    printf("Total memory used: %zu bytes\n", num_records * sizeof(Part));
}

// frees up all allocated memory before exiting the program
void free_memory() {
    int i;
    for (i = 0; i < num_records; i++) {
        free(database[i].part_name);
        free(database[i].part_size_metric);
    }
    free(database); // frees the whole database memory
    printf("Memory freed\n");
}

// shows the menu and handles user input
void menu() {
    int choice;
    while (1) {
        // Shows the menu and asks the user for input
        printf("\nMENU\n");
        printf("1. Print all records\n");
        printf("2. Print number of records\n");
        printf("3. Print size of database\n");
        printf("4. Add record\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        // looks at the user's choice
        if (choice == 1) {
            print_records();
        } else if (choice == 2) {
            print_num_records();
        } else if (choice == 3) {
            print_memory_size();
        } else if (choice == 4) {
            add_record();
        } else if (choice == 5) {
            delete_record();
        } else if (choice == 6) {
            free_memory(); // Clean up memory before exiting the program
            printf("Exiting\n");
            break;
        } else {
            printf("wrong choice. Try again\n");
        }
    }
}


int main() {
    menu(); // Show the menu and start talking to user
    return 0;
}