#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
<<<<<<< HEAD
  int value;
=======
  int e;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
/* Standardize from: for(j = 1; j < 400 - 1; j++) {...} */
  for (j = 1; j <= 398; j++) {
=======
  outer:
  for (row = 1; row < 400 - 1; row++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    loopi:
/* Standardize from: for(i = 1; i < 400 - 1; i++) {...} */
    for (i = 1; i <= 398; i++) {
      value = ((orig[j][i - 1] + orig[j][i + 1]) + (orig[j - 1][i] + orig[j + 1][i])) + orig[j][i];
      sol[j][i] = value;
/*
      if(value < 0){
        value = 0;
      }
      else if(value > 255){
        value = 255;
      }
      sol[j][i] = value;
*/
=======
    inner:
    for (column = 1; column < 400 - 1; column++) {
      e = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner_e:
      for (i = -1; i <= 1; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        inner_i:
        for (j = -1; j <= 1; j++) {
          e += filter[((i + 1) * 3) + (j + 1)] * orig[row + i][column + j];
        }
      }
      sol[row][column] = e;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}