case "${TRAVIS_OS_NAME}" in
  osx)
    brew link gcc || true
    ;;
esac

if test "${BUILD_TYPE}" = "Coverage"; then
  curl -sLo lcov.tar.gz https://github.com/linux-test-project/lcov/archive/v1.14.tar.gz
  gunzip -c lcov.tar.gz | tar xvf -
  make -C lcov-1.14 install PREFIX=${HOME} BIN_DIR=${HOME}/bin
  gem install coveralls-lcov
fi
