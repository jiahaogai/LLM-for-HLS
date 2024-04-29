<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 4 + 0; i < 8192 + 0 + 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 4 + 0; j < 8192 + 0 + 4; j++) {
      i_col = i - 4;
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        sum = ((double )0);
        middle_col:
        for (k_col = 0; k_col < 9; k_col++) {
          sum += filter[k_col] * orig[i_col + align[k_col] - 4 + (j + align[k_col] - 4) * 8192];
        }
        sol[i - 4 + j * 8192] = sum;
        k_col++;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
<<<<<<< HEAD
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 0 + 1; j < 33 + 1 - 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 33;k_col++) {...} */
    for (k_col = 0 + 1; k_col < 33 + 1 - 1; k_col++) {
      int _in_k_col = 0 + 1 + k_col;
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 32;i_col++) {...} */
      for (i_col = 0 + 1; i_col < 32 + 1 - 1; i_col++) {
        int _in_i_col = 0 + 1 + i_col;
        sum += filter[0] * orig[(_in_j - 1) * 32 + _in_i_col - 1] + filter[1] * orig[(_in_j - 1) * 32 + _in_i_col + 0] + filter[2] * orig[(_in_j - 1) * 32 + _in_i_col + 1] + filter[3] * orig[_in_j * 32 + _in_i_col - 1] + filter[4] * orig[_in_j * 32 + _in_i_col + 0] + filter[5] * orig[_in_j * 32 + _in_i_col + 1] + filter[6] * orig[(_in_j + 1) * 32 + _in_i_col - 1] + filter[7] * orig[(_in_j + 1) * 32 + _in_i_col + 0] + filter[8] * orig[(_in_j + 1) * 32 + _in_i_col + 1];
      }
      sol[_in_j * 32 + k_col] = sum;
=======
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 8191; i++) {
      i_col = i - 1;
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{2}
      loopk:
      for (k = 1; k < 9; k++) {
        sum = ((double )0);
        k_col++;
        i_col = i - 1;
        sum += ((orig[i_col][k_col] - 32768.0) * filter[k]);
      }
      sol[i][j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}