C     Kara's VMS Tutorial - example file
C     (C) Kara Ottewell 1996-2026
C
C---- SDEB.FOR - a program with one obvious bug, for the debugger ----
      PROGRAM SHOW_DEBUG
C     Fill an array and a table, then print a scaled average
      INTEGER N(3,3)
      REAL A, B, C, SS
      COMMON /RESULTS/ N, A, B, C, SS
      REAL Q(10)
      INTEGER I, J
      DO 10 I = 1, 10
          Q(I) = REAL(I) * 1.5
   10 CONTINUE
      DO 30 J = 1, 3
          DO 20 I = 1, 3
              N(I,J) = I * J
   20     CONTINUE
   30 CONTINUE
      A = Q(1)
      B = Q(5)
      C = Q(10)
      CALL AVERAGE(Q, 10)
      STOP
      END

      SUBROUTINE AVERAGE(VALUES, COUNT)
C     Print the average of VALUES, scaled by SS from the common block
      INTEGER COUNT
      REAL VALUES(COUNT)
      INTEGER N(3,3)
      REAL A, B, C, SS
      COMMON /RESULTS/ N, A, B, C, SS
      REAL TOTAL
      INTEGER I
      TOTAL = 0.0
      DO 40 I = 1, COUNT
          TOTAL = TOTAL + VALUES(I)
   40 CONTINUE
C     SS is meant to be the scale factor, but nothing ever sets it
      WRITE(6,1000) TOTAL / (COUNT * SS)
      RETURN
 1000 FORMAT(' Scaled average:',F10.4)
      END
