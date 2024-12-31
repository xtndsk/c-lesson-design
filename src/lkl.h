#ifndef _LKL_H_
    #define _LKL_H_
#endif

#define STRN 1024

typedef struct Prob* Prob_ptr;
typedef struct Bprob* Bprob_ptr;
typedef struct Stu* Stu_ptr;
typedef struct Bstu* Bstu_ptr;

struct Prob {
    struct Prob *prev;
    struct Prob *next;
    int num1, num2;
    int opt, id;
};

struct Bprob {
    struct Bprob *prev;
    struct Bprob *next;
    struct Prob  *val;
};

struct Stu {
    struct Stu *prev;
    struct Stu *next;
    int score;
    char profe[STRN];
    char name[STRN];
    int cls;
};

struct Bstu {
    struct Bstu *prev;
    struct Bstu *next;
    struct Stu  *val;
};

int Prob_size(Prob_ptr);