(ns sigma.core
  (:gen-class))

(defn -main
  [& args]
  (def s (new com.codetinkerer.sigma.SigmaBridge))
  (def ctx (.initContext s))
  (.loop s ctx)
  (.cleanup s ctx)
)
