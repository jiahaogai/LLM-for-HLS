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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (ftidy = 0; ftidy < 5; ftidy++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        for (ftidx = 0; ftidx < 5; ftidx++) {
          idx = ti + ftidx;
          idy = tj + ftidy;
          if (idx < 0 || idx > 255 || idy < 0 || idy > 255) {
            t += filter[ftidx + ftidy * 5] * 0;
          }
           else {
            t += filter[ftidx + ftidy * 5] * orig[idx + idy * 256];
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}