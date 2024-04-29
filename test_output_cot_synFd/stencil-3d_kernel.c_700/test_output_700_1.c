#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long i;
  long j;
  long k;
  long r;
  long s;
  long t;
  double _tmp_ = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_i:
  for (i = 1; i < 390 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 390 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for (k = 1; k < 390 - 1; k++) {
        sum_tmp = 0.0;
        r = i - 1;
        s = j - 1;
        t = k - 1;
        loop_r:
        for (; r < i + 2; r++) {
          loop_s:
          for (s = j - 1; s < j + 2; s++) {
            loop_t:
            for (t = k - 1; t < k + 2; t++) {
              _tmp_ = orig[r][s][t];
              sum_tmp += _tmp_;
            }
          }
        }
        sol[i][j][k] = sum_tmp;
      }
    }
  }
}