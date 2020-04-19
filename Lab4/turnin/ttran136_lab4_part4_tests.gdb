# Test file for "Lab4"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x01 => PORTB: 0x00 PORTC: 0x00"
# Set inputs
set State = Start
setPINA 0x01
# Continue for several ticks
continue 4
# Set expect values
expectPORTB 0x00
expectPORTC 0x00
# Check pass/fail
checkResult

test "PINA: 0x04, 0x00, 0x02 => PORTB: PORTC: 0x06"
set State = Init
setPINA 0x04
continue 0
setPINA 0x00
continue 0
setPINA 0x02
continue 0
expectPORTB 0x01
expectPORTC 0x03
checkResult

test " PINA 0x03 => PORTC: 0x00"
set State = Start
setPINA 0x03
continue 4
expectPORTC 0x00
checkResult

test "PINA: 0x01, 0x02 = > PORTC: 0x07"
set State = Start
setPINA 0x01
continue 4
setPINA 0x02
continue 4
expectPORTC 0x07
checkResult

test "PINA: 0x02, 0x01, 0x02 => PORTC: 0x06"
set State = Start
setPINA 0x02
continue 4
setPINA 0x01
continue 4
setPINA 0x02
continue 4
expectPORTC 0x06
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
