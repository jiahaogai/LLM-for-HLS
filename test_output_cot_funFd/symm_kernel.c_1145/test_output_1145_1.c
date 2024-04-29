Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{15}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{80}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
Code: #pragma ACCEL PARALLEL reduction=C FACTOR=auto{15}
int i;
int j;
int k;
double mult;
double temp1;
double temp2;
double C[60][80];
double A[60][60];
double B[60][80];
for (i = 0; i < 60; i++) {
   for (j = 0; j < 80; j++) {
      C[i][j] = 0.0;
      for (k = 0; k < 60; k++) {
         mult = A[i][k] * B[k][j];
         temp1 = C[i][j] + mult;
         temp2 = C[i][j] - mult;
      }
      C[i][j] = temp1 + alpha * temp2;
   }
}
for (i = 0; i < 60; i++) {
   for (j = 0; j < 80; j++) {
      C[i][j] += beta * A[i][j];
   }
}