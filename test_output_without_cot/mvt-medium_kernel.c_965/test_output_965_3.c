#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{16}