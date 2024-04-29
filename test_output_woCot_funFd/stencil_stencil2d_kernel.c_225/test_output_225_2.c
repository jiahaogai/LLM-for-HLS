Code: #pragma ACCEL kernel

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
  for (i = 8; i < 8184 - 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8192 - 8; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) >> 2)][j + ((k - 4) & 4)];
      }
      sol[i][j] = result;
    }
  }
//#pragma endscop
}