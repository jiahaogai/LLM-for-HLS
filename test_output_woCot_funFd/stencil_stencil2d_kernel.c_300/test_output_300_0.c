#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int k_col;
  int k_row;
//#pragma scop
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      k_col = -1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k_col <= 1) {
        k_row = -1;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        while (k_row <= 1) {
          k_col += 1;
          k_row += 1;
          k = k_row * 2 + k_col;
          sol[i][j] += filter[k][0] * orig[i + k_row][j + k_col];
        }
      }
    }
  }
//#pragma endscop
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int k = 0; k < 4; ++k) {
        sol[i][j] += filter[k][j] * orig[i][k];
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}