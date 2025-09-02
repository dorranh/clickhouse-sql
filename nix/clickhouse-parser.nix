(final: prev: {
  clickhouse-parser-lib = (prev.clickhouse.override {rustSupport = false;}).overrideAttrs (oldAttrs: {
    cmakeFlags =
      oldAttrs.cmakeFlags
      ++ [
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
      ];

    # Note to self: Need to grab all of the content from .. during the buildPhase since it is not
    # available afterwards.
    #
    #
    # Also! Depending on how things are looking I might need to just bring in my own project into this
    # build, calling the Clickhouse cmake file as a cmake external dependency. That way all of the various
    # 3rd-party dependencies that ClickHouse relies on will get properly resolved.

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
      mkdir -p $out/build-dir
      cp -r . $out/build-dir
    '';
  });
})
