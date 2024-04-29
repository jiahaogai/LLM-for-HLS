#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int row;
  int col;
  int flit;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  loopj:
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 0; k < 64; k++) {
      row = ((j + 0) * 64) + k;
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      loopi:
      for (i = 0; i < 9; i++) {
        col = ((j + ((i - 4) + 0)) * 64) + ((k + ((i - 4) + 0)) + 0);
        sum += orig[col] * filter[i];
      }
      sol[row] = sum;
=======
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 1; k < 9; k++) {
        val += orig[idx + k] * filter[k];
      }
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}