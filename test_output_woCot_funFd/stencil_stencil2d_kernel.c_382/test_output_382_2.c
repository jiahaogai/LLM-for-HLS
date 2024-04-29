#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][20][3],int sol[25][20][3],int filter[20][3])
=======
void stencil(int orig[25][20][3],int sol[25][20][3],int filter[3][3][3])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int r;
  int q;
  int p;
  int s;
<<<<<<< HEAD
=======
  int t;
  int u;
  int v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  for (r = 0; r < 25; r++) {
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 25 - 1; r++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{3}
      for (p = 0; p < 3; p++) {
        s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
	for (int _in_s = 0; _in_s < 3; _in_s++) {
          int _in_r = r - 1 + _in_s;
          if (_in_r < 0) {
            _in_r = -1;
          }
          if (_in_r > 24) {
            _in_r = 25;
          }
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (int _in_q = 0; _in_q < 20; _in_q++) {
            int _in_p = p - 1 + _in_q;
            if (_in_p < 0) {
              _in_p = -1;
            }
            if (_in_p > 19) {
              _in_p = 20;
            }
            s += ((orig[_in_r][_in_q][_in_p]) * (filter[_in_q][_in_p]));
          }
        }
	sol[r][q][p] = s;
=======
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 1; p < 3 - 1; p++) {
        v = 0;
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{2}
          for (t = 0; t < 3; t++) {
            for (p = 0; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][0] = v;
        v = 0;
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
          for (t = 0; t < 3; t++) {
            for (p = 1; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][1] = v;
        v = 0;
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
          for (t = 1; t < 3; t++) {
            for (p = 1; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][2] = v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}