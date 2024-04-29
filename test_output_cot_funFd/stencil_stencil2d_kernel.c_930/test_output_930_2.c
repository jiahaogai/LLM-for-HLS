#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fa;
  int tmp;
  int i_up;
  int i_down;
  int j_left;
  int j_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 1; j < 64 - 1; j++) {
      i_up = i - 1;
      i_down = i + 1;
      j_left = j - 1;
      j_right = j + 1;
      idx = i * 64 + j;
      fa = filter[4];
      tmp = fa * orig[i_up * 64 + j_left];
      tmp += fa * orig[i_up * 64 + j];
      tmp += fa * orig[i_up * 64 + j_right];
      tmp += fa * orig[i * 64 + j_left];
      tmp += fa * orig[i * 64 + j_right];
      tmp += fa * orig[i_down * 64 + j_left];
      tmp += fa * orig[i_down * 64 + j];
      tmp += fa * orig[i_down * 64 + j_right];
      sol[idx] = tmp;
    }
  }
}