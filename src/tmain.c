#include <json-c/json.h>
#include "mongoose.h"
#include <json-c/json_object_iterator.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void handle_post(struct mg_connection *c, struct mg_http_message *hm) {
    char json_data[1024] = {0};
    snprintf(json_data, sizeof(json_data), "%d", (int)hm->body.len);

    struct json_object *parsed_json = json_tokener_parse(json_data);
    if (!parsed_json) {
        mg_http_reply(c, 400, "Content-Type: application/json\r\n", 
                      "{\"ans\":\"no\"}");
        return;
    }

    struct json_object *name_obj;
    json_object_object_get_ex(parsed_json, "account", &name_obj);
    const char *name = json_object_get_string(name_obj);

    // 构造响应 JSON：{"message": "Hello, <name>!"}
    struct json_object *response_json = json_object_new_object();
    struct json_object *message = json_object_new_string("ok");
    json_object_object_add(response_json, "ans", message);
    json_object_object_add(response_json, "type", json_object_new_string("Teacher"));

    // 发送响应
    mg_http_reply(c, 200, "Content-Type: application/json\r\n", 
                    "%s", json_object_to_json_string(response_json));

    // 释放 JSON 对象
    json_object_put(response_json);

    json_object_put(parsed_json); // 释放解析的 JSON 对象
}

// 通用事件处理器
static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_match(hm->uri, mg_str("/"), NULL)) { // 仅处理 "/api" 路径
            if (mg_strcmp(hm->method, mg_str("POST")) == 0) {
                handle_post(c, hm); // 处理 POST 请求
            } else {
                mg_http_reply(c, 405, "Content-Type: application/json\r\n", 
                              "{\"ans\":\"no\"}");
            }
        } else {
            mg_http_reply(c, 404, "Content-Type: application/json\r\n", 
                          "{\"ans\":\"no\"}");
        }
    }
}

int main() {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr); // 初始化 Mongoose 管理器
    mg_http_listen(&mgr, "http://0.0.0.0:8080", fn, NULL); // 启动服务器监听 8080 端口
    printf("Server started on http://0.0.0.0:8080\n");

    for (;;) mg_mgr_poll(&mgr, 1000); // 循环处理事件

    mg_mgr_free(&mgr); // 释放资源
    return 0;
}