//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the LineFormatter library
//          https://github.com/RobTillaart/LineFormatter
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "LineFormatter.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "LINEFORMATTER_LIB_VERSION: %s\n", (char*) LINEFORMATTER_LIB_VERSION);

  LineFormatter Line;

  assertEqual(0, Line.getMaxLength());
  Line.setMaxLength(80);
  assertEqual(80, Line.getMaxLength());

  assertEqual(0, Line.getAutoNewLine());
  Line.setAutoNewLine(5);
  assertEqual(5, Line.getAutoNewLine());
}


unittest(test_position)
{
  LineFormatter L;

  assertEqual(0, (int)Line.getPos());
  assertEqual(20, (int)Line.gotoPos(20));
  assertEqual(20, (int)Line.gotoPos(15));

  Line.repeat(10, '*');
  assertEqual(30, (int)Line.getPos());
  Line.repeat(10, "--");
  assertEqual(50, (int)Line.getPos());
}


unittest(test_tab)
{
  LineFormatter L;

  fprintf(stderr, "tab setting\n");
  for (int i = 8; i <= 80; i += 8)
  {
    Line.addTab(i);
  }
  assertEqual(10, Line.getTabCount());
  for (int i = 0; i < Line.getTabCount(); i++)
  {
    fprintf(stderr, "%d\t", 8 + i*8);
    assertEqual(8 + i*8, Line.getTabStop(i));
  }

  fprintf(stderr, "tab test - !! cur position is one before tab position\n");
  for (int i = 0; i < Line.getTabCount(); i++)
  {
    fprintf(stderr, "%d\t", 8 + i*8);  // tab positions
    Line.write('\t');
    assertEqual(8 + i*8, (int)Line.getPos() + 1 );  // current position is just before tab
  }

}


unittest_main()

// --------
