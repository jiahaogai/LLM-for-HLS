#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int jj;
  int kk;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      for (k = 0; k < 8; k++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
	for (kk = 0; kk < 8; kk++) {
	  jj = j - 4 + k;
	  if (jj < 1) {
	    jj = 1;
	  }
	  if (jj > 8191) {
	    jj = 8191;
	  }
	  sum += filter[k * 8 + kk] * orig[i * 8192 + jj * 8 + kk];
	}
      }
      sol[i * 8192 + j] = sum;
    }
  }
}