#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int tmp_row;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_row = 0;
    
#pragma ACCEL PARALLEL reduction=tmp_row FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = orig[i + (j - 4)];
      tmp_row += filter_elem * tmp;
    }
    sol[i] = tmp_row;
=======
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 8191; k++) {
      idx = (8192 + 1) * j + k;
      val = ((orig[idx - 8192] + orig[idx - 8191]) + orig[idx - 1]) + ((orig[idx + 1] + orig[idx + 8191]) + orig[idx + 8192]);
      sol[idx] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}