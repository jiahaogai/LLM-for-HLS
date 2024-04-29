#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  int k;
//#pragma scop
=======
void stencil(int orig[25],int sol[25],int filter[25])
{
  int i;
  int j;
  int jj;
  int i_col;
  int j_col;
  int tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][j + 1]) + (filter[0][2] * orig[i][j + 2]) + (filter[1][0] * orig[i + 1][j]) + (filter[1][1] * orig[i + 1][j + 1]) + (filter[1][2] * orig[i + 1][j + 2]) + (filter[2][0] * orig[i + 2][j]) + (filter[2][1] * orig[i + 2][j + 1]) + (filter[2][2] * orig[i + 2][j + 2])) / 121;
    }
  }
//#pragma endscop
=======
  outer:
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 25; j++) {
      i_col = ((i - 1) < 0) ? 0 : (i - 1);
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{1}
      inner:
      for (j_col = ((j - 1) < 0) ? 0 : (j - 1); j_col < 25; j_col++) {
        if (((i - 1) < 0) || ((j - 1) < 0)) {
          tmp = 0;
        }
        else {
          tmp = orig[i_col * 25 + j_col] + filter[0];
        }
        
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{1}
        inner_1:
        for (jj = 1; jj < 25; jj++) {
          i_col = ((i - 1) < 0) ? 0 : (i - 1);
          tmp += orig[i_col * 25 + j_col + jj] * filter[jj];
        }
        sol[i * 25 + j] = tmp;
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}