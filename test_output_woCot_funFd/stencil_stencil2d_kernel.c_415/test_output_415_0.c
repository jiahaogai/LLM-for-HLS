#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[8192],int sol[8192],int filter[9])
=======
void stencil(double orig[8192],double sol[8192],double filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int pad;
  pad = 1;
=======
  int k_col;
  int i_col;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int _in;
        int _out;
        _in = orig[i * 8192 + j] + k * 8192;
        _out = sol[i * 8192 + j] + filter[pad + k] * _in;
        t = _out;
      }
      sol[i * 8192 + j] = t;
=======
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        if (((i_col + k_col) < 0) || ((i_col + k_col) > 255)) {
          sum = 0.0;
        }
         else {
          sum = orig[i_col + k_col] * filter[k_col];
        }
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        sol[i * 256 + j] = sum;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}