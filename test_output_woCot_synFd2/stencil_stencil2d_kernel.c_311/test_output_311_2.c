#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 8191;j++) {...} */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
    for (k = 1; k < 8191; k++) {
      idx0 = k - 1;
      idx1 = k;
      idx2 = k + 1;
      idx3 = k + 1 + 8191;
      idx4 = k + 8191;
      idx5 = k - 1 + 8191;
      idx6 = idx1 - 8191;
      idx7 = idx1 + 1;
      idx8 = idx1 + 1 + 8191;
      idx = idx1 * 8192 + j;
      sol[idx] = ((filter[0] * orig[idx0]) + (filter[1] * orig[idx1]) + (filter[2] * orig[idx2]) + (filter[3] * orig[idx3]) + (filter[4] * orig[idx4]) + (filter[5] * orig[idx5]) + (filter[6] * orig[idx6]) + (filter[7] * orig[idx7]) + (filter[8] * orig[idx8])) / 408.0;
    }
  }
}