#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t serialized = serialize(state);
    insert_at_tail(&q->data, serialized);
}

struct game_state dequeue(struct queue *q) {
    uint64_t serialized = remove_from_head(&q->data);
    return deserialize(serialized);
}

bool state_in_list(struct linked_list list, struct game_state curr) {
    uint64_t target = serialize(curr);
    for (struct list_node *node = list.head; node != NULL; node = node->next) {
        if (node->value == target) {
            return true;
        }
    }
    return false;
}

int number_of_moves(struct game_state start) {
    struct queue q = {0};
    struct linked_list visited = {0};
    int result = -1;
    
    enqueue(&q, start);
    
    while (q.data.head != NULL) {
        struct game_state current = dequeue(&q);
        
        // Skip if we've already seen this exact state (including move count)
        if (state_in_list(visited, current)) {
            continue;
        }
        
        // Mark this state as visited
        uint64_t serialized = serialize(current);
        insert_at_tail(&visited, serialized);
        
        // Check if solved
        if (current.tiles[0][0] == 1 && current.tiles[0][1] == 2 &&
            current.tiles[0][2] == 3 && current.tiles[0][3] == 4 &&
            current.tiles[1][0] == 5 && current.tiles[1][1] == 6 &&
            current.tiles[1][2] == 7 && current.tiles[1][3] == 8 &&
            current.tiles[2][0] == 9 && current.tiles[2][1] == 10 &&
            current.tiles[2][2] == 11 && current.tiles[2][3] == 12 &&
            current.tiles[3][0] == 13 && current.tiles[3][1] == 14 &&
            current.tiles[3][2] == 15 && current.tiles[3][3] == 0) {
            result = current.num_steps;
            break;
        }
        
        // Generate and enqueue valid moves
        struct game_state up = current;
        move_up(&up);
        if (up.num_steps != current.num_steps) {
            enqueue(&q, up);
        }
        
        struct game_state down = current;
        move_down(&down);
        if (down.num_steps != current.num_steps) {
            enqueue(&q, down);
        }
        
        struct game_state left = current;
        move_left(&left);
        if (left.num_steps != current.num_steps) {
            enqueue(&q, left);
        }
        
        struct game_state right = current;
        move_right(&right);
        if (right.num_steps != current.num_steps) {
            enqueue(&q, right);
        }
    }
    
    // Clean up both queues
    free_list(q.data);
    free_list(visited);
    
    return result;
}