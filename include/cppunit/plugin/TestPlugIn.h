#ifndef CPPUNIT_PLUGIN_TESTPLUGIN
#define CPPUNIT_PLUGIN_TESTPLUGIN

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/plugin/Parameters.h>

namespace CppUnit
{
class Test;
class TestFactoryRegistry;
class TestResult;
}

/*! \file
 */


/*! Test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * This class define the interface implemented by test plug-in. A pointer to that
 * interface is returned by the function exported by the test plug-in.
 *
 * Plug-in are loaded/unloaded by PlugInManager. When a plug-in is loaded, 
 * initialize() is called. Before unloading the plug-in, the PlugInManager
 * call uninitialize().
 *
 * addListener() and removeListener() are called respectively before and after
 * the test run.
 *
 * \see CPPUNIT_PLUGIN_IMPLEMENT, CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL
 * \see TestPlugInDefaultImpl.
 */
struct CppUnitTestPlugIn
{
  /*! Called just after loading the dynamic library. 
   *
   * Override this method to add additional suite to the registry, though this
   * is preferably done using the macros (CPPUNIT_TEST_SUITE_REGISTRATION...).
   * If you are creating a custom listener to extends the plug-in runner,
   * you can use this to configure the listener using the \a parameters.
   *
   * You could also use the parameters to specify some global parameter, such
   * as test datas location, database name...
   *
   * N.B.: Parameters interface is not define yet, and the plug-in runner does
   * not yet support plug-in parameter.
   */
  virtual void initialize( CppUnit::TestFactoryRegistry *registry,
                           const CppUnit::Parameters &parameters ) =0;

  /*! Gives a chance to the plug-in to register TestListener.
   * 
   * Override this method to add a TestListener for the test run. This is useful
   * if you are writing a custom TestListener, but also if you need to
   * setUp some global resource: listen to TestListener::startTestRun(), 
   * and TestListener::endTestRun().
   */
  virtual void addListener( CppUnit::TestResult *eventManager ) =0;

  /*! Gives a chance to the plug-in to remove its registered TestListener.
   *
   * Override this method to remove a TestListener that has been added.
   */
  virtual void removeListener( CppUnit::TestResult *eventManager ) =0;

  /*! Called just before unloading the dynamic library.
   * 
   * Override this method to unregister test factory added in initialize().
   * This is necessary to keep the TestFactoryRegistry 'clean'. When
   * the plug-in is unloaded from memory, the TestFactoryRegistry will hold
   * reference on test that are no longer available if they are not 
   * unregistered.
   */
  virtual void uninitialize( CppUnit::TestFactoryRegistry *registry ) =0;
};



/*! Name of the function exported by a test plug-in.
 * \ingroup WritingTestPlugIn
 *
 * The signature of the exported function is:
 * \code
 * CppUnitTestPlugIn *CPPUNIT_PLUGIN_EXPORTED_NAME(void);
 * \endif
 */
#define CPPUNIT_PLUGIN_EXPORTED_NAME cppunitTestPlugIn

/*! Type of the function exported by a plug-in.
 * \ingroup WritingTestPlugIn
 */
typedef CppUnitTestPlugIn *(*TestPlugInSignature)();


/*! Implements the function exported by the test plug-in
 * \ingroup WritingTestPlugIn
 */
#define CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( TestPlugInInterfaceType )       \
  CPPUNIT_PLUGIN_EXPORT CppUnitTestPlugIn *CPPUNIT_PLUGIN_EXPORTED_NAME(void)  \
  {                                                                            \
    static TestPlugInInterfaceType plugIn;                                     \
    return &plugIn;                                                            \
  }                                                                            \
  typedef char __CppUnitPlugInExportFunctionDummyTypeDef  // dummy typedef so it can end with ';'


// Note: This include should remain after definition of CppUnitTestPlugIn
#include <cppunit/plugin/TestPlugInAdapter.h>


/*! \def CPPUNIT_PLUGIN_IMPLEMENT_MAIN()
 * \brief Implements the 'main' function for the plug-in.
 *
 * This macros implements the main() function for dynamic library.
 * For example, WIN32 requires a DllMain function, while some Unix 
 * requires a main() function. This macros takes care of the implementation.
 */

// Win32
#if defined(CPPUNIT_HAVE_WIN32_DLL_LOADER)
#if !defined(APIENTRY)
#define WIN32_LEAN_AND_MEAN 
#define NOGDI
#define NOUSER
#define NOKERNEL
#define NOSOUND
#define NOMINMAX
#include <windows.h>
#endif
#define CPPUNIT_PLUGIN_IMPLEMENT_MAIN()               \
  BOOL APIENTRY DllMain( HANDLE hModule,              \
                         DWORD  ul_reason_for_call,   \
                         LPVOID lpReserved )          \
  {                                                   \
      return TRUE;                                    \
  }                                                   \
  typedef char __CppUnitPlugInImplementMainDummyTypeDef

// Unix
#elif defined(CPPUNIT_HAVE_UNIX_DLL_LOADER)
#define CPPUNIT_PLUGIN_IMPLEMENT_MAIN()               \
  int main( int argc, char *argv[] )                  \
  {                                                   \
    return 0;                                         \
  }                                                   \
  typedef char __CppUnitPlugInImplementMainDummyTypeDef


// Other
#else     // other platforms don't require anything specifics
#endif



/*! Implements and exports the test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * This macro exports the test plug-in function using the subclass, 
 * and implements the 'main' function for the plug-in using 
 * CPPUNIT_PLUGIN_IMPLEMENT_MAIN().
 *
 * When using this macro, CppUnit must be linked as a DLL (shared library).
 * Otherwise, tests registered to the TestFactoryRegistry in the DLL will 
 * not be visible to the DllPlugInTester.
 *
 * \see CppUnitTestPlugIn
 * \see CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL(), CPPUNIT_PLUGIN_IMPLEMENT_MAIN().
 */
#define CPPUNIT_PLUGIN_IMPLEMENT()                                      \
  CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( CppUnit::TestPlugInAdapter );  \
  CPPUNIT_PLUGIN_IMPLEMENT_MAIN()


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)


#endif // CPPUNIT_PLUGIN_TESTPLUGIN
