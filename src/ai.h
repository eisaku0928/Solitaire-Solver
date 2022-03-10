#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "utils.h"

// Declare function prototypes
void initialize_ai();
void find_solution( state_t* init_state );
void free_memory(unsigned expanded_nodes);

// Frees branch
void free_branch(node_t *n);

#endif
