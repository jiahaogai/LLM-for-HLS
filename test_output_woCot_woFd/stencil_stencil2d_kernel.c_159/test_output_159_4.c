#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        int flt;
        int res;
        cur = orig[i * 8 + j];
        flt = filter[pad + k];
        res = cur * flt;
        t += res;
      }
      sol[i * 8 + j] = t;
    }
  }
}