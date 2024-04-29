<<<<<<< HEAD
#pragma ACCEL kernel

=======
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int x;
  int y;
  int xmin = 1;
  int xmax = 8190;
  int ymin = 1;
  int ymax = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      x = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (y = -4; y <= 4; y++) {
        int tmp_x;
        int tmp_y;
        tmp_x = x + y;
        tmp_y = j + y;
        if (tmp_x < xmin) {
          x = xmin;
        }
        else if (tmp_x > xmax) {
          x = xmax;
        }
        else {
          x = tmp_x;
        }
        
#pragma ACCEL PIPELINE auto{off}
          if (tmp_y < ymin) {
            y = ymin;
          }
          else if (tmp_y > ymax) {
            y = ymax;
          }
          else {
            y = tmp_y;
          }
          x = orig[x + y * 8192] * filter[y + 4];
        }
      }
      sol[i * 8192 + j] = x;
=======
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        tmp += orig[i + k - 4] * filter[k];
      }
      sol[i * 8192 + j] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}