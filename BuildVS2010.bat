@echo off
@rem This .bat file builds the targets for CPPUnit using VS2010.  For this to work
@rem correctly, the following requirements must be met:
@rem
@rem 1) It needs to be run from a DOS command line and not double click in Explorer etc.
@rem 2) The VS2010 environment must be initialized.  This might already be done,
@rem    depending on your VS2010 install options.  If not, click "Microsoft Visual
@rem    Studio 2010" -> "Visual Studio Tools" -> "Visual Studio Command Prompt (2010)"
@rem    and run this .bat file from the resulting command window.
@rem 3) A number of things work better if the files in this directory structure are
@rem    headed by a top level directory with no spaces in any level.  [Don't put it
@rem    under "x:\Program Files" for example.]


if not "%1" == "" goto %1%

call BuildVS2010.bat Clean
call BuildVS2010.bat Build

goto :exit


:Clean
devenv  Build2010.sln /clean "Debug|Win32"
devenv  Build2010.sln /clean "Debug Unicode|Win32"
devenv  Build2010.sln /clean "Debug DLL|Win32"
devenv  Build2010.sln /clean "Debug Static|Win32"
devenv  Build2010.sln /clean "Debug No Type Info Name|Win32"
devenv  Build2010.sln /clean "Debug NtTimer|Win32"
devenv  Build2010.sln /clean "Release|Win32"
devenv  Build2010.sln /clean "Release Unicode|Win32"
devenv  Build2010.sln /clean "Release DLL|Win32"
devenv  Build2010.sln /clean "Release Static|Win32"
goto :exit

:Build
@rem Note that reported MSB3073 "build errors" for 'simple_plugin' and 'hierarchy'
@rem projects are a demonstration of failed unit tests and are not actual build
@rem errors.
echo on
devenv  Build2010.sln /build "Debug|Win32"
devenv  Build2010.sln /build "Debug Unicode|Win32"
devenv  Build2010.sln /build "Debug DLL|Win32"
devenv  Build2010.sln /build "Debug Static|Win32"
devenv  Build2010.sln /build "Debug No Type Info Name|Win32"
devenv  Build2010.sln /build "Debug NtTimer|Win32"
devenv  Build2010.sln /build "Release|Win32"
devenv  Build2010.sln /build "Release Unicode|Win32"
devenv  Build2010.sln /build "Release DLL|Win32"
devenv  Build2010.sln /build "Release Static|Win32"

goto :exit


:exit
