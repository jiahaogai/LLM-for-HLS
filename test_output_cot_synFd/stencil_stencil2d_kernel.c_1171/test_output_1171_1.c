#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      t = 0;
      int _in_i = i - 1 + pad;
      int _in_j = j - 1 + pad;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        int _flt_i = k / 3 - 1 + pad;
        int _flt_j = k % 3 - 1 + pad;
        t += orig[_in_i * 64 + _in_j] * filter[_flt_i * 3 + _flt_j];
      }
      sol[i * 64 + j] = t;
    }
  }
}