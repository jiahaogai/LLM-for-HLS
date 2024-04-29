#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        if ((((i_col >= 0) && (i_col < 8192))) && (((j >= 0) && (j < 8)) || ((j >= 8184) && (j < 8192)))) {
          k_col = j + k;
          if (((k_col >= 0) && (k_col < 8192))) {
            sum += filter[((k + 4) << 3) + 4] * orig[i_col * 8192 + k_col];
          }
        }
      }
      sol[i * 8192 + j] = sum;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      i_col = i * 64;
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = i_col + k * 8;
        sum += filter[k] * orig[k_col + j];
      }
      sol[i_col + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}