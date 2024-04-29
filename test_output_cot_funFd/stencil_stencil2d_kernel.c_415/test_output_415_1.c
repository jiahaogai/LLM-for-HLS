#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int filter_elem;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        int i_up;
        int i_down;
        int j_left;
        int j_right;
        i_up = i - 4 + ((filter_elem / 8));
        i_down = i - 4 + ((8 - (filter_elem / 8)));
        j_left = j - 4 + ((filter_elem % 8));
        j_right = j - 4 + ((8 - (filter_elem % 8)));
        if (i_up < 0) {
          i_up = 0;
        }
        if (i_down > 255) {
          i_down = 255;
        }
        if (j_left < 0) {
          j_left = 0;
        }
        if (j_right > 255) {
          j_right = 255;
        }
        t += (orig[i_up * 256 + j_left] - orig[i_down * 256 + j_right]) * filter[filter_elem];
      }
      sol[i * 256 + j] = t;
    }
  }
}