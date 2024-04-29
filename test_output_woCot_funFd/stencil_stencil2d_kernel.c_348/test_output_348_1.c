#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int ti;
  int tj;
  int idx;
  int val;
=======
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      ti = ((8 * i) + 1) - 1;
      tj = ((8 * j) + 1) - 1;
      val = ((orig[ti + 0 + (tj + 0) * 8192]) + (orig[ti + 1 + (tj + 0) * 8192]) + (orig[ti + 0 + (tj + 1) * 8192]) + (orig[ti + 1 + (tj + 1) * 8192]) + (orig[ti + 0 + (tj - 1) * 8192]) + (orig[ti + 1 + (tj - 1) * 8192]) + (orig[ti - 1 + (tj + 0) * 8192]) + (orig[ti - 1 + (tj + 1) * 8192]) + (orig[ti - 1 + (tj - 1) * 8192])) / 9;
      idx = (i - 1) + ((j - 1) * 8);
      sol[idx] = val;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{126}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 32));
        i_col = ((8 * j) + (k % 32));
        j_col = (k_col * 256) + i_col;
        t += ((orig[j_col]) * (filter[k]));
      }
      sol[(((256 * i) + j) - 1)] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}