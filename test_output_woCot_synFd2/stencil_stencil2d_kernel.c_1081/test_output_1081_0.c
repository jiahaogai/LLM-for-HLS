#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{6}
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      sol[i * 8 + j] = 0;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i * 8 + j] += filter[k] * orig[i * 8 + j + k - 4];
      }
    }
  }
//#pragma endscop
}