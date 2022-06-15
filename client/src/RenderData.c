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