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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_l2:
    for (j = 0; j < 8; j++) {
      loop_l3:
      for (k = 0; k < 8; k++) {
        ti = i - 4 + ((8 - 1) << 3);
        tj = j - 4 + ((8 - 1) << 3);
        tk = k - 4 + ((8 - 1) << 3);
        idx = ti * 64 + tj;
        idy = tk * 8 + j;
        idz = i * 8 + k;
        fl = 0;
        loop_l4:
        for (k = 0; k < 9; k++) {
          fl += filter[k] * orig[idx + (k << 3)] ;
        }
        sol[idz] = fl;
      }
    }
  }
}