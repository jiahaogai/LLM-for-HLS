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
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ftidx = -(4 + k);
        idx = i + ftidx;
        if (idx < 0 || idx >= 256) {
          idx = (idx < 0 ? -1 : 0);
        }
        ftidy = -(4 + k);
        idy = j + ftidy;
        if (idy < 0 || idy >= 256) {
          idy = (idy < 0 ? -1 : 0);
        }
        t += ((orig[idx + ((idy) * 256)] * filter[k]));
      }
      sol[i + (j * 256)] = t;
    }
  }
}