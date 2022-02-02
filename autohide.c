#include "autohide.h"

int getYMouseLocation(xdo_t *xdo) {
    int y;
    xdo_get_mouse_location(xdo, NULL, &y, NULL);
    return y;
}

void hideBar(xdo_t *xdo, Window bar) {
    if (USE_TOP_BAR == 1) {
        xdo_unmap_window(xdo, bar);
    } else if (USE_BOTTOM_BAR == 1) {
        xdo_unmap_window(xdo, bar);
    }
}

void showBar(xdo_t *xdo, Window bar) {
    if (USE_TOP_BAR == 1) {
        xdo_map_window(xdo, bar);
    } else if (USE_BOTTOM_BAR == 1) {
        xdo_map_window(xdo, bar);
    }
}

Window *getBar(xdo_t *xdo) {
    Window *bar = 0;
    Window *list = NULL;
    xdo_search_t query;
    unsigned int n_win = 0;

    // initialize query to find bar window
    memset(&query, 0, sizeof(xdo_search_t));
    query.max_depth = -1;
    query.require = SEARCH_ANY;
    query.searchmask |= SEARCH_CLASS;
    query.winclass = BAR_WM_CLASS;

    xdo_search_windows(xdo, &query, &list, &n_win);
    bar = &list[0];

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
    int ishidden = 0;
    while (1) {
        // get mouse location
        int y = getYMouseLocation(xdo);

        // if mouse is in top bar
        if (y < MARGIN_TOP && USE_TOP_BAR == 1) {
            // if mouse is in top bar and bar is hidden
            usleep(CURSOR_WINDOW_DELAY * 1000);
            showBar(xdo, *bar);
            ishidden = 0;
        }
        // if mouse is in bottom bar
        else if (y > MARGIN_BOTTOM && USE_BOTTOM_BAR == 1) {
            // if mouse is in bottom bar and bar is hidden
            usleep(CURSOR_WINDOW_DELAY * 1000);
            showBar(xdo, *bar);
            ishidden = 0;
        }
        // if mouse is not in top or bottom bar
        else if (y > MARGIN_HIDE_TOP && y < MARGIN_HIDE_BOTTOM) {
            if (ishidden == 0) {
                hideBar(xdo, *bar);
                ishidden = 1;
            }
        }

        // sleep
        usleep(LOOP_DELAY);
    }
    

    // cleanup
    xdo_free(xdo);
    return 0;
}
