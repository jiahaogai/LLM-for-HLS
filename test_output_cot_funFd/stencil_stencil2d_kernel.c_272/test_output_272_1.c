#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int col;
  int index;
  int value;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (row = 1; row < 400 - 1; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (col = 1; col < 400 - 1; col++) {
      value = ((orig[row - 1][col - 1] + orig[row - 1][col + 1]) + (orig[row + 1][col - 1] + orig[row + 1][col + 1])) + orig[row][col];
      sol[row][col] = value;
    }
  }
//#pragma endscop
}