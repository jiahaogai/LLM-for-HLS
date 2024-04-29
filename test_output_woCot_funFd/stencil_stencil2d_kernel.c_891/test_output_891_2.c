#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 1; j < 400 - 1; j++) {
      flatten_i = i + 400;
      flatten_j = j + 400;
      sol[i][j] = ((orig[i][j] + orig[flatten_i][j] + orig[i][flatten_j] + orig[flatten_i][flatten_j]) / 4) - (filter[0] * (sol[i][j] + sol[flatten_i][j] + sol[i][flatten_j] + sol[flatten_i][flatten_j])) + (filter[1] * (orig[i + 1][j] + orig[flatten_i + 1][j] + orig[i][j + 1] + orig[flatten_i][j + 1] + orig[i + 1][j + 1] + orig[flatten_i + 1][j + 1] + orig[i][j - 1] + orig[flatten_i][j - 1] + orig[i - 1][j] + orig[flatten_i - 1][j])) - (filter[2] * (orig[i - 1][j - 1] + orig[flatten_i - 1][j - 1] + orig[i - 1][j + 1] + orig[flatten_i - 1][j + 1] + orig[i + 1][j - 1] + orig[flatten_i + 1][j - 1] + orig[i + 1][j + 1] + orig[flatten_i + 1][j + 1]));
    }
  }
}