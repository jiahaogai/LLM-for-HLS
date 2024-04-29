#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][20][30],int sol[25][20][30],int filter[9][9][30])
=======
void stencil(int orig[25][20][3],int sol[25][20][3],int filter[20][3])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int r;
  int q;
  int p;
<<<<<<< HEAD
  int s;
  int t;
  int u;
  int v;
=======
  int d;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 1; p < 30 - 1; p++) {
        v = 0;
        for (t = -1; t <= 1; t++) {
          s = 0;
          for (u = -1; u <= 1; u++) {
            s += filter[t + 1][u + 1][p] * orig[r + t][q][p + u];
          }
          v += s;
        }
        sol[r][q][p] = v;
=======
      for (p = 1; p < 3 - 1; p++) {
        for (d = 0; d < 3; d++) {
          sol[r][q][d] = filter[q][p] * orig[r][q][d] + (1 - filter[q][p]) * (sol[r][q - 1][d] + sol[r][q + 1][d] + sol[r - 1][q][d] + sol[r + 1][q][d]);
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}