#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8192; j++) {
      val = 0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = j + k;
        if (((k_col >= 0) && (k_col < 8192))) {
          idx = i * 8192 + k_col;
          val += filter[((k + 4) * 256)] * orig[idx];
        }
      }
      sol[i * 8192 + j] = val;
    }
  }
}