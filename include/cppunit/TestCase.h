#ifndef CPPUNIT_TESTCASE_H
#define CPPUNIT_TESTCASE_H

#include <string>

#ifndef CPPUNIT_TEST_H
#include "Test.h"
#endif

#ifndef CPPUNIT_TESTASSERT_H
#include "TestAssert.h"
#endif

namespace CppUnit {

  class TestResult;

  /**
   * A test case defines the fixture to run multiple tests. 
   * To define a test case
   * do the following:
   * - implement a subclass of TestCase 
   * - the fixture is defined by instance variables 
   * - initialize the fixture state by overriding setUp
   *   (i.e. construct the instance variables of the fixture)
   * - clean-up after a test by overriding tearDown.
   *
   * Each test runs in its own fixture so there
   * can be no side effects among test runs.
   * Here is an example:
   * 
   * \code
   * class MathTest : public TestCase {
   *     protected: int m_value1;
   *     protected: int m_value2;
   *
   *     public: MathTest (string name)
   *                 : TestCase (name) {
   *     }
   *
   *     protected: void setUp () {
   *         m_value1 = 2;
   *         m_value2 = 3;
   *     }
   * }
   * \endcode
   *
   * For each test implement a method which interacts
   * with the fixture. Verify the expected results with assertions specified
   * by calling assert on the expression you want to test:
   * 
   * \code
   *    protected: void testAdd () {
   *        int result = value1 + value2;
   *        assert (result == 5);
   *    }
   * \endcode
   * 
   * Once the methods are defined you can run them. To do this, use
   * a TestCaller.
   *
   * \code
   * Test *test = new TestCaller<MathTest>("testAdd", MathTest::testAdd);
   * test->run ();
   * \endcode
   *
   *
   * The tests to be run can be collected into a TestSuite. 
   * 
   * \code
   * public: static TestSuite *MathTest::suite () {
   *      TestSuite *suiteOfTests = new TestSuite;
   *      suiteOfTests->addTest(new TestCaller<MathTest>(
   *                              "testAdd", testAdd));
   *      suiteOfTests->addTest(new TestCaller<MathTest>(
   *                              "testDivideByZero", testDivideByZero));
   *      return suiteOfTests;
   *  }
   * \endcode
   * 
   *
   * \see TestResult
   * \see TestSuite 
   * \see TestCaller
   *
   */

  class TestCase : public Test,
                   public TestAssert
  {
    public:
      TestCase         ();
      TestCase         (std::string Name);
      ~TestCase        ();

      virtual void        run              (TestResult *result);
      virtual TestResult  *run             ();
      virtual int         countTestCases   () const;
      std::string         getName          () const;
      std::string         toString         () const;

      virtual void        setUp            ();
      virtual void        tearDown         ();

    protected:
      virtual void        runTest          ();
    
      TestResult          *defaultResult   ();
    
    private:
      TestCase (const TestCase& other); 
      TestCase& operator= (const TestCase& other); 

    private:
      const std::string   m_name;
  };

} // namespace CppUnit

#endif // CPPUNIT_TESTCASE_H 
