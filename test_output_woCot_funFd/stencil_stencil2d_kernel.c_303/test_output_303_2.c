#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int s;
  int jj;
  int jj_col;
  int flatten_i;
  int flatten_j;
  int pad_col;
  int pad_row;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  pad_col = 1;
  pad_row = 1;
  
#pragma ACCEL PARALLEL PAD_FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL PAD_FACTOR=auto{8}
    loop_j:
    for (j = 0; j < 64; j++) {
      s = 0.0;
      loop_k:
      for (k = 0; k < 9; k++) {
        jj = i + ((k / 3) - 1);
        jj_col = j + ((k % 3) - 1);
        if ((jj >= 0) && (jj_col >= 0) && (jj < 64) && (jj_col < 64)) {
          flatten_i = i * 64 + jj;
          flatten_j = jj_col;
          s += ((double )filter[k]) * orig[flatten_i * 64 + flatten_j];
        }
      }
      sol[i * 64 + j] = s;
    }
  }
}