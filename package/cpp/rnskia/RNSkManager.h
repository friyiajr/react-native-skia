#pragma once

#include <jsi/jsi.h>
#include <map>
#include <memory>

#include "RNSkPlatformContext.h"
#include <JsiSkCanvas.h>
#include <RNSkDrawView.h>
#include <RNSkJsiViewApi.h>

namespace RNSkia {

using namespace facebook;

class RNSkManager {
public:
  /**
    Initialializes a new instance of the RNSkManager
    @param jsRuntime The main JavaScript runtime
    @param jsCallInvoker The callinvoker
    @param platformContext Context used by wrappers to get platform
    functionality
  */
  RNSkManager(jsi::Runtime *jsRuntime,
              std::shared_ptr<facebook::react::CallInvoker> jsCallInvoker,
              std::shared_ptr<RNSkPlatformContext> platformContext);

  ~RNSkManager();

  /**
   * Registers a RNSkDrawView with the given native id
   * @param nativeId Native view id
   * @param view View to register
   */
  void registerSkiaDrawView(size_t nativeId, RNSkDrawView *view);

  /**
   * Unregisters the RNSkDrawView from the list of registered views
   * @param nativeId Native view Id
   */
  void unregisterSkiaDrawView(size_t nativeId);

  /**
   * @return The platform context
   */
  std::shared_ptr<RNSkPlatformContext> getPlatformContext() {
    return _platformContext;
  }

private:
  /**
   * Installs the javascript methods for registering/unregistering draw
   * callbacks for RNSkDrawViews. Called on installation of the parent native
   * module.
   */
  void installBindings();

  jsi::Runtime *_jsRuntime;
  std::shared_ptr<RNSkPlatformContext> _platformContext;
  std::shared_ptr<facebook::react::CallInvoker> _jsCallInvoker;
  std::shared_ptr<RNSkJsiViewApi> _viewApi;
};

} // namespace RNSkia