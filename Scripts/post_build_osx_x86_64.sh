#!/bin/sh

##### log file path for this script #####
LOGFILE=../../script_log.txt
rm -f $LOGFILE

##### original installation of ffmpeg #####
FFMPEG_LIB=../_deps/ffmpeg-build/ffmpeg/x86_64/lib/
echo "FFMPEG_LIB:\t" $FFMPEG_LIB  >> $LOGFILE

##### App bundle name
APP_BUNDLE=FFmpegVideoComponent.app
echo "APP_BUNDLE:\t" $APP_BUNDLE  >> $LOGFILE

##### executable name #####
APP_NAME=FFmpegVideoComponent
echo "APP_NAME:\t" $APP_NAME  >> $LOGFILE

##### Runpath to set #####
RUNPATH=@executable_path/../libs
echo "RUNPATH:\t" $RUNPATH >> $LOGFILE

echo "\n" >> $LOGFILE

##### built products dir #####
BUILT_PRODUCTS_DIR=$1
echo "BUILT_PRODUCTS_DIR:\t" $BUILT_PRODUCTS_DIR >> $LOGFILE

##### lib files to copy #####
LIBS_TO_COPY=('libavcodec*.dylib' 'libavformat*.dylib' 'libavutil*.dylib' 'libswscale*.dylib' 'libswresample*.dylib')

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}
echo "install_name_tool -add_rpath" $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME} >> $LOGFILE
echo "\n" >> $LOGFILE

##### create sub dir in app bundle #####
mkdir ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs/

#### copy libs #####
echo "copy libs..." >> $LOGFILE
for pattern in "${LIBS_TO_COPY[@]}"; do
  for libfile in ${FFMPEG_LIB}${pattern}; do
    echo $(basename "$libfile") >> $LOGFILE
    cp "$libfile" ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs/
    echo "cp $libfile ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs/" >> $LOGFILE
  done
done

echo "\n" >> $LOGFILE
echo "Script done." >> $LOGFILE
