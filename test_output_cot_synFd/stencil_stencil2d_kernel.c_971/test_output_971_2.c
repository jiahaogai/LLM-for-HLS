#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int r;
  int r_col;
  int c;
  int c_col;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      temp = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        k_col = k + 4;
        r = i + k;
        if (((r < 0) || (r > 63))) {
          r_col = 0;
        }
         else {
          r_col = r;
        }
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{1}
        for (c = -4; c <= 4; c++) {
          c_col = c + 4;
          if ((((r_col == 0)) && (c_col < 0))) {
            c_col = 0;
          }
           else if ((((r_col == 0)) && (c_col > 63))) {
            c_col = 63;
          }
           else if ((((r_col == 63)) && (c_col < 0))) {
            c_col = 0;
          }
           else if ((((r_col == 63)) && (c_col > 63))) {
            c_col = 63;
          }
           else if (((r_col < 0)) && (c_col >= 0)) {
            r_col = 0;
            c_col = c;
          }
           else if (((r_col > 63)) && (c_col >= 0)) {
            r_col = 63;
            c_col = c;
          }
           else if (((r_col < 0)) && (c_col > 63)) {
            c_col = 63;
          }
           else if (((r_col > 63)) && (c_col > 63)) {
            c_col = 63;
          }
           else {
            c_col = c_col;
          }
          temp += ((filter[k + 4]) * (orig[r_col * 64 + c_col])) ;
        }
      }
      sol[i * 64 + j] = temp;
    }
  }
}