//
// Created by Curtis Barnhart on 2023-09-11.
//

#ifndef ALGEBRA_CYCLE_H
#define ALGEBRA_CYCLE_H

namespace CycleNotation {
    class Cycle {
        private:
            char *cycles;
            char length;
            bool ownership;

        public:
            static char *simplify(char *reader, char *end, char *reader2, char *end2, char *writer);
            static char *simplify(char *reader, char *end, char *writer); // TODO: move this to private after done debugging
            Cycle (char *cycles, char length, bool ownership);
            ~Cycle();
            int apply(int value);
    };

} // CycleNotation

#endif //ALGEBRA_CYCLE_H
