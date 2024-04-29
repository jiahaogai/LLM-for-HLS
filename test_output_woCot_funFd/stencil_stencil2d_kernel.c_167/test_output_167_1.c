#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double FLT_SCALE = 1.0 / ((double )8192);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8;j++) {...} */
  for (j = 0 + 1; j < 8 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 8;k++) {...} */
    for (k = 0 + 1; k < 8 + 1; k++) {
      i = k + ((j + 1) * 8);
      sum = ((filter[0] * orig[i]) + (filter[1] * (orig[i + 1] + orig[i - 1])) + (filter[2] * orig[i + 8]) + (filter[3] * (orig[i + 9] + orig[i - 9])) + (filter[4] * orig[i + 16]) + (filter[5] * (orig[i + 17] + orig[i - 17])) + (filter[6] * orig[i + 24]) + (filter[7] * (orig[i + 25] + orig[i - 25])) + (filter[8] * orig[i + 32]));
      sum *= FLT_SCALE;
      sol[i] = sum;
    }
  }
}