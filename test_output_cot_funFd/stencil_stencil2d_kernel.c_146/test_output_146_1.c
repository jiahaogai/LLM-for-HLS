#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{126}
#pragma ACCEL PARALLEL FACTOR=auto{1}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      row = i * 64;
      col = j * 64;
      sol[row + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        flit = filter[k] * orig[row + col + k];
        sol[row + col] += flit;
      }
    }
  }
}