#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 8192; i++) {
    int val = ((int )0);
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 9; j++) {
      row = i - 4 + j / 5;
      col = j % 5;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      if ((row >= 0) && (row < 8192) && (col >= 0) && (col < 8)) {
        val += ((int )filter[j]) * orig[row * 8 + col];
      }
    }
    sol[i] = val;
  }
}