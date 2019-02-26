* lightning project

lightning project has a dynamic library: libLightning-debug.dylib. Find it and we need this to build svgBuilder



* svgBuilder project
under monorepo svgBuilder folder (here wsvgBuilder is an illustration, needs to build under original monorepo's svgBuilder),tidy up things and expose API in wangyiMoho.h. Run g++ to compile and generate libsvgBuilder.so

g++ -fPIC -shared -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/3rdparty/include/librsvg-2.0 -I/usr/local/include/gdk-pixbuf-2.0 -I/usr/local/Cellar/pango/1.42.1/include/pango-1.0 -I/usr/local/include/libcroco-0.6 -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include -I/usr/local/include/cairo -I/usr/local/Cellar/glib/2.56.1/include/glib-2.0 -I/usr/include/libxml2 -I/usr/local/Cellar/imagemagick/7.0.8-2/include/ImageMagick-7 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk/System/Library/Frameworks/JavaVM.framework/Headers -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src -I/Users/Yiyang.Wang/Snapchat/Dev/monorepo/rendering/lightning/_builds/osx-10-13-dep-10-10-cxx17-fpic/src/Lightning/Proto -I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include -I/Users/Yiyang.Wang/Snapchat/Dev/hunter/_Base/xxxxxxx/f891d3c/60fc936/Install/include/eigen3 -L. -lLightning-debug -lcurl -o libsvgBuilder.so main.cpp wangyi.cpp wangyiMoho.cpp ../lightningTestApp/HTTPDownloader.cpp -fPIC -std=c++17 -stdlib=libc++ -march=skylake -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mfma -mbmi2 -mavx2 -mno-sse4a -mno-xop

Outputs: libsvgBuilder.so


* lightningWrapper.h/cpp wrap libsvgBuilder.so

Compile using: g++ -fPIC -shared -L./wsvgBuilder -lsvgBuilder -o libLightningWrapper.so lightningWrapper.cpp

Outputs: libLightningWrapper.so

* clibLightning.c exposes Lua API

Compile using: gcc -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup -L. -llightningWrapper -o clibLightning.so clibLightning.c 

Outputs: clibLightning.so

* call.lua

require("clibLightning") 
print(wLightning(81))

note that *.dylib needs to be copied to /usr/local/lib

* MOHO

libLightning-debug.dylib -> /usr/local/lib/
libsvgBuilder.so -> /usr/local/lib/
libLightningWrapper.so -> /usr/local/lib/
clibLightning.so -> /usr/local/lib/lua/5.2




