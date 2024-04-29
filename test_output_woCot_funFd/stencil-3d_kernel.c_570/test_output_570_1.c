#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
<<<<<<< HEAD
  long s;
=======
  long _in;
  long _out;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
<<<<<<< HEAD
  loopj:
  for (j = 1; j < 32 + 1; j++) {
=======
  loop_x:
  for (i = 0; i < 32; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopk:
    for (k = 1; k < 32 + 1; k++) {
=======
    loop_y:
    for (j = 0; j < 32; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        idx = i + ((j - 1) * (32 + 1)) + ((k - 1) * (32 + 1) * (32 + 1));
        s = orig[idx] + ((j > 1 ? orig[idx - 1] : 0) + (j < 32 ? orig[idx + 1] : 0) + (k > 1 ? orig[idx - (32 + 1)] : 0) + (k < 32 ? orig[idx + (32 + 1)] : 0) + (((32 + 1) * (32 + 1)) > ((k - 1) * (32 + 1)) ? orig[idx - ((32 + 1) * (32 + 1))] : 0) + (((32 + 1) * (32 + 1)) > (32 * (k - 1)) ? orig[idx - ((32 + 1) * (k - 1))] : 0)) - (((32 + 1) * (32 + 1)) > (32 * (k + 1)) ? orig[idx + ((32 + 1) * (k + 1))] : 0) - (((32 + 1) * (32 + 1)) > ((k + 1) * (32 + 1)) ? orig[idx + ((32 + 1) * (32 + 1)) - 1] : 0);
        sol[idx] = s;
=======
      loop_z:
      for (k = 0; k < 32; k++) {
        _out = ((i + 2) % 32) * 32 * 32 + ((j + 2) % 32) * 32 + ((k + 2) % 32);
        _in = i * 32 * 32 + j * 32 + k;
        sol[_out] = ((long )0);
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        loop_k:
        for (idx = 0; idx < 30; idx++) {
          sol[_out] += orig[_in] * filter[idx];
          _in++;
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}