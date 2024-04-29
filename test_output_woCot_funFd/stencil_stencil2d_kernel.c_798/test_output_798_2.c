#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + neighbor[k].i]) * 256 + j + neighbor[k].j;
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{8}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer_sol:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle_sol:
    for (j = 0; j < 256; j++) {
      int _in_val = sol[i * 256 + j];
      orig[i * 256 + j] = _in_val;
    }
  }
}