#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil_label1:
  for (i = 4096; i < 8192 - 4096; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    stencil_label2:
    for (j = 0; j < 64; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{8}
      stencil_label3:
      for (k = -4; k < 5; k++) {
        idx = i + k * 64;
        val += filter[k + 4] * orig[idx];
      }
      sol[i] = val;
    }
  }
}