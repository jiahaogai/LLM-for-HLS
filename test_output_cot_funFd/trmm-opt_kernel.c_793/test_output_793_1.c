Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{80}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int i;
Code: int j;
Code: int k;
Code: double sum;
Code: //#pragma scop
Code: i = 0;
Code: while (i < 60) {
Code:   j = 0;
Code:   while (j < 80) {
Code:     sum = 0.0;
Code:     k = 0;
Code:     while (k < 60) {
Code:       sum = sum + A[i][k] * B[k][j];
Code:       k++;
Code:     }
Code:     B[i][j] = sum;
Code:     j++;
Code:   }
Code:   i++;
Code: }
Code: //#pragma endscop
Code: return 0;