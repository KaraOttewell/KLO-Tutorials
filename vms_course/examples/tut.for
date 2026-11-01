C     Kara's VMS Tutorial - example file
C     (C) Kara Ottewell 1996-2026
C
C---- TUT.FOR - a first program to compile, link and run ----
      PROGRAM TUT
C     Print a short table of numbers, their squares and square roots
      INTEGER I
      REAL ROOT
      WRITE(6,1000)
      DO 10 I = 1, 5
          ROOT = SQRT(REAL(I))
          WRITE(6,1001) I, I*I, ROOT
   10 CONTINUE
      STOP
 1000 FORMAT(' Number  Square  Square root')
 1001 FORMAT(1X,I6,I8,F13.4)
      END
