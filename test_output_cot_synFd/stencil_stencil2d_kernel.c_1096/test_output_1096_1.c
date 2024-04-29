#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int pad;
  int pad2;
  int r_col;
  int r_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  pad = 1;
  pad2 = pad << 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (r = pad; r < 64 + pad; r++) {
    inner_row:
    for (r_row = 0; r_row < 3; r_row++) {
      inner_col:
      for (r_col = 0; r_col < 3; r_col++) {
        int _r = r - pad + r_row;
        int _c = pad + r_col;
        sum = ((double )0);
        total:
        for (q = 0; q < 9; q++) {
          sum += filter[q] * orig[_r * 64 + _c + ((q - 4) << 6)];
        }
        sol[_r * 64 + _c] = sum;
      }
    }
  }
}