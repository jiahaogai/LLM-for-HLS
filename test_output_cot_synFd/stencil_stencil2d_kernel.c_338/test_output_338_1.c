#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int k;
  int flit_row;
  int flit_column;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loop_row:
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_column:
    for (column = 1; column < 400 - 1; column++) {
      flit_row = row - 1;
      flit_column = column - 1;
      sol[row][column] = ((filter[0] * orig[flit_row][flit_column]) + (filter[1] * (orig[flit_row][flit_column + 1] + orig[flit_row][flit_column - 1])) + (filter[2] * (orig[flit_row + 1][flit_column] + orig[flit_row - 1][flit_column]))) + (filter[3] * orig[flit_row + 1][flit_column + 1]) + (filter[4] * (orig[flit_row + 1][flit_column - 1] + orig[flit_row - 1][flit_column + 1]));
    }
  }
}