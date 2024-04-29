Code: 
int i;
int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
    for (j = 0; j < 256; j++) {
      sol[i] += filter[j] * orig[i * 256 + j];
    }
  }
}