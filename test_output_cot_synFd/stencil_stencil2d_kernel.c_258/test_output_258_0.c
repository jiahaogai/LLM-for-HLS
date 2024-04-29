#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (8190 * (k - 4)) + j;
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 8186) {
          idx = 8186;
        }
        s += orig[idx] * filter[k];
      }
      sol[i * 8190 + j] = s;
    }
  }
}