#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i * 8 + j] + orig[i * 8 + j + 1] + orig[i * 8 + j + 8] + orig[i * 8 + j - 1] + orig[i * 8 + j - 8] + orig[(i - 1) * 8 + j] + orig[(i - 1) * 8 + j + 1] + orig[(i - 1) * 8 + j - 1] + orig[(i - 1) * 8 + j + 8] + orig[(i - 1) * 8 + j - 8]) / 10) + filter[4];
      sol[i * 8 + j] = result;
    }
  }
//#pragma endscop
}