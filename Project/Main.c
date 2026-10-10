#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>


#define LINE_SIZE 256
#define ROOM_NAME_SIZE 50
#define MIN_TEMPERATURE 0.0
#define MAX_TEMPERATURE 30.0
#define DEGREES_PER_DASH 0.5
#define TEMPERATURE_WIDTH 5
#define FILENAME_SIZE 256
#define CSV_HEADER "Temperature,Room"

typedef struct temp
{
    double value;
    struct temp* next;
} Temperature;

typedef struct room
{
    char* name;
    Temperature* temperatures;
    Temperature* last_temperature;
    struct room* next;
} Room;


int input(const char* string, char* answer, size_t size);
int read_line(FILE* f, char* line, size_t size);
void fix_string(char* string);

void print_temperatures(const Room* room);
void free_rooms(Room* head);
Room* read_csv(const char* filename);
Room* find_room(Room* head, const char* name);
Room* create_room(const char* name);


// Returns 1 for a complete line, 0 for EOF/error, and -1 for an oversized line.
int read_line(FILE* f, char* line, size_t size)
{
    if (size < 2 || fgets(line, size, f) == NULL)
    {
        return 0;
    }

    if (strchr(line, '\n') == NULL)
    {
        int character = fgetc(f);

        if (character != '\n' && character != EOF)
        {
            while (character != '\n' && character != EOF)
            {
                character = fgetc(f);
            }

            return -1;
        }
    }

    return 1;
}


// Removes surrounding whitespace, mainly used for the newline from fgets.
void fix_string(char* string)
{
    char* start = string;

    while (isspace((unsigned char)*start))
    {
        start++;
    }

    size_t length = strlen(start);

    while (length > 0 && isspace((unsigned char)start[length - 1]))
    {
        length--;
    }

    memmove(string, start, length);
    string[length] = '\0';
}


// Finds and returns the room names node that is passed into the function.
Room* find_room(Room* head, const char* name)
{
    while (head != NULL && strcmp(head->name, name) != 0)
    {
        head = head->next;
    }

    return head;
}

// Creates and returns a new node associated with a recently found room.
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
    new_room->last_temperature = NULL;
    new_room->next = NULL;

    return new_room;
}


// Reads each row once and adds its temperature to the matching room.
// Main function for creating a linked list of rooms each with linked list of temperatures.
Room* read_csv(const char* filename)
{
    FILE* f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("%s: %s\n", filename, strerror(errno));
        return NULL;
    }

    Room* head = NULL;
    Room* tail = NULL;
    char line[LINE_SIZE];
    size_t line_number = 1;
    int valid = 1;
    int result = read_line(f, line, sizeof(line));

    if (result != 1)
    {
        fprintf(stderr, "Could not read CSV header, or header is too long.\n");
        fclose(f);
        return NULL;
    }

    fix_string(line);

    if (strcmp(line, CSV_HEADER) != 0)
    {
        fprintf(stderr, "Expected CSV header: %s\n", CSV_HEADER);
        fclose(f);
        return NULL;
    }

    while (valid && (result = read_line(f, line, sizeof(line))) != 0)
    {
        line_number++;

        if (result == -1)
        {
            fprintf(stderr, "Line %zu: line is too long.\n", line_number);
            valid = 0;
        }
        else
        {
            fix_string(line);
        }

        if (valid && line[0] != '\0')
        {
            char* comma = strchr(line, ',');

            if (comma == NULL || strchr(comma + 1, ',') != NULL)
            {
                fprintf(stderr,"Line %zu: expected temperature and room separated by one comma.\n", line_number);
                valid = 0;
            }
            else
            {
                // Following part splits the row by the comma to handle the double and the room name individually.
                *comma = '\0';
                char* room_name = comma + 1;

                fix_string(line);
                fix_string(room_name);

                if (strcmp(room_name, "quit") == 0 || strcmp(room_name, "jukka") == 0)
                {
                    fprintf(stderr,"Line %zu: room name '%s' is not allowed.\n", line_number, room_name);
                    valid = 0;
                }
                else if (room_name[0] == '\0')
                {
                    fprintf(stderr, "Line %zu: room name is missing.\n", line_number);
                    valid = 0;
                }
                else if (strlen(room_name) >= ROOM_NAME_SIZE)
                {
                    fprintf(stderr,"Line %zu: room name exceeds %d bytes.\n", line_number, ROOM_NAME_SIZE - 1);
                    valid = 0;
                }

                if (valid)
                {
                    char* end;
                    errno = 0;
                    double temperature = strtod(line, &end);

                    if (end == line || *end != '\0' ||
                        errno == ERANGE || !isfinite(temperature))
                    {
                        fprintf(stderr,"Line %zu: temperature must be a finite number.\n", line_number);
                        valid = 0;
                    }

                    if (valid)
                    {
                        Room* room = find_room(head, room_name);

                        if (room == NULL)
                        {
                            Room* new_room = create_room(room_name);

                            if (new_room == NULL)
                            {
                                fprintf(stderr, "Not enough memory to store rooms.\n");
                                valid = 0;
                            }
                            else
                            {
                                if (head == NULL)
                                {
                                    head = new_room;
                                }
                                else
                                {
                                    tail->next = new_room;
                                }

                                tail = new_room;
                                room = new_room;
                            }
                        }

                        if (valid)
                        {
                            Temperature* new_temp = malloc(sizeof(Temperature));

                            if (new_temp == NULL)
                            {
                                fprintf(stderr, "Not enough memory to store temperatures.\n");
                                valid = 0;
                            }
                            else
                            {
                                new_temp->value = temperature;
                                new_temp->next = NULL;

                                if (room->temperatures == NULL)
                                {
                                    room->temperatures = new_temp;
                                }
                                else
                                {
                                    room->last_temperature->next = new_temp;
                                }

                                room->last_temperature = new_temp;
                            }
                        }
                    }
                }
            }
        }
    }

    if (ferror(f))
    {
        fprintf(stderr, "Error while reading %s.\n", filename);
        valid = 0;
    }

    fclose(f);

    if (!valid)
    {
        free_rooms(head);
        return NULL;
    }

    if (head == NULL)
    {
        fprintf(stderr, "CSV file contains no temperature readings.\n");
    }

    return head;
}

// Print the temperatures following their representation in dashes.
void print_temperatures(const Room* room)
{
    printf("\n%s\n", room->name);

    int width = TEMPERATURE_WIDTH;
    const Temperature* tail = room->temperatures;


    while (tail != NULL)
    {
        int length = snprintf(NULL, 0, "%.1f", tail->value);

        if (length > width)
        {
            width = length;
        }

        tail = tail->next;
    }

    tail = room->temperatures;

    while (tail != NULL)
    {
        printf("%*.1f ", width, tail->value);

        if (tail->value < MIN_TEMPERATURE ||
            tail->value > MAX_TEMPERATURE)
        {
            printf("X");
        }
        else
        {
            int dashes = (int)(tail->value / DEGREES_PER_DASH);

            for (int i = 0; i < dashes; i++)
            {
                printf("-");
            }
        }

        printf("\n");
        tail = tail->next;
    }
}


// Frees the temperature lists before freeing their rooms.
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


// Prompts for a nonempty answer that fits in the passed buffer length. Returns 0 for different errors.
int input(const char* string, char* answer, size_t size)
{
    printf("%s\n", string);

    int result = read_line(stdin, answer, size);

    if (result == 0)
    {
        printf("Could not read input.\n");
        return 0;
    }

    if (result == -1)
    {
        printf("Input too long.\n");
        return 0;
    }

    fix_string(answer);

    if (answer[0] == '\0')
    {
        printf("Input cannot be empty.\n");
        return 0;
    }

    return 1;
}

// Main function responsible of the program flow.
int main(void)
{
    char filename[FILENAME_SIZE];
    Room* head = NULL;
    int running = 1;

    while (running && head == NULL)
    {
        if (input("Enter CSV filename or path, quit to exit:", filename, sizeof(filename)) != 0)
        {
            if (strcmp(filename, "quit") == 0)
            {
                running = 0;
            }
            else
            {
                head = read_csv(filename);
            }
        }
        else if (feof(stdin) || ferror(stdin))
        {
            running = 0;
        }
    }

    if (head == NULL)
    {
        return 0;
    }

    printf("WELCOME TO PASI CSV READER!\n\nThis program reads %s for temperature information about the rooms it contains.\n"
        "Feel free to edit the room names and temperature values inside the file, but keep the format and header intact.\n"
        "Rooms named \"quit\" or \"jukka\" in the .csv will produce an error to keep them as functional commands.\n", filename);

    while (running)
    {
        Room* tail = head;
        printf("Available rooms:\n");

        while (tail != NULL)
        {
            printf("- %s\n", tail->name);
            tail = tail->next;
        }

        char answer[ROOM_NAME_SIZE];

        if (input("Enter room name (case-sensitive), or quit to exit:", answer, sizeof(answer)) != 0)
        {
            if (strcmp(answer, "quit") == 0)
            {
                running = 0;
            }
            else if (strcmp(answer, "jukka") == 0)
            {
                printf("pasi ja jukka tappeli, pasi voitti.\n");
            }
            else
            {
                Room* selected_room = find_room(head, answer);

                if (selected_room == NULL)
                {
                    printf("Room not found.\n");
                }
                else
                {
                    print_temperatures(selected_room);
                }
            }
        }
        else if (feof(stdin) || ferror(stdin))
        {
            running = 0;
        }
    }

    free_rooms(head);

    return 0;
}