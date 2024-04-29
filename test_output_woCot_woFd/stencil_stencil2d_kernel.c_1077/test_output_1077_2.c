- Automatically pipeline the middle loop for hardware acceleration.
- Divide the middle loop into tiles of size 1 for efficient hardware resource utilization.
- Execute the middle loop iterations in parallel with a factor of 1 for concurrent processing on hardware.
- Automatically pipeline the inner loop for hardware acceleration.
- Divide the inner loop into tiles of size 1 for efficient hardware resource utilization.
- Execute the inner loop iterations in parallel with a factor of 1 for concurrent processing on hardware.

#pragma ACCEL kernel