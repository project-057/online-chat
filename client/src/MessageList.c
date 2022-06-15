#include "MessageList.h"
#include <string.h>
#include <stdlib.h>

MessageList* create_message_list() {
    return malloc(sizeof(MessageList));
}

void delete_message_list(MessageList* ml) {
    free(ml);
}

void add_message(MessageList* ml, char* message) {
    if (ml->count >= MAX_MESSAGE_LIST_COUNT) {
        return;
    }
    strcpy(ml->array[ml->count++], message);
}