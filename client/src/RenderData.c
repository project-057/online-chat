#include "RenderData.h"
#include <string.h>
#include <stdlib.h>

RenderData* create_render_data() {
    RenderData* rd = malloc(sizeof(RenderData));
    rd->box_buffer_len = 0;
    rd->line_text_len = 0;
    memset(rd->box_buffer, 0, MAX_MESSAGE_LIST_COUNT*MAX_MESSAGE_SIZE);
    memset(rd->line_text, 0, MAX_MESSAGE_SIZE);
    return rd;
}

void delete_render_data(RenderData* rd) {
    free(rd);
}

void add_message_to_box_buffer(RenderData* rd, char* message, int message_len) {
    strcpy(rd->box_buffer + rd->box_buffer_len, message);
    rd->box_buffer_len += message_len;
}