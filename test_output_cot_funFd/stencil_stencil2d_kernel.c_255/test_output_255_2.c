#pragma ACCEL kernel

void stencil(int orig[400],int sol[400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int ind_row;
  int ind_col;
  int ind;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 9; i++) {
     flatten_filter[i] = filter[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    val = 0;
    ind_row = i - 4 + 0;
    ind_col = 0 - 4 + 0;
    for (j = 0; j < 9; j++) {
      ind = ind_row + sizeof(int) * j % 8;
      val += flatten_filter[j] * orig[ind] + 0;
    }
    sol[i] = val;
  }
}