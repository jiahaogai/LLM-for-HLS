#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int fidx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        fidx = k - 4;
        idx = (256 + i + ((fidx >> 3) - 1)) % 256;
        fidx = k - 4 & 15;
        idx = j + ((fidx >> 3) - 1);
        if (idx < 0) {
          idx += 256;
        }
        else {
          idx %= 256;
        }
        val += orig[idx] * filter[k];
      }
      sol[i * 256 + j] = val;
    }
  }
}