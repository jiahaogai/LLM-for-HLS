#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{stencil_label1}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -1; k <= 1; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
	for (int jj = -1; jj <= 1; jj++) {
	  t += filter[((k + 1) * 3) + (jj + 1)] * orig[i + k + pad][j + jj + pad];
	}
      }
      sol[i][j] = t;
    }
  }
}