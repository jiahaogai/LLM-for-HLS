#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (x = -4; x < 5; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
	for (y = -2; y < 3; y++) {
	  t += filter[4 + x] * orig[i + x + ((j + y) * 64)];
	}
      }
      sol[i + j] = t;
    }
  }
}