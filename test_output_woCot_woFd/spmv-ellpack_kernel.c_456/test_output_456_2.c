5. `#pragma ACCEL PIPELINE auto{off}`:
   Do not automatically pipeline this loop.

6. `#pragma ACCEL TILE FACTOR=auto{8}`:
   Divide this loop into smaller parts with a factor of 8 to improve parallelism.

7. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
   Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

8. `#pragma ACCEL PIPELINE auto{off}`:
   Do not automatically pipeline this loop.

9. `#pragma ACCEL TILE FACTOR=auto{8}`:
   Divide this loop into smaller parts with a factor of 8 to improve parallelism.

10. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

11. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

12. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

13. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

14. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

15. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

16. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

17. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

18. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

19. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

20. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

21. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

22. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

23. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

24. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

25. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

26. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

27. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

28. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

29. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

30. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

31. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

32. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

33. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

34. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

35. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

36. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

37. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

38. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

39. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

40. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

41. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

42. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

43. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

44. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

45. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

46. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

47. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

48. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

49. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

50. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

51. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

52. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

53. `#pragma ACCEL PIPELINE auto{off}`:
    Do not automatically pipeline this loop.

54. `#pragma ACCEL TILE FACTOR=auto{8}`:
    Divide this loop into smaller parts with a factor of 8 to improve parallelism.

55. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
    Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma