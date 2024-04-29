#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int flatten_i;
  int flatten_j;
  int flatten_k;
  int index;
  int val;
=======
  int t;
  int bound = 32;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  loop_i:
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 337; j++) {
      flatten_i = i * 337;
      flatten_j = j * 337;
      val = 0;
      loop_k:
      for (k = -4; k <= 4; k++) {
        k_col = k + 4;
        i_col = flatten_i + k_col;
        loop_j_col:
        for (j_col = -4; j_col <= 4; j_col++) {
          index = i_col + j_col;
          val += orig[index] * filter[k_col * 9 + j_col + 4];
        }
      }
      sol[flatten_j + flatten_i] = val;
=======
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -bound; k < bound + 1; k++) {
        if ((k != 0)) {
          t += filter[((bound + 1) + k)] * orig[i + k];
        }
      }
      sol[j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}