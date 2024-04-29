#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int idx;
  int val;
=======
  int t;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 32; i++) {
=======
  for (i = 0; i < 32 + 2 * 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 32; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        if ((k_col >= 0)) {
           if ((k_col < 32)) {
            idx = k_col * 32 + j + ((k % 3) - 1);
            if ((idx >= 0)) {
               if ((idx < 8192)) {
                val += orig[idx] * filter[k];
              }
           }
          }
        }
      }
      sol[i * 32 + j] = val;
=======
    for (j = 0; j < 32 + 2 * 1; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i * (32 + 2 * 1) + j * (32 + 2 * 1) + pad * k];
      }
      sol[i * (32 + 2 * 1) + j * (32 + 2 * 1) + pad] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}