#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
=======
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8188; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{10}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-1 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
    }
=======
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_orig = orig[i];
    tmp_sol = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = tmp_orig * filter_elem;
      tmp_sol += tmp;
    }
    sol[i] = tmp_sol;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}