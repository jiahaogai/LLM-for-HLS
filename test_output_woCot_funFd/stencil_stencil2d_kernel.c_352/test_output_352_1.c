#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
=======
void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int r;
  int q;
  int p;
  int r_col;
  int q_col;
  int p_col;
  int r_row;
  int q_row;
  int p_row;
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j] + (1 + filter[1]) * orig[i][j + 1] + (2 + filter[2]) * orig[i][j + 2] + (3 + filter[3]) * orig[i][j + 3] + (4 + filter[4]) * orig[i][j + 4] + (5 + filter[5]) * orig[i][j + 5] + (6 + filter[6]) * orig[i][j + 6] + (7 + filter[7]) * orig[i][j + 7] + (8 + filter[8]) * orig[i][j + 8] + (9 + filter[9]) * orig[i][j + 9]) / ((0 + filter[0]) + (1 + filter[1]) + (2 + filter[2]) + (3 + filter[3]) + (4 + filter[4]) + (5 + filter[5]) + (6 + filter[6]) + (7 + filter[7]) + (8 + filter[8]) + (9 + filter[9]));
    }
  }
//#pragma endscop
=======
  outer:
  for (r = 1; r < 400 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (q = 1; q < 400 - 1; q++) {
      sol[r][q] = 0.0;
      inner:
      for (p = 0; p < 25; p++) {
        r_col = r + ((p + 1) / 25) - 1;
        q_col = q + ((p + 1) % 25) - 1;
        p_col = p - ((p + 1) % 25);
        r_row = r + (-(p + 1) / 25);
        q_row = q + (-(p + 1) % 25);
        p_row = p - (-(p + 1) % 25);
        sol[r][q] += filter[p] * orig[r_col][q_col] + filter[p_col] * orig[r_row][q_row] + filter[p_row] * orig[r_row][q_col];
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}