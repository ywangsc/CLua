/*
-I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/3rdparty/include/librsvg-2.0 -I/usr/local/include/gdk-pixbuf-2.0 -I/usr/local/Cellar/pango/1.42.1/include/pango-1.0 -I/usr/local/include/libcroco-0.6 -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include -I/usr/local/include/cairo -I/usr/local/Cellar/glib/2.56.1/include/glib-2.0 -I/usr/include/libxml2 -I/usr/local/Cellar/imagemagick/7.0.8-2/include/ImageMagick-7 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk/System/Library/Frameworks/JavaVM.framework/Headers -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src/Lightning/Proto
-I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include -I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include/eigen3

flags: Not all yet
-fPIC -std=c++17 -stdlib=libc++ -march=skylake
-msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mfma -mbmi2 -mavx2 -mno-sse4a -mno-xop


use this to compile:
g++ -fPIC -shared -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/3rdparty/include/librsvg-2.0 -I/usr/local/include/gdk-pixbuf-2.0 -I/usr/local/Cellar/pango/1.42.1/include/pango-1.0 -I/usr/local/include/libcroco-0.6 -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include -I/usr/local/include/cairo -I/usr/local/Cellar/glib/2.56.1/include/glib-2.0 -I/usr/include/libxml2 -I/usr/local/Cellar/imagemagick/7.0.8-2/include/ImageMagick-7 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk/System/Library/Frameworks/JavaVM.framework/Headers -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src/Lightning/Proto -I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include -I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include/eigen3 -L. -lLightning-debug -lcurl -o libsvgBuilder.so main.cpp wangyi.cpp ../lightningTestApp/HTTPDownloader.cpp -fPIC -std=c++17 -stdlib=libc++ -march=skylake -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mfma -mbmi2 -mavx2 -mno-sse4a -mno-xop
*/


#include "lightningWrapper.h"

extern "C" {   

  void testcall_lightning() {
    //something inside svgBuilder 
    wangyiSimplified();
  } 
} 