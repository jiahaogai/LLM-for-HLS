#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int bi;
  int bj;
  bi = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_bi:
  for ( ; bi < 8; bi++) {
    bj = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    loop_bj:
    for ( ; bj < 8; bj++) {
      tmp = 0;
      loop_k:
      for (k = -4; k <= 4; k++) {
        tmp += filter[4 + k] * orig[bi * 64 + bj * 8 + k];
      }
      sol[bi * 64 + bj * 8 + 4] = tmp;
    }
  }
}