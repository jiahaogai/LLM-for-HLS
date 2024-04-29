Details: 

--->
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 256; j++) {
      oidx = i * 256 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{8}
      filter:
      for (k = 0; k < 9; k++) {
        idx = oidx + fl[k];
        val += orig[idx] * filter[k];
      }
      sol[oidx] = val;
    }
  }
}