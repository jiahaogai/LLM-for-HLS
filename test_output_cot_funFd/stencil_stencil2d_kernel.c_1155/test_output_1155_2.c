#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int ftidx;
  int ftidy;
  int tidx;
  int tidy;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i - 4 + ((int )0);
      idy = j - 4 + ((int )0);
      sol[i * 256 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        ftidx = idx + ((int )filter[k]);
        ftidy = idy + ((int )filter[k + 8]);
        tidx = ftidx;
        tidy = ftidy;
        if (ftidx < 0) {
          tidx = 0;
        }
         else {
          if (ftidx > 255) {
            tidx = 255;
          }
        }
        if (ftidy < 0) {
          tidy = 0;
        }
         else {
          if (ftidy > 255) {
            tidy = 255;
          }
        }
        sol[i * 256 + j] += orig[tidx * 256 + tidy] * ((int )filter[k]);
      }
    }
  }
}