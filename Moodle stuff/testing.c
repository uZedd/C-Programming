#include <stdio.h>

#define NAME_SIZE 32
#define ELEMENT_SIZE 16
#define MAX_POKEMON 10

typedef struct my_pokemon {
    char name[NAME_SIZE];
    char element[ELEMENT_SIZE];
    int id;
} pokemon;

void print_all_pokemon(pokemon *pokemon_list);

void print_all_pokemon(pokemon *pokemon_list) {
    for (int i = 0; pokemon_list[i].id != 0 && i<MAX_POKEMON; i++) {
        printf("%d %s %s\n", pokemon_list[i].id, pokemon_list[i].name, pokemon_list[i].element);
    }
}
void print_bugsies(pokemon *pokemon_list) {

}

int main() {
    pokemon pasi = {"pasi", "ghost", 94};
    struct my_pokemon jukka = {"jukka", "bug", 69};
    pokemon rayquaza = {"rayquaza", "dragon", 384};
    pokemon marowak = {"marowak", "ghost", 14};

    pokemon shiny_pokemon[] = {pasi, jukka, rayquaza, marowak};

    print_all_pokemon(shiny_pokemon);

    return 0;
}