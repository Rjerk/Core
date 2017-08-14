#include "../../unp.h"

void sig_int(int)
{
    void pr_cpu_time(void);
    pr_cpu_time();
    exit(0);
}
