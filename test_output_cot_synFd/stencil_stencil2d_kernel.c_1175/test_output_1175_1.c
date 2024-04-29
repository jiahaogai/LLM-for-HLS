#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{9}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      row = i - 4;
      col = j - 4;
      k = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (int _in_k = 0; _in_k < 9; _in_k++) {
        int _k = filter[k++];
        int _row = row + _k;
        int _col = col + _k;
        sol[i] += orig[_row * 8192 + _col] * _k;
      }
    }
  }
}