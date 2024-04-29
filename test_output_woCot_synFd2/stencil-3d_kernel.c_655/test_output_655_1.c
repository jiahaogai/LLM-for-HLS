#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double C0I;
  double C1I;
  double C2I;
  double _in_;
  double _out_;
  C0I = 1.0 / ((double )C0);
  C1I = 1.0 / ((double )C1);
  C2I = C0I * C1I;
//#pragma scop
  _out_ = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (long i = 1; i < 27 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (long j = 1; j < 27 - 1; j++) {
      for (long k = 1; k < 27 - 1; k++) {
        _in_ = ((double )(- 3)) * (orig[i * 27 + j * 1 + k] * C2I);
        _in_ += 2.0 * (orig[i * 27 + j * 1 + k - 1] * C1I);
        _in_ += 2.0 * (orig[i * 27 + j * 1 + k + 1] * C1I);
        _in_ += (orig[i * 27 + j * 1 + k - 27] * C1I);
        _in_ += (orig[i * 27 + j * 1 + k + 27] * C1I);
        _in_ += (orig[(i - 1) * 27 + j * 1 + k] * C0I);
        _in_ += (orig[(i + 1) * 27 + j * 1 + k] * C0I);
        _in_ += (orig[i * 27 + (j - 1) * 1 + k] * C0I);
        _in_ += (orig[i * 27 + (j + 1) * 1 + k] * C0I);
        _in_ += (orig[i * 27 + j * 1 + k - 1] * C0I);
        _in_ += (orig[i * 27 + j * 1 + k + 1] * C0I);
        sol[i * 27 + j * 1 + k] = _in_;
      }
    }
  }
//#pragma endscop
}