
//todo: added MACRO functions

#include "readBMP.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
#define Mult9(a) ((a)<<3 + (a))

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


/* Compute min and max of two integers, respectively */
//int min(int a, int b) { return (a < b ? a : b); }
//int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
void initialize_pixel_sum(pixel_sum *sum) {
	sum->red = sum->green = sum->blue = 0;
	//sum->num = 0;
	return;
}

//todo: פונקציה מיותרת
/*
 * assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum, int kernelScale) {

	// divide by kernel's weight
	sum.red = sum.red / kernelScale;
	sum.green = sum.green / kernelScale;
	sum.blue = sum.blue / kernelScale;

	// truncate each pixel's color values to match the range [0,255]
	current_pixel->red = (unsigned char) (min(max(sum.red, 0), 255));
	current_pixel->green = (unsigned char) (min(max(sum.green, 0), 255));
	current_pixel->blue = (unsigned char) (min(max(sum.blue, 0), 255));
	return;
}

/*
* sum_pixels_by_weight - Sums pixel values, scaled by given number
*/
static void sum_pixels_by_weight(pixel_sum *sum, pixel p, int weight) {
	sum->red += ((int) p.red) * weight;
	sum->green += ((int) p.green) * weight;
	sum->blue += ((int) p.blue) * weight;
	//sum->num++;
	return;
}

//todo: פונקציה מיותרת
/*
 *  Applies kernel for pixel at (i,j)
 */
static pixel applyKernel(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

	int ii, jj;
	int currRow, currCol;
	pixel_sum sum;
	pixel current_pixel;

    //todo: פונקציה מיותרת
	//initialize_pixel_sum(&sum);
    //sum.num = 0;
    sum.red = 0;
    sum.blue = 0;
    sum.green = 0;
	//todo: changed i++ to ++i
	for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ++ii) {
        jj = max(j-1, 0);
        int limitIteration = min(j+1, dim-1);
		//pixel* pp = src + (sizeof(pixel) * calcIndex(ii, jj, dim));
		for(; jj <= limitIteration; ++jj) {

			int kRow, kCol;

			// compute row index in kernel
			if (ii < i) {
				kRow = 0;
			} else if (ii > i) {
				kRow = 2;
			} else {
				kRow = 1;
			}

			// compute column index in kernel
			if (jj < j) {
				kCol = 0;
			} else if (jj > j) {
				kCol = 2;
			} else {
				kCol = 1;
			}

			// apply kernel on pixel at [ii,jj]
			//todo: פונקציה מיותרת
			//sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
			pixel p = src[calcIndex(ii, jj, dim)];
            //printf("%x : %x\n", src + (sizeof(pixel) * calcIndex(ii, jj, dim)),pp  );
			//pixel p = *pp;

			//pp += sizeof(pixel);
            int weight = kernel[kRow][kCol];
			sum.red += ((int) p.red) * weight;
			sum.green += ((int) p.green) * weight;
			sum.blue += ((int) p.blue) * weight;
			//sum.num++;
		}
	}

	// assign kernel's result to pixel at [i,j]
	//assign_sum_to_pixel(&current_pixel, sum, kernelScale);

    // divide by kernel's weight
    sum.red = sum.red / kernelScale;
    sum.green = sum.green / kernelScale;
    sum.blue = sum.blue / kernelScale;

    // truncate each pixel's color values to match the range [0,255]
    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
	return current_pixel;
}

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

	for (; i < limit; ++i) {
		j =  1;
        int index = calcIndex(i, j, dim);
		for (; j < limit; ++j) {
			//dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
            //dst[index] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);

            //
            //int ii, jj;
            //int currRow, currCol;
            pixel_sum sum;
            pixel current_pixel;

            //todo: פונקציה מיותרת
            //initialize_pixel_sum(&sum);
            //sum.num = 0;
            sum.red = 0;
            sum.blue = 0;
            sum.green = 0;
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

    int weight = -1;
    int flag9;
    //todo: changed i++ to ++i
    for (; i < limit; ++i) {
        j =  baseJ;
        int index = calcIndex(i, j, dim);
        for (; j < limit; ++j) {
            //dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
            //dst[index] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);

            //
            int ii, jj;
            int currRow, currCol;
            pixel_sum sum;
            pixel current_pixel;

            //todo: פונקציה מיותרת
            //initialize_pixel_sum(&sum);
            //sum.num = 0;
            sum.red = 0;
            sum.blue = 0;
            sum.green = 0;

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
                      ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + 9*((int) p5.red);
            sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                        ((int) p4.green) + ((int) p6.green) +
                        ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + 9*((int) p5.green);
            sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                       ((int) p4.blue) + ((int) p6.blue) +
                       ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + 9*((int) p5.blue);

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
                        ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + 9*((int) p5.red);
            sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                          ((int) p4.green) + ((int) p6.green) +
                          ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + 9*((int) p5.green);
            sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                         ((int) p4.blue) + ((int) p6.blue) +
                         ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + 9*((int) p5.blue);

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

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void blur(int dim, pixel_sum *srcSum, pixel *dst) {
    int i, j;
    i = 1;
    int baseJ = i; // j = kernelSize / 2;
    int limit = dim - 1;
    //int weight = 1;
    //todo: changed i++ to ++i
    for (; i < limit; ++i) {
        j =  baseJ;
        int index = calcIndex(i, j, dim);
        for (; j < limit; ++j) {
            pixel current_pixel;
            pixel_sum sum = srcSum[index];
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
void sharp(int dim, pixel *src, pixel *dst) {
    int i, j;
    i = 1;
    int baseJ = i; // j = kernelSize / 2;
    int limit = dim - 1;

    int weight = -1;
    int flag9;
    //todo: changed i++ to ++i

    //int debug = 1;
    for (; i < limit; ++i) {
        j =  baseJ;
        int index = calcIndex(i, j, dim);
        for (; j < limit; ++j) {
            pixel current_pixel = dst[index];
            pixel blurred = src[index];
            pixel_sum sum;
            sum.red = -(blurred.red*9 - ((int)current_pixel.red)) + ((int)current_pixel.red) * 9;
            sum.green = -(blurred.green*9 - ((int)current_pixel.green)) + ((int)current_pixel.green) * 9;
            sum.blue = -(blurred.blue*9 - ((int)current_pixel.blue)) + ((int)current_pixel.blue )* 9;;

            //printf("%d: %d, %d, %d\n",debug, sum.red, sum.green, sum.blue);
            //debug++;

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

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void pixelsSum(int dim, pixel *src, pixel_sum *dst) {
    int i, j;
    //todo: kernelsize / 2 = 1
    i = 1;
    int baseJ = i; // j = kernelSize / 2;
    int limit = dim - 1;
    for (; i < limit; ++i) {
        j =  baseJ;
        int index = calcIndex(i, j, dim);
        for (; j < limit; ++j) {
            int ii, jj;
            pixel_sum sum;
            sum.red = 0;
            sum.blue = 0;
            sum.green = 0;
            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ++ii) {
                jj = max(j-1, 0);
                int index = calcIndex(ii, jj, dim);
                pixel p1 = src[index];
                pixel p2 = src[index + 1];
                pixel p3 = src[index + 2];
                sum.red += ((int) p1.red) + ((int) p2.red) + ((int) p3.red);
                sum.green += ((int) p1.green) + ((int) p2.green) + ((int) p3.green);
                sum.blue += ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue);
            }
            // truncate each pixel's color values to match the range [0,255]
            dst[index] = sum;
            ++index;
        }
    }
}

void charsToPixels(Image *charsImg, pixel* pixels) {

	int row, col;
	// todo: optimizations here
	//todo: changed i++ to ++i

	for (row = 0 ; row < m ; ++row) {
		int rowN = row*n;
		int rowN3 = 3*rowN;
		for (col = 0 ; col < n ; ++col) {
			int rowNPlusCol = rowN + col;
			int col3 = 3*col;
			int rowN3Pluscol3  = rowN3 + col3;

			char* p = (image->data) + rowN3Pluscol3;

			/*pixels[rowNPlusCol].red = image->data[rowN3Pluscol3];
			pixels[rowNPlusCol].green = image->data[rowN3Pluscol3 + 1];
			pixels[rowNPlusCol].blue = image->data[rowN3Pluscol3 + 2];*/

			pixels[rowNPlusCol].red = *p;
			pixels[rowNPlusCol].green = *(p+1);
			pixels[rowNPlusCol].blue = *(p+2);
		}
	}
}

void pixelsToChars(pixel* pixels, Image *charsImg) {

	//todo: changed i++ to ++i
	int row, col;
	for (row = 0 ; row < m ; ++row) {
		int rowN = row*n;
		int rowN3 = 3*rowN;
		for (col = 0 ; col < n ; ++col) {
			int rowNPlusCol = rowN + col;
			int rowN3PlusCol3 = rowN3 + 3*col;

			char *p = (image->data) + rowN3PlusCol3;
			*p = pixels[rowNPlusCol].red;
			*(p+1) = pixels[rowNPlusCol].green;
			*(p+2) = pixels[rowNPlusCol].blue;
/*			image->data[rowN3PlusCol3] = pixels[rowNPlusCol].red;
			image->data[rowN3PlusCol3 + 1] = pixels[rowNPlusCol].green;
			image->data[rowN3PlusCol3 + 2] = pixels[rowNPlusCol].blue;*/
		}
	}
}

    //todo: פונקציה מיותרת
void copyPixels(pixel* src, pixel* dst) {

	int row, col;
	for (row = 0 ; row < m ; ++row) {
        int rowN = row*n;
        for (col = 0 ; col < n ; ++col) {
            int rowNPlusCol  = rowN + col;
            dst[rowNPlusCol].red = src[rowNPlusCol].red;
			dst[rowNPlusCol].green = src[rowNPlusCol].green;
			dst[rowNPlusCol].blue = src[rowNPlusCol].blue;
		}
	}
}

//todo: פונקציה מיותרת

/*int calcIndex(int i, int j, int n) {
	return ((i)*(n)+(j));
}*/

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