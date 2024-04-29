#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double A[25][25],double B[25][25])
=======
void stencil(int rows,int cols,int A[rows][cols],int B[rows][cols])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int r;
  int c;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  for (r = 0; r < 25; r++) {
=======
  for (r = 1; r < rows - 1; r++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    for (c = 0; c < 25; c++) {
      B[r][c] = 0.2 * A[r][c] + 0.8 * (B[r - 1][c - 1] + B[r - 1][c] + B[r - 1][c + 1] + B[r][c - 1] + B[r][c + 1] + B[r + 1][c - 1] + B[r + 1][c] + B[r + 1][c + 1]);
=======
    for (c = 1; c < cols - 1; c++) {
      int v =  A[r][c];
      B[r][c] = ((v + A[r - 1][c - 1] + A[r - 1][c] + A[r - 1][c + 1]
           + A[r][c - 1] + A[r][c + 1] + A[r + 1][c - 1] + A[r + 1][c]) / 8);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}