#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明 kernel_adi 函数
void kernel_adi(int tsteps, int n, double u[60][60], double v[60][60], double p[60][60], double q[60][60]);

int main() {
    int tsteps = 40, n = 60;
    double u[60][60], v[60][60], p[60][60], q[60][60];

    // 初始化随机数生成器
    srand((unsigned int)time(NULL));

    // 使用随机数初始化矩阵 u 和 v，这里我们假设初始条件可以是随机的
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            u[i][j] = (double)rand() / RAND_MAX * 10.0;
            v[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // 调用 kernel_adi 函数
    kernel_adi(tsteps, n, u, v, p, q);

    // 打印 u, v 矩阵的一些元素以进行验证
    printf("After kernel_adi:\n");
    printf("u[30][30] = %f\n", u[30][30]);
    printf("v[30][30] = %f\n", v[30][30]);
    printf("p[30][30] = %f\n", p[30][30]);
    printf("q[30][30] = %f\n", q[30][30]);

    return 0;
}
