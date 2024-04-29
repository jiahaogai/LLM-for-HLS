#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  double sum;
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + i;
        if (k_col < 0) {
          k_col += 8192;
        }
        else {
          if (k_col > 8191) {
            k_col -= 8192;
          }
        }
        i_col = j + k;
        if (i_col < 0) {
          i_col += 8192;
        }
        else {
          if (i_col > 8191) {
            i_col -= 8192;
          }
        }
        sum += filter[k + 4] * orig[k_col * 8192 + i_col];
      }
      sol[i * 8192 + j] = sum;
=======
    for (j = 0; j < 9; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{62}
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + k - 4];
      }
      sol[i + j - 4] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}