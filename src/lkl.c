#include <stdio.h>
#include <stdlib.h>
#include "lkl.h"
/*
define head_ptr
    prev = NULL
    next = NULL(mut)
    val = NULL(all)
*/
Bprob_ptr srch_problem(Prob_ptr head, int (*check)(Prob_ptr)) {
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

int add_problem(int pos, Prob_ptr head, int num1, int num2, int opt) {
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

int Prob_size(Prob_ptr head) {
    int sz = 0;
    for (; head; head = head->next) ++sz;
    return sz - 1;
}

void printProb(Prob_ptr head) {
    while (head) {
        printf("%d ", head->id);
        head = head->next;
    }   puts("");
}

Prob_ptr remove_problem(Prob_ptr head, Bprob_ptr boat) {

}