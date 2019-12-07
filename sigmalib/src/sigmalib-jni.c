#include <jni.h>

#include "sigmalib.h"

JNIEXPORT jlong JNICALL Java_com_codetinkerer_sigma_SigmaBridge_initContext(
  JNIEnv *env,
  jobject obj
) {
  sigma_context_t *context = sigma_init();
  return (jlong)context;
}

JNIEXPORT void JNICALL Java_com_codetinkerer_sigma_SigmaBridge_loop(
  JNIEnv *env,
  jobject obj, jlong ctx
) {
  sigma_loop((sigma_context_t*) ctx);
}

JNIEXPORT void JNICALL Java_com_codetinkerer_sigma_SigmaBridge_cleanup(
  JNIEnv *env,
  jobject obj,
  jlong ctx
) {
  sigma_cleanup((sigma_context_t*) ctx);
}
