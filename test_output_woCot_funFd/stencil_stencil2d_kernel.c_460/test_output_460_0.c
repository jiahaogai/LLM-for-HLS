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
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
<<<<<<< HEAD
=======
    tmp_orig = 0;
    tmp_sol = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + 4;
        i_col = i + k_col;
        if ((((i_col >= 0) && (i_col < 8192))) && (((j >= 0) && (j < 8192)))) {
          sum += filter[k + 4] * orig[i_col] * orig[j];
        }
      }
      sol[i * 8192 + j] = sum;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = orig[i + (-4 + j)];
      tmp_orig += filter_elem * tmp;
      tmp_sol += filter_elem * tmp;
    }
    sol[i] = tmp_sol;
    orig[i] = tmp_orig;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}