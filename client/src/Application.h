#pragma once
#include "ApplicationState.h"
#include "MessageList.h"
#include "RenderData.h"

#include <stdbool.h>
#include <nuklear_cross.h>

#define WINDOW_HEIGHT   480
#define WINDOW_WIDTH    640
#define MAX_ROOM_NUMBER_SIZE 19
#define MAX_NICKNAME_SIZE 16

typedef struct {
    /* Nuklear specific data and render data */
    struct nkc* nkc_handle;
    struct nk_context* ctx;
    RenderData* render_data;

    /* Window data */
    bool is_running;
    int window_height;
    int window_width;

    /* Logic data */
    MessageList* message_list;
    ApplicationState application_state;
    char room_number[MAX_ROOM_NUMBER_SIZE];
    int room_number_size;
    char nickname[MAX_NICKNAME_SIZE];
    int nickname_size;
    
    /* Network data */
    int sockfd;
} Application;

Application* create_application();
void delete_application(Application* app);
void update(Application* app);
void render(Application* app);