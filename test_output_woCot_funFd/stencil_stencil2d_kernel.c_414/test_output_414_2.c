#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int ti;
  int tj;
  int fi;
//#pragma scop
=======
  int k;
  int result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction = orig FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      ti = i - 4 + j;
      sol[i] += filter[j] * (ti < 0 ? 0 : (ti > 8191 ? 0 : orig[ti]));
    }
  }
//#pragma endscop
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{4}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 8; k++) {
        result += filter[k] * orig[i + (-4 + k) * 8192] [j + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = result;
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}