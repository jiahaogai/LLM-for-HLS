#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int r;
  int q;
  int p;
  int r_col;
  int q_col;
  int p_col;
  int r_row;
  int q_row;
  int p_row;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (r = 1; r < 400 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (q = 1; q < 400 - 1; q++) {
      sol[r][q] = 0.0;
      inner:
      for (p = 0; p < 25; p++) {
        r_col = r + ((p + 1) / 25) - 1;
        q_col = q + ((p + 1) % 25) - 1;
        p_col = p - ((p + 1) % 25);
        r_row = r + (-(p + 1) / 25);
        q_row = q + (-(p + 1) % 25);
        p_row = p - (-(p + 1) % 25);
        sol[r][q] += filter[p] * orig[r_col][q_col] + filter[p_col] * orig[r_row][q_row] + filter[p_row] * orig[r_row][q_col];
      }
    }
  }
}