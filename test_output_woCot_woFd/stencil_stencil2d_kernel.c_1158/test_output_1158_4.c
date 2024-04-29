#pragma ACCEL kernel

__kernel void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    for (j = 1; j < 32 + 1 - 1; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (i + off[k].i) * 32 + j + off[k].j;
        s += filter[k] * orig[idx];
      }
      sol[i * 32 + j] = s;
    }
  }
//#pragma endscop
}