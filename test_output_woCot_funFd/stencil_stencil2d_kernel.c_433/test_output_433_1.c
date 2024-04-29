#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0; j < 256; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 256; i++) {
      i_col = ((256 + 1 - 2) + i) % 256;
      j_col = ((256 + 1 - 2) + j) % 256;
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk:
      for (k = 0; k < 9; k++) {
        k_col = ((256 + 1 - 2) + k) % 256;
        flit += ((orig[i_col * 256 + j_col] * filter[k]) << 7);
      }
      sol[i * 256 + j] = flit >> 7;
    }
  }
}