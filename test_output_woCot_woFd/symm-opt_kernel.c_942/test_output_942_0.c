#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
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
        temp2[0] = C[i][j_col + 0] + mult;
        temp2[1] = C[i][j_col + 1] + mult;
        temp2[2] = C[i][j_col + 2] + mult;
        temp2[3] = C[i][j_col + 3] + mult;
        temp2[4] = C[i][j_col + 4] + mult;
        temp2[5] = C[i][j_col + 5] + mult;
        temp2[6] = C[i][j_col + 6] + mult;
        temp2[7] = C[i][j_col + 7] + mult;
        temp2[8] = C[i][j_col + 8] + mult;
        temp2[9] = C[i][j_col + 9] + mult;
        temp2[10] = C[i][j_col + 10] + mult;
        temp2[11] = C[i][j_col + 11] + mult;
        temp2[12] = C[i][j_col + 12] + mult;
        temp2[13] = C[i][j_col + 13] + mult;
        temp2[14] = C[i][j_col + 14] + mult;
        temp2[15] = C[i][j_col + 15] + mult;
        temp2[16] = C[i][j_col + 16] + mult;
        temp2[17] = C[i][j_col + 17] + mult;
        temp2[18] = C[i][j_col + 18] + mult;
        temp2[19] = C[i][j_col + 19] + mult;
        temp2[20] = C[i][j_col + 20] + mult;
        temp2[21] = C[i][j_col + 21] + mult;
        temp2[22] = C[i][j_col + 22] + mult;
        temp2[23] = C[i][j_col + 23] + mult;
        temp2[24] = C[i][j_col + 24] + mult;
        temp2[25] = C[i][j_col + 25] + mult;
        temp2[26] = C[i][j_col + 26] + mult;
        temp2[27] = C[i][j_col + 27] + mult;
        temp2[28] = C[i][j_col + 28] + mult;
        temp2[29] = C[i][j_col + 29] + mult;
        temp2[30] = C[i][j_col + 30] + mult;
        temp2[31] = C[i][j_col + 31] + mult;
        temp2[32] = C[i][j_col + 32] + mult;
        temp2[33] = C[i][j_col + 33] + mult;
        temp2[34] = C[i][j_col + 34] + mult;
        temp2[35] = C[i][j_col + 35] + mult;
        temp2[36] = C[i][j_col + 36] + mult;
        temp2[37] = C[i][j_col + 37] + mult;
        temp2[38] = C[i][j_col + 38] + mult;
        temp2[39] = C[i][j_col + 39] + mult;
        C[i][j_col + 0] = temp2[0];
        C[i][j_col + 1] = temp2[1];
        C[i][j_col + 2] = temp2[2];
        C[i][j_col + 3] = temp2[3];
        C[i][j_col + 4] = temp2[4];
        C[i][j_col + 5] = temp2[5];
        C[i][j_col + 6] = temp2[6];
        C[i][j_col + 7] = temp2[7];
        C[i][j_col + 8] = temp2[8];
        C[i][j_col + 9] = temp2[9];
        C[i][j_col + 10] = temp2[10];
        C[i][j_col + 11] = temp2[11];
        C[i][j_col + 12] = temp2[12];
        C[i][j_col + 13] = temp2[13];
        C[i][j_col + 14] = temp2[14];
        C[i][j_col + 15] = temp2[15];
        C[i][j_col + 16] = temp2[16];
        C[i][j_col + 17] = temp2[17];
        C[i][j_col + 18] = temp2[18];
        C[i][j_col + 19] = temp2[19];
        C[i][j_col + 20] = temp2[20];
        C[i][j_col + 21] = temp2[21];
        C[i][j_col + 22] = temp2[22];
        C[i][j_col + 23] = temp2[23];
        C[i][j_col + 24] = temp2[24];
        C[i][j_col + 25] = temp2[25];
        C[i][j_col + 26] = temp2[26];
        C[i][j_col + 27] = temp2[27];
        C[i][j_col + 28] = temp2[28];
        C[i][j_col + 29] = temp2[29];
        C[i][j_col + 30] = temp2[30];
        C[i][j_col + 31] = temp2[31];
        C[i][j_col + 32] = temp2[32];
        C[i][j_col + 33] = temp2[33];
        C[i][j_col + 34] = temp2[34];
        C[i][j_col + 35] = temp2[35];
        C[i][j_col + 36