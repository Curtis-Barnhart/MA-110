//
// Created by Curtis Barnhart on 2023-09-11.
//

#include <cstdlib>
#include <cstdio>

#include "Cycle.h"

namespace CycleNotation {
    /**
     * Constructor allows you to make a new Cycle object if you have an array of chars that represents a valid cycle.
     * The Constructor does not simplify an array that could be simplified.
     * The Constructor remembers ownership of the array of cycles given - if it is owned by the object, the object on
     * destruction will free the array.
     *
     * @param cycles
     * @param length
     * @param ownership
     */
    Cycle::Cycle(char *cycles, char length, bool ownership) {
        this->cycles = cycles;
        this->length = length;
        this->ownership = ownership;
    }

    /**
     * The Destructor will free the underlying array of cycles if the object has ownership of it.
     */
    Cycle::~Cycle() {
        if (this->ownership) {
            free(this->cycles);
        }
    }

    /**
     * Cycle::simplify reduces an array representing cyclic notation elements of a group to use as few cycles as
     * possible, writing the result into a provided buffer. It does not check the length of the provided buffer,
     * but does return a pointer to after the last element it wrote in the buffer.
     *
     * @param reader pointer to the beginning of the array of cyclic notation elements to read.
     * @param end pointer to after the last element of the array of cyclic notation elements to read.
     * @param writer pointer to the buffer to place the result in.
     * @return pointer to after where the method finished writing in the buffer.
     */
    char *simplify(char *reader, char *end, char *writer) {
        return CycleNotation::simplify(reader, end, nullptr, nullptr, writer);
    }

    /**
     * Cycle::simplify reduces two arrays representing cyclic notation elements of a group to use as few cycles
     * as possible, writing the result into a provided buffer. It does not check the length of the provided buffer,
     * but does return a pointer to after the last element it wrote in the buffer.
     *
     * @param reader1 pointer to the beginning of the first array of cyclic notation elements to be read.
     * @param end1 pointer to after the last element of the first array of cyclic notation elements to read.
     * @param reader2 pointer to the beginning of the second array of cyclic notation elements to be read.
     * @param end2 pointer to after the last element of the second array of cyclic notation elements to read.
     * @param writer pointer to the buffer to place the result in.
     * @return pointer to after where the method finished writing in the buffer.
     */
    char *simplify(char *reader1, char *end1, char *reader2, char *end2, char *writer) {
        char *reader = reader1, *end = end1;
        char last_written = 1;
        char whole_cycle_max = 0, sub_cycle_max = 0;
        char map_old[255], map_new[255];
        char first_in_cycle = 0, previous = 0, current;

        which_read:
        while (reader < end) {
            current = *(reader++);
            if (current == 0) { // do the stuff to combine the two layers
                if (first_in_cycle) { // only tie up loose end if there is a loose end to tie up
                    map_new[previous] = first_in_cycle; // tying up loose end
                }
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
        if (end == end1) {
            reader = reader2;
            end = end2;
            goto which_read;
        }
        // When you're done you should be able to look at the first array to get the actual values
        // free original underlying array if you owned it
        reader = map_old + 1;
        end = map_old + whole_cycle_max + 1;
        while (reader < end) {
            current = *reader;
            *reader = (char) (reader - map_old); // Shortening conversion should be fine as long as reader doesn't get too big
            if (current == (reader - map_old)) {
                if (!last_written) {
                    reader++;
                    continue;
                } else {
                    *(writer++) = (last_written = 0);
                    reader++;
                }
            } else {
                *(writer++) = (last_written = current);
                reader = map_old + current;
            }
        }

        if (whole_cycle_max == 0) { // If this is the identity but actually has 0 elements in it
            *(writer++) = 0;
        }

        return writer;
    }

    /**
     * Evaluates how a single item is transformed according to a cycle.
     *
     * @param value element to transform.
     * @return transformation of value.
     */
    char apply(char value, char *reader, char *end) {
        char current, first_in_cycle;
        enum STATE {SEEK_VALUE, SEEK_ZERO, SET_FIRST_IN_CYCLE, SET_VALUE};
        STATE state = SET_FIRST_IN_CYCLE;

        while (reader < end) {
            current = *(reader++);
            switch (state) {
                case SEEK_VALUE:
                    if (current == 0) {
                        state = SET_FIRST_IN_CYCLE;
                    } else if (current == value) {
                        state = SET_VALUE;
                    }
                    break;
                case SEEK_ZERO:
                    if (current == 0) {
                        state = SET_FIRST_IN_CYCLE;
                    }
                    break;
                case SET_FIRST_IN_CYCLE:
                    if (current == 0) {
                        continue;
                    } if (current == value) {
                        state = SET_VALUE;
                    } else {
                        first_in_cycle = current;
                        state = SEEK_VALUE;
                    }
                    break;
                case SET_VALUE:
                    if (current == 0) {
                        value = first_in_cycle;
                        state = SET_FIRST_IN_CYCLE;
                    } else {
                        value = current;
                        state = SEEK_ZERO;
                    }
                    break;
            }
        }

        return value;
    }
} // CycleNotation
