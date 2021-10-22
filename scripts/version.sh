#!/usr/bin/env bash

cat <<EOT >./firmware/CLK-01/version.h
#ifndef version_h
#define version_h
#define VERSION "$(git rev-parse HEAD)"
#endif
EOT
