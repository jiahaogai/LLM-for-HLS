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
  pad = 1;
  pad2 = ((pad * 2) + 1);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (r = 0; r < 8; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (q = 0; q < 8; q++) {
      sum = 0.0;
      inner:
      for (p = 0; p < 9; p++) {
        r_col = pad2 + (r + p) % 8;
        r_row = pad2 + (q + p) % 8;
        sum += filter[p] * orig[r_col * 8 + r_row];
      }
      sol[r * 8 + q] = sum;
    }
  }
}