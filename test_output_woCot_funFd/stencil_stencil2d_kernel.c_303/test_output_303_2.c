#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int s;
  int jj;
  int jj_col;
  int flatten_i;
  int flatten_j;
  int pad_col;
  int pad_row;
=======
  int k_col;
  int buf[9];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
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
=======
  outer:
  for (i = 0; i < 8192; i++) {
     middle:
    for (j = 0; j < 9; j++) {
      buf[j] = orig[i - 4 + j];
    }
    inner:
    for (j = 0; j < 9; j++) {
      k_col = 0;
       inner_par:
      for (k = 0; k < 9; k++) {
        sol[i] += buf[k] * filter[k_col++];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}