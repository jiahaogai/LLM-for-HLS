#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int r_col;
  int c_col;
  double temp;
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  int temp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 2; r < 128 - 1; r++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (c = 2; c < 64 - 1; c++) {
      temp = 0.0;
      r_col = r - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        c_col = c - 1 + i;
        temp += filter[i] * orig[r_col * 64 + c_col];
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 2; c < 64 - 1; c++) {
      temp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        i = r + (-1 + k);
        j = c + (-1 + k);
        temp += orig[i * 64 + j] * filter[k];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[r * 64 + c] = temp;
    }
  }
}