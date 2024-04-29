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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      middle:
      for (k = 0; k < 9; k++) {
        ftidx = ((4 - ((8 * i) + ((k + 4) & 7)))) - 1;
        ftidy = ((4 - ((8 * j) + ((k + 4) & 7)))) - 1;
        idx = (8 * i) + (k & 7);
        idy = (8 * j) + (k & 7);
        t += filter[k] * orig[idx + ((-ftidy) & 127) + ((-ftidx) & 127) * 256];
      }
      sol[j + i * 256] = t;
    }
  }
}