#!/usr/bin/zsh

function build_cpputest() {
    local build_dir="cpputest_build"
    pushd cpputest
    if [[ ! -d "$build_dir" ]]; then
        mkdir cpputest_build
    fi

    pushd "$build_dir"
    ../configure
    make
    cp -r lib/ ../../target/
    popd
}

build_cpputest
