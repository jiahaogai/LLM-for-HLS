#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int index;
  int fval;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:
/* Standardize from: for(i = 1; i < 8; i++) {...} */
  for (i = 1; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    jloop:
    for (j = 1; j < 8; j++) {
      kloop:
      for (k = 1; k < 8; k++) {
        ti = -4 + i;
        tj = -4 + j;
        tk = -4 + k;
        index = ti * 64 + tj * 8 + tk;
        fval = filter[k + 4];
        sol[index] = fval * orig[index];
      }
    }
  }
}