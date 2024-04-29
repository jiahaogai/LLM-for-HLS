<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil3d(long C0,long C1,long orig[25][25][25],long sol[25][25][25])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long kj;
  long i_col;
  long j_col;
  long k_col;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sum0 = 0;
  sum1 = 0;
  i_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  j_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k_col = 2;
  
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  while (i < 25 - 1) {
=======
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  ko = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  while (ko < 32) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    j = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (j < 25 - 1) {
=======
    ki = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (ki < 25) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
      k = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 25 - 1) {
        ko = i + 1;
        ki = i - 1;
        kj = j + 1;
        sum0 = orig[ko][j][k] + orig[ki][j][k] + orig[ko][kj][k] + orig[ki][kj][k] - 
          orig[ko][j][ki] - orig[ki][j][ki] - orig[ko][ki][k] - orig[ki][ki][k];
        mul0 = sum0 * C0;
        k--;
        sum1 = orig[ko][j][k] + orig[ki][j][k] + orig[ko][kj][k] + orig[ki][kj][k] - 
          orig[ko][j][ki] - orig[ki][j][ki] - orig[ko][ki][k] - orig[ki][ki][k];
        mul1 = sum1 * C1;
        sol[i][j][k] = mul0 + mul1;
      }
      k = 25 - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma A
=======
      kj = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      while (kj < 25) {
        i = ko + 1;
        j = ki + 1;
        k = kj + 1;
        sum0 += orig[i][j][k] - ((orig[i][j][k - 1] + orig[i][j][k + 1]) + (orig[i][j - 1][k] + orig[i][j + 1][k]) + (orig[i - 1][j][k] + orig[i + 1][j][k])) / 4;
        sum1 += orig[i][j][k] - ((orig[i][j][k - 1] + orig[i][j][k + 1]) + (orig[i][j - 1][k] + orig[i][j + 1][k]) + (orig[i - 1][j][k] + orig[i + 1][j][k])) / 6;
      }
      ki++;
    }
    k_col++;
  }
  ko = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  ki = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  while (ki < 25 - 1) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    kj = 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (kj < 25 - 1) {
      i = ko + 1;
      j = ki + 1;
      k = kj + 1;
      mul0 = sum0 * C0;
      mul1 = sum1 * C1;
      sol[i][j][k] = mul0 - mul1;
      sum0 = 0;
      sum1 = 0;
      kj++;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = kj - 1; k < 25 - 1; k++) {
        i = ko + 1;
        j = ki + 1;
        sum0 += orig[i][j][k + 1] - orig[i][j][k - 1];
        sum1 += orig[i][j + 1][k] - orig[i][j - 1][k];
      }
      k = kj + 1;
      j = ki + 1;
      sum0 += orig[ko + 1][j][k] - orig[ko - 1][j][k];
      sum1 += orig[ko + 1][j + 1][k] - orig[ko + 1][j - 1][k];
    }
    ki++;
    k_col++;
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
