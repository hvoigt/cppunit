#include <cppunit/TestResult.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/plugin/TestPlugIn.h>
#include "ClockerXmlHook.h"
#include "ClockerListener.h"
#include "ClockerModel.h"



class ClockerPlugIn : public CppUnitTestPlugIn
{
public:
  ClockerPlugIn()
    : m_dumper( NULL )
    , m_model( NULL )
    , m_xmlHook( NULL )
  {
  }

  ~ClockerPlugIn()
  {
    delete m_dumper;
    delete m_model;
    delete m_xmlHook;
  }


  void initialize( CppUnit::TestFactoryRegistry *registry,
                   const CppUnit::Parameters &parameters )
  {
    bool text = false;
    if ( parameters.size() > 0  &&  parameters[0] == "text" )
      text = true;

    m_model = new ClockerModel();
    m_dumper = new ClockerListener( m_model, text );
    m_xmlHook = new ClockerXmlHook( m_model );
  }


  void addListener( CppUnit::TestResult *eventManager )
  {
    eventManager->addListener( m_dumper );
  }


  void removeListener( CppUnit::TestResult *eventManager )
  {
    eventManager->removeListener( m_dumper );
  }


  void addXmlOutputterHooks( CppUnit::XmlOutputter *outputter )
  {
    outputter->addHook( m_xmlHook );
  }


  void removeXmlOutputterHooks()
  {
  }


  void uninitialize( CppUnit::TestFactoryRegistry *registry )
  {
  }

private:
  ClockerListener *m_dumper;
  ClockerModel *m_model;
  ClockerXmlHook *m_xmlHook;
};


CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( ClockerPlugIn );

CPPUNIT_TESTPLUGIN_MAIN();