#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        row = i * 8 + k - 4;
        col = j * 8 + k - 4;
        if (row < 0 || 8 <= row || col < 0 || 8 <= col) {
          t += 0;
        }
         else {
          t += orig[row * 8 + col] * filter[k];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}