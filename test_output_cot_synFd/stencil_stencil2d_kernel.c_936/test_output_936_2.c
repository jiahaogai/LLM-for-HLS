Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        idx = (8192 + orig[-8192 + i + ((k - 4) * 8192)]) % 8192;
        s += filter[k] * orig[idx];
      }
      sol[i * 8192 + j] = s;
    }
  }
//#pragma endscop
}