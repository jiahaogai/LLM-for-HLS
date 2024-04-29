#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long _in_;
  long _out_;
  _in_ = 0;
  _out_ = 0;
  while (_out_ < 32768 - 1) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    k = _out_ / (39304);
    j = (_out_ - k * 39304) / 9216;
    i = (_out_ - k * 39304 - j * 9216) / 144;
    t = ((0 + 4) + ((0 + 4) * 9216)) + ((0 + 4) * 144) + 1;
    sol[ _out_ ] = ((orig[ _in_ ] + orig[ _in_ + 1 ] + orig[ _in_ + 144 ] + orig[ _in_ + 144 + 1 ])) + ((orig[ _in_ + 9216 ] + orig[ _in_ + 9216 + 1 ] + orig[ _in_ + 9216 + 144 ] + orig[ _in_ + 9216 + 144 + 1 ])) + ((orig[ _in_ + 19840 ] + orig[ _in_ + 19840 + 1 ] + orig[ _in_ + 19840 + 144 ] + orig[ _in_ + 19840 + 144 + 1 ])) + ((orig[ _in_ + 29592 ] + orig[ _in_ + 29592 + 1 ] + orig[ _in_ + 29592 + 144 ] + orig[ _in_ + 29592 + 144 + 1 ])) + 8 * t;
    _in_++;
    _out_++;
  }
}