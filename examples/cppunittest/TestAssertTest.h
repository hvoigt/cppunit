#ifndef TESTASSERTTEST_H
#define TESTASSERTTEST_H

#include <cppunit/extensions/HelperMacros.h>


class TestAssertTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( TestAssertTest );
  CPPUNIT_TEST( testAssertThrow );
  CPPUNIT_TEST( testAssertNoThrow );
  CPPUNIT_TEST( testAssertAssertionFail );
  CPPUNIT_TEST( testAssertAssertionPass );
  CPPUNIT_TEST( testAssert );
  CPPUNIT_TEST( testAssertEqual );
  CPPUNIT_TEST( testAssertMessageTrue );
  CPPUNIT_TEST( testAssertMessageFalse );
  CPPUNIT_TEST( testAssertDoubleEquals );
  CPPUNIT_TEST( testAssertDoubleEqualsPrecision );
  CPPUNIT_TEST( testAssertDoubleNonFinite );
  CPPUNIT_TEST( testFail );
  CPPUNIT_TEST( testKnownFailureAssert );
  CPPUNIT_TEST( testKnownFailureAssertMessage );
  CPPUNIT_TEST( testKnownFailure );
  CPPUNIT_TEST( testKnownFailureEqual );
  CPPUNIT_TEST( testKnownFailureEqualMessage );
  CPPUNIT_TEST( testKnownFailureDoubleEqual );
  CPPUNIT_TEST( testKnownFailureDoubleEqualMessage );
  CPPUNIT_TEST_SUITE_END();

public:
  TestAssertTest();

  virtual ~TestAssertTest();

  virtual void setUp();
  virtual void tearDown();

  void testAssertThrow();
  void testAssertNoThrow();
  void testAssertAssertionFail();
  void testAssertAssertionPass();

  void testBasicAssertions();

  void testAssert();
  
  void testAssertEqual();

  void testAssertMessageTrue();
  void testAssertMessageFalse();

  void testAssertDoubleEquals();
  void testAssertDoubleEqualsPrecision();
  void testAssertDoubleNonFinite();

  void testAssertLongEquals();
  void testAssertLongNotEquals();

  void testFail();
  void testKnownFailureAssert();
  void testKnownFailureAssertMessage();
  void testKnownFailure();
  void testKnownFailureEqual();
  void testKnownFailureEqualMessage();
  void testKnownFailureDoubleEqual();
  void testKnownFailureDoubleEqualMessage();

private:
  TestAssertTest( const TestAssertTest &copy );
  void operator =( const TestAssertTest &copy );

  void checkDoubleNotEquals( double expected, 
                             double actual, 
                             double delta );

  void checkMessageContains( CPPUNIT_NS::Exception *e,
                             std::string expectedMessage );

private:
};

#endif  // TESTASSERTTEST_H
