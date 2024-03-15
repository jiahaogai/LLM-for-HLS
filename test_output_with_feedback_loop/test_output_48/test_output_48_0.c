The ACCEL annotation for kernel is required to identify the kernel function, while other ACCEL annotations can be used to tune the performance of individual operations. 

# DRIVING FACTOR ANALYSIS
## Summary of timing breakdown

| Name                  | Min runtime | Max runtime | Avg runtime | Min period | Max period | Avg period |
| --------------------- | ----------- | ----------- | ----------- | ---------- | ---------- | ---------- |
| kernel_3mm            | 1.621040    | 2.000000    | 1.720641    | 128        | 128        | 128        |
| kernel_3mm/kernel_3mm_1 | 0.000000    | 0.000000    | 0.000000    | 1          | 1          | 1          |
| kernel_3mm/kernel_3mm_2 | 0.000000    | 0.000000    | 0.000000    | 64         | 64         | 64         |
| kernel_3mm/kernel_3mm_3 | 0.000000    | 0.000000    | 0.000000    | 1          | 1          | 1          |
| kernel_3mm/kernel_3mm_4 | 0.000000    | 0.000000    | 0.000000    | 16         | 16         | 16         |
| kernel_3mm/kernel_3mm_5 | 0.000000    | 0.000000    | 0.000000    | 4          | 4          | 4          |

## Detailed kernel: kernel_3mm
#pragma ACCEL kernel

void kernel_3mm(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][60],double B[60][50],double F[50][70],double C[50][80],double D[80][70],double G[40][70])
{
  int i;
  int j;
  int k;
//#pragma scop
/* E := A*B */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{60}
      for (k = 0; k < 60; ++k) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
/* F := C*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      F[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 80; ++k) {
        F[i][j] += C[i][k] * D[k][j];
      }
    }
  }
/* G := E*F */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      G[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{50}
      for (k = 0; k < 50; ++k) {
        G[i][j] += E[i][k] * F[k][j];
      }
    }
  }
//#pragma endscop
}