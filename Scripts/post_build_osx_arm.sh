#!/bin/sh

##### log file path for this script #####
LOGFILE=../../script_log.txt
rm $LOGFILE

##### original installation of ffmpeg #####
FFMPEG_LIB=../../ffmpeg/osx_arm/lib/
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

##### lib files to copy #####
LIBS=('libavformat.59.dylib' 'libavcodec.59.dylib' 'libswscale.6.dylib' 'libavutil.57.dylib' 'libswresample.4.dylib')

##### add rpath to executable #####
echo "adding rpath..." >> $LOGFILE
install_name_tool -add_rpath $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}
echo "install_name_tool -add_rpath" $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME} >> $LOGFILE
echo "\n" >> $LOGFILE

##### create sub dir in app bundle #####
mkdir ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs/

#### copy libs #####
echo "copy libs..." >> $LOGFILE
for lib in "${LIBS[@]}"; do
  echo $lib >> $LOGFILE
  # copy lib file to sub dir
  cp ${FFMPEG_LIB}$lib ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs
  echo "cp" ${FFMPEG_LIB}$lib ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/libs >> $LOGFILE
  
  # change rpath for lib file
  # this is probably not necessary anymore
  #install_name_tool -change ${FFMPEG_LIB}$lib $RUNPATH ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}
  #install_name_tool -change ${FFMPEG_LIB}$lib @rpath/${lib} ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME}
  #echo "install_name_tool -change" ${FFMPEG_LIB}$lib @rpath/${lib} ${BUILT_PRODUCTS_DIR}/${APP_BUNDLE}/Contents/MacOS/${APP_NAME} >> $LOGFILE
  #echo $lib
done

echo "\n" >> $LOGFILE
echo "Script done." >> $LOGFILE
