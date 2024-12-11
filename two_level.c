#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10

// Structure to represent a file
struct File 
{
    char name[30];
};

// Structure to represent a user directory
struct UserDirectory 
{
    char username[30];
    struct File files[MAX_FILES];
    int fileCount;
} users[MAX_USERS];

int userCount = 0;

// Function to add a user
void addUser() 
{
    if (userCount >= MAX_USERS) 
    {
        printf("Maximum number of users reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    users[userCount].fileCount = 0;
    userCount++;
    printf("User added successfully.\n");
}

// Function to add a file for a specific user
void addFile() 
{
    char username[30], filename[30];
    printf("Enter username: ");
    scanf("%s", username);

    // Find the user
    for (int i = 0; i < userCount; i++) 
    {
        if (strcmp(users[i].username, username) == 0) 
        {
            if (users[i].fileCount >= MAX_FILES) 
            {
                printf("User's directory is full. Cannot add more files.\n");
                return;
            }

            printf("Enter file name: ");
            scanf("%s", filename);

            // Check for duplicate files
            for (int j = 0; j < users[i].fileCount; j++) 
            {
                if (strcmp(users[i].files[j].name, filename) == 0) 
                {
                    printf("File already exists.\n");
                    return;
                }
            }

            strcpy(users[i].files[users[i].fileCount].name, filename);
            users[i].fileCount++;
            printf("File added successfully.\n");
            return;
        }
    }

    printf("User not found.\n");
}

// Function to list all files of a specific user
void listFiles() 
{
    char username[30];
    printf("Enter username: ");
    scanf("%s", username);

    // Find the user
    for (int i = 0; i < userCount; i++) 
    {
        if (strcmp(users[i].username, username) == 0) 
        {
            if (users[i].fileCount == 0) 
            {
                printf("No files found for user %s.\n", username);
            } 
            else 
            {
                printf("Files of user %s:\n", username);
                for (int j = 0; j < users[i].fileCount; j++) 
                {
                    printf("%d. %s\n", j + 1, users[i].files[j].name);
                }
            }
            return;
        }
    }

    printf("User not found.\n");
}

// Main function
int main() 
{
    int choice;

    while (1) 
    {
        printf("\nTwo-Level Directory:\n");
        printf("1. Add User\n");
        printf("2. Add File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addUser();
                break;
            case 2:
                addFile();
                break;
            case 3:
                listFiles();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}