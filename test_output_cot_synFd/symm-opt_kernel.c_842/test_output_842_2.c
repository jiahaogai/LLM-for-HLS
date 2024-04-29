Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        k_col = k * 80;
        mult = alpha * A[i][k] * B[k][j];
        temp2 = C[i][j_col + 0] + mult;
        temp3 = C[i][j_col + 1] + mult;
        temp4 = C[i][j_col + 2] + mult;
        temp5 = C[i][j_col + 3] + mult;
        temp6 = C[i][j_col + 4] + mult;
        temp7 = C[i][j_col + 5] + mult;
        temp8 = C[i][j_col + 6] + mult;
        temp9 = C[i][j_col + 7] + mult;
        temp10 = C[i][j_col + 8] + mult;
        temp11 = C[i][j_col + 9] + mult;
        temp12 = C[i][j_col + 10] + mult;
        temp13 = C[i][j_col + 11] + mult;
        temp14 = C[i][j_col + 12] + mult;
        temp15 = C[i][j_col + 13] + mult;
        temp16 = C[i][j_col + 14] + mult;
        temp17 = C[i][j_col + 15] + mult;
        temp18 = C[i][j_col + 16] + mult;
        temp19 = C[i][j_col + 17] + mult;
        temp20 = C[i][j_col + 18] + mult;
        temp21 = C[i][j_col + 19] + mult;
        temp22 = C[i][j_col + 20] + mult;
        temp23 = C[i][j_col + 21] + mult;
        temp24 = C[i][j_col + 22] + mult;
        temp25 = C[i][j_col + 23] + mult;
        temp26 = C[i][j_col + 24] + mult;
        temp27 = C[i][j_col + 25] + mult;
        temp28 = C[i][j_col + 26] + mult;
        temp29 = C[i][j_col + 27] + mult;
        temp30 = C[i][j_col + 28] + mult;
        temp31 = C[i][j_col + 29] + mult;
        temp32 = C[i][j_col + 30] + mult;
        temp33 = C[i][j_col + 31] + mult;
        temp34 = C[i][j_