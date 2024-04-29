Code: ### #pragma ACCEL kernel

### 
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}
#pragma ACCEL PARALLEL FACTOR=auto{10}
 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{32}
 
#pragma ACCEL PARALLEL FACTOR=auto{4}
 
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{32}
 
#pragma ACCEL PARALLEL FACTOR=auto{4}
 
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}

---
#pragma ACCEL kernel

### 
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{4}
 
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}
 
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{16}
 
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{__PARA__L9}
 
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L13}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LL