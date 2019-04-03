/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> pixelColor;
   	map <Point<3>, TileImage*> tileMap;
    for(int i = 0; i<(int)theTiles.size(); i++){
  		LUVAPixel avgColor = theTiles[i].getAverageColor();
  		Point<3> tmp(avgColor.l, avgColor.u, avgColor.v);
  		pixelColor.push_back(tmp);
  		tileMap[tmp] = &theTiles[i];
  	}
    KDTree<3> sourceTree(pixelColor);

    int row = theSource.getRows();
    int col = theSource.getColumns();

    MosaicCanvas* output = new MosaicCanvas(row, col);

    for(int r=0; r<row; r++){
      for(int c=0; c<col; c++){
        LUVAPixel pixel = theSource.getRegionColor(r, c);
        Point<3> point(pixel.l,pixel.u,pixel.v);
        Point<3> index = sourceTree.findNearestNeighbor(point);

        TileImage *tmp= tileMap[index];
        output->setTile(r,c, tmp);
      }
    }

    return output;
}
