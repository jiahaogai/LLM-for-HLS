#ifndef STENCIL_H
#define STENCIL_H

#ifndef ACCEL_CONFIG
#define ACCEL_CONFIG
/*#define ACCEL_AUTO_PIPELINE*/
/*#define ACCEL_AUTO_TILE*/
/*#define ACCEL_AUTO_PARALLEL*/
#define ACCEL_DEBUG
#endif

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result = orig[i * 256 + j] * filter[k];
      }
      sol[i * 256 + j] = result;
    }
  }
}

#endif