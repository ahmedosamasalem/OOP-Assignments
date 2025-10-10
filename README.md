# OOP-Assignments
 Program breakdown: 
Filter List (1–15)
1.	Grayscale conversion filter
Description: Converts the image to be consisting only of shades of gray from white to black depending on the intensity of the values of each pixel as a bright pixel will lean towards white and a dark pixel will lean towards black.
Created by: Ahmed Osama Salem (20240010)
2.	Black and white filter
Description: Similar to the Grayscale filter, the black and white filter changes all the colors of the image to be either white or black depending on the brightness of the pixel a dark pixel will be black, and a light one will be white with no shades of gray in between.
Created by: Kareem Osama Hamed (20240418)
3.	Invert image filter
Description: This filter transforms the colors of each pixel by reversing each pixel's RGB values so a black pixel will be white, a red pixel will become a mix of green and blue, by applying this method to each pixel in the image we get a new image that is inverted in colors.
Created by: Omar Sayed Amin (20240775)
4.	Merge images filter
Description: When applying this filter we first use the resize function if the two image doesn't have same dimensions, this function change the size of an image to a new width and new height , it calculate scaleX and scaleY which is every pixel in new image finds the corresponding pixel in the original image by using these scales and copies the color RGB from the original image to the new image this gives a resized image .
Then we use merge function which combines two images of the same size into 1 image by applying the formula (Pixel 1 + Pixel 2)/2 which creates a merged image.
Created by: Ahmed Osama Salem (20240010)
5.	Flip image filter
Description: This filter gives the user a choice either to flip the image vertically or to flip it horizontally then gives the user the final image as requested.
Created by: Kareem Osama Hamed (20240418)
6.	Rotate image filter
Description: This filter rotates the image by placing the pixels of every row in the original image to the last column in the  new image and by doing this operation to every row we get a new image that is rotated by 90 degrees and by the user’s choice wither to do a 90,180,270 degree rotation we do this operation an amount of times to get to the desired degree of rotation.
Created by: Omar Sayed Amin (20240775)
7.	Darken and lighten image filter
Description: This filter allows the user to choose 1(lighten) or 2(darken) , if user choose 1 so the function of lighten run and this function increases the brightness of each pixel of RGB by (1 + 0.6) that is making  image 60% more brighter if user choose 2 so the function darken run and this function decrease the brightness of each pixel of RGB by 60%
Created by: Ahmed Osama Salem (20240010)
8.	Crop Image 
Description: Crop Image simply crop a portion of the image based on the coordinates and dimensions entered by the user. We make sure, of course, that the dimensions are greater than zero, that the coordinates are square, and that the area to be cropped is no larger than the borders of the original image. We crop by ensuring that every pixel in the new image has the same path as the original image, but with a shift in the coordinates.
Created by: Kareem Osama Hamed (20240418)
9.	Add a frame to the image
Description: This filter adds a frame to the image by increasing the width and height of the image and filling the new area with a color determined by the user then if the user chooses the program will add 2 decorative lines to the frame.
Created by: Omar Sayed Amin (20240775)
10.	Detect image edges
Description: this filter is used in detecting and highlighting the edges in an image, first it converts the image to black and white to maintain detection process, then detect edges by using pixels it compare its brightness with the right pixel and down pixel, if the neighbor pixels are different it means there is a change in brightness so it indicates that there is an edge in this pixel so this pixel colored black otherwise the pixel turns to white.
Therefore, the result image is white with black edges.
Created by: Ahmed Osama Salem (20240010)
11.	Resizing image filter
Description: uses the resize function introduced in the merge filter.
Created by: Kareem Osama Hamed (20240418)
12.	Blur image filter
Description: this filter makes the image lose details and become blurry by making each pixel the average of a square of surrounding pixels.
Created by: Omar Sayed Amin (20240775)
13.	Wando’s natural sunlight
Description: makes the image sunny, so  wants to make the revolution have a yellow color by increasing the red and green colors, which will produce a yellow color, and reducing the blue color so that it has a bright or warm appearance, meaning adjusting the color balance in the image, and I make sure, of course, when I increase the red and green that they do not exceed 255 and the blue does not fall below 0 so that the colors are clear from 0 to 255.
Created by: Kareem Osama Hamed (20240418)
14.	Wando is purple at night
Description: this filter apply a purple color on image it looks on every pixel in the image using two nested loops for width and height , then for each pixel it increases the R and B by 20 and decrease G by 20 that is gives in the final image a purpled image .
Created by: Ahmed Osama Salem (20240010)
15.	Infrared Photography
Description: This filter changes the colors of the image to be like an infrared image; the filter does this by setting the value of the red color to 255 and inversing the values of the blue and green by subtracting the value of each color from 255 and setting it.
Created by: Omar Sayed Amin (20240775)

