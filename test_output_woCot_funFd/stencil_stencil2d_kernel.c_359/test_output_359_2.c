<<<<<<< HEAD
#pragma ACCEL kernel
=======
Details: 
unknown pragma: PIPELINE
 #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
  int row;
  int col;
=======
  int tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) > -1 ? (k - 4) : 0);
        col = j + ((k - 4) > -1 ? 0 : - (k - 4));
        sum += filter[k] * orig[row * 8 + col];
      }
      sol[i * 8 + j] = sum;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8191; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        tmp += filter[k] * orig[i + idx[k] - 1 + (j + idx[k] - 1) * 8192];
      }
      sol[i + j * 8192] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}