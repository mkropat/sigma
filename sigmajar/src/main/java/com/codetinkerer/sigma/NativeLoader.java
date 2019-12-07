package com.codetinkerer.sigma;

import java.io.File;
import java.io.InputStream;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Files;

public class NativeLoader {
  public static void loadFromJar(String libName) {
    try {
      URL libUrl = SigmaBridge.class.getResource("/" + libName);

      File tmpDir = Files.createTempDirectory(SigmaBridge.class.getSimpleName()).toFile();
      tmpDir.deleteOnExit();

      File libFile = new File(tmpDir, libName);
      libFile.deleteOnExit();

      try (InputStream fis = libUrl.openStream()) {
        Files.copy(fis, libFile.toPath());
      }

      System.load(libFile.getAbsolutePath());
    }
    catch (IOException ex) {
      throw new ExceptionInInitializerError(ex);
    }
  }
}
