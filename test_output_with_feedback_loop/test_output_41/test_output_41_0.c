#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (tj = 0; tj < 40; tj++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (tk = 0; tk < 40; tk++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
      for (i = 0; i < 120; i++) {
        tmp += A[i][tj] * B[i][tk];
      }
      C4[tj][tk] = tmp;
    }
  }
}