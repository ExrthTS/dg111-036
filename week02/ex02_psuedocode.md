BEGIN [ตรวจสอบเกรด]
INPUT score
IF score >= 80 THEN grade = A
ELSE IF score >= 70 THEN grade = "B"
ELSE IF score >= 60 THEN grade = "C"
ELSE IF score >= 50 THEN grade = "D"
ELSE grade = "F"
	END IF
	OUTPUT grade
END


BEGIN [หาค่าสูงสุดจาก 2 ตัวเลข]
	INPUT a & b
	IF a > b THEN
		OUTPUT a
	ELSE
		OUTPUT b
	END IF
END


BEGIN [นับจาก 1 ถึง N]
	INPUT N
	i = 1
	WHILE i <= N DO
		OUTPUT i
		i = i + 1
	END WHILE
	END
END
