#ifndef CPPUNIT_AUTOREGISTERSUITE_H
#define CPPUNIT_AUTOREGISTERSUITE_H

#include <string>

#include "TestSuiteFactory.h"
#include "TestFactoryRegistry.h"


namespace CppUnit {

  /** Automatically register the test suite of the specified type.
   *
   * This object will register the test returned by TestCaseType::suite()
   * when constructed to the test registry.
   *
   * This object is intented to be used as a static variable.
   *
   * \param TestCaseType Type of the test case which suite is registered.
   * \see CU_TEST_SUITE_REGISTRATION.
   */
  template<class TestCaseType>
  class AutoRegisterSuite
  {
    public:
      /** Auto-register the suite factory in the global registry.
       */
      AutoRegisterSuite()
      {
        AbstractTestFactory *factory = new TestSuiteFactory<TestCaseType>();
        TestFactoryRegistry::getRegistry().registerFactory( factory );
      }

      /** Auto-register the suite factory in the specified registry.
       * \param name Name of the registry.
       */
      AutoRegisterSuite( const std::string &name )
      {
        TestSuiteFactory *factory = new TestSuiteFactory<TestCaseType>();
        TestFactoryRegistry::getRegistry( name ).registerFactory( factory );
      }
  };

} // namespace CppUnit


#endif  // CPPUNIT_AUTOREGISTERSUITE_H
