#!/usr/bin/zsh

if [[ ! -d cpputest ]]; then
    git clone git@github.com:cpputest/cpputest
    pushd cpputest
    git checkout 3641e0735c3e521ec138aa7d99ccdddbb471cc6b
    popd
fi
