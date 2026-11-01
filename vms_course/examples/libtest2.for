C     Kara's VMS Tutorial - example file
C     (C) Kara Ottewell 1996-2026
C
C---- LIBTEST2.FOR - functions to put in an object library ----
      REAL FUNCTION FAHRENHEIT(CELSIUS)
C     Convert a temperature from Celsius to Fahrenheit
      REAL CELSIUS
      FAHRENHEIT = CELSIUS * 9.0 / 5.0 + 32.0
      RETURN
      END

      REAL FUNCTION CELSIUS(FAHRENHEIT)
C     Convert a temperature from Fahrenheit to Celsius
      REAL FAHRENHEIT
      CELSIUS = (FAHRENHEIT - 32.0) * 5.0 / 9.0
      RETURN
      END
