#include <cppunit/Portability.h>
#include <sstream>
#include <utility>
#include "cppunit/TestSuite.h"
#include "cppunit/extensions/TestFactoryRegistry.h"

#if CPPUNIT_USE_TYPEINFO
#  include "cppunit/extensions/TypeInfoHelper.h"
#endif


namespace CppUnit {

TestFactoryRegistry::TestFactoryRegistry( std::string name ) :
    m_name( name )
{
}

TestFactoryRegistry::~TestFactoryRegistry()
{
  for ( Factories::iterator it = m_factories.begin(); it != m_factories.end(); ++it )
  {
    TestFactory *factory = it->second;
    delete factory;
  }
}


TestFactoryRegistry &
TestFactoryRegistry::getRegistry()
{
  static TestFactoryRegistry registry;
  return registry;
}


TestFactoryRegistry &
TestFactoryRegistry::getRegistry( const std::string &name )
{
// No clean-up at the current time => memory leaks.
// Need to find a way to solve the folowing issue:
// getRegistry().registryFactory( "Functionnal", 
//                                getRegistry( "Functionnal" ) );
// => the test factory registry "Functionnal" would be
// destroyed twice: once by the map below, once by the getRegistry() factory.
  static NamedRegistries registries;

  NamedRegistries::const_iterator foundIt = registries.find( name );
  if ( foundIt == registries.end() )
  {
    TestFactoryRegistry *factory = new TestFactoryRegistry( name );
    registries.insert( std::make_pair( name, factory ) );
    return *factory;
  }
  return *foundIt->second;
}


void 
TestFactoryRegistry::registerFactory( const std::string &name,
                                      TestFactory *factory )
{
  m_factories[name] = factory;
}


void 
TestFactoryRegistry::registerFactory( TestFactory *factory )
{
  std::ostringstream stream;
  static int serialNumber = 1;
  stream << "@Dummy@"  <<  serialNumber++;
  std::string name( stream.str() );

  registerFactory( name, factory );
}

Test *
TestFactoryRegistry::makeTest()
{
  TestSuite *suite = new TestSuite( m_name );
  addTestToSuite( suite );
  return suite;
}


void 
TestFactoryRegistry::addTestToSuite( TestSuite *suite )
{
  for ( Factories::iterator it = m_factories.begin(); 
        it != m_factories.end(); 
        ++it )
  {
    TestFactory *factory = (*it).second;
    suite->addTest( factory->makeTest() );
  }
}


}  // namespace CppUnit
