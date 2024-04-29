Code: #pragma ACCEL kernel
 
#pragma ACCEL PIPELINE auto{off}
 
#pragma ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8190; j++) {
      sol[i * 8192 + j] = filter[4] * orig[i * 8192 + j] + filter[1] * (orig[i * 8192 + j - 1] + orig[i * 8192 + j + 1]) + filter[2] * (orig[i * 8192 + j - 8192] + orig[i * 8192 + j + 8192]) + filter[3] * (orig[i * 8192 + j - 8194] + orig[i * 8192 + j + 8194]);
    }
  }
//#pragma endscop
}