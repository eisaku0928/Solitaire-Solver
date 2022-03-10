#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"


void copy_state(state_t* dst, state_t* src){

	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;

		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){

		// Declare new node by copying state of n
    node_t* new_node = NULL;
		new_node = create_init_node(&(n->state));

		/* Set parent and depth according to n,
		and move and state.cursor according to the currently viewing
		action and peg */
		new_node->parent = n;
		new_node->depth = n->depth + 1;
		new_node->move = action;
		new_node->state.cursor = *selected_peg;

		// Execute move on the new node to update its state
    execute_move_t( &(new_node->state), &(new_node->state.cursor), action );

	return new_node;

}

/**
 * Find a solution path as per algorithm description in the handout
 */
void find_solution( state_t* init_state  ){

	// Declare hash table
	HashTable table;

	// Choose initial capacity of PRIME NUMBER
	// Specify the size of the keys and values you want to store once
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);

	// Initialize Stack
	initialize_stack();

	//Add the initial node
	node_t* n = create_init_node( init_state );

	// Declare variables for best number of remaining pegs and currently viewing peg's position.
	int remaining_pegs;
	position_s position;

	// Push initial node into stack
	stack_push(n);

	// Store remaining pegs as initial number of pegs
	remaining_pegs = num_pegs(&(n->state));

	/* While stack is not empty, view each node, and perform depth first search
	by popping and viewing top node on stack and constructing an implicit graph. */
	while(!is_stack_empty()){
		// View top of stack and pop
		n = stack_top();
		stack_pop();

		// increment number of expanded nodes
		expanded_nodes++;

		/* If found a better solution than the current best (least) solution,
		 update remaining_pegs and save solution. */
		if (num_pegs(&(n->state)) < remaining_pegs){
			save_solution(n);
			remaining_pegs = num_pegs(&(n->state));
		}

		// Initially set current node to having no child
		n->child = false;

		/* Go through each peg and consider each jump action. */
		for (position.x = 0; position.x < SIZE; position.x++){
			for (position.y = 0; position.y < SIZE; position.y++){
				for (int move = left; move <= down; ++move){

					/* If current jump can apply at current state and position, generate
					new node (child of node n). */
					if (can_apply(&(n->state), &position, move)){
						node_t *new_node = applyAction(n, &position, move);

						// Increment number of generated nodes.
						generated_nodes++;

						// If peg solitaire is solved, end search
						if (won(&(new_node->state))){

							// Save solution, and update best count for remaining number of pegs
							save_solution(new_node);
							remaining_pegs = num_pegs(&(new_node->state));

							// Destroy HashTable and free stack.
							ht_destroy(&table);
							free_stack();

							// Free entire branch that led to current node.
							free_branch(new_node);
							return;
						}

						// Avoid duplicates by checking if the new_node has already been seen.
						if (!ht_contains(&table, new_node->state.field)){

							// If not, insert in hash table.
							ht_insert(&table, new_node->state.field, new_node->state.field);

							// Set currently viewing node to having a child
							if (!n->child){
								n->child = true;
							}

							// Push child node into stack.
							stack_push(new_node);
						}
						else {
							// If current child node has already been seen, free the node.
							free(new_node);
						}

					}
				}
			}
		}

		/* If current node is deepest node and if this node did not "win", this means
		entire branch leading to current child can be cut free'd. */
		if (!n->child){
			/* If stack is empty, current branch only exists and leads to root.
			Thus current child and all parents can be free'd. */
			if (is_stack_empty()){
				free_branch(n);
			}
			else{
				/* If stack is not empty peek at top of stack and compare current node's parent
				to its parent, and free current branch. */

				// Create pointers to parent of parents and currently freeing parent.
				node_t *parent = n->parent;
				node_t *current = parent;
				// Peek at top of stack.
				node_t *stackTop = stack_top();

				/* Compare to stack_top's parent, and free until currently viewing node becomes
				 stack_top's parent. */
				while (parent != stackTop->parent){
					parent = current->parent;
					free(current);
					current = parent;
				}
				// Free deepest child node of branch.
				free(n);

			}
		}

		// If the current number of expanded_nodes exceed budget, stop search.
		if (expanded_nodes >= budget){

			/* Free path that leads to top of stack before freeing entire stack.
			If stack is empty, n until root would have been free'd in previous step. */
			if (!is_stack_empty()){
				node_t *stackTop = stack_top();
				stack_pop();
				free_branch(stackTop);
			}

			// Destroy hash table and free stack.
			ht_destroy(&table);
			free_stack();
			return;
		}
	}

	// If program finished within budget, destroy hash table and free stack.
	ht_destroy(&table);
	free_stack();
	return;
}

/* Function to free branch from passed in child node up until root.
Called when freeing nodes that expanded and do not exist inside stack. */
void free_branch(node_t *n){
	// Set two pointers. One for traversing and one for freeing.
	node_t *cursor = n;
	node_t *tmp;

	// Parse through each node and destroy preceding node.
	while (cursor != NULL){
		tmp = cursor;
		cursor = cursor->parent;
		free(tmp);
	}
}
