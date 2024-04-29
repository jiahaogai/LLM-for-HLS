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
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{2}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (i + k) * 8192 + j;
        if ((((i + k) >= 0) && ((i + k) < 8192))) {
          s += ((orig[idx]) * (filter[k + 4]));
        }
      }
      sol[i * 8192 + j] = s;
    }
  }
}