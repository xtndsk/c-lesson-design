#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lkl.h"
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
    return res->next;
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
    return res->next;
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