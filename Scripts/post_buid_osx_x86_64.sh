#!/bin/sh

##### log file path for this script #####
LOGFILE=../../script_log.txt
rm $LOGFILE

##### Use pkg-config to find FFmpeg library path #####
FFMPEG_LIB=$(pkg-config --variable=libdir libavcodec)
echo "FFMPEG_LIB:\t" $FFMPEG_LIB  >> $LOGFILE

##### App bundle name
APP_BUNDLE=FFmpegVideoComponent.app

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### lib files to copy #####
LIBS_TO_COPY=$(pkg-config --libs libavcodec libavformat libavutil libswscale libswresample | xargs -n1 | grep -E '\.dylib$' | xargs -n1 basename)

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}