#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8192; j++) {
      sol[i * 8192 + j] = ((int )filter[0]) * orig[i * 8192 + j] + ((int )filter[1]) * (orig[i * 8192 + j + 1]) + ((int )filter[2]) * (orig[i * 8192 + j + 2]) + ((int )filter[3]) * (orig[i * 8192 + j + 3]) + ((int )filter[4]) * (orig[i * 8192 + j + 4]) + ((int )filter[5]) * (orig[i * 8192 + j + 5]) + ((int )filter[6]) * (orig[i * 8192 + j + 6]) + ((int )filter[7]) * (orig[i * 8192 + j + 7]) + ((int )filter[8]) * (orig[i * 8192 + j + 8]);
    }
  }
}