Code: 
 #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184 - 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8192 - 8; j++) {
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i * 8192 + j] += filter[k] * orig[(i + ((k - 4) > -1 ? (k - 4) : 0)) * 8192 + j + ((k - 4) > -1 ? (k - 4) : 0)];
      }
    }
  }
//#pragma endscop
}