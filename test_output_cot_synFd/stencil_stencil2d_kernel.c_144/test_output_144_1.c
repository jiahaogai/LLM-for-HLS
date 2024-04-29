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
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 32; j-- > 32 - 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 32; k-- > 32 - 1; ) {
      idx = (j - 1) * 32 + k - 1;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
      loopi:
      for (i = 32; i--; ) {
        val += orig[idx + i - 1] * filter[i];
      }
      sol[idx] = val;
    }
  }
}