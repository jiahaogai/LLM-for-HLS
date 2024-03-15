#pragma ACCEL THREAD FACTOR=1`

  
#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        int i_in_j;
        int i_n;
        int j_1;
        int j_in_i;
        int j_n;
        double a;
        double b;
        double c;
        double d;
        double e;
        double f;
        double g;
        double h;
        double _in;
        double _out;
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
		i_n = 2L;
		j_n = 2L;
		a = ex[i][j];
		b = ey[i][j];
		c = hz[i][j];
		d = ex[i][j + 1];
		e = ey[i][j + 1];
		f = hz[i][j + 1];
		g = ex[i + 1][j];
		h = ey[i + 1][j];
		_in = a * b - c;
		_out = a * h + b * g - c;
		i_in_j = i * nx + j;
		j_1 = j + 1;
		j_in_i = i * ny + j;
		ex[i][j] = _out;
		ey[i][j] = _in;
		hz[i][j] = _out + (( (d - e) * (b - g)) + ((f - h) * (a - c)) ) / (2.0 * (2.0 * 2.0));
      }
    }
  }
}