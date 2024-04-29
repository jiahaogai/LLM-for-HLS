Code: `
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      for (k = 0; k < 9; k++) {
        sol[i * 8192 + j] += filter[k] * orig[(i + pad[0]) * 8192 + (j + pad[1]) * 9 + k];
      }
    }
  }
//#pragma endscop
}
`