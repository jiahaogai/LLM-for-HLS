#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 1; j <= 32; j++) {
    int _in_j = 0 + 32 * (j - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 33;k++) {...} */
    for (k = 1; k <= 32; k++) {
      int _in_k = 0 + 32 * (k - 1);
      int val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_fl:
/* Standardize from: for(fl = 0;fl < 9;fl++) {...} */
      for (fl = 0; fl < 9; fl++) {
        int _fl = fl;
        int _in_idx = _in_k + _fl;
        val += ((int )filter[_fl]) * orig[_in_idx];
      }
      sol[_in_j] = val;
    }
  }
}