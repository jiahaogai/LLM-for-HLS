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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8184; j += 8) {
      for (k = 8; k < 8192; k += 8) {
        ti = i - 4;
        tj = j - 4;
        tk = k - 4;
        fl = 0;
        for (idx = 0; idx < 8; ++idx) {
          idy = ti + idx;
          for (idz = 0; idz < 8; ++idz) {
            tk += 1;
            fl += orig[idz * 8192 + idy] * filter[idx * 8 + idz];
          }
        }
        sol[k] = fl;
      }
    }
  }
}