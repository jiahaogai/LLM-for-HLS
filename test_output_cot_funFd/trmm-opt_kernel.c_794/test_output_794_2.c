#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
int i;
int j;
int k;
double sum;
//#pragma scop
for (i = 0; i < 60; i++) {
   for (j = 0; j < 80; j++) {
      sum = 0.0;
      for (k = 0; k < 60; ++k) {
         sum += A[i][k] * B[k][j];
      }
      B[i][j] = sum;
   }
}
//#pragma endscop