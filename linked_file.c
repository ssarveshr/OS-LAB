#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100

typedef struct Block {
    int blockNumber;
    struct Block *next;
} Block;

typedef struct File {
    char fileName[100];
    Block *startBlock;
} File;

File files[MAX_BLOCKS];
int fileCount = 0;
int availableBlocks[MAX_BLOCKS]; // 0 means free, 1 means allocated

void initializeBlocks() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        availableBlocks[i] = 0; // All blocks are initially free
    }
}

Block *allocateBlocks(int numBlocks) {
    Block *head = NULL, *tail = NULL;
    for (int i = 0; i < MAX_BLOCKS && numBlocks > 0; i++) {
        if (availableBlocks[i] == 0) {
            Block *newBlock = (Block *)malloc(sizeof(Block));
            newBlock->blockNumber = i;
            newBlock->next = NULL;

            if (head == NULL) {
                head = newBlock;
            } else {
                tail->next = newBlock;
            }
            tail = newBlock;

            availableBlocks[i] = 1; // Mark block as allocated
            numBlocks--;
        }
    }

    if (numBlocks > 0) {
        printf("Not enough free blocks available.\n");
        return NULL;
    }
    return head;
}

void createFile(char *fileName, int numBlocks) {
    if (fileCount >= MAX_BLOCKS) {
        printf("Maximum file limit reached.\n");
        return;
    }

    Block *allocatedBlocks = allocateBlocks(numBlocks);
    if (allocatedBlocks == NULL) {
        printf("File '%s' creation failed.\n", fileName);
        return;
    }

    strcpy(files[fileCount].fileName, fileName);
    files[fileCount].startBlock = allocatedBlocks;
    fileCount++;

    printf("File '%s' created successfully with %d blocks.\n", fileName, numBlocks);
}

void deleteFile(char *fileName) {
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].fileName, fileName) == 0) {
            Block *current = files[i].startBlock;
            while (current != NULL) {
                availableBlocks[current->blockNumber] = 0; // Mark block as free
                Block *temp = current;
                current = current->next;
                free(temp);
            }

            // Shift remaining files
            for (int j = i; j < fileCount - 1; j++) {
                files[j] = files[j + 1];
            }
            fileCount--;

            printf("File '%s' deleted successfully.\n", fileName);
            return;
        }
    }
    printf("File '%s' not found.\n", fileName);
}

void displayFile(char *fileName) {
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].fileName, fileName) == 0) {
            printf("File '%s' is allocated the following blocks:\n", fileName);

            Block *current = files[i].startBlock;
            while (current != NULL) {
                printf("%d -> ", current->blockNumber);
                current = current->next;
            }
            printf("NULL\n");
            return;
        }
    }
    printf("File '%s' not found.\n", fileName);
}

void displayAllFiles() {
    if (fileCount == 0) {
        printf("No files created.\n");
        return;
    }

    printf("Files and their allocated blocks:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("File: %s\nBlocks: ", files[i].fileName);

        Block *current = files[i].startBlock;
        while (current != NULL) {
            printf("%d -> ", current->blockNumber);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, numBlocks;
    char fileName[100];
    initializeBlocks();

    while (1) {
        printf("\nLinked File Allocation Menu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Display File\n");
        printf("4. Display All Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter number of blocks required: ");
                scanf("%d", &numBlocks);
                createFile(fileName, numBlocks);
                break;
            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", fileName);
                deleteFile(fileName);
                break;
            case 3:
                printf("Enter file name to display: ");
                scanf("%s", fileName);
                displayFile(fileName);
                break;
            case 4:
                displayAllFiles();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
