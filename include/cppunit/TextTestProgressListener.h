#ifndef CPPUNIT_TEXTTESTPROGRESSLISTENER_H
#define CPPUNIT_TEXTTESTPROGRESSLISTENER_H

#include <cppunit/TestListener.h>


namespace CppUnit
{

/*! \class TextTestProgressListener
 * \brief This class represents
 */
class TextTestProgressListener : public TestListener
{
public:
  /*! Constructs a TextTestProgressListener object.
   */
  TextTestProgressListener();

  /// Destructor.
  virtual ~TextTestProgressListener();

  void startTest( Test *test );
  void addFailure( const TestFailure &failure );

  void done();

private:
  /// Prevents the use of the copy constructor.
  TextTestProgressListener( const TextTestProgressListener &copy );

  /// Prevents the use of the copy operator.
  void operator =( const TextTestProgressListener &copy );

private:
};


} //  namespace CppUnit


#endif  // CPPUNIT_TEXTTESTPROGRESSLISTENER_H
