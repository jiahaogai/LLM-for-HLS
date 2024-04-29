#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int k1;
  int k2;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 8;j++) {...} */
  for (j = 1; j < 8; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 8;k++) {...} */
    for (k = 1; k < 8; k++) {
      k1 = 8 * j - 1;
      k2 = 8 * k - 1;
      mul = filter[0] * orig[k1 + k2];
      
#pragma ACCEL PARALLEL reduction=mul FACTOR=auto{9}
      loopr:
      for (r = 1; r < 9; r++) {
        i = k1 + r;
        temp = filter[r] * orig[i];
        mul += temp;
      }

/* Standardize from: sol[k1 + k2] = mul; */
      sol[k1 + k2] = mul;
    }
  }
}