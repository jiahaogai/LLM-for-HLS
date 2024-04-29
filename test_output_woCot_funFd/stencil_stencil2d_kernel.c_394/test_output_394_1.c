<<<<<<< HEAD
**Example:**

c
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}
=======
Code: #pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
stencil_label1:
   for (i = 0; i < 32; i++) {
      
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{32}
      stencil_label2:
      for (j = 0; j < 32; j++) {
         tmp = 0.0;
         
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
         stencil_label3:
         for(k = -1; k <= 1; k++) {
             for(l = -1; l <= 1; l++) {
                 tmp += filter[k + 1][l + 1] * orig[i + k][j + l];
             }
         }
         sol[i][j] = tmp;
      }
   }
 }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
