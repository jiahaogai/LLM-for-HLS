Details:

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int idy;
  int idz;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_l1:
/* Standardize from: for(i = 0; i < 32; i++) {...} */
  for (i = 0; i <= 31; i++) {
    ti = 1 * i;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_l2:
/* Standardize from: for(j = 0; j < 32; j++) {...} */
    for (j = 0; j <= 31; j++) {
      tj = 32 * ti + 1 * j;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_l3:
/* Standardize from: for(k = 0; k < 32; k++) {...} */
      for (k = 0; k <= 31; k++) {
        tk = 90184 * tj + 32 * k;
        idx = 1 * i - 1 + 0;
        idy = 1 * j - 1 + 0;
        idz = 1 * k - 1 + 0;
        fl = filter[0];
        sol[tk] = orig[idx][idy][idz] * fl;
        loop_k:
#pragma ACCEL PARALLEL FACTOR=auto{6}
        for (kd = 1; kd <= 8; kd++) {
          idz = 1 * kd - 1 + k;
          fl = filter[kd];
          sol[tk] += orig[idx][idy][idz] * fl;
        }
      }
    }
  }
}