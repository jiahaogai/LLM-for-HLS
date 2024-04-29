**Filter Coefficients:**  
`int filter[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1}`

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_i = i + ((k - 4) >> 1);
        int cur_j = j + ((k - 4) & 1);
        //
        // Boundary Check
        //
        if (cur_i >= 0 && cur_i < 256 && cur_j >= 0 && cur_j < 256) {
          result += cur_filter * orig[cur_i * 256 + cur_j];
        }
      }
      sol[i * 256 + j] = result;
    }
  }
}