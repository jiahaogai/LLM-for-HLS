#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      value = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i + ((400 + 8 - 1) * (k / 8));
        idy = j + ((400 + 8 - 1) * (k % 8));
        value += orig[idx][idy] * filter[k];
      }
      sol[i][j] = value;
    }
  }
}