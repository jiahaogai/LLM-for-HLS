#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[20][3])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
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
      }
    }
  }
//#pragma endscop
}