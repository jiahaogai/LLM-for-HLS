#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{7}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int pad;
  pad = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0 + 1 - 1; j < 32 + 1 - 1 + 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0 + 1 - 1; i < 32 + 1 - 1 + 1; i++) {
      k_col = 0;
      
#pragma ACCEL PIPELINE auto{}
      loopk_col:
      for (k = 0; k < 9; k++) {
        k_col = k_col + filter[k] * orig[i + pad + ((j + pad) * 32)];
      }
      sol[i + ((j ) * 32)] = k_col;
    }
  }
}