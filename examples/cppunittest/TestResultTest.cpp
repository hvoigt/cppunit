#include "CoreSuite.h"
#include "TestResultTest.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestResultTest,
                                       coreSuiteName() );


TestResultTest::TestResultTest()
{
}


TestResultTest::~TestResultTest()
{
}


void 
TestResultTest::setUp()
{
  m_result = new CPPUNIT_NS::TestResult();
  m_listener1 = new MockTestListener( "listener1" );
  m_listener2 = new MockTestListener( "listener2" );
  m_dummyTest = new CPPUNIT_NS::TestCase();
}


void 
TestResultTest::tearDown()
{
  delete m_dummyTest;
  delete m_listener1;
  delete m_listener2;
  delete m_result;
}


void 
TestResultTest::testConstructor()
{
  CPPUNIT_ASSERT( !m_result->shouldStop() );
}


void 
TestResultTest::testStop()
{
  m_result->stop();
  CPPUNIT_ASSERT( m_result->shouldStop() );
}


void 
TestResultTest::testAddError()
{
  CPPUNIT_NS::Exception *dummyException = new CPPUNIT_NS::Exception( 
                                           CPPUNIT_NS::Message( "some_error" ) );
  m_listener1->setExpectFailure( m_dummyTest, dummyException, true );
  m_result->addListener( m_listener1 );

  m_result->addError( m_dummyTest, dummyException );

  m_listener1->verify();
}


void 
TestResultTest::testAddFailure()
{
  CPPUNIT_NS::Exception *dummyException = new CPPUNIT_NS::Exception( 
                                            CPPUNIT_NS::Message("some_error" ) );
  m_listener1->setExpectFailure( m_dummyTest, dummyException, false );
  m_result->addListener( m_listener1 );

  m_result->addFailure( m_dummyTest, dummyException );

  m_listener1->verify();
}


void 
TestResultTest::testStartTest()
{
  m_listener1->setExpectStartTest( m_dummyTest );
  m_result->addListener( m_listener1 );
  
  m_result->startTest( m_dummyTest );

  m_listener1->verify();
}


void 
TestResultTest::testEndTest()
{
  m_listener1->setExpectEndTest( m_dummyTest );
  m_result->addListener( m_listener1 );
  
  m_result->endTest( m_dummyTest );

  m_listener1->verify();
}


void 
TestResultTest::testStartSuite()
{
  m_listener1->setExpectStartSuite( m_dummyTest );
  m_result->addListener( m_listener1 );
  
  m_result->startSuite( m_dummyTest );

  m_listener1->verify();
}


void 
TestResultTest::testEndSuite()
{
  m_listener1->setExpectEndSuite( m_dummyTest );
  m_result->addListener( m_listener1 );
  
  m_result->endSuite( m_dummyTest );

  m_listener1->verify();
}


void 
TestResultTest::testRunTest()
{
  m_listener1->setExpectStartTestRun( m_dummyTest, m_result );
  m_listener1->setExpectEndTestRun( m_dummyTest, m_result );
  m_result->addListener( m_listener1 );
  
  m_result->runTest( m_dummyTest );

  m_listener1->verify();
}


void 
TestResultTest::testTwoListener()
{
  m_listener1->setExpectStartTest( m_dummyTest );
  m_listener2->setExpectStartTest( m_dummyTest );
  CPPUNIT_NS::Exception *dummyException1 = new CPPUNIT_NS::Exception( 
                                             CPPUNIT_NS::Message( "some_error" ) );
  m_listener1->setExpectFailure( m_dummyTest, dummyException1, true );
  m_listener2->setExpectFailure( m_dummyTest, dummyException1, true );
  m_listener1->setExpectEndTest( m_dummyTest );
  m_listener2->setExpectEndTest( m_dummyTest );
  m_result->addListener( m_listener1 );
  m_result->addListener( m_listener2 );

  m_result->startTest( m_dummyTest );
  m_result->addError( m_dummyTest, dummyException1 );
  m_result->endTest( m_dummyTest );

  m_listener1->verify();
  m_listener2->verify();
}
