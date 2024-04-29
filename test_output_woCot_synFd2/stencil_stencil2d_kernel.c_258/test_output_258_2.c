#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        if ((8191 > ((i + k) - 1))) {
          result += filter[((k + 4) << 3) + (k + 4)] * orig[((i + k) - 1) * 8186 + j - 1];
        }
      }
      sol[(i - 1) * 8186 + j - 1] = result;
    }
  }
}