#include <cppunit/Asserter.h>
#include <cppunit/Exception.h>
#include <cppunit/Message.h>


CPPUNIT_NS_BEGIN


void 
Asserter::fail( std::string message, 
                const SourceLine &sourceLine, bool known )
{
  fail( Message( "assertion failed", message ), sourceLine, known );
}


void 
Asserter::fail( const Message &message, 
                const SourceLine &sourceLine, bool known )
{
  throw Exception( message, sourceLine, known );
}


void 
Asserter::failIf( bool shouldFail, 
                  const Message &message, 
                  const SourceLine &sourceLine, bool known )
{
  if ( shouldFail )
    fail( message, sourceLine, known );
}


void 
Asserter::failIf( bool shouldFail, 
                  std::string message, 
                  const SourceLine &sourceLine, bool known )
{
  failIf( shouldFail, Message( "assertion failed", message ), sourceLine, known );
}


std::string 
Asserter::makeExpected( const std::string &expectedValue )
{
  return "Expected: " + expectedValue;
}


std::string 
Asserter::makeActual( const std::string &actualValue )
{
  return "Actual  : " + actualValue;
}


Message 
Asserter::makeNotEqualMessage( const std::string &expectedValue,
                               const std::string &actualValue,
                               const AdditionalMessage &additionalMessage,
                               const std::string &shortDescription )
{
  Message message( shortDescription,
                   makeExpected( expectedValue ),
                   makeActual( actualValue ) );
  message.addDetail( additionalMessage );

  return message;
}


void 
Asserter::failNotEqual( std::string expected, 
                        std::string actual, 
                        const SourceLine &sourceLine,
                        const AdditionalMessage &additionalMessage,
                        std::string shortDescription, bool known )
{
  fail( makeNotEqualMessage( expected,
                             actual,
                             additionalMessage,
                             shortDescription ), 
        sourceLine, known );
}


void 
Asserter::failNotEqualIf( bool shouldFail,
                          std::string expected, 
                          std::string actual, 
                          const SourceLine &sourceLine,
                          const AdditionalMessage &additionalMessage,
                          std::string shortDescription, bool known )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage, shortDescription, known );
}


CPPUNIT_NS_END
