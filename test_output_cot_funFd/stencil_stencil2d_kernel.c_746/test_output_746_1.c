#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 32 + 1 - 1; k++) {
      i = k + j * (32 + 1);
      val = ((orig[i - 1 - (32 + 1)] + orig[i - (32 + 1)]) + orig[i + (32 + 1) - 1]) + orig[i + (32 + 1)];
      sol[i] = val;
/* Standardize from: for(idx = 1... */
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopidx:
      for (idx = 1; idx < 9; ++idx) {
        filter[idx] = val;
        val = ((orig[i - 1 - (32 + 1)] + orig[i - (32 + 1)]) + orig[i + (32 + 1) - 1]) + orig[i + (32 + 1)];
      }
    }
  }
}