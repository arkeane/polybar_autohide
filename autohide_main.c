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

int activeWindowIsFullscreen(xdo_t *xdo) {
    int fullscreen = 0;
    Window window;
    long nitems;
    unsigned char *states;

    int ret = xdo_get_active_window(xdo, &window);
    if (ret == XDO_ERROR || window == 0)
        return 0;

    ret = xdo_get_window_property(xdo, window, "_NET_WM_STATE", &states, &nitems, NULL, NULL);
    if (ret == XDO_ERROR)
        return 0;

    char *state;
    for (int i = 0; i < nitems; ++i) {
        state = XGetAtomName(xdo->xdpy, ((Atom*)states)[i]);
        if (strcmp(state, "_NET_WM_STATE_FULLSCREEN") == 0)
            fullscreen = 1;
        XFree(state);
    }
    free(states);

    return fullscreen;
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
        // check if active window is fullscreen
        if (hidden && CHECK_FULLSCREEN && activeWindowIsFullscreen(xdo)) {
            usleep(LOOP_DELAY * 1000);
            continue;
        }

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
