// //////////////////////////////////////////////////////////////////////////
// Header file HelperMacros.h
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/15
// //////////////////////////////////////////////////////////////////////////
#ifndef CPPUNIT_EXTENSIONS_HELPERMACROS_H
#define CPPUNIT_EXTENSIONS_HELPERMACROS_H

#include <string>
#include <cppunit/extensions/AutoRegisterSuite.h>
#include <cppunit/extensions/TestSuiteBuilder.h>

// The macro __CU_SUITE_CTOR_ARGS expand to an expression used to construct
// the TestSuiteBuilder with macro CU_TEST_SUITE.
//
// The name of the suite is extracted from the macro parameter
// if CU_USE_TYPEINFO is not defined, otherwise it is extracted using
// RTTI.
//
// This macro is for cppunit internal and should not be use otherwise.
#ifdef CU_USE_TYPEINFO
#define __CU_SUITE_CTOR_ARGS( ATestCaseType )

#else  // CU_USE_TYPEINFO
#define __CU_SUITE_CTOR_ARGS( ATestCaseType ) (std::string(#ATestCaseType))

#endif // CU_USE_TYPEINFO


/** Begins the declaration of the test suite
 *
 * The CU_TEST_XXX macros are helper to define test suite that are 
 * automatically registered to the TestRegistry.
 * 
 * You just need to add a set of macro to declare the unit test method.
 * Those macros will create a template method named registerTests
 * with adds the test methods using TestCaller to the suite.
 *
 * This macro will also define a static method named suite() that
 * return a pointer on the suite associated to the test case type.
 * The method signature is: \code static CppUnit::TestSuite *suite().\endcode
 *
 * Notes that you must directly inherit from CppUnit::TestCase when using
 * this macro. See CU_TEST_SUB_SUITE if you need to declare a suite
 * for a sub-class inheriting a test case that use CU_TEST_SUITE.
 *
 * \code
 * #include <cppunit/AutoRegisterTests.h>
 * class MyTest : public CppUnit::TestCase {
 *   CU_TEST_SUITE( MyTest );
 *   CU_TEST( testEquality );
 *   CU_TEST( testSetName );
 *   CU_TEST_SUITE_END();
 * public:
 *   void testEquality();
 *   void testSetName();
 * };
 * \endcode
 * 
 * Somewhere in an implementation file:
 *
 * \code
 * CU_TEST_SUITE_REGISTRATION( MyTest );
 * \encode
 * 
 * The great thing about that is that you can even used it on template test case.
 * You don't even need to specify the template parameters! For example:
 *
 * \code
 * template<typename CharType>
 * class StringTest : public CppUnit::Testcase {
 *   CU_TEST_SUITE( StringTest );
 *   CU_TEST( testAppend );
 *   CU_TEST_SUITE_END();
 * public:  
 *   ...
 * };
 * \endcode
 *
 * And you need to add in an implementation file:
 *
 * \code
 * CU_TEST_SUITE_REGISTRATION( String<char> );
 * CU_TEST_SUITE_REGISTRATION( String<wchar_t> );
 * \encode
 *
 * \param ATestCaseType Type of the test case class.
 * \see CU_TEST_SUB_SUITE, CU_TEST, CU_TEST_SUITE_END, CU_TEST_SUITE_REGISTRATION.
 */
#define CU_TEST_SUITE( ATestCaseType )                                  \
  private:                                                              \
    typedef ATestCaseType __ThisTestCaseType;                           \
  public:                                                               \
    static CppUnit::Test *suite()                                       \
    {                                                                   \
      __ThisTestCaseType *test =NULL;                                   \
      CppUnit::TestSuiteBuilder<__ThisTestCaseType>                     \
          suite __CU_SUITE_CTOR_ARGS( ATestCaseType );                  \
      __ThisTestCaseType::registerTests( suite, test );                 \
      return suite.takeSuite();                                         \
    }                                                                   \
    template<typename TestCaseType>                                     \
    static void                                                         \
    registerTests( CppUnit::TestSuiteBuilder<TestCaseType> &suite,      \
                   TestCaseType *test )                                 \
    {


/** Begins the declaration of the test suite
 * 
 * This macro works just the same as CU_TEST_SUITE, but allow you to specify
 * the base class. When the test are registered, the base class test
 * defined using the CU_TEST_SUITE macro or CU_TEST_SUB_SUITE macro are
 * added to the suite.
 *
 * Here is an example:
 *
 * \code
 * #include <cppunit/AutoRegisterTests.h>
 * class MySubTest : public MyTest {
 *   CU_TEST_SUB_SUITE( MySubTest, MyTest );
 *   CU_TEST( testAdd );
 *   CU_TEST( testSub );
 *   CU_TEST_SUITE_END();
 * public:
 *   void testAdd();
 *   void testSub();
 * };
 * \endcode
 *
 * \param ATestCaseType Type of the test case class.
 * \see CU_TEST_SUITE.
 */
#define CU_TEST_SUB_SUITE( ATestCaseType, ASuperClass )                       \
  private:                                                                    \
    typedef ASuperClass __ThisSuperClassType;                                 \
  CU_TEST_SUITE( ATestCaseType );                                             \
      __ThisSuperClassType::registerTests( suite, test )

/** Adds a method to the suite.
 * \param testMethod Name of the method of the test case to add to the
 *                   suite. The signature of the method must be of
 *                   type: void testMethod();
 * \see  CU_TEST_SUITE.
 */
#define CU_TEST( testMethod )                                           \
      suite.addTestCaller( #testMethod, testMethod ) 

/** Ends the declaration of the test suite and automatically register
 * the test suite in the TestRegistry.
 *
 * After this macro, member access is set to "private".
 *
 * \see TestRegistry.
 * \see  CU_TEST_SUITE.
 */
#define CU_TEST_SUITE_END()                                             \
}                                                                       \
  private:

#define __CU_CONCATENATE_DIRECT( s1, s2 ) s1##s2
#define __CU_CONCATENATE( s1, s2 ) __CU_CONCATENATE_DIRECT( s1, s2 )

/** Decorates the specified string with the line number to obtain a unique name;
 * @param str String to decorate.
 */
#define __CU_MAKE_UNIQUE_NAME( str ) __CU_CONCATENATE( str, __LINE__ )

/** Implementation of the auto-registration of test into the TestRegistry.
 * Should be placed in the cpp file.
 * @param ATestCaseType Type of the test case class.
 * \warning This macro should be used only once per line of code (the line
 *          number is used to name a hidden static variable).
 * \see  CU_TEST_SUITE, CppUnit::AutoRegisterSuite.
 */
#define CU_TEST_SUITE_REGISTRATION( ATestCaseType )                     \
  static CppUnit::AutoRegisterSuite< ATestCaseType >                    \
             __CU_MAKE_UNIQUE_NAME(__autoRegisterSuite )


#endif  // CPPUNIT_EXTENSIONS_HELPERMACROS_H
