

#ifndef CPPUNIT_TESTDECORATOR_H
#define CPPUNIT_TESTDECORATOR_H

#ifndef CPPUNIT_TEST_H
#include "../Test.h"
#endif

namespace CppUnit {

class TestResult;

/*
 * A Decorator for Tests
 *
 * Does not assume ownership of the test it decorates
 *
 */ 

class TestDecorator : public Test 
{
public:
                TestDecorator   (Test *test);
                ~TestDecorator  ();

    int         countTestCases  () const;
    void        run             (TestResult *result) const;
    std::string toString        () const;
    std::string getName         () const;

protected:
    Test        *m_test;

private:
  TestDecorator( const TestDecorator &);
  void operator =( const TestDecorator & );
};


inline TestDecorator::TestDecorator (Test *test)
{ m_test = test; }


inline TestDecorator::~TestDecorator ()
{}


inline TestDecorator::countTestCases () const
{ return m_test->countTestCases (); }


inline void TestDecorator::run (TestResult *result) const
{ m_test->run (result); }


inline std::string TestDecorator::toString () const
{ return m_test->toString (); }


inline std::string TestDecorator::getName () const
{ return m_test->getName(); }

} // namespace CppUnit

#endif

