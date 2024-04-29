#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      loopk:
      for (k = j - 4; k <= j + 4; k++) {
        i_col = i - 4 + k_col;
        if ((((i_col >= 0) && (i_col < 8191))) && (((k >= 0) && (k < 8191)))) {
          sum += filter[k_col] * orig[i_col + ((k * 8192) + j)];
        }
        k_col++;
      }
      sol[i + ((j * 8192) + 8192)] = sum;
    }
  }
}