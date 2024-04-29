#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t_j;
  int t_k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 9; j++) {
      t_j = i + ((j - 4) * 64);
      // bounds check
      if (((t_j >= 0) && (t_j < 8192))) {
        tmp += ((orig[t_j]) * (filter[j])) ;
      }
    }
    sol[i] = tmp;
  }
}