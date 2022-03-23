#include "randomizer.h"

// Sets up randomizer so it will not repeat himself
void set_up_random() {
    srand(time(NULL));
}

// Returns random value from 1 to h
size_t random_record(const size_t h) {
    return 1 + rand() % (h + 1);
}
