#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[400],int sol[400],int filter[9])
{
  int i;
  int j;
  int fl;
  int o;
  int s;
=======
void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      o = orig[i * 400 + j];
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (fl = 0; fl < 9; fl++) {
        s += o * filter[fl];
      }
      sol[i * 400 + j] = s;
    }
  }
=======
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (l = 0; l < 3; l++) {
          sol[i][j] += filter[k][l] * orig[i + -1 + k][j + -1 + l];
        }
      }
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}