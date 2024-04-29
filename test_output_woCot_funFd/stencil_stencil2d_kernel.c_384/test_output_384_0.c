#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int ti;
  int tj;
  int tk;
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (ti = 1; ti < 8; ti++) {
=======
  for (i = 0; i < 8192; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    middle:
    for (tj = 1; tj < 8; tj++) {
      inner:
      for (tk = 1; tk < 8; tk++) {
        i = (8 * ti) - 1;
        j = (8 * tj) - 1;
        k = (8 * tk) - 1;
        idx = i * 64 + j * 8 + k;
        val = ((orig[idx + 64] + orig[idx + 1]) + orig[idx]) + ((orig[idx + 64 - 1] + orig[idx + 1 - 8]) + orig[idx - 8]);
        sol[idx] = val;
      }
=======
    inner:
    for (j = 0; j < 9; j++) {
      val = filter[j];
      idx = i - 4 + ((j - 4) / 8192);
      sol[i] += val * orig[idx];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}