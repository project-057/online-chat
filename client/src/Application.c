#include "Application.h"
#include "ApplicationState.h"

#include <stdlib.h>
#include <nuklear_cross.h>
#include <nuklear.h>

#define RED_BOLD "\033[1;31m"
#define DEFAULT "\033[0m"

Application* create_application() {
    Application* app = malloc(sizeof(Application));
    app->is_running = true;
    app->window_height = WINDOW_HEIGHT;
    app->window_width = WINDOW_WIDTH;

    app->nkc_handle = malloc(sizeof(struct nkc));
    if (!nkc_init(app->nkc_handle, "Online chat by HSE student!!!", app->window_width, app->window_height, NKC_WIN_NORMAL)) {
        puts(RED_BOLD"[ERROR]"DEFAULT" failed to init nuklear app\n");
        return NULL;
    }
    app->application_state = AS_INIT;

    app->render_data = create_render_data();
    app->message_list = create_message_list();
    return app;
}

void delete_application(Application* app) {
    nkc_shutdown(app->nkc_handle);
    free(app->nkc_handle);
    delete_message_list(app->message_list);
    delete_render_data(app->render_data);
    free(app);
}

static void process_button_click(Application* app) {
    add_message(app->message_list, app->render_data->line_text);
    app->render_data->line_text[app->render_data->line_text_len++] = '\n';
    strcpy(app->render_data->box_buffer + app->render_data->box_buffer_len, app->render_data->line_text);
    app->render_data->box_buffer_len += app->render_data->line_text_len;
    memset(app->render_data->line_text, 0, MAX_MESSAGE_SIZE);
    app->render_data->line_text_len = 0;
}

static void process_initial_data(Application* app) {
    puts("[INFO] Cathed data:\n");
    printf("%s\n", app->room_number);
    printf("%s\n", app->nickname);
}

void update(Application* app) {
    struct nk_context *ctx = nkc_get_ctx(app->nkc_handle);
    if (!ctx) {
        puts(RED_BOLD"[ERROR]"DEFAULT" failed to get ctx\n");
    }
    app->ctx = ctx;

    union nkc_event e = nkc_poll_events(app->nkc_handle);
    if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) ){
        app->is_running = false;
    }

    if (app->application_state & AS_JOIN_BUTTON_CLICK) {
        process_initial_data(app);
        app->application_state -= AS_JOIN_BUTTON_CLICK;
        app->application_state -= AS_INIT;
        app->application_state |= AS_CHAT;
    }

    static int prev_message_list_count = 0;
    if (app->application_state & AS_SUBMIT_BUTTON_CLICK) {
        process_button_click(app);
        app->application_state -= AS_SUBMIT_BUTTON_CLICK;
        prev_message_list_count += 1;
    }
}

void render(Application* app) {
    if (nk_begin(app->ctx, "Online CHAAT!!", nk_rect(0, 0, app->window_width, app->window_height), NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {
        /* initial screen*/
        if (app->application_state & AS_INIT) {
            nk_layout_space_begin(app->ctx, NK_STATIC, app->window_height/2 - 75, 1);
            nk_layout_space_push(app->ctx, nk_rect(0, 0, app->window_width, app->window_height/2));
            nk_layout_space_end(app->ctx);
            float ratio[2] = { app->window_width * 2 / 10, app->window_width * 8 / 10 };
            nk_layout_row(app->ctx, NK_STATIC, 30, 2, ratio);
            nk_label(app->ctx, "Room number:", NK_LEFT);
            nk_flags active1 = nk_edit_string(app->ctx, NK_EDIT_FIELD, app->room_number, &app->room_number_size, MAX_ROOM_NUMBER_SIZE, nk_filter_decimal);
            nk_label(app->ctx, "Nickname:", NK_LEFT);
            nk_flags active2 = nk_edit_string(app->ctx, NK_EDIT_FIELD, app->nickname, &app->nickname_size, MAX_NICKNAME_SIZE, nk_filter_ascii);
            nk_layout_row_static(app->ctx, 25, app->window_width - 10, 1);
            if (nk_button_label(app->ctx, "Join") || (active1 & active2 & NK_EDIT_COMMITED)) {
                app->application_state |= AS_JOIN_BUTTON_CLICK;
            }
        }

        /* chat screen */
        if (app->application_state & AS_CHAT) {
            float ratio[2] = {app->window_width*627/640*8/10, app->window_width*627/640*2/10 - 5};
            nk_layout_row_static(app->ctx, app->window_height - 40, app->window_width*627/640, 1);
            nk_edit_string(app->ctx, NK_EDIT_BOX, app->render_data->box_buffer, &app->render_data->box_buffer_len, MAX_MESSAGE_LIST_COUNT*MAX_MESSAGE_SIZE, nk_filter_default);

            nk_layout_row(app->ctx, NK_STATIC, 25, 2, ratio);
            nk_flags active = nk_edit_string(app->ctx, NK_EDIT_FIELD, app->render_data->line_text, &app->render_data->line_text_len, MAX_MESSAGE_SIZE, nk_filter_default);
            if (nk_button_label(app->ctx, "Submit") || (active & NK_EDIT_COMMITED)) {
                app->application_state |= AS_SUBMIT_BUTTON_CLICK;
            }
        }
    }
    nk_end(app->ctx);


    nkc_render(app->nkc_handle, nk_rgb(40,40,40) );
}