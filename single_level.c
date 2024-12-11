#include <stdio.h>
#include <string.h>
#define MAX_FILES 100

struct File 
{
    char name[30];
};

struct File directory[MAX_FILES];
int fileCount = 0;

// Function to add a file to the directory
void addFile() 
{
    if (fileCount >= MAX_FILES) 
    {
        printf("Directory is full. Cannot add more files.\n");
        return;
    }
    char filename[30];
    printf("Enter file name: ");
    scanf("%s", filename);

    // Check for duplicate filenames
    for (int i = 0; i < fileCount; i++) 
    {
        if (strcmp(directory[i].name, filename) == 0) 
        {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(directory[fileCount].name, filename);
    fileCount++;
    printf("File added successfully.\n");
}

// Function to display all files
void listFiles() 
{
    if (fileCount == 0) 
    {
        printf("Directory is empty.\n");
        return;
    }

    printf("Files in the directory:\n");
    for (int i = 0; i < fileCount; i++) 
    {
        printf("%d. %s\n", i + 1, directory[i].name);
    }
}

// Function to delete a file
void deleteFile() 
{
    if (fileCount == 0) 
    {
        printf("Directory is empty. No files to delete.\n");
        return;
    }

    char filename[30];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    int found = 0;
    for (int i = 0; i < fileCount; i++) 
    {
        if (strcmp(directory[i].name, filename) == 0) 
        {
            found = 1;
            for (int j = i; j < fileCount - 1; j++) 
            {
                strcpy(directory[j].name, directory[j + 1].name);
            }
            fileCount--;
            printf("File deleted successfully.\n");
            break;
        }
    }

    if (!found) 
    {
        printf("File not found.\n");
    }
}

// Main function
int main() 
{
    int choice;
    while (1) 
    {
        printf("\nSingle Level Directory:\n");
        printf("1. Add File\n");
        printf("2. List Files\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFile();
                break;
            case 2:
                listFiles();
                break;
            case 3:
                deleteFile();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
