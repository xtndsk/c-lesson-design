#ifndef _LKL_H_
    #define _LKL_H_
#endif

#define STRN 1024

typedef struct Prob* Prob_ptr;
typedef struct Bprob* Bprob_ptr;
typedef struct Stu* Stu_ptr;
typedef struct Bstu* Bstu_ptr;

typedef struct Prob {
    struct Prob *prev;
    struct Prob *next;
    int num1, num2;
    int opt, id;
} Prob;

typedef struct Bprob {
    struct Bprob *prev;
    struct Bprob *next;
    struct Prob  *val;
} Bprob;

typedef struct Stu {
    struct Stu *prev;
    struct Stu *next;
    int id;
    int score;
    char profe[STRN];
    char name[STRN];
    int cls;
} Stu;

typedef struct Bstu {
    struct Bstu *prev;
    struct Bstu *next;
    struct Stu  *val;
} Bstu;

Bprob_ptr Prob_srch(Prob_ptr head, int (*check)(Prob_ptr));
int Prob_add(int pos, Prob_ptr head, int num1, int num2, int opt);
int Prob_rm(int pos, Prob_ptr head);
int Prob_size(Prob_ptr head);
int Bprob_size(Bprob_ptr head);
void Prob_print(Prob_ptr head);
int Prob_rm_l(Bprob_ptr boat);
int Prob_add_l(Prob_ptr head, Bprob_ptr boat);
int Prob_change(int pos, Prob_ptr head, int num1, int num2, int opt);
Prob_ptr Prob_merge(Prob_ptr l, Prob_ptr r, int(*cmp)(const void*, const void*));
Prob_ptr Prob_sort(Prob_ptr ptr, int(*cmp)(const void*, const void*));
int Prob_s_and_rebuild(Prob_ptr ptr, int (*cmp)(const void*, const void*));

Bstu_ptr Stu_srch(Stu_ptr head, int (*check)(Stu_ptr));
int Stu_add(int pos, Stu_ptr head, int cls, int score, char* name, char* profe);
int Stu_rm(int pos, Stu_ptr head);
int Stu_size(Stu_ptr head);
int Bstu_size(Bstu_ptr head);
void Stu_print(Stu_ptr head);
int Stu_rm_l(Bstu_ptr boat);
int Stu_add_l(Stu_ptr head, Bstu_ptr boat);
int Stu_change(int pos, Stu_ptr head, int cls, int score, char* name, char* profe);
Stu_ptr Stu_merge(Stu_ptr l, Stu_ptr r, int(*cmp)(const void*, const void*));
Stu_ptr Stu_sort(Stu_ptr ptr, int(*cmp)(const void*, const void*));
int Stu_s_and_rebuild(Stu_ptr ptr, int (*cmp)(const void*, const void*));

char* Prob_to_json(Prob_ptr head);
char* BProb_to_json(Bprob_ptr head);
Prob_ptr Prob_de_json(char* str);
Bprob_ptr Bprob_de_json(char* str);

char* Stu_to_json(Stu_ptr head);
char* Bstu_to_json(Bstu_ptr head);
Stu_ptr Stu_de_json(char* str);
Bstu_ptr Bstu_de_json(char* str);

int write_Bp(Bprob_ptr head, char* filename);
int write_P(Prob_ptr head, char* filename);
int write_Bs(Bstu_ptr head, char* filename);
int write_S(Stu_ptr head, char* filename);

Bprob_ptr read_Bp(char* filename); //
Prob_ptr read_P(char* filename); //
Bstu_ptr read_Bs(char* filename); //
Stu_ptr read_S(char* filename); //