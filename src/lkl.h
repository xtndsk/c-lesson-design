#ifndef _LKL_H_
    #define _LKL_H_
#endif

#define STRN 1024

struct Prob {
    struct Prob *prev;
    struct Prob *next;
    int num[2];
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
    struct Score *val;
    char profe[STRN];
    char name[STRN];
    int cls;
};

struct Bstu {
    struct Bstu *prev;
    struct Bstu *next;
    struct Stu  *val;
};

struct Score {
    struct Score *prev;
    struct Score *next;
    int id, test, score;
};

struct Exam {
    struct Exam *prev;
    struct Exam *next;
    struct Prob *val; 
};