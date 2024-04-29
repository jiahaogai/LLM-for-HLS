#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
=======
  int t;
  int pt = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
<<<<<<< HEAD
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + k - 4];
      }
      sol[i + j - 4] = sum;
    }
=======
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        t += 0;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      middle:
      for (j = 0; j < 8; j++) {
        if (k < 0 || k > 8191) {
          t += 0;
        }
        else {
          t += filter[j] * orig[k];
        }
        k++;
      }
    }
    sol[i] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}