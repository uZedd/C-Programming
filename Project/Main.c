#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct temp
{
    double value;
    struct temp* next;
} Temperature;

typedef struct room
{
    char* name;
    Temperature* temperatures;
    struct room* next;
} Room;


int input(char* string);
void fix_string(char* string);

void free_rooms(Room* head);
Room* read_csv(const char* filename);
Room* find_room(Room* head, const char* name);
Room* create_room(const char* name);


Room* find_room(Room* head, const char* name)
{
    while (head != NULL && strcmp(head->name, name) != 0)
    {
        head = head->next;
    }

    return head;
}


Room* create_room(const char* name)
{
    Room* new_room = malloc(sizeof(Room));
    if (new_room == NULL)
    {
        return NULL;
    }

    new_room->name = malloc(strlen(name) + 1);
    if (new_room->name == NULL)
    {
        free(new_room);
        return NULL;
    }

    strcpy(new_room->name, name);
    new_room->temperatures = NULL;
    new_room->next = NULL;

    return new_room;
}


int load_temperatures(const char* filename, Room* room)
{
    FILE* f = fopen(filename, "r");
    if (f == NULL)
    {
        return 0;
    }

    char line[100];
    Temperature* tail = NULL;

    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f) != NULL)
    {
        double temperature;
        char room_name[50];

        if (sscanf(line, "%lf,%49[^\r\n]", &temperature, room_name) == 2)
        {
            if (strcmp(room->name, room_name) == 0)
            {
                Temperature* new_temp = malloc(sizeof(Temperature));
                if (new_temp == NULL)
                {
                    fclose(f);
                    return 0;
                }

                new_temp->value = temperature;
                new_temp->next = NULL;

                if (room->temperatures == NULL)
                {
                    room->temperatures = new_temp;
                }
                else
                {
                    tail->next = new_temp;
                }

                tail = new_temp;
            }
        }
    }

    fclose(f);
    return 1;
}

Room* read_csv(const char* filename)
{
    Room* head = NULL;
    Room* tail = NULL;

    FILE* f = fopen(filename, "r");
    if (f == NULL)
    {
        return NULL;
    }

    char line[100];
    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f) != NULL)
    {
        double temperature;
        char room_name[50];

        if (sscanf(line, "%lf,%49[^\r\n]", &temperature, room_name) == 2)
        {
            if (find_room(head, room_name) == NULL)
            {
                Room* new_room = create_room(room_name);

                if (new_room == NULL)
                {
                    fclose(f);
                    free_rooms(head);
                    return NULL;
                }

                if (load_temperatures(filename, new_room) == 0)
                {
                    fclose(f);
                    free_rooms(new_room);
                    free_rooms(head);
                    return NULL;
                }

                if (head == NULL)
                {
                    head = new_room;
                }
                else
                {
                    tail->next = new_room;
                }

                tail = new_room;
            }
        }
    }

    fclose(f);
    return head;
}

void free_rooms(Room* head)
{
    while (head != NULL)
    {
        Room* next_room = head->next;
        Temperature* temp = head->temperatures;

        while (temp != NULL)
        {
            Temperature* next_temp = temp->next;
            free(temp);
            temp = next_temp;
        }

        free(head->name);
        free(head);
        head = next_room;
    }
}


// Function that takes a query message, prints it for the user and then takes their input
int input(char* string, char* answer)
{
    printf("%s\n", string);

    char fetch[100];
    if (fgets(fetch, 100, stdin) == NULL)
    {
        return 0;
    }
    fix_string(fetch);

    answer = fetch;

    return 1;
}


// Function to fix char arrays mainly fetched with fgets. Deletes the newline and inserts a null operator to the end.
void fix_string(char* string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
    return;
}


int main(void)
{
    Room* head = read_csv("Temperatures.csv");

    if (head == NULL)
    {
        printf("Error reading CSV file.\n");
        return 1;
    }


    printf("Available rooms:\n");

    Room* tail = head;
    while (tail != NULL)
    {
        printf("- %s\n", tail->name);
        tail = tail->next;
    }


    char answer[50];

    if (input("Enter room name:", answer, sizeof(answer)) == 0)
    {
        free_rooms(head);
        return 1;
    }


    Room* selected_room = find_room(head, answer);

    if (selected_room == NULL)
    {
        printf("Room not found.\n");
    }
    else
    {
        print_temperatures(selected_room);
    }


    free_rooms(head);

    return 0;
}