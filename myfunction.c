
//todo: added MACRO functions

#include "readBMP.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))

typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;


/* Compute min and max of two integers, respectively */
//int min(int a, int b) { return (a < b ? a : b); }
//int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
void initialize_pixel_sum(pixel_sum *sum) {
	sum->red = sum->green = sum->blue = 0;
	sum->num = 0;
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
	sum->num++;
	return;
}

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
    sum.num = 0;
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
			sum.num++;
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
void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {
	//todo: optimizations here
	int i, j;
	i = kernelSize / 2;
	int baseJ = i; // j = kernelSize / 2;
	int limit = dim - kernelSize / 2;
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
            sum.num = 0;
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
                    sum.num++;
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
            //

            dst[index] = current_pixel;
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

void doConvolution(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

	//pixel* pixelsImg = malloc(m*n*sizeof(pixel));
	pixel* backupOrg = malloc(m*n*3);

	//charsToPixels(image, pixelsImg);
    pixel* pixelsImg = (pixel*) image->data;
    //for ()

    //Took advice from Liz Aharonian that memcpy was more efficient in running time than copyPixels
    memcpy(backupOrg, pixelsImg, m*n*3);

	//copyPixels(pixelsImg, backupOrg);

	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);

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
	int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	/*
	* [-1, -1, -1]
	* [-1, 9, -1]
	* [-1, -1, -1]
	*/
	int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

	// blur image
	doConvolution(image, 3, blurKernel, 9);

	// write result image to file
	writeBMP(image, srcImgpName, blurRsltImgName);

	//smooth(m, backupOrg, pixelsImg, kernelSize, sharpKernel, 1);

	// sharpen the resulting image
	doConvolution(image, 3, sharpKernel, 1);

	// write result image to file
	writeBMP(image, srcImgpName, sharpRsltImgName);
}
