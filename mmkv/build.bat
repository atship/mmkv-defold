xmake f -p windows -a x86 -m release 
xmake

xmake f -p windows -a x64 -m release 
xmake

xmake f -p android -a arm64-v8a -m release --ndk_sdkver=21
xmake

xmake f -p android -a armeabi-v7a -m release --ndk_sdkver=19
xmake

move build\lib C:\Users\hualin\Documents\defold\mmkv\mmkv\