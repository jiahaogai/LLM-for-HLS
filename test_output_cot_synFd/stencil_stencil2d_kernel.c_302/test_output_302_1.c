# pragma ACCEL kernel


#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
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
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 8192 - 1; k++) {
      idx0 = (j - 1) * 8192 + k - 1;
      idx1 = (j - 1) * 8192 + k;
      idx2 = (j - 1) * 8192 + k + 1;
      idx3 = (j) * 8192 + k - 1;
      idx4 = (j) * 8192 + k;
      idx5 = (j) * 8192 + k + 1;
      idx6 = (j + 1) * 8192 + k - 1;
      idx7 = (j + 1) * 8192 + k;
      idx8 = (j + 1) * 8192 + k + 1;
      val = ((filter[0] * orig[idx0]) + (filter[1] * orig[idx1]) + (filter[2] * orig[idx2])) + ((filter[3] * orig[idx3]) + (filter[4] * orig[idx4]) + (filter[5] * orig[idx5])) + ((filter[6] * orig[idx6]) + (filter[7] * orig[idx7]) + (filter[8] * orig[idx8]));
      sol[idx4] = val;
    }
  }
}