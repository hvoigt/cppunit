#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>


CPPUNIT_NS_BEGIN


TestResultCollector::TestResultCollector( SynchronizationObject *syncObject )
    : TestSuccessListener( syncObject )
{
  reset();
}


TestResultCollector::~TestResultCollector()
{
  freeFailures();
}


void 
TestResultCollector::freeFailures()
{
  TestFailures::iterator itFailure = m_failures.begin();
  while ( itFailure != m_failures.end() )
    delete *itFailure++;
  m_failures.clear();

  itFailure = m_knownFailures.begin();
  while ( itFailure != m_knownFailures.end() )
    delete *itFailure++;
  m_knownFailures.clear();
}


void 
TestResultCollector::reset()
{
  TestSuccessListener::reset();

  ExclusiveZone zone( m_syncObject ); 
  freeFailures();
  m_testErrors = 0;
  m_tests.clear();
}


void 
TestResultCollector::startTest( Test *test )
{
  ExclusiveZone zone (m_syncObject); 
  m_tests.push_back( test );
}


void 
TestResultCollector::addFailure( const TestFailure &failure )
{
  TestSuccessListener::addFailure( failure );

  ExclusiveZone zone( m_syncObject ); 

  if (failure.isKnownFailure()) {
    m_knownFailures.push_back( failure.clone() );
    return;
  }

  if ( failure.isError() )
    ++m_testErrors;
  m_failures.push_back( failure.clone() );
}


/// Gets the number of run tests.
int 
TestResultCollector::runTests() const
{ 
  ExclusiveZone zone( m_syncObject ); 
  return m_tests.size(); 
}


/// Gets the number of detected errors (uncaught exception).
int 
TestResultCollector::testErrors() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_testErrors;
}


/// Gets the number of detected failures (failed assertion).
int 
TestResultCollector::testFailures() const
{ 
  ExclusiveZone zone( m_syncObject ); 
  return m_failures.size() - m_testErrors;
}


/// Gets the total number of detected failures.
int 
TestResultCollector::testFailuresTotal() const
{
  ExclusiveZone zone( m_syncObject ); 
  return m_failures.size();
}


/// Gets the total number of known failures.
int
TestResultCollector::testKnownFailures() const
{
  ExclusiveZone zone( m_syncObject );
  return m_knownFailures.size();
}


/// Returns a the list failures (random access collection).
const TestResultCollector::TestFailures & 
TestResultCollector::failures() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_failures; 
}


/// Returns the list of known failures (random access collection).
const TestResultCollector::TestFailures &
TestResultCollector::knownFailures() const
{
  ExclusiveZone zone( m_syncObject );
  return m_knownFailures;
}


const TestResultCollector::Tests &
TestResultCollector::tests() const
{
  ExclusiveZone zone( m_syncObject );
  return m_tests;
}


CPPUNIT_NS_END

