Julius: WebAssembly *Asyncify* 対応 ビルド情報
==========================================================================
LDFLAGS :   zlibのライブラリへのパスを通すこと
CC      :   emcc
CFLAGS  :   zlibのヘッダへのパスを通すこと
    -s  :   ASYNCIFY および ASYNCIFY_IMPORTS を指定すること
            ファイル読み込み中のOOMへ対処するためINITIAL_MEMORYを指定すること
AR      :   emar
RANLIB  :   emranlib
その他  :   *libsent* mictype は openal のみ対応
            *libsent* openmp は非対応のため無効化
            *libjulius* pthread は非対応のため無効化
            *libjulius* plugin は搭載しない予定のため無効化

例)
LDFLAGS="-L /path/to/zlib -lidbfs.js" CC=emcc CFLAGS='-I /path/to/zlib -s INITIAL_MEMORY=671088640 -s ASYNCIFY -s ASYNCIFY_IMPORTS=[\"wait_animation_frame\"] -Oz' AR=emar RANLIB=emranlib ./configure --with-mictype=openal --disable-openmp --disable-pthread --disable-plugin
