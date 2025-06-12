#include "food_order.h"

#include <stddef.h>
#include <stdlib.h>

/*
 * You’re building the backend for a food delivery app. A critical task is to process an incoming
 * order. The logic changes depending on whether the restaurant is currently open
 * or closed. If it’s open, you create a standard order confirmation. If it’s closed, you create
 * a pre-order confirmation for the next day.
 * Your goal is to implement the control logic that, given an order request, checks the restaurant’s
 * status, prepares the appropriate confirmation, and sends a notification.
*/

int process_food_order(struct OrderRequest *request) {
    struct OderConfirmation * confirmation = NULL;
    
    int status = check_restaurant_status(request);
    if (status) {
        confirmation = create_standard_confirmation();
    } else {
        confirmation = create_preorder_confirmation();
    }
    if (confirmation) {
        send_confirmation_notification(confirmation);
        free(confirmation);
    }
    return (confirmation != NULL);
}