#pragma once
#include <stdint.h>
#include <stdio.h>

typedef uint32_t ApplicationState;

enum ApplicationStateFlags {
    AS_INIT = 1,
    AS_CHAT = 1 << 1,
    AS_SUBMIT_BUTTON_CLICK = 1 << 2,
    AS_JOIN_BUTTON_CLICK = 1 << 3
};

void print_application_state(ApplicationState as);