C := alpha*A*B + beta*C;
int r;
int q;
int p;
double accum;
r = 0;
while (r < 60) {
  q = 0;
  while (q < 80) {
    p = 0;
    accum = 0.0;
    while (p < 60) {
      accum += alpha * A[r][p] * B[p][q];
      p++;
    }
    C[r][q] = accum + beta * C[r][q];
    q++;
  }
  r++;
}
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int r;
  int q;
  int p;
  double accum;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (r = 0; r < 60; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (q = 0; q < 80; q++) {
      accum = 0.0;
      
#pragma ACCEL PARALLEL reduction=accum FACTOR=auto{5}
      for (p = 0; p < 60; p++) {
        accum += alpha * A[r][p] * B[p][q];
      }
      C[r][q] = accum + beta * C[r][q];
    }
  }
  
#pragma endscop
}