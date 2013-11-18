:: ab_usgs.bat
:: ABasin 3.0x4.5 km

set GDAL_CACHEMAX=500

set NED13=ned13.tif
set COLORS=colors1.txt
set DRG=drg.tif
set NAIP=naip.tif

set BASE=ab
set WNES=-projwin 424400 4388800 427400 4384300

set IN=%NED13%
set OUT=%BASE%_ned13.tif
gdal_translate -of GTiff %WNES% %IN% %OUT%
set IN=%OUT%
gdalinfo -stats -mm %IN% > %IN%.txt
gdaldem color-relief %IN% %COLORS% %IN%.color.tif
gdaldem hillshade  %IN%  %IN%.shade.tif
:: hsv_merge.py %IN%.color.tif %IN%.shade.tif foo.tif
:: gdal_translate foo.tif -of PNG %IN%.png
gdal_translate -of XYZ %IN% %IN%.xyz

set IN=%DRG%
set OUT=%BASE%_drg.tif
gdal_translate -of GTiff %WNES% %IN% %OUT%
set IN=%OUT%
gdalinfo -stats -mm %IN% > %IN%.txt

set IN=%NAIP%
set OUT=%BASE%_naip.tif
gdal_translate -of GTiff %WNES% %IN% %OUT%
set IN=%OUT%
gdalinfo -stats -mm %IN% > %IN%.txt

