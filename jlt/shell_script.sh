#!/bin/bash

VERSION=1.2

DEBUG_LOGS=0
VERBOSE=0
CLEANUP=0
DEVICE_NAME=arm9
DEV_DECODER_FILE=~/repos/fw/tools/decode.pl
RELEASES_ROOT=/home/releases
LOG_DECODE=~/bin/log_decode

extract_bin () {
    if [ -f $1 ]; then
        ARCH_FILE=$(realpath $1)
        [ -d "$2" ] && rm -rf $2
        mkdir -p $2 && cd $2
        case "$ARCH_FILE" in
            *.tar.bz2)   tar xjf "$ARCH_FILE"     ;;
            *.tar.gz)    tar xzf "$ARCH_FILE"     ;;
            *.tar.xz)    tar xJf "$ARCH_FILE"     ;;
            *.bz2)       bunzip2 "$ARCH_FILE"     ;;
            *.rar)       unrar e "$ARCH_FILE"     ;;
            *.gz)        gunzip "$ARCH_FILE"      ;;
            *.tar)       tar xf "$ARCH_FILE"      ;;
            *.tbz2)      tar xjf "$ARCH_FILE"     ;;
            *.tgz)       tar xzf "$ARCH_FILE"     ;;
            *.zip)       unzip "$ARCH_FILE"       ;;
            *)           echo "'$ARCH_FILE' cannot be extracted by $SCRIPTNAME" ;;
        esac
        cd - > /dev/null 2>&1
    fi
}

goto_exit() {
    if [ $CLEANUP -eq 1 ] ; then
        rm -rf $HOME/temp_bin
    fi
    exit $1
}

help_usage() {
    echo "Advance decoder script v$VERSION"
    echo ""
    echo "Usage: shell_script [-V] <release_num>|<build>|local [-v] [-debug] [-dev] [-device <device_name>]
    [-sym <symbol_file>] -o <out_file> <log_file>"
    echo "  -V: see the version number and changelist"
    echo "  <release_num>: release number"
    echo "      or <build> directory or archive file or 'local' for no build"
    echo "      for 'local' option, the symbol file needs to be supplied"
    echo "  -debug: use in debug mode, note: this does not perform the conversion"
    echo "  -v: Verbose output"
    echo "  -dev: use dev version of decode.pl"
    echo "      Note: using local build makes this default, thus not needed"
    echo "  -device <device_name>: Default device is arm9. If a different device is to be used, this"
    echo "      can be supplied using -device option"
    echo "  -sym <symbol_file>: The symbol file is derived from the release. This option should be"
    echo "      used in case of no release ('local') or to force use another symbol file than the release"
    echo "  -o <out_file>: output filename. Defaults to <log_file>_decoded[_<ran_num>].txt"
    echo "  <log_file>: path to log file to be decoded"
    echo ""
    echo "  Example:"
    echo "      decode based on release number:"
    echo "              shell_script 2508 log.txt"
    echo "      use release symbol files, but dev decoder:"
    echo "              shell_script 2508 -dev log.txt"
    echo "      use local build:"
    echo "              shell_script ~/repos/fw/builds log.txt"
    echo "      use local archive:"
    echo "              shell_script build.tar.xz log.txt"
    echo "      no release:"
    echo "              shell_script local -sym symbols.dbg log.txt"
}

print_version() {
    echo "Advanced decoder script v$VERSION"
    echo ""
    echo "Changelist:"
    echo "* Version 1.2 =>"
    echo "      + Fix for date appended output file name"
    echo "      + More modularization"
    echo "* Version 1.1 =>"
    echo "      + Fixed issues if local and no symbol file"
    echo "      + Added support for local build directory/archive file too"
    echo "      + Refactored the code a bit and made it modular"
    echo "* Version 1.0 =>"
    echo "      + Initial version"
    echo ""
}

# If no arguments are passed, print usage and quit
parse_args() {
    if [ $# -le 0 ] ; then
        help_usage
        goto_exit 0
    fi

    # Parse all the args

    # The first arg should always tell us about the release
    if [ $1 -ge 0 2>/dev/null ] ; then
        RELEASE_NUM=$1
    elif [ $1 == "-V" ] ; then
        print_version
        goto_exit 1
    else
        BINARY_LOCATION=$1
    fi

    # Shift the args
    shift

    while [ $# -gt 0 ]; do
        if [ "$1" == "-device" ] ; then
            shift
            DEVICE_NAME=$1
        elif [ "$1" == "-dev" ] ; then
            DECODER_FILE=$DEV_DECODER_FILE
        elif [ "$1" == "-debug" ] ; then
            DEBUG_LOGS=1
        elif [ "$1" == "-v" ] ; then
            VERBOSE=1
        elif [ "$1" == "-sym" ] ; then
            shift
            SYMBOL_FILE=$1
        elif [ "$1" == "-o" ] ; then
            shift
            OUT_FILE=$1
        else
            LOG_FILE=$1
        fi
        shift
    done
}

# Find the release directory
get_release_dir() {
    if [ ! -z "$RELEASE_NUM" ] ; then
        RELEASE_ROOT=$RELEASES_ROOT
        RELEASE_DIR=$(find $RELEASE_ROOT -maxdepth 1 -type d -name $RELEASE_NUM\*)
    elif [ "$BINARY_LOCATION" == "local" ] ; then
        DECODER_FILE=$DEV_DECODER_FILE
        if [ ! -e "$SYMBOL_FILE" ] ; then
            SYMBOL_FILE=symbols.dbg
            if [ ! -e "$SYMBOL_FILE" ] ; then
                echo "PANIC: no symbol file detected"
                goto_exit 1
            fi
        fi
    elif [ ! -z "$BINARY_LOCATION" ] ; then
        # Check if the binary is a directory or an archive file
        bin_attr="$(file $BINARY_LOCATION)"
        if [[ ${bin_attr#*: } == 'directory' ]] ; then
            RELEASE_DIR=$BINARY_LOCATION
        else
            RELEASE_DIR=$HOME/temp_bin
            extract_bin $BINARY_LOCATION $RELEASE_DIR
            CLEANUP=1
        fi
    fi

    # If not the dev decoder file, fetch the file from release directory
    if [ -z "$DECODER_FILE" ] ; then
        DECODER_FILE=$RELEASE_DIR/decode/decode.pl
    fi

    # Find the device directory and based on that the symbol file
    if [ -z "$SYMBOL_FILE" ] ; then
        DEV_DIR=$(find $RELEASE_DIR/ -maxdepth 1 -type d -name $DEVICE_NAME*)
        SYMBOL_FILE=$DEV_DIR/debug/symbols.dbg
    fi
}

# Check if the input file is a binary, decode it to text
decode_input_file() {
    file_attr="$(file --mime $LOG_FILE)"
    if [[ ${file_attr#*=} == 'binary' ]]; then
        if [ ! -e $LOG_DECODE ]; then
            echo "PANIC: no ~/bin/log_decode to decode binary log $LOG_FILE"
            goto_exit 1
        fi
        [ $VERBOSE -eq 1 ] && echo "$LOG_DECODE $LOG_FILE > ${LOG_FILE%.*}_decoded.${LOG_FILE##*.}"
        [ $VERBOSE -eq 1 ] && echo ""
        $LOG_DECODE $LOG_FILE > ${LOG_FILE%.*}_decoded.txt
        LOG_FILE=${LOG_FILE%.*}_decoded.txt
    fi
}

# Derive the output filename
derive_out_file() {
    if [ -z "$OUT_FILE" ] ; then
        TEMP_FILE=${LOG_FILE%.*}_decoded.${LOG_FILE##*.}
        while [ -e "$TEMP_FILE" ] ; do
            TEMP_FILE=${TEMP_FILE%.*}_"`date +%d%m%y_%k%M%S`".${LOG_FILE##*.}
        done
        OUT_FILE=$TEMP_FILE
    fi
}

decode() {
    # Make sure we have all the files we need
    if [ ! -e "$DECODER_FILE" ]; then
        echo "PANIC: Decoder file $DECODER_FILE does not exist"
        goto_exit 1
    fi

    if [ ! -e "$SYMBOL_FILE" ]; then
        echo "PANIC: Symbol file $SYMBOL_FILE does not exist"
        goto_exit 1
    fi

    if [ -z "$LOG_FILE" ] || [ ! -e "$LOG_FILE" ]; then
        echo "PANIC: Missing log file"
        goto_exit 1
    fi

    if [ $DEBUG_LOGS -eq 1 ] ; then
        [ ! -z "$RELEASE_ROOT" ] && echo "RELEASE_ROOT  = $RELEASE_ROOT"
        [ ! -z "$RELEASE_NUM" ] && echo "RELEASE_NUM   = $RELEASE_NUM"
        [ ! -z "$RELEASE_NAME" ] && echo "RELEASE_NAME  = $RELEASE_NAME"
        [ ! -z "$RELEASE_DIR" ] && echo "RELEASE_DIR   = $RELEASE_DIR"
        [ ! -z "$DEV_DIR" ] && echo "DEV_DIR       = $DEV_DIR"
        [ ! -z "$SYMBOL_FILE" ] && echo "SYMBOL_FILE   = $SYMBOL_FILE"
        [ ! -z "$DECODER_FILE" ] && echo "DECODER_FILE  = $DECODER_FILE"
        [ ! -z "$LOG_FILE" ] && echo "LOG_FILE      = $LOG_FILE"
        [ ! -z "$OUT_FILE" ] && echo "OUT_FILE      = $OUT_FILE"
    else
        [ $VERBOSE -eq 1 ] && echo "cat $LOG_FILE | $DECODER_FILE --nocolor --fw_dbg_file=$SYMBOL_FILE > $OUT_FILE"
        [ $VERBOSE -eq 1 ] && echo ""
        cat $LOG_FILE | $DECODER_FILE --nocolor --fw_dbg_file=$SYMBOL_FILE > $OUT_FILE
        ret=$?
        if [ $ret != 0 ] ; then
            goto_exit $ret
        fi
        echo ""
        echo "Decoded into $OUT_FILE"
    fi
}

#### Script start
parse_args "$@"

get_release_dir

decode_input_file

derive_out_file

decode

goto_exit 0
#### Script end
