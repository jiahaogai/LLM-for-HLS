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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_bi:
  while (bi < 8) {
    bj = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_bj:
    while (bj < 8) {
      tmp = 0;
      loop_k:
      for (k = -4; k < 5; k++) {
        tmp += filter[k + 4] * orig[bi * 64 + bj * 8 + k];
      }
      sol[bi * 64 + bj * 8 + 4] = tmp;
      bj++;
    }
    bi++;
  }
}