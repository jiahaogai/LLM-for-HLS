#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
<<<<<<< HEAD
  for (j = 1; j < 337; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 337; i++) {
      flatten_idx = ((j - 1) * 337) + i;
      center = orig[flatten_idx];
      idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = -4; k <= 4; k++) {
        if ((j + k) < 1 || (j + k) > 337) {
          continue;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopidx:
        for (idx = (k == -4 ? 1 : 0); idx < 5; idx++) {
          if ((i + idx) < 1 || (i + idx) > 337) {
            sol[flatten_idx] = center;
          }
          else {
            sol[flatten_idx] = center + filter[idx + 4] * orig[((j + k) - 1) * 337 + i + idx];
          }
        }
      }
=======
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + (j * 32);
      center = orig[idx];
      flatten_idx = ((idx > 1) ? (idx - 1) : 1);
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (; k < 9; k++) {
        sol[idx] += filter[k] * orig[flatten_idx + k - 1];
      }
      sol[idx] = center - (sol[idx] / 9.0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}