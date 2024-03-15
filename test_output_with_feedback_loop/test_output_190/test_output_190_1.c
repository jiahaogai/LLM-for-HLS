sum = 0.0;
  float tmp = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 4000; t++) {
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (i = 0; i < 200; i++) {
      tmp = data[t * 200 + i];
      sum = sum + tmp;
    }
  }
//  printf("sum: %f\n",sum);

}