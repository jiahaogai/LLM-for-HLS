#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      s = 0;
=======
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      s = 0.0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = -4; k <= 4; k++) {
<<<<<<< HEAD
        idx = (i - 1) * 8192 + (j - 1) + k;
        if (idx < 0) {
          idx = 0;
        }
        else if (idx > 8191) {
          idx = 8191;
        }
        s += orig[idx] * filter[k + 4];
      }
      sol[i * 8192 + j] = s;
=======
        idx = (i - 1) * 8190 + j + k;
        if (idx < 0) {
          idx = -idx;
        }
        
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{16}
        for (int _in_idx_ = 0; _in_idx_ < 1; _in_idx_++) {
          s += ((double )filter[k + 4]) * orig[idx];
        }
      }
      sol[i * 8190 + j] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}