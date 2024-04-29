#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -1; k <= 1; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
	for (int jj = -1; jj <= 1; jj++) {
	  int x = pad + i * 64 + k;
	  int y = pad + j * 64 + jj;
	  if (x < 0 || x >= 8192 || y < 0 || y >= 8192) {
	    t += 0;
	  }
	  else {
	    t += filter[((k + 1) * 3) + (jj + 1)] * orig[x * 8192 + y];
	  }
	}
      }
      sol[i * 64 + j] = t;
    }
  }
}