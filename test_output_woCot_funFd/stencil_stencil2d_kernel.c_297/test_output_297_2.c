Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 64; j++) {
      temp = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = j + ((k % 3) - 1);
        k_row = i + ((k / 3) - 1);
        if ((((k_row >= 0) && (k_row < 128))) && (((k_col >= 0) && (k_col < 64)))) {
          temp += filter[k] * orig[k_row * 64 + k_col];
        }
      }
      sol[i * 64 + j] = temp;
    }
  }
}