#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idy;
  int ftidx;
  int ftidy;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      idx = 0;
      idy = 0;
      t = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      while (ti <= -1 + 8) {
        ftidx = ti + 8;
        if (ftidx >= 0) {
          idx += 1;
          t += ((orig[(ti + 4) * 256 + tj + 4] + orig[ftidx * 256 + tj + 4]) * filter[idx]);
        }
        ti += 1;
      }
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      while (tj <= -1 + 8) {
        ftidy = tj + 8;
        if (ftidy >= 0) {
          idy += 1;
          t += ((orig[ti * 256 + tj + 4] + orig[ti * 256 + ftidy]) * filter[idy]);
        }
        tj += 1;
      }
      sol[i * 256 + j] = t;
    }
  }
}