#include <filesystem>
#include <iostream>

#ifdef MACOSX
#include <Carbon/Carbon.h>
#endif

#include "directory.h"
#include "file_string_utils.h"

bool make_dir(std::string dir)
{
  if (dir.empty())
  {
    return true;
  }
 
  while (dir.back() == '/')
  {
    dir.pop_back();
  }

  if (std::filesystem::exists(dir))
  {
std::cout << "make_dir: \"" << dir << "\" already exists\n";
    return true;
  }

std::cout << "make_dir: \"" << dir << "\"\n";

  std::filesystem::path p = dir;
  std::error_code ec;
  bool retval = std::filesystem::create_directories(p, ec);
  if (!retval)
  {
std::cout << ec.message() << "\n";
  }
  return retval;
}

#ifdef MACOSX
// From https://developer.apple.com/carbon/tipsandtricks.html
Boolean AmIBundled()
{
  FSRef processRef;
  FSCatalogInfo processInfo;
  int isBundled;
  ProcessSerialNumber psn = {0, kCurrentProcess};

  GetProcessBundleLocation (&psn, &processRef);
  FSGetCatalogInfo (&processRef, kFSCatInfoNodeFlags, &processInfo, NULL, NULL, NULL);
  isBundled = processInfo.nodeFlags & kFSNodeIsDirectoryMask;

  return( isBundled );
}
#endif

std::string GetProcessDir()
{
#ifdef IPHONE
    std::cout << "Yikes, calling GetProcessDir\n";
    Assert(0);
#endif // IPHONE

#ifdef MACOSX
    // This works for exes which are not bundles!
    CFBundleRef mainBundle = CFBundleGetMainBundle();

    // Find the executable URL - this works even for non-bundles!
    CFURLRef fileUrl = CFBundleCopyExecutableURL(mainBundle);

    // Convert URL to path
    CFStringRef filePath = CFURLCopyFileSystemPath(fileUrl, kCFURLPOSIXPathStyle);

    // Convert (unicode ?) CFStringRef to a const char *
    static const int MAX_STR = 1024;
    char bytes[MAX_STR];

    std::string fileName;
    if (CFStringGetCString(filePath, bytes, MAX_STR, CFStringGetSystemEncoding()))
    {
        fileName = bytes;
    }
    else
    {
        // TODO
        std::cout << "Unexpected: didn't get exe file name: " << bytes << "\n";
    }
    std::string root = just_path(fileName); // strip exe name from end

    if (AmIBundled())
    {
#ifdef BUNDLE_CHECK_DEBUG
        std::cout << "This really is an app bundle.\n";
#endif
    }
    else
    {
#ifdef BUNDLE_CHECK_DEBUG
        std::cout << "This  is not an app bundle.\n";
#endif
    }

#ifdef PROCESS_DIR_DEBUG
    std::cout << "GetProcessDir() result: " << root.c_str() << "\n";
#endif

    return root;
#endif // MACOSX
return {};
}

std::string get_data_dir()
{
#ifdef RASPBERRY_PI
  return "./";
#endif

#ifdef WIN32
  std::string dataDir = GetProcessDir();
  dataDir += "/Data/";
  return dataDir;
#endif
  
#ifdef MACOSX
  if (AmIBundled())
  {
    std::string dataDir = GetProcessDir();
    dataDir += "/../Resources/assets/";
    return dataDir;
  }
  else
  {
    // Command-line version
    return "../assets/";
  }

#endif
  
#ifdef IPHONE
  return iOSGetDataDir();
#endif
}

std::string get_save_dir_macosx_bundled()
{
  static std::string s;
  static bool first = true;
  if (first)
  {
    first = false;

    s = "/Users/Shared/";
    //s += appName;
    //s += "/";

    //MkDir(s);
  }

  return s;
}

std::string get_save_dir_macosx_not_bundled()
{
  static std::string s;
  static bool first = true;
  if (first)
  {
    first = false;

    s += "../save/";

    //MkDir(s);
  }

  return s;
}

std::string get_save_dir()
{
  std::string dir;

#ifdef MACOSX
  if (AmIBundled())
  {
    dir = get_save_dir_macosx_bundled();
  }
  else
  {
    dir = get_save_dir_macosx_not_bundled();
  }
#endif

  std::cout << "Save dir: \"" << dir << "\"\n";

  static bool first_time = true;
  if (first_time)
  {
    make_dir(dir);
  }

  return dir;
}

