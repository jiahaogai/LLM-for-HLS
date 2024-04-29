#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        idx = (i + 4) * 8192 + (j + 4) * 8 + k;
        s += filter[4 + k] * orig[idx];
      }
      sol[i * 8192 + j] = s;
    }
  }
//#pragma endscop
}