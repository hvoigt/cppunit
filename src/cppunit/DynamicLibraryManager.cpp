#include <cppunit/plugin/DynamicLibraryManager.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)
#include <cppunit/plugin/DynamicLibraryManagerException.h>

namespace CppUnit
{


DynamicLibraryManager::DynamicLibraryManager( const std::string &libraryFileName )
    : m_libraryHandle( NULL )
{
  loadLibrary( libraryFileName );
}


DynamicLibraryManager::~DynamicLibraryManager()
{
  releaseLibrary();
}


DynamicLibraryManager::Symbol 
DynamicLibraryManager::findSymbol( const std::string &symbol )
{
  try
  {
    Symbol symbolPointer = doFindSymbol( symbol );
    if ( symbolPointer != NULL )
      return symbolPointer;
  }
  catch ( ... )
  {
  }

  throw DynamicLibraryManagerException( m_libraryName, symbol );
  return NULL;    // keep compiler happy
}


void
DynamicLibraryManager::loadLibrary( const std::string &libraryName )
{
  try
  {
    releaseLibrary();
     m_libraryHandle = doLoadLibrary( libraryName );
    if ( m_libraryHandle != NULL )
      return;
  }
  catch (...)
  {
  }

  throw DynamicLibraryManagerException( m_libraryName );
}


void 
DynamicLibraryManager::releaseLibrary()
{
  if ( m_libraryHandle != NULL )
  {
    doReleaseLibrary();
    m_libraryHandle = NULL;
  }
}


} //  namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)
