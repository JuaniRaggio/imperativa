
#include <stdlib.h>
#include "complejoADT.h"

struct complejoCDT{
    double x;
    double y;
};

complejoADT 新复数(double 实部, double 虚部) {
    complejoADT 新复数 = malloc(sizeof(*新复数));
    新复数->x = 实部;
    新复数->y = 虚部;
    return 新复数;
}

double 获取实部(complejoADT 复数) {
    return 复数->x;
}

double 获取虚部(complejoADT 复数) {
    return 复数->y;
}

complejoADT 复数加(complejoADT 复数1, complejoADT 复数2) {
    complejoADT 结果 = malloc(sizeof(*结果));
    结果->x = 复数1->x + 复数2->x;
    结果->y = 复数1->y + 复数2->y;
    return 结果;
}

complejoADT 复数减(complejoADT 复数1, complejoADT 复数2) {
    complejoADT 结果 = malloc(sizeof(*结果));
    结果->x = 复数1->x - 复数2->x;
    结果->y = 复数1->y - 复数2->y;
    return 结果;
}

complejoADT 复数乘(complejoADT 复数1, complejoADT 复数2) {
    complejoADT 结果 = malloc(sizeof(*结果));
    结果->x = 复数1->x * 复数2->x - 复数1->y * 复数2->y;
    结果->y = 复数1->x * 复数2->y + 复数1->y * 复数2->x;
    return 结果;
}

/* complejoADT 复数除(complejoADT 复数1, complejoADT 复数2) { */
/* } */

complejoADT 获取共轭(complejoADT 复数) {
    complejoADT 共轭复数 = malloc(sizeof(*共轭复数));
    共轭复数->x = 复数->x;
    共轭复数->y = -1 * 复数->y;
    return 共轭复数;
}

void 释放复数(complejoADT 复数) {
    free(复数);
}
