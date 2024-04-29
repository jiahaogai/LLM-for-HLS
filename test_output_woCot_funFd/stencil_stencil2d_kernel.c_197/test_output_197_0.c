#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
<<<<<<< HEAD
  int pt = 4;
=======
  int pt;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 9; j++) {
<<<<<<< HEAD
      t += orig[i + (j - 4)] * filter[j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
=======
      pt = i - 4 + j;
      if (pt < 0 || pt > 8191) {
        t += 0;
      }
       else {
        t += orig[pt] * filter[j];
      }
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    sol[i] = t;
  }
}