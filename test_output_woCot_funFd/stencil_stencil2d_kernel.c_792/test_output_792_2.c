Code: #pragma ACCEL kernel
 #pragma ACCEL PIPELINE auto{off}

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sol[i * 8192 + j] = ((filter[0] * orig[i * 8192 + j]) + (filter[1] * (orig[i * 8192 + j - 1] + orig[i * 8192 + j + 1])) + (filter[2] * (orig[i * 8192 + j - 8192] + orig[i * 8192 + j + 8192]))) + ((filter[3] * (orig[i * 8192 + j - 16] + orig[i * 8192 + j + 16])) + (filter[4] * (orig[i * 8192 + j - 16 * 2] + orig[i * 8192 + j + 16 * 2])));
    }
  }
//#pragma endscop
}