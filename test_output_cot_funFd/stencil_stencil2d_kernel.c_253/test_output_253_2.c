#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        int flattener;
        flattener = k * 8192;
        cur = i + k;
        if (cur < 0 || cur >= 8192) {
          cur = pad * 8192;
        }
        t += filter[((k + 1) + pad)] * orig[cur + j + flattener];
      }
      sol[i * 8192 + j] = t;
    }
  }
}