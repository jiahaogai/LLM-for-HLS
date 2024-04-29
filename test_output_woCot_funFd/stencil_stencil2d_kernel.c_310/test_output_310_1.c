#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int ti;
  int tj;
  int fi;
  int fj;
=======
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      val = 0;
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx];
      tk = ((-filter[0] / 2) + 8) + filter[0];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
      for (fi = -4; fi <= 4; fi++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (fj = -4; fj <= 4; fj++) {
          tj = fj + j;
          ti = fi + i;
          val += filter[fi + 4] * filter[fj + 4] * orig[ti * 8192 + tj];
        }
      }
      sol[i * 8192 + j] = val;
=======
      for (k = (-filter[0] / 2) + 1; k < tk; k++) {
        tj = j + k;
        if (tj < 1) {
          tj = 1;
        }
        else {
          if (tj > 8192) {
            tj = 8192;
          }
        }
        sol[idx] += val * filter[k + (-filter[0] / 2)];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}