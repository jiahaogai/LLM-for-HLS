#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int t;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 0 + 1; j < 33 - 1 + 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      int _in_k_col = 0 + k_col;
      int _in_j_col = _in_j - 1 - 0 + _in_k_col;
      i_col = _in_j_col;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{62}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        int _in_i = 1 + i;
        j_col = i_col;
        t = 0;
        loopk:
        for (k = 1; k < 3 + 1; k++) {
          int _in_k = 1 + k;
          t += filter[k] * orig[(_in_k_col - 1 + _in_k) * 32 + _in_i - 1 + _in_k];
        }
	sol[(_in_k_col - 1 + 1) * 32 + _in_i - 1 + 1] = t;
      }
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 0) * (256 + 1) * k + (256 + 1) * j + i;
        val += filter[k] * orig[idx];
      }
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}