#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int pt = 4;
=======
  int tmp;
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      t += orig[k] * filter[j];
    }
    sol[i] = t;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8191; j++) {
      tmp = 0;
      t = 48;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        tmp += ((int )filter[t]) * orig[i + k + 1];
        t--;
      }
      sol[j] = tmp;
    }
    sol[8192] = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      tmp = sol[j];
      sol[j] = sol[j + 1];
      sol[j + 1] = tmp;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}