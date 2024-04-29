Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 256; i < 128 + 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 32; j < 64 + 32; j++) {
      idx = i * 64 + j;
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{31}
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + align[k]];
      }
      sol[idx] = val;
    }
  }
}