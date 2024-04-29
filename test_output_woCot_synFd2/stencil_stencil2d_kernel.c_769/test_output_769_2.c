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
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      ti = 8 * i;
      tj = 8 * j;
      idx = ti - 1;
      idy = tj - 1;
      inner:
      for (ftidy = 0; ftidy < 5; ftidy++) {
        ftidx = ftidy - 1;
        if (idx + ftidx >= 0 && idy + ftidy >= 0 && idx + ftidx < 8192 && idy + ftidy < 8192) {
          result += filter[ftidy * 5 + ftidx] * orig[idx + ftidx + (idy + ftidy) * 8192];
        }
      }
      sol[ti + tj] = result;
      result = 0;
    }
  }
}