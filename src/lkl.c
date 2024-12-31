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

Prob_ptr Prob_sort(Prob_ptr head);