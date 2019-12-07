package com.codetinkerer.sigma;

import com.codetinkerer.sigma.NativeLoader;

public class SigmaBridge {
  public native long initContext();
  public native void loop(long ctx);
  public native void cleanup(long ctx);

  static {
    NativeLoader.loadFromJar("sigmalib.so");
  }
}
