/*
 * Copyright (C) 2019-present Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */
// ignore_for_file: unused_import, undefined_function

import 'dart:ffi';
import 'dart:io' show Platform;
import 'dart:typed_data';

/// Search dynamic lib from env.KRAKEN_LIBRARY_PATH or /usr/lib
const String KRAKEN_JS_ENGINE = 'KRAKEN_JS_ENGINE';
final String kkJsEngine = Platform.environment[KRAKEN_JS_ENGINE] ??
    ((Platform.isIOS || Platform.isMacOS || Platform.isAndroid) ? 'jsc' : 'quickjs');
final String libName = 'libkraken_webview_$kkJsEngine';
final String nativeDynamicLibraryName = (Platform.isMacOS || Platform.isIOS)
    ? '$libName.dylib'
    : Platform.isWindows ? '$libName.dll' : '$libName.so';
DynamicLibrary nativeDynamicLibrary =
    DynamicLibrary.open(nativeDynamicLibraryName);