#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmpp;
  int range;
  range = 32;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      tmp = 0;
      inner:
      for (k = -4; k < 5; k++) {
        tmpp = orig[i + k];
        if (tmpp) {
          tmp += tmpp * filter[4 + k];
        }
      }
      sol[i / 64 * 64 + j / 64] = tmp;
    }
  }
}