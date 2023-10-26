#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> 
// Task structure
typedef struct Task {
    char description[100];  
    char dueDate[20];       
    bool isDone;            
    time_t timestamp;       
    struct Task* next;     
} Task;

// To-Do List structure (using a queue)
typedef struct ToDoList {
    Task* front;  
    Task* rear;   
} ToDoList;

// Function to create a new task
Task* createTask(char description[], char dueDate[]) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newTask->description, description);
    strcpy(newTask->dueDate, dueDate);
    newTask->isDone = false;
    newTask->timestamp = time(NULL); 
    newTask->next = NULL;
    return newTask;
}

// Function to initialize the to-do list
void initializeToDoList(ToDoList* list) {
    list->front = list->rear = NULL;
}

// Function to add a task to the to-do list
void addTask(ToDoList* list) {
    char description[100];  
    char dueDate[20];       

    printf("Enter task description: ");
    getchar();  
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = '\0';  

    printf("Enter due date: ");
    fgets(dueDate, sizeof(dueDate), stdin);
    dueDate[strcspn(dueDate, "\n")] = '\0';  

    Task* newTask = createTask(description, dueDate);
    if (list->rear == NULL) {
        list->front = list->rear = newTask;
    } else {
        list->rear->next = newTask;
        list->rear = newTask;
    }
    printf("Task added successfully.\n");
}

// Function to mark a task as done by index
void markTaskDone(ToDoList* list, int index) {
    Task* current = list->front;
    Task* previous = NULL;
    int i = 1;

    while (current != NULL && i < index) {
        previous = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Task with index %d not found.\n", index);
    } else {
        current->isDone = true;
        printf("Task %d marked as done: %s\n", index, current->description);
    }
}

// Function to delete a task by index
void deleteTask(ToDoList* list, int index) {
    Task* current = list->front;
    Task* previous = NULL;
    int i = 1;

    while (current != NULL && i < index) {
        previous = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Task with index %d not found.\n", index);
    } else {
        
        if (previous == NULL) {
            list->front = current->next;
            
            if (current == list->rear) {
                list->rear = NULL;
            }
        } else {
            previous->next = current->next;
            

            if (current == list->rear) {
                list->rear = previous;
            }
        }

        free(current); 
        printf("Task %d deleted: %s\n", index, current->description);
    }
}


void displayToDoList(ToDoList* list) {
    Task* current = list->front;
    int index = 1;
    if (current == NULL) {
        printf("To-Do List is empty.\n");
        return;
    }

    printf("-------------------------------------------------------------\n");
    printf("|  Index  |  Description                |  Due Date    |  Status  |  Timestamp             |\n");
    printf("-------------------------------------------------------------\n");

    while (current != NULL) {
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&current->timestamp));
        printf("|   %2d   |  %-26s  |  %-11s  |  %s  |  %s  |\n", index, current->description, current->dueDate, current->isDone ? "Done" : "Not Done", timestamp);
        current = current->next;
        index++;
    }

    printf("-------------------------------------------------------------\n");
}

int main() {
    ToDoList list;
    initializeToDoList(&list);
    int choice;
    int index; 

    while (1) {
        printf("Menu:\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Done\n");
        printf("3. Delete Task\n"); 
        printf("4. Display To-Do List\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&list);
                break;
            case 2:
                displayToDoList(&list);
                printf("Enter the index of the task you want to mark as done: ");
                scanf("%d", &index);
                markTaskDone(&list, index);
                break;
            case 3:
                displayToDoList(&list);
                printf("Enter the index of the task you want to delete: ");
                scanf("%d", &index);
                deleteTask(&list, index);
                break;
            case 4:
                displayToDoList(&list);
                break;
            case 5:
                exit(0); 
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
