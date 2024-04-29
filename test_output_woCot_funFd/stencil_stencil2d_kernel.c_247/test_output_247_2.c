<<<<<<< HEAD
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
=======
Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  middle:
  for (j = 0; j < 256; j++) {
    val = 0;
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
    inner:
    for (k = 0; k < 9; k++) {
      idx = (256 * (k - 4)) + j;
      val += filter[k] * orig[i * 256 + idx];
    }
    sol[i * 256 + j] = val;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
=======
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += filter[k] * orig[i * 256 + idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  middle:
  for (j = 0; j < 256; j++) {
    val = 0;
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
    inner:
    for (k = 0; k < 9; k++) {
      idx = (256 * (k - 4)) + j;
      val += filter[k] * orig[i * 256 + idx];
    }
    sol[i * 256 + j] = val;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += orig[i * 256 + idx] * filter[k];
=======
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += filter[k] * orig[i * 256 + idx];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 256 + j] = val;
    }
  }
<<<<<<< HEAD
}
=======
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
