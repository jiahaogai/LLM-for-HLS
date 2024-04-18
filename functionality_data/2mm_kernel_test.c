#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明 kernel_2mm 函数
void kernel_2mm(int ni, int nj, int nk, int nl, double alpha, double beta, double tmp[40][50], double A[40][70], double B[70][50], double C[50][80], double D[40][80]);

int main() {
    int ni = 40, nj = 50, nk = 70, nl = 80;
    double alpha = 1.2, beta = 0.8;
    double tmp[40][50], A[40][70], B[70][50], C[50][80], D[40][80];

    // 初始化随机数生成器
    srand((unsigned int)time(NULL));

    // 使用随机数初始化矩阵 A, B, C, D
    for (int i = 0; i < ni; i++) {
        for (int k = 0; k < nk; k++) {
            A[i][k] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    for (int k = 0; k < nk; k++) {
        for (int j = 0; j < nj; j++) {
            B[k][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    for (int j = 0; j < nj; j++) {
        for (int l = 0; l < nl; l++) {
            C[j][l] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    for (int i = 0; i < ni; i++) {
        for (int l = 0; l < nl; l++) {
            D[i][l] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // 调用 kernel_2mm 函数
    kernel_2mm(ni, nj, nk, nl, alpha, beta, tmp, A, B, C, D);

    // 打印 D 矩阵的一些元素以进行验证
    printf("D[20][40] = %f\n", D[20][40]);
    printf("D[30][60] = %f\n", D[30][60]);

    return 0;
}
