#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir on POSIX systems


/* This program contains a Human + AI coded in C database,
Storage capacity is unknown. */


#define MAX_INPUT_LENGTH 256 // Max item length is 256 characters
#define MAX_GROUP_NAME 64 // Max groups 64
#define DATABASE_DIR "groups" //Defines the function of "Groups"

// Function to create the base directory if it doesn't exist
void create_database_directory() {
    struct stat st = {0};
    if (stat(DATABASE_DIR, &st) == -1) {
        #ifdef _WIN32
            // For Windows
            _mkdir(DATABASE_DIR);
        #else
            // For POSIX systems (Linux, macOS)
            mkdir(DATABASE_DIR, 0700);
        #endif
    }
}

// Function to create a new group file
void create_group(const char *group_name) {
    char file_path[MAX_INPUT_LENGTH];
    sprintf(file_path, "%s/%s.txt", DATABASE_DIR, group_name);

    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Error creating group file");
    } else {
        printf("Group '%s' created successfully.\n", group_name);
        fclose(file);
    }
}

// Function to add an item to a specific group file
void add_item_to_group(const char *group_name, const char *item) {
    char file_path[MAX_INPUT_LENGTH];
    sprintf(file_path, "%s/%s.txt", DATABASE_DIR, group_name);

    FILE *file = fopen(file_path, "a"); // "a" for append mode
    if (file == NULL) {
        printf("Error: Group '%s' does not exist.\n", group_name);
    } else {
        fprintf(file, "%s\n", item);
        printf("'%s' added to group '%s'.\n", item, group_name);
        fclose(file);
    }
}

// Function to view all items in a group file
void view_group_items(const char *group_name) {
    char file_path[MAX_INPUT_LENGTH];
    sprintf(file_path, "%s/%s.txt", DATABASE_DIR, group_name);

    FILE *file = fopen(file_path, "r"); // "r" for read mode
    if (file == NULL) {
        printf("Error: Group '%s' does not exist.\n", group_name);
        return;
    }

    char line[MAX_INPUT_LENGTH];
    printf("\n--- Items in Group '%s' ---\n", group_name);
    while (fgets(line, sizeof(line), file)) {
        printf("- %s", line); // line already contains a newline
    }
   // printf("---------------------------\n");

    fclose(file);
}

// Function to check if an item exists in a specific group file
void check_item_in_group(const char *group_name, const char *item) {
    char file_path[MAX_INPUT_LENGTH];
    sprintf(file_path, "%s/%s.txt", DATABASE_DIR, group_name);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: Group '%s' does not exist.\n", group_name);
        return;
    }

    char line[MAX_INPUT_LENGTH];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strcmp(item, line) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);
    if (found) {
        printf("The item '%s' is in group '%s'.\n", item, group_name);
    } else {
        printf("The item '%s' was not found in group '%s'.\n", item, group_name);
    }
}

int main() {
    create_database_directory();

    char group_name[MAX_GROUP_NAME];
    char item_name[MAX_INPUT_LENGTH];
    int choice;

    while (1) {
        printf("\n--- The Archives ---\n");
        printf("\n--- Database Menu ---\n");
        printf("1. Create a new group\n");
        printf("2. Add an item to a group\n");
        printf("3. View all items in a group\n");
        printf("4. Check if an item exists in a group\n");
        printf("5. Exit\n");
        printf("Enter your choice (The Number listed next to it): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear the trailing newline

        switch (choice) {
            case 1:
                printf("Enter the name for the new group: ");
                fgets(group_name, sizeof(group_name), stdin);
                group_name[strcspn(group_name, "\n")] = 0;
                create_group(group_name);
                break;
            case 2:
                printf("Enter the group name: ");
                fgets(group_name, sizeof(group_name), stdin);
                group_name[strcspn(group_name, "\n")] = 0;
                printf("Enter the item to add: ");
                fgets(item_name, sizeof(item_name), stdin);
                item_name[strcspn(item_name, "\n")] = 0;
                add_item_to_group(group_name, item_name);
                break;
            case 3:
                printf("Enter the group name to view: ");
                fgets(group_name, sizeof(group_name), stdin);
                group_name[strcspn(group_name, "\n")] = 0;
                view_group_items(group_name);
                break;
            case 4:
                printf("Enter the group name: ");
                fgets(group_name, sizeof(group_name), stdin);
                group_name[strcspn(group_name, "\n")] = 0;
                printf("Enter the item to check: ");
                fgets(item_name, sizeof(item_name), stdin);
                item_name[strcspn(item_name, "\n")] = 0;
                check_item_in_group(group_name, item_name);
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        
        
        printf("Not official copyright\n");
        printf("\n");
        
        
        
    }

    return 0;
}
