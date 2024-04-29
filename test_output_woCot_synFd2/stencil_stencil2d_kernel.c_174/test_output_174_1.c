#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -4; k <= 4; k++) {
        idx = (i - 1) * 8192 + (j - 1) + k;
        if (idx < 0) {
          idx = 0;
        }
        else if (idx > 8191) {
          idx = 8191;
        }
        s += orig[idx] * filter[k + 4];
      }
      sol[i * 8192 + j] = s;
    }
  }
//#pragma endscop
}