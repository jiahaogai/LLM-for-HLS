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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      for (k = 0; k < 8; k++) {
        ti = i - 4 + 0;
        tj = j - 4 + 0;
        tk = k - 4 + 0;
        idx = ti * 64 + tj * 8 + tk;
        fl = filter[0];
        sol[idx] = orig[idx] + fl * (orig[idx + 64 * 8] + orig[idx + 64] + orig[idx - 64] + orig[idx - 64 * 8]);
        fl = filter[1];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 1] + orig[idx + 64 + 1] + orig[idx - 64 + 1] + orig[idx - 64 * 8 + 1]);
        fl = filter[2];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 2] + orig[idx + 64 + 2] + orig[idx - 64 + 2] + orig[idx - 64 * 8 + 2]);
        fl = filter[3];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 3] + orig[idx + 64 + 3] + orig[idx - 64 + 3] + orig[idx - 64 * 8 + 3]);
        fl = filter[4];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 4] + orig[idx + 64 + 4] + orig[idx - 64 + 4] + orig[idx - 64 * 8 + 4]);
        fl = filter[5];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 5] + orig[idx + 64 + 5] + orig[idx - 64 + 5] + orig[idx - 64 * 8 + 5]);
        fl = filter[6];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 6] + orig[idx + 64 + 6] + orig[idx - 64 + 6] + orig[idx - 64 * 8 + 6]);
        fl = filter[7];
        sol[idx] = sol[idx] + fl * (orig[idx + 64 * 8 + 7] + orig[idx + 64 + 7] + orig[idx - 64 + 7] + orig[idx - 64 * 8 + 7]);
      }
    }
  }
}