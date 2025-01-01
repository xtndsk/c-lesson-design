#include <json-c/json_object.h>
#include <json-c/json_object_iterator.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lkl.h"
#include <json-c/json.h>
/*
define head_ptr
    prev = NULL
    next = NULL(mut)
    val = NULL(all)
*/
Bprob_ptr Prob_srch(Prob_ptr head, int (*check)(Prob_ptr)) {
    Bprob_ptr res = (Bprob_ptr) malloc (sizeof(Bprob)), cur = res;
    for (; head; head = head->next) {
        if (check(head)) {
            cur->next = (Bprob_ptr) malloc (sizeof(Bprob));
            cur->next->prev = cur;
            cur->next->next = NULL;
            cur->next->val = head;
        }
    }   res->next->prev = NULL;
    return res;
}

int Prob_add(int pos, Prob_ptr head, int num1, int num2, int opt) {
    int sz = Prob_size(head);
    if (pos > sz) return 0;

    Prob_ptr new_ptr = (Prob_ptr) malloc (sizeof(Prob));
    new_ptr->num1 = num1, new_ptr->num2 = num2, new_ptr->opt = opt, new_ptr->id = pos + 1;

    for (; head; head = head->next) {
        if (pos == head->id) {
            new_ptr->prev = head;
            new_ptr->next = head->next;
            new_ptr->next->prev = new_ptr;
            head->next = new_ptr;
        } else if (head->id > pos + 1) {
            head->id += 1;
        }
    }
    return 1;
}

int Prob_rm(int pos, Prob_ptr head) {
    int sz = Prob_size(head);
    if (pos > sz) return 0;

    Prob_ptr rm;
    for (; head; head = head->next) {
        if (pos == head->id) {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            Prob_ptr rm = head;
        } else if (head->id > pos) {
            head->id -= 1;
        }
    }
    if (rm) free(rm), rm = NULL;
    return 1;
}

int Prob_size(Prob_ptr head) {
    int sz = 0;
    for (; head; head = head->next) ++sz;
    return sz - 1;
}

void Prob_print(Prob_ptr head) {
    while (head) {
        printf("%d ", head->id);
        head = head->next;
    }   puts("");
}

int Prob_rm_l(Bprob_ptr boat) {
    Bprob_ptr h = boat;
    for (; boat; boat = boat->next) {
        if (boat->val) {
            boat->val->next->prev = boat->val->prev;
            boat->val->prev->next = boat->val->next;
            free(boat->val); boat->val = NULL;
        }
    }
    for (; h->next; h = h->next) {
        if (h->prev) free(h->prev), h->prev = NULL;
    }   free(h), h = NULL;
    return 1;
}

int Prob_add_l(Prob_ptr head, Bprob_ptr boat) { // add at the end of ll
    for (; head->next; head = head->next) ;

    Bprob_ptr h = boat;
    for (; boat; boat = boat->next) {
        if (boat->val) {
            head->next = boat->val;
            boat->val->prev = head;
            boat->val->next = NULL;
            head = head->next;
        }
    }
    for (; h->next; h = h->next) {
        if (h->prev) free(h->prev), h->prev = NULL;
    }   free(h), h = NULL;
    return 1;
}

int Prob_change(int pos, Prob_ptr head, int num1, int num2, int opt) {
    int sz = Prob_size(head);
    if (pos > sz) return 0;

    for (; head; head = head->next) {
        if (pos == head->id) {
            head->num1 = num1;
            head->num2 = num2;
            head->opt = opt;
            break;
        }
    }
    return 1;
}

Prob_ptr Prob_merge(Prob_ptr l, Prob_ptr r, int(*cmp)(const void*, const void*)) {
    Prob_ptr res = (Prob_ptr) malloc(sizeof(Prob)), cur = res;
    while (l && r) {
        if (cmp(l, r)) cur->next = l, l = l->next, cur = cur->next;
        else           cur->next = r, r = r->next, cur = cur->next;
    }
    while (l) cur->next = l, l = l->next, cur = cur->next;
    while (r) cur->next = r, r = r->next, cur = cur->next;
    return res->next;
}

Prob_ptr Prob_sort(Prob_ptr ptr, int(*cmp)(const void*, const void*)) {
    if (ptr->next == NULL) return ptr;

    Prob_ptr fast = ptr, slow = ptr, sign = NULL;
    while (fast && fast->next) {
        sign = slow;
        fast = fast->next->next;
        slow = slow->next;
    }   sign->next = NULL;
    Prob_ptr l = Prob_sort(ptr, cmp);
    Prob_ptr r = Prob_sort(slow, cmp);
    return Prob_merge(l, r, cmp);
}

int Prob_s_and_rebuild(Prob_ptr ptr, int (*cmp)(const void*, const void*)) {
    Prob_ptr res = Prob_sort(ptr->next, cmp);
    ptr->next = res;
    for (Prob_ptr pr = ptr; res; res = res->next, pr = pr->next) {
        res->prev = pr;
    }
    return 1;
}

Bstu_ptr Stu_srch(Stu_ptr head, int (*check)(Stu_ptr)) {
    Bstu_ptr res = (Bstu_ptr) malloc (sizeof(Bstu)), cur = res;
    for (; head; head = head->next) {
        if (check(head)) {
            cur->next = (Bstu_ptr) malloc (sizeof(Bstu));
            cur->next->prev = cur;
            cur->next->next = NULL;
            cur->next->val = head;
        }
    }   res->next->prev = NULL;
    return res;
}

int Stu_add(int pos, Stu_ptr head, int cls, int score, char* name, char* profe) {
    int sz = Stu_size(head);
    if (pos > sz) return 0;

    Stu_ptr new_ptr = (Stu_ptr) malloc (sizeof(Stu));
    new_ptr->cls = cls, new_ptr->score = score, new_ptr->id = pos + 1;
    strcpy(new_ptr->name, name);
    strcpy(new_ptr->profe, profe);

    for (; head; head = head->next) {
        if (pos == head->id) {
            new_ptr->prev = head;
            new_ptr->next = head->next;
            new_ptr->next->prev = new_ptr;
            head->next = new_ptr;
        } else if (head->id > pos + 1) {
            head->id += 1;
        }
    }
    return 1;
}

int Stu_rm(int pos, Stu_ptr head) {
    int sz = Stu_size(head);
    if (pos > sz) return 0;

    Stu_ptr rm;
    for (; head; head = head->next) {
        if (pos == head->id) {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            Stu_ptr rm = head;
        } else if (head->id > pos) {
            head->id -= 1;
        }
    }
    if (rm) free(rm), rm = NULL;
    return 1;
}

int Stu_size(Stu_ptr head) {
    int sz = 0;
    for (; head; head = head->next) ++sz;
    return sz - 1;
}

void Stu_print(Stu_ptr head) {
    while (head) {
        printf("%d ", head->id);
        head = head->next;
    }   puts("");
}

int Stu_rm_l(Bstu_ptr boat) {
    Bstu_ptr h = boat;
    for (; boat; boat = boat->next) {
        if (boat->val) {
            boat->val->next->prev = boat->val->prev;
            boat->val->prev->next = boat->val->next;
            free(boat->val); boat->val = NULL;
        }
    }
    for (; h->next; h = h->next) {
        if (h->prev) free(h->prev), h->prev = NULL;
    }   free(h), h = NULL;
    return 1;
}

int Stu_add_l(Stu_ptr head, Bstu_ptr boat) { // add at the end of ll
    for (; head->next; head = head->next) ;

    Bstu_ptr h = boat;
    for (; boat; boat = boat->next) {
        if (boat->val) {
            head->next = boat->val;
            boat->val->prev = head;
            boat->val->next = NULL;
            head = head->next;
        }
    }
    for (; h->next; h = h->next) {
        if (h->prev) free(h->prev), h->prev = NULL;
    }   free(h), h = NULL;
    return 1;
}

int Stu_change(int pos, Stu_ptr head, int cls, int score, char* name, char* profe) {
    int sz = Stu_size(head);
    if (pos > sz) return 0;

    for (; head; head = head->next) {
        if (pos == head->id) {
            head->cls = cls;
            head->score = score;
            strcpy(head->name, name);
            strcpy(head->profe, profe);
            break;
        }
    }
    return 1;
}

Stu_ptr Stu_merge(Stu_ptr l, Stu_ptr r, int(*cmp)(const void*, const void*)) {
    Stu_ptr res = (Stu_ptr) malloc(sizeof(Stu)), cur = res;
    while (l && r) {
        if (cmp(l, r)) cur->next = l, l = l->next, cur = cur->next;
        else           cur->next = r, r = r->next, cur = cur->next;
    }
    while (l) cur->next = l, l = l->next, cur = cur->next;
    while (r) cur->next = r, r = r->next, cur = cur->next;
    return res->next;
}

Stu_ptr Stu_sort(Stu_ptr ptr, int(*cmp)(const void*, const void*)) {
    if (ptr->next == NULL) return ptr;

    Stu_ptr fast = ptr, slow = ptr, sign = NULL;
    while (fast && fast->next) {
        sign = slow;
        fast = fast->next->next;
        slow = slow->next;
    }   sign->next = NULL;
    Stu_ptr l = Stu_sort(ptr, cmp);
    Stu_ptr r = Stu_sort(slow, cmp);
    return Stu_merge(l, r, cmp);
}

int Stu_s_and_rebuild(Stu_ptr ptr, int (*cmp)(const void*, const void*)) {
    Stu_ptr res = Stu_sort(ptr->next, cmp);
    ptr->next = res;
    for (Stu_ptr pr = ptr; res; res = res->next, pr = pr->next) {
        res->prev = pr;
    }
    return 1;
}

int Bprob_size(Bprob_ptr head) {
    int sz = 0;
    for (; head; head = head->next) ++sz;
    return sz - 1;
}

char* Prob_to_json(Prob_ptr head) {
    struct json_object *json_obj = json_object_new_object();
    struct json_object *json_arr = json_object_new_array();
    for (; head; head = head->next) {
        if (!head->prev) {
            struct json_object *prob_s = json_object_new_object();
            json_object_object_add(prob_s, "num1", json_object_new_int(head->num1));
            json_object_object_add(prob_s, "num2", json_object_new_int(head->num2));
            json_object_object_add(prob_s, "opt", json_object_new_int(head->opt));
            json_object_object_add(prob_s, "id", json_object_new_int(head->id));
            json_object_array_add(json_arr, prob_s);
        }
    }
    json_object_object_add(json_obj, "Prob", json_arr);
    int sz = Prob_size(head);
    char *str = (char*) malloc(sizeof(char) * STRN * sz);
    strcpy(str, json_object_to_json_string(json_obj));
    return str;
}

char* Bprob_to_json(Bprob_ptr head) {
    struct json_object *json_obj = json_object_new_object();
    struct json_object *json_arr = json_object_new_array();
    for (; head; head = head->next) {
        if (!head->prev) {
            struct json_object *prob_s = json_object_new_object();
            json_object_object_add(prob_s, "num1", json_object_new_int(head->val->num1));
            json_object_object_add(prob_s, "num2", json_object_new_int(head->val->num2));
            json_object_object_add(prob_s, "opt", json_object_new_int(head->val->opt));
            json_object_object_add(prob_s, "id", json_object_new_int(head->val->id));
            json_object_array_add(json_arr, prob_s);
        }
    }
    json_object_object_add(json_obj, "Prob", json_arr);
    int sz = Bprob_size(head);
    char *str = (char*) malloc(sizeof(char) * STRN * sz);
    strcpy(str, json_object_to_json_string(json_obj));
    return str;
}

Prob_ptr Prob_de_json(char *str) {
    Prob_ptr head = (Prob_ptr) malloc(sizeof(Prob)), res = head;
    struct json_object *parsed_obj = json_tokener_parse(str);
    struct json_object *parsed_arr;
    json_object_object_get_ex(parsed_obj, "Prob", &parsed_arr);
    for (int i = 0; i < json_object_array_length(parsed_arr); ++i) {
        struct json_object *item = json_object_array_get_idx(parsed_arr, i);
        head->next = (Prob_ptr) malloc (sizeof(Prob)), head->next->prev = head;
        json_object_object_foreach(item, key, val) {
            if (strcmp(key, "num1") == 0) {
                head->next->num1 = json_object_get_int(val);
            } else if (strcmp(key, "num2") == 0) {
                head->next->num2 = json_object_get_int(val);
            } else if (strcmp(key, "opt") == 0) {
                head->next->opt = json_object_get_int(val);
            } else if (strcmp(key, "id") == 0) {
                head->next->id = json_object_get_int(val);
            }
        }
        head = head->next;
    }
    return res;
}

Bprob_ptr Bprob_de_json(char *str) {
    Bprob_ptr head = (Bprob_ptr) malloc(sizeof(Bprob)), res = head;
    struct json_object *parsed_obj = json_tokener_parse(str);
    struct json_object *parsed_arr;
    json_object_object_get_ex(parsed_obj, "Prob", &parsed_arr);
    for (int i = 0; i < json_object_array_length(parsed_arr); ++i) {
        struct json_object *item = json_object_array_get_idx(parsed_arr, i);
        head->next = (Bprob_ptr) malloc (sizeof(Bprob)), head->next->prev = head;
        head->val = (Prob_ptr) malloc (sizeof(Prob));
        json_object_object_foreach(item, key, val) {
            if (strcmp(key, "num1") == 0) {
                head->next->val->num1 = json_object_get_int(val);
            } else if (strcmp(key, "num2") == 0) {
                head->next->val->num2 = json_object_get_int(val);
            } else if (strcmp(key, "opt") == 0) {
                head->next->val->opt = json_object_get_int(val);
            } else if (strcmp(key, "id") == 0) {
                head->next->val->id = json_object_get_int(val);
            }
        }
        head = head->next;
    }
    return res;
}

char* Stu_to_json(Stu_ptr head) {
    struct json_object *json_obj = json_object_new_object();
    struct json_object *json_arr = json_object_new_array();
    for (; head; head = head->next) {
        if (!head->prev) {
            struct json_object *stu_s = json_object_new_object();
            json_object_object_add(stu_s, "score", json_object_new_int(head->score));
            json_object_object_add(stu_s, "cls", json_object_new_int(head->cls));
            json_object_object_add(stu_s, "id", json_object_new_int(head->id));
            json_object_object_add(stu_s, "profe", json_object_new_string(head->profe));
            json_object_object_add(stu_s, "name", json_object_new_string(head->name));
            json_object_array_add(json_arr, stu_s);
        }
    }
    json_object_object_add(json_obj, "Stu", json_arr);
    int sz = Stu_size(head);
    char *str = (char*) malloc(sizeof(char) * STRN * sz);
    strcpy(str, json_object_to_json_string(json_obj));
    return str;
}

char* Bstu_to_json(Bstu_ptr head) {
    struct json_object *json_obj = json_object_new_object();
    struct json_object *json_arr = json_object_new_array();
    for (; head; head = head->next) {
        if (!head->prev) {
            struct json_object *stu_s = json_object_new_object();
            json_object_object_add(stu_s, "score", json_object_new_int(head->val->score));
            json_object_object_add(stu_s, "cls", json_object_new_int(head->val->cls));
            json_object_object_add(stu_s, "id", json_object_new_int(head->val->id));
            json_object_object_add(stu_s, "profe", json_object_new_string(head->val->profe));
            json_object_object_add(stu_s, "name", json_object_new_string(head->val->name));
            json_object_array_add(json_arr, stu_s);
        }
    }
    json_object_object_add(json_obj, "Stu", json_arr);
    int sz = Bstu_size(head);
    char *str = (char*) malloc(sizeof(char) * STRN * sz);
    strcpy(str, json_object_to_json_string(json_obj));
    return str;

}

int Bstu_size(Bstu_ptr head) {
    int sz = 0;
    for (; head; head = head->next) ++sz;
    return sz - 1;
}

Stu_ptr Stu_de_json(char* str) {
    Stu_ptr head = (Stu_ptr) malloc(sizeof(Stu)), res = head;
    struct json_object *parsed_obj = json_tokener_parse(str);
    struct json_object *parsed_arr;
    json_object_object_get_ex(parsed_obj, "Stu", &parsed_arr);
    for (int i = 0; i < json_object_array_length(parsed_arr); ++i) {
        struct json_object *item = json_object_array_get_idx(parsed_arr, i);
        head->next = (Stu_ptr) malloc (sizeof(Stu)), head->next->prev = head;
        json_object_object_foreach(item, key, val) {
            if (strcmp(key, "cls") == 0) {
                head->next->cls = json_object_get_int(val);
            } else if (strcmp(key, "score") == 0) {
                head->next->score = json_object_get_int(val);
            } else if (strcmp(key, "profe") == 0) {
                strcpy(head->next->profe, json_object_get_string(val));
            } else if (strcmp(key, "name") == 0) {
                strcpy(head->next->name, json_object_get_string(val));
            }else if (strcmp(key, "id") == 0) {
                head->next->id = json_object_get_int(val);
            }
        }
        head = head->next;
    }
    return res;
}

Bstu_ptr Bstu_de_json(char* str) {
    Bstu_ptr head = (Bstu_ptr) malloc(sizeof(Bstu)), res = head;
    struct json_object *parsed_obj = json_tokener_parse(str);
    struct json_object *parsed_arr;
    json_object_object_get_ex(parsed_obj, "Stu", &parsed_arr);
    for (int i = 0; i < json_object_array_length(parsed_arr); ++i) {
        struct json_object *item = json_object_array_get_idx(parsed_arr, i);
        head->next = (Bstu_ptr) malloc (sizeof(Stu)), head->next->prev = head;
        head->val = (Stu_ptr) malloc (sizeof(Stu));
        json_object_object_foreach(item, key, val) {
            if (strcmp(key, "cls") == 0) {
                head->next->val->cls = json_object_get_int(val);
            } else if (strcmp(key, "score") == 0) {
                head->next->val->score = json_object_get_int(val);
            } else if (strcmp(key, "profe") == 0) {
                strcpy(head->next->val->profe, json_object_get_string(val));
            } else if (strcmp(key, "name") == 0) {
                strcpy(head->next->val->name, json_object_get_string(val));
            }else if (strcmp(key, "id") == 0) {
                head->next->val->id = json_object_get_int(val);
            }
        }
        head = head->next;
    }
    return res;
}

int write_Bp(Bprob_ptr head, char *filename) {
    FILE *file = fopen(filename, "wb") ;
    char *data = Bprob_to_json(head);
    if (file == NULL) {
        perror("文件打开失败");
        return EXIT_FAILURE;
    }
    // 使用 fwrite 写入数据
    size_t data_size = strlen(data); // 获取数据大小
    if (fwrite(data, sizeof(char), data_size, file) != data_size) {
        perror("写入失败");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("数据已写入文件：%s\n", filename);

    fclose(file);
    return EXIT_SUCCESS;

}

int write_P(Prob_ptr head, char *filename) {
    FILE *file = fopen(filename, "wb") ;
    char *data = Prob_to_json(head);
    if (file == NULL) {
        perror("文件打开失败");
        return EXIT_FAILURE;
    }
    // 使用 fwrite 写入数据
    size_t data_size = strlen(data); // 获取数据大小
    if (fwrite(data, sizeof(char), data_size, file) != data_size) {
        perror("写入失败");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("数据已写入文件：%s\n", filename);

    fclose(file);
    return EXIT_SUCCESS;

}
int write_Bs(Bstu_ptr head, char *filename) {
    FILE *file = fopen(filename, "wb") ;
    char *data = Bstu_to_json(head);
    if (file == NULL) {
        perror("文件打开失败");
        return EXIT_FAILURE;
    }
    // 使用 fwrite 写入数据
    size_t data_size = strlen(data); // 获取数据大小
    if (fwrite(data, sizeof(char), data_size, file) != data_size) {
        perror("写入失败");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("数据已写入文件：%s\n", filename);

    fclose(file);
    return EXIT_SUCCESS;

}

int write_S(Stu_ptr head, char *filename) {
    FILE *file = fopen(filename, "wb") ;
    char *data = Stu_to_json(head);
    if (file == NULL) {
        perror("文件打开失败");
        return EXIT_FAILURE;
    }
    // 使用 fwrite 写入数据
    size_t data_size = strlen(data); // 获取数据大小
    if (fwrite(data, sizeof(char), data_size, file) != data_size) {
        perror("写入失败");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("数据已写入文件：%s\n", filename);

    fclose(file);
    return EXIT_SUCCESS;

}


Bprob_ptr read_Bp(char* filename) {

    // 打开文件以读取模式 ("rb" 表示读取二进制文件)
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("文件打开失败");
        return NULL;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);  // 将文件指针移动到末尾
    long file_size = ftell(file); // 获取文件大小
    rewind(file);  // 将文件指针重置到开头

    // 分配内存以存储文件内容
    char *buffer = (char *)malloc(file_size + 1); // +1 为了存储字符串的 '\0'
    if (buffer == NULL) {
        perror("内存分配失败");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    if (fread(buffer, sizeof(char), file_size, file) != file_size) {
        perror("读取失败");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // 确保缓冲区以 '\0' 结束，便于作为字符串使用
    Bprob_ptr head = (Bprob_ptr) malloc (sizeof(Bprob));
    head = Bprob_de_json(buffer);

    free(buffer);
    fclose(file);
    return head;
}
Prob_ptr read_P(char* filename) {

    // 打开文件以读取模式 ("rb" 表示读取二进制文件)
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("文件打开失败");
        return NULL;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);  // 将文件指针移动到末尾
    long file_size = ftell(file); // 获取文件大小
    rewind(file);  // 将文件指针重置到开头

    // 分配内存以存储文件内容
    char *buffer = (char *)malloc(file_size + 1); // +1 为了存储字符串的 '\0'
    if (buffer == NULL) {
        perror("内存分配失败");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    if (fread(buffer, sizeof(char), file_size, file) != file_size) {
        perror("读取失败");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // 确保缓冲区以 '\0' 结束，便于作为字符串使用
    Prob_ptr head = (Prob_ptr) malloc (sizeof(Prob));
    head = Prob_de_json(buffer);

    free(buffer);
    fclose(file);
    return head;
}
Bstu_ptr read_Bs(char* filename) {

    // 打开文件以读取模式 ("rb" 表示读取二进制文件)
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("文件打开失败");
        return NULL;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);  // 将文件指针移动到末尾
    long file_size = ftell(file); // 获取文件大小
    rewind(file);  // 将文件指针重置到开头

    // 分配内存以存储文件内容
    char *buffer = (char *)malloc(file_size + 1); // +1 为了存储字符串的 '\0'
    if (buffer == NULL) {
        perror("内存分配失败");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    if (fread(buffer, sizeof(char), file_size, file) != file_size) {
        perror("读取失败");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // 确保缓冲区以 '\0' 结束，便于作为字符串使用
    Bstu_ptr head = (Bstu_ptr) malloc (sizeof(Bstu));
    head = Bstu_de_json(buffer);

    free(buffer);
    fclose(file);
    return head;
}
Stu_ptr read_S(char* filename) {

    // 打开文件以读取模式 ("rb" 表示读取二进制文件)
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("文件打开失败");
        return NULL;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);  // 将文件指针移动到末尾
    long file_size = ftell(file); // 获取文件大小
    rewind(file);  // 将文件指针重置到开头

    // 分配内存以存储文件内容
    char *buffer = (char *)malloc(file_size + 1); // +1 为了存储字符串的 '\0'
    if (buffer == NULL) {
        perror("内存分配失败");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    if (fread(buffer, sizeof(char), file_size, file) != file_size) {
        perror("读取失败");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // 确保缓冲区以 '\0' 结束，便于作为字符串使用
    Stu_ptr head = (Stu_ptr) malloc (sizeof(Stu));
    head = Stu_de_json(buffer);

    free(buffer);
    fclose(file);
    return head;
}