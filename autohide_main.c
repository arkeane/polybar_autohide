#include "autohide.h"
#include "autohide_aux.c"

Window *getBar(xdo_t *xdo) {
    Window *bar = NULL;
    Window **list = malloc(sizeof(Window *) * 20);
    xdo_search_t query;
    unsigned int n_win = 0;

    // initialize query to find bar window
    memset(&query, 0, sizeof(xdo_search_t));
    query.max_depth = -1;
    query.require = SEARCH_ANY;
    query.searchmask |= SEARCH_CLASS;
    query.winclass = BAR_WM_CLASS;

    xdo_search_windows(xdo, &query, list, &n_win);
    bar = list[0];

    free(list);
    return bar;
}

int main(){
    // init xdo
    xdo_t *xdo = xdo_new(NULL);
    if (xdo == NULL) {
        fail("Failed to initialize xdo");
    }

    // get bar window object
    Window *bar = getBar(xdo);
    if (bar == NULL) {
        fail("Failed to find bar");
    }

    // main loop
    int y = 0;
    bool hidden = false;
    while (1) {
        // get mouse location
        xdo_get_mouse_location(xdo, NULL, &y, NULL);

        // if mouse is not in top or bottom bar
        if (y > MARGIN_HIDE_TOP && y < MARGIN_HIDE_BOTTOM) {
            if (!hidden) {
                xdo_unmap_window(xdo, *bar);
                hidden = true;
            }
            usleep(CURSOR_WINDOW_DELAY * 1000);
            continue;
        }

        // if mouse is in top bar
        else if (y < MARGIN_TOP && USE_TOP_BAR == 1) {
            // if mouse is in top bar and bar is hidden
            usleep(CURSOR_WINDOW_DELAY * 1000);
            xdo_map_window(xdo, *bar);
            hidden = false;
            continue;
        }

        // if mouse is in bottom bar
        else if (y > MARGIN_BOTTOM && USE_BOTTOM_BAR == 1) {
            // if mouse is in bottom bar and bar is hidden
            usleep(CURSOR_WINDOW_DELAY * 1000);
            xdo_map_window(xdo, *bar);
            hidden = false;
            continue;
        }

        usleep(LOOP_DELAY);
    }
    
    xdo_free(xdo);
    return 0;
}