#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int i_pad;
        int j_pad;
        i_pad = i + k;
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j_pad = -1 * pad; j_pad <= 1 * pad; j_pad++) {
          if ((((i_pad >= 0) && (i_pad < 8)) && ((j_pad >= 0) && (j_pad < 8))) && ((k != 0) || (j_pad != 0))) {
            t += filter[((k + 1) * 3) + (j_pad + 1)] * orig[i_pad * 8 + j_pad];
          }
        }
      }
      sol[i * 8 + j] = t;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[pad + i - 4 + j];
    }
    sol[i] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}