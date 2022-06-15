#pragma once

#define MAX_MESSAGE_LIST_COUNT 512
#define MAX_MESSAGE_SIZE 512

typedef struct {
    char array[MAX_MESSAGE_LIST_COUNT][MAX_MESSAGE_SIZE];
    int count;
} MessageList;

MessageList* create_message_list();
void delete_message_list(MessageList* ml);
void add_message(MessageList* ml, char* message);