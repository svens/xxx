if test "${TRAVIS_OS_NAME}" = "osx"; then
  brew link gcc || true
fi

if test "${BUILD_TYPE}" = "Coverage"; then
  curl -sLo lcov-master.tar.gz https://github.com/linux-test-project/lcov/archive/master.tar.gz
  gunzip -c lcov-master.tar.gz | tar xvf -
  make -C lcov-master install PREFIX=${HOME} BIN_DIR=${HOME}/bin
  gem install coveralls-lcov
fi
