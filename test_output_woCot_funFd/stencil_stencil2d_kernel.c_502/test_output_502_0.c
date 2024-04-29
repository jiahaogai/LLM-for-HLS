<<<<<<< HEAD
#pragma ACCEL kernel
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  stencil_label1:
  for (r = 0; r < 128 - 2; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    stencil_label2:
    for (c = 0; c < 64 - 2; c++) {
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      stencil_label3:
      for (k1 = 0; k1 < 3; k1++) {
        
#pragma ACCEL PIPELINE auto{off}
        stencil_label4:
        for (k2 = 0; k2 < 3; k2++) {
          mul = filter[k1 * 3 + k2] * orig[(r + k1) * 64 + c + k2];
          temp += mul;
        }
      }
      sol[r * 64 + c] = temp;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
