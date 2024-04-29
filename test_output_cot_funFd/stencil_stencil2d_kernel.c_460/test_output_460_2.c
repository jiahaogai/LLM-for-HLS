#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        ti = i + (-1 + k);
        tj = j + (-1 + k);
        tk = 0;
#pragma ACCEL PARALLEL FACTOR=auto{8}
	for (idx = 0; idx < 8; ++idx) {
          tk += ((ti + idx - 1) % 8192) * 8192;
        }
        tk += ((tj - 1) % 8192);
        val += filter[k] * orig[tk];
      }
      sol[i * 8192 + j] = val;
    }
  }
}