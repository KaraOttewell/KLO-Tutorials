C     Kara's VMS Tutorial - example file
C     (C) Kara Ottewell 1996-2026
C
C---- LIBTEST1.FOR - calls the functions in LIBTEST2 ----
      PROGRAM LIBTEST
C     Print a temperature conversion table, converting each value
C     there and back again as a check
      REAL CELSIUS, FAHRENHEIT, TEMPERATURE
      INTEGER I
      WRITE(6,1000)
      DO 10 I = 0, 100, 25
          TEMPERATURE = REAL(I)
          WRITE(6,1001) TEMPERATURE, FAHRENHEIT(TEMPERATURE),
     1                  CELSIUS(FAHRENHEIT(TEMPERATURE))
   10 CONTINUE
      STOP
 1000 FORMAT(' Celsius  Fahrenheit  And back')
 1001 FORMAT(1X,F7.1,F12.1,F10.1)
      END
