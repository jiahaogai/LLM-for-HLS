### ACCEL PIPELINE auto{}

### ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}

### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}

### ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{16}