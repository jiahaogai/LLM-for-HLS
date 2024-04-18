#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明 kernel_seidel_2d 函数
void kernel_seidel_2d(int tsteps, int n, double A[120][120]);

int main() {
    int tsteps = 40, n = 120;
    double A[120][120];

    // 使用随机数初始化 A 矩阵
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // 调用 kernel_seidel_2d 函数
    kernel_seidel_2d(tsteps, n, A);

    // 打印 A 矩阵的一些元素以进行验证
    printf("After kernel_seidel_2d:\n");
    for (int i = 118; i <= 118; i++) { // 选择特定行以简化输出，实际测试时可以选择更多的点或者更有代表性的点
        for (int j = 118; j <= 118; j++) {
            printf("A[%d][%d] = %f\n", i, j, A[i][j]);
        }
    }

    return 0;
}
