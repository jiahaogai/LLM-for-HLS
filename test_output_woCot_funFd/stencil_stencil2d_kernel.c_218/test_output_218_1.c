#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
<<<<<<< HEAD
  int bound;
//#pragma scop
=======
  int r_col;
  int c_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8191; c++) {
<<<<<<< HEAD
      bound = 8192 + 1;
      sol[r * 8192 + c] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (i = r - 4; i <= r + 4; i++) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
        for (j = c - 4; j <= c + 4; j++) {
          if (((i < 0) || (i > 8191)) || ((j < 0) || (j > 8191))) {
            continue;
          }
          else {
            sol[r * 8192 + c] += filter[((i - r + 4) + 5) * 9 + ((j - c + 4) + 5)] * orig[i * 8192 + j];
          }
        }
      }
    }
  }
//#pragma endscop
=======
      r_col = r - 4;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (i = 0; i < 9; i++) {
        c_col = c - 4;
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{32}
        for (j = 0; j < 9; j++) {
          sol[r * 8192 + c] += filter[i * 9 + j] * orig[r_col * 8192 + c_col + j];
        }
        c_col = c + 4;
      }
      r_col = r + 4;
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}