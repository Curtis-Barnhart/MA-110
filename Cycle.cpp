//
// Created by Curtis Barnhart on 2023-09-11.
//

#include <cstdlib>
#include <cstdio>

#include "Cycle.h"

namespace CycleNotation {
    Cycle::Cycle(char *cycles, char length, bool ownership) {
        this->cycles = cycles;
        this->length = length;
        this->ownership = ownership;
    }

    Cycle::~Cycle() {
        if (this->ownership) {
            free(this->cycles);
        }
    }

    /**
     * Cycle::simplify
     *
     * @param reader1 pointer to the first element in the cycle to simply
     * @param end1 pointer to "element" after the last element in the cycle to simplify - a pointer to just after the end
     * @param writer buffer in which to write the result of the simplify operation
     * @return position of writer after done writing
     */
    char *Cycle::simplify(char *reader1, const char *end1, char *writer) {// char *reader2, const char *end2) {
        char last_written = 0;
        char whole_cycle_max = 0, sub_cycle_max = 0; // The biggest element over all subcycles
        char map_old[255], map_new[255];
        char first_in_cycle = 0, previous = 0, current;

        while (reader1 < end1) {
            current = *(reader1++);
            if (current == 0) { // do the stuff to combine the two layers
                map_new[previous] = first_in_cycle; // tying up loose end
                for (char i = 1; i <= whole_cycle_max; i++) {
                    map_old[i] = map_new[map_old[i]];
                }
                for (char i = 1; i <= sub_cycle_max; i++) {
                    map_new[i] = i;
                }
                sub_cycle_max = 0; // reset sub_cycle_max
                first_in_cycle = 0; // before you reset first_in_cycle, you're going to have to use it
            } else {
                while (sub_cycle_max < current) { // add identity for missing elements in new generation
                    sub_cycle_max++;
                    map_new[sub_cycle_max] = sub_cycle_max;
                }
                while (whole_cycle_max < current) { // add identity for missing elements in old generation
                    whole_cycle_max++;
                    map_old[whole_cycle_max] = whole_cycle_max;
                }

                if (!first_in_cycle) { // If at beginning of new cycle, save the first element
                    first_in_cycle = current;
                    previous = current;
                } else { // Otherwise save it to the map and carry on
                    map_new[previous] = current;
                    previous = current;
                }
            }
        }
        // When you're done you should be able to look at the first array to get the actual values
        // free original underlying array if you owned it
        reader1 = map_old + 1;
        end1 = map_old + whole_cycle_max + 1;
        while (reader1 < end1) {
            current = *reader1;
            *reader1 = (char) (reader1 - map_old); // Shortening conversion should be fine as long as reader1 doesn't get too big
            if (current == (reader1 - map_old)) {
                if (!last_written) {
                    reader1++;
                    continue;
                } else {
                    *(writer++) = (last_written = 0);
                    reader1++;
                }
            } else {
                *(writer++) = (last_written = current);
                reader1 = map_old + current;
            }
        }

        if (whole_cycle_max == 0) { // If this is the identity but actually has 0 elements in it
            *(writer++) = 0;
        }

        return writer;
    }

    int Cycle::apply(int value) {

    }
} // CycleNotation