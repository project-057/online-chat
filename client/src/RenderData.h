#pragma once
#include "MessageList.h"

typedef struct {
    char box_buffer[MAX_MESSAGE_LIST_COUNT*MAX_MESSAGE_SIZE];
    int box_buffer_len;
    char line_text[MAX_MESSAGE_SIZE];
    int line_text_len;
} RenderData;

RenderData* create_render_data();
void delete_render_data(RenderData* rd);
void add_message_to_box_buffer(RenderData* rd, char* message, int message_len);