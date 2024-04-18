#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明 kernel_3mm 函数
void kernel_3mm(int ni, int nj, int nk, int nl, int nm, double E[40][50], double A[40][60], double B[60][50], double F[50][70], double C[50][80], double D[80][70], double G[40][70]);

int main() {
    int ni = 40, nj = 50, nk = 60, nl = 70, nm = 80;
    double E[40][50], A[40][60], B[60][50], F[50][70], C[50][80], D[80][70], G[40][70];

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

    for (int i = 0; i < nj; i++) {
        for (int k = 0; k < nm; k++) {
            C[i][k] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    for (int k = 0; k < nm; k++) {
        for (int j = 0; j < nl; j++) {
            D[k][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // 调用 kernel_3mm 函数
    kernel_3mm(ni, nj, nk, nl, nm, E, A, B, F, C, D, G);

    // 打印 G 矩阵的一些元素以进行验证
    printf("G[20][35] = %f\n", G[20][35]);
    printf("G[30][45] = %f\n", G[30][45]);

    return 0;
}
