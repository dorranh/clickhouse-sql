(final: prev: {
   clickhouse-parser-lib = (prev.clickhouse.override {rustSupport=false;}).overrideAttrs (oldAttrs: {
    buildPhase = ''
        # Note: buildPhase is run in cmake build directory not the repo root.
        mkdir -p headers
        find ../src/Parsers -name '*.h' -exec echo "Found header file:" {} \; -exec cp {} ./headers/ \;

        # Build the static lib for the clickhouse SQL parser (libclickhouse_parsers)
        cmake --build . --target clickhouse_parsers --verbose
    '';

    installPhase = ''
        mkdir -p $out/include/clickhouse
        cp -r headers $out/include/clickhouse
        cp src/Parsers/libclickhouse_parsers.a $out/include/clickhouse/
    '';
   });
})

