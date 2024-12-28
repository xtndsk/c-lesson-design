#ifndef _SRVR_H_
    #define _SRVR_H_
#endif

static void handle_post(struct mg_connection *c, struct mg_http_message *hm);
static void fn(struct mg_connection *c, int ev, void *ev_data);
