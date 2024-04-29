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
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      inner:
      for (k = 0; k < 128 + 2; k++) {
        ti = i - 1;
        tj = j - 1;
        tk = k - 1;
        idx = ti * 128 + tj;
        idy = idx + 128;
        idz = idy + 1;
        fl = filter[0] * orig[idx] + filter[1] * orig[idy] + filter[2] * orig[idz];
        sol[idx] = fl;
        fl = filter[3] * orig[idx] + filter[4] * orig[idy] + filter[5] * orig[idz];
        sol[idy] = fl;
        fl = filter[6] * orig[idx] + filter[7] * orig[idy] + filter[8] * orig[idz];
        sol[idz] = fl;
      }
    }
  }
}