#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) to: for(int j ... ) */
  for(int j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk:
/* Standardize from: for(k ... ) to: for(int k ... ) */
    for(int k = 1; k < 33 - 1; k++) {
      idx = (j - 1) * (33 - 2) + (k - 1);
      val = orig[idx] + filter[0] * orig[idx + 33] + filter[1] * orig[idx + 33 + 1] + filter[2] * orig[idx + 33 + 2] + filter[3] * orig[idx + 1] + filter[4] * orig[idx + 1 + 1] + filter[5] * orig[idx + 1 + 2] + filter[6] * orig[idx - 1] + filter[7] * orig[idx - 1 + 1] + filter[8] * orig[idx - 1 + 2];
      sol[idx] = val;
    }
  }
}