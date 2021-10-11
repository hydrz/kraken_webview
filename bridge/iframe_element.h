/*
 * Copyright (C) 2020 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#ifndef KRAKENBRIDGE_IFRAME_ELEMENT_H
#define KRAKENBRIDGE_IFRAME_ELEMENT_H

#include "kraken/include/kraken_bridge.h"

#define KRAKEN_EXPORT_C extern "C" __attribute__((visibility("default"))) __attribute__((used))

namespace kraken::binding::jsc {

struct NativeIframeElement;

class JSIframeElement : public JSElement {
public:
  static std::unordered_map<JSContext *, JSIframeElement *> instanceMap;
  OBJECT_INSTANCE(JSIframeElement)
  JSObjectRef instanceConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount,
                                  const JSValueRef *arguments, JSValueRef *exception) override;
protected:
  JSIframeElement() = delete;
  explicit JSIframeElement(JSContext *context);
  ~JSIframeElement();

  static JSValueRef postMessage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
                                const JSValueRef arguments[], JSValueRef *exception);

  JSFunctionHolder m_postMessage{context, prototypeObject, this, "postMessage", postMessage};
};

class IframeElementInstance : public ElementInstance {
  public:
    DEFINE_OBJECT_PROPERTY(IFrameElement, 3, width, height, contentWindow)
    DEFINE_PROTOTYPE_OBJECT_PROPERTY(IFrameElement, 1, postMessage)
    IframeElementInstance() = delete;
    ~IframeElementInstance();
    explicit IframeElementInstance(JSIframeElement *jsIframeElement);
    JSValueRef getProperty(std::string &name, JSValueRef *exception) override;
    bool setProperty(std::string &name, JSValueRef value, JSValueRef *exception) override;
    void getPropertyNames(JSPropertyNameAccumulatorRef accumulator) override;

    NativeIframeElement *nativeIframeElement{nullptr};

  private:
    double _width{0};
    double _height{0};
};

using IframePostMessage = void (*)(NativeIframeElement *nativePtr, NativeString *message);

struct NativeIframeElement {
  NativeIframeElement() = delete;
  explicit NativeIframeElement(NativeElement *nativeElement) : nativeElement(nativeElement){};

  NativeElement *nativeElement;

  IframePostMessage postMessage;
};

} // namespace kraken::binding::jsc

KRAKEN_EXPORT_C
void initBridge();

#endif // KRAKENBRIDGE_IFRAME_ELEMENT_H
