#ifndef CPPUNIT_HELPER_COMMANDLINEPARSER_H
#define CPPUNIT_HELPER_COMMANDLINEPARSER_H

#include <cppunit/Portability.h>
#include <cppunit/plugin/Parameters.h>
#include <string>
#include <stdexcept>
#include <deque>


/*! Exception thrown on error while parsing command line.
 */
class CommandLineParserException : public std::runtime_error
{
public:
  CommandLineParserException( std::string message )
    : std::runtime_error( message )
  {
  }
};


struct CommandLinePlugInInfo
{
  std::string m_fileName;
  CppUnit::Parameters m_parameters;
};


/*! \brief Parses a command line.

-c --compiler
-x --xml [filename]
-s --xsl stylesheet
-e --encoding encoding
-b --brief-progress
-n --no-progress
-t --text
-o --cout
filename[="options"]
:testpath

 */
class CommandLineParser
{
public:
  /*! Constructs a CommandLineParser object.
   */
  CommandLineParser( int argc, 
                     char *argv[] );

  /// Destructor.
  virtual ~CommandLineParser();

  /*! Parses the command line.
   * \exception CommandLineParserException if an error occurs.
   */
  void parse();

  bool useCompilerOutputter() const;
  bool useXmlOutputter() const;
  std::string getXmlFileName() const;
  std::string getXmlStyleSheet() const;
  std::string getEncoding() const;
  bool useBriefTestProgress() const;
  bool noTestProgress() const;
  bool useTextOutputter() const;
  bool useCoutStream() const;
  std::string getTestPath() const;
  int getPlugInCount() const;
  CommandLinePlugInInfo getPlugInAt( int index ) const;

protected:
  /// Prevents the use of the copy constructor.
  CommandLineParser( const CommandLineParser &copy );

  /// Prevents the use of the copy operator.
  void operator =( const CommandLineParser &copy );

  void readNonOptionCommands();

  bool hasNextArgument() const;

  std::string getNextArgument();

  std::string getCurrentArgument() const;

  bool argumentStartsWith( const std::string &expected ) const;

  void getNextOption();

  bool isOption( const std::string &shortName,
                 const std::string &longName );

  std::string getNextParameter();

  std::string getNextOptionalParameter();

  void fail( std::string message );

protected:
  bool m_useCompiler;
  bool m_useXml;
  std::string m_xmlFileName;
  std::string m_xsl;
  std::string m_encoding;
  bool m_briefProgress;
  bool m_noProgress;
  bool m_useText;
  bool m_useCout;
  std::string m_testPath;

  typedef std::deque<CommandLinePlugInInfo> PlugIns;
  PlugIns m_plugIns;

  typedef std::deque<std::string> Arguments;
  Arguments m_arguments;
  int m_currentArgument;

  std::string m_option;
};


#endif  // CPPUNIT_HELPER_COMMANDLINEPARSER_H
