#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flt;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (row = 0; row < 32; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (col = 0; col < 32; col++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      inner:
      for (flt = 0; flt < 9; flt++) {
        k_col = col + ((flt - 4) % 32);
        k = row + ((flt - 4) / 32);
        if (k_col < 0 || k_col > 31) {
          tmp += orig[row * 32 + col] * filter[flt];
        }
         else if (k < 0 || k > 31) {
          tmp += orig[row * 32 + col] * filter[flt];
        }
         else {
          tmp += orig[k * 32 + k_col] * filter[flt];
        }
      }
      sol[row * 32 + col] = tmp;
    }
  }
}