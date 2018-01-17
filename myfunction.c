
//todo: added MACRO functions

#include "readBMP.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
#define Mult9(a) (((a) << 3) + (a))

typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
	//todo : remove anything connetected to num
    //int num;
} pixel_sum;

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void blurImg(int dim, pixel *src, pixel *dst) {
	//todo: optimizations here
	int i, j;
	i = 1;
	//int baseJ = i; // j = kernelSize / 2;
	int limit = dim - 1;
    //int weight = 1;
    //todo: changed i++ to ++i
    //todo: out of the loop
    pixel_sum sum;
    pixel current_pixel;
    for (; i < limit; ++i) {
		j =  1;
        int index = calcIndex(i, j, dim);
		for (; j < limit; ++j) {
			//dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
            //dst[index] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);

            //
            //int ii, jj;
            //int currRow, currCol;

            //todo: פונקציה מיותרת
            //initialize_pixel_sum(&sum);
/*            //sum.num = 0;
            sum.red = 0;
            sum.blue = 0;
            sum.green = 0;*/
            //todo: changed i++ to ++i

            //ii = max(i-1, 0);
            //jj = max(j-1, 0);
            //ii = i - 1;
           // jj = j - 1;
            register int index1 = calcIndex(i-1, j - 1, dim);
            pixel p1 = src[index1];
            pixel p2 = src[index1 + 1];
            pixel p3 = src[index1 + 2];
            pixel p4 = src[index1 + dim];
            pixel p5 = src[index1 + dim + 1];
            pixel p6 = src[index1 + dim + 2];
            pixel p7 = src[index1 + dim + dim];
            pixel p8 = src[index1 + dim + dim + 1];
            pixel p9 = src[index1 + dim + dim + 2];

            sum.red = ((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                    ((int) p4.red) + ((int) p5.red) + ((int) p6.red) +
                    ((int) p7.red) + ((int) p8.red) + ((int) p9.red);
            sum.green = ((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                    ((int) p4.green) + ((int) p5.green) + ((int) p6.green) +
                    ((int) p7.green) + ((int) p8.green) + ((int) p9.green);
            sum.blue = ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                    ((int) p4.blue) + ((int) p5.blue) + ((int) p6.blue) +
                    ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue);
            //sum.num += 3;

            // assign kernel's result to pixel at [i,j]
            //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
            // divide by kernel's weight
            sum.red = sum.red / 9;
            sum.green = sum.green / 9;
            sum.blue = sum.blue / 9;

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(sum.red, 255));
            current_pixel.green = (unsigned char) (min(sum.green, 255));
            current_pixel.blue = (unsigned char) (min(sum.blue, 255));
            //

            dst[index] = current_pixel;
            ++index;


            ++j;
            index1 = calcIndex(i-1, j - 1, dim);
            p1 = src[index1];
            p2 = src[index1 + 1];
            p3 = src[index1 + 2];
            p4 = src[index1 + dim];
            p5 = src[index1 + dim + 1];
            p6 = src[index1 + dim + 2];
            p7 = src[index1 + dim + dim];
            p8 = src[index1 + dim + dim + 1];
            p9 = src[index1 + dim + dim + 2];

            sum.red = ((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                      ((int) p4.red) + ((int) p5.red) + ((int) p6.red) +
                      ((int) p7.red) + ((int) p8.red) + ((int) p9.red);
            sum.green = ((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                        ((int) p4.green) + ((int) p5.green) + ((int) p6.green) +
                        ((int) p7.green) + ((int) p8.green) + ((int) p9.green);
            sum.blue = ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                       ((int) p4.blue) + ((int) p5.blue) + ((int) p6.blue) +
                       ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue);
            //sum.num += 3;

            // assign kernel's result to pixel at [i,j]
            //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
            // divide by kernel's weight
            sum.red = sum.red / 9;
            sum.green = sum.green / 9;
            sum.blue = sum.blue / 9;

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(sum.red, 255));
            current_pixel.green = (unsigned char) (min(sum.green, 255));
            current_pixel.blue = (unsigned char) (min(sum.blue, 255));
            //

            dst[index] = current_pixel;
            ++index;
		}
	}
}

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void sharpImg(int dim, pixel *src, pixel *dst) {
    //todo: optimizations here
    int i, j;
    i = 1;
    int baseJ = i; // j = kernelSize / 2;
    int limit = dim - 1;
    //todo: changed i++ to ++i

    //todo: out of the loop
    pixel_sum sum;
    pixel current_pixel;
    for (; i < limit; ++i) {
        j =  baseJ;
        int index = calcIndex(i, j, dim);
        for (; j < limit; ++j) {
            //dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
            //dst[index] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);

            //
            int ii, jj;

            //todo: פונקציה מיותרת
            //initialize_pixel_sum(&sum);
            //sum.num = 0;
/*            sum.red = 0;
            sum.blue = 0;
            sum.green = 0;*/

            //todo: changed i++ to ++i
            //ii = max(i-1, 0);
            //jj = max(j-1, 0);
            ii = i - 1;
            jj = j - 1;
            register int index1 = calcIndex(ii, jj, dim);
            pixel p1 = src[index1];
            pixel p2 = src[index1 + 1];
            pixel p3 = src[index1 + 2];
            pixel p4 = src[index1 + dim];
            pixel p5 = src[index1 + dim + 1];
            pixel p6 = src[index1 + dim + 2];
            pixel p7 = src[index1 + dim + dim];
            pixel p8 = src[index1 + dim + dim + 1];
            pixel p9 = src[index1 + dim + dim + 2];

            sum.red = -(((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                      ((int) p4.red) +  ((int) p6.red) +
                      ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + Mult9(((int) p5.red));
            sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                        ((int) p4.green) + ((int) p6.green) +
                        ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + Mult9(((int) p5.green));
            sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                       ((int) p4.blue) + ((int) p6.blue) +
                       ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + Mult9(((int) p5.blue));

            // assign kernel's result to pixel at [i,j]
            //assign_sum_to_pixel(&current_pixel, sum, kernelScale);

            // todo: מיותר מכיוון ש סקייל = 1
/*            // divide by kernel's weight
            sum.red = sum.red / kernelScale;
            sum.green = sum.green / kernelScale;
            sum.blue = sum.blue / kernelScale;*/

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            //

            dst[index] = current_pixel;
            ++index;

            ++j;
            index1 = calcIndex(i-1, j - 1, dim);
            p1 = src[index1];
            p2 = src[index1 + 1];
            p3 = src[index1 + 2];
            p4 = src[index1 + dim];
            p5 = src[index1 + dim + 1];
            p6 = src[index1 + dim + 2];
            p7 = src[index1 + dim + dim];
            p8 = src[index1 + dim + dim + 1];
            p9 = src[index1 + dim + dim + 2];

            sum.red = -(((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                        ((int) p4.red) +  ((int) p6.red) +
                        ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + Mult9(((int) p5.red));
            sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                          ((int) p4.green) + ((int) p6.green) +
                          ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + Mult9(((int) p5.green));
            sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                         ((int) p4.blue) + ((int) p6.blue) +
                         ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + Mult9(((int) p5.blue));

            // assign kernel's result to pixel at [i,j]
            //assign_sum_to_pixel(&current_pixel, sum, kernelScale);

            // todo: מיותר מכיוון ש סקייל = 1
/*            // divide by kernel's weight
            sum.red = sum.red / kernelScale;
            sum.green = sum.green / kernelScale;
            sum.blue = sum.blue / kernelScale;*/

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            //

            dst[index] = current_pixel;
            ++index;
        }
    }

}

void doConvolution(Image *image, int kernelScale) {

    int size = m*n;
    int tripleSize = size + size + size;
    //pixel* pixelsImg = malloc(m*n*sizeof(pixel));
    pixel* backupOrg = malloc(tripleSize);

    //charsToPixels(image, pixelsImg);
    pixel* pixelsImg = (pixel*) image->data;
    //for ()

    //Took advice from Liz Aharonian that memcpy was more efficient in running time than copyPixels
    memcpy(backupOrg, pixelsImg, tripleSize);

    //copyPixels(pixelsImg, backupOrg);
    if (kernelScale == 9) {
        blurImg(m, backupOrg, pixelsImg);
    } else {
        sharpImg(m, backupOrg, pixelsImg);

    }

    //pixelsToChars(pixelsImg, image);

    //free(pixelsImg);
    free(backupOrg);
}





void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName) {

    /*
    * [1, 1, 1]
    * [1, 1, 1]
    * [1, 1, 1]
    */
    //int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    /*
    * [-1, -1, -1]
    * [-1, 9, -1]
    * [-1, -1, -1]
    */
    //int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

    // blur image
    doConvolution(image, 9);

    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);

    //smooth(m, backupOrg, pixelsImg, kernelSize, sharpKernel, 1);

    // sharpen the resulting image
    doConvolution(image, 1);

    // write result image to file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}