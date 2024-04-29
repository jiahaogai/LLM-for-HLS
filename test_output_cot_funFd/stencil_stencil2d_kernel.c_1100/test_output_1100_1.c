#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int idxm2;
  int idym2;
  int idxp2;
  int idyp2;
  int idxm1;
  int idym1;
  int idxp1;
  int idyp1;
  int idx0;
  int idy0;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loopj0:
/* Standardize from: for(j = 1;j < 31;j++) {...} */
  for (j = 1; j <= 31 - 1; j++) {
    int _in_j = 0 + 32 * (j);
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi0:
/* Standardize from: for(i = 1;i < 31;i++) {...} */
    for (i = 1; i <= 31 - 1; i++) {
      int _in_i = 0 + 1 * (i);
      idx0 = _in_i + _in_j;
      idy0 = _in_i + 32 * (j);
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        int _in_k = 0 + 1 * (k);
        idx = idx0 + _in_k;
        idy = idy0 + _in_k;
        if (idx >= 0 && idx < 8192 && idy >= 0 && idy < 8192) {
          t += filter[k] * orig[idx];
        }
      }
      sol[idy0] = t;
    }
  }
}