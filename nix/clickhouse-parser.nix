(final: prev: {
   clickhouse-parser-lib = (prev.clickhouse.override {rustSupport=false;}).overrideAttrs (oldAttrs: {
    buildPhase = ''
        runHook preBuild

        # Grab the relevant header files we need in our output since they do not seem to be available later.
        mkdir -p headers
        find src/Parsers -name '*.h' -exec cp {} ./headers/ \;

        # Build the static lib for the clickhouse SQL parser (libclickhouse_parsers)
        cmake --build . --target clickhouse_parsers --verbose
        runHook postBuild
    '';

    installPhase = ''
        mkdir -p $out/include/clickhouse/headers
        cp headers/* $out/include/clickhouse/headers/
        cp src/Parsers/libclickhouse_parsers.a $out/include/clickhouse/
    '';
   });
})

