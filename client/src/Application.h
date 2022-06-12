#pragma once
#include <stdbool.h>

typedef struct {
    bool is_running;
} Application;

Application* create_application();
void delete_application(Application* app);