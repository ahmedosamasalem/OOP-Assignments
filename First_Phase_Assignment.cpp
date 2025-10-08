/*
========================================================
 CS213 - Assignment 1 - Part 2
 Team Submission

 Section: S 7&8
 
 Team Members:
 - Ahmed Osama Salem (ID: 20240010): Filters 1(Grayscale), 4(Merge), 7(Darken and Lighten Image), 10(Detect Image Edges), 16(bonus: make the image purple)
 - Kareem Osama Hamed (ID: 20240418): Filters 2(Black and White), 5(Flip Image), 8(Crop Images), 11(Resizing Images), 13(bonus: natural sunlight)
 - Omar Sayed Amin (ID: 20240775): Filters 3(Invert), 6(Rotate), 9(Adding a frame), 12(2 Versions of Blur Image), 17(bonus: Infrared), The menu

 File Description:
 This file contains the implementation of all 12 filters required
 for Part 2 of the assignment in additon to  3 filters from the bonus tasks.
 The program provides a menu for the user to choose a filter and applies it to the input image
 and allows the user to load another image or save the current image at any time through
 the running of the application, It also loops until the user requests to exit the program.
========================================================
*/
#include <bits/stdc++.h>
#include "Image_class.h"
using namespace std;
int working = 1;
Image image1;
string image_name;
bool check_name_exist(string name)
{
    bool file_name;
    bool file_ext = false;
    int dot_place = -1;
    for(int i = name.size() - 1; i >= 0; i--)
    {
        if(name[i] == '.')
        dot_place = i;
    }
    if(dot_place == -1)
    return false;
    string ext;
    for(int i = dot_place + 1; i < name.size(); i++)
    {
        ext += name[i];
    }
    string extentions[5] = {"png","jpg","bmp","tga","jpeg"};
    for(int i = 0; i < 5; i++)
    {
        if(file_ext == true)
            break;
        if(ext == extentions[i])
            file_ext = true;
    }
    bool file_exist = std::filesystem::exists(name);
    return file_ext && file_exist;
}
bool check_name(string name)
{
    bool file_name;
    bool file_ext = false;
    int dot_place = -1;
    for(int i = name.size() - 1; i >= 0; i--)
    {
        if(name[i] == '.')
        dot_place = i;
    }
    if(dot_place == -1)
    return false;
    string ext;
    for(int i = dot_place + 1; i < name.size(); i++)
    {
        ext += name[i];
    }
    string extentions[5] = {"png","jpg","bmp","tga","jpeg"};
    for(int i = 0; i < 5; i++)
    {
        if(file_ext == true)
            break;
        if(ext == extentions[i])
            file_ext = true;
    }
    return file_ext;
}
void load_image()
{
    cout << "Please Enter the image's name: \n";
    cin >> image_name;
    if(!check_name_exist(image_name))
    {
        cout << "Image's name is incorrect or the file doesn't exist, Please try again.\n";
        load_image();
    }
    else
    {
    image1.loadNewImage(image_name);
    cout << "Image loaded succesfully.\n";
    }
}
void first_load()
{
    cout << "Welcome to our image procesing application.\n";
    cout << "Please enter the image's name to load it:\n";
    cin >> image_name;
    if(!check_name_exist(image_name))
    {
        cout << "The image's name is incorrect or the file doesn't exist, Please try again.\n";
        load_image();
    }
    else
    {
    image1.loadNewImage(image_name);
    cout << "Image loaded succesfully.\n";
    }
}

Image resize( Image input_image, int new_Width, int new_Height) 
{
    Image resized_image(new_Width, new_Height); 
    double scaleX = (double)input_image.width / new_Width;
    double scaleY = (double)input_image.height / new_Height;
    for (int y = 0; y < new_Height; y++) 
    {
       for (int x = 0; x < new_Width; x++) 
       {
         int org_width  = x * scaleX;
         int org_height = y * scaleY;

           for (int c = 0; c < 3; c++)
           {
            unsigned char value = input_image.getPixel(org_width, org_height, c);
            resized_image.setPixel(x, y, c, value);
           }
        }
    }
    return resized_image;
}
Image merge( Image img1, Image img2)
{
    Image merged(img1.width, img1.height);
    for (int y = 0; y < img1.height; y++) 
    {
        for (int x = 0; x < img1.width; x++)
         {
            for (int c = 0; c < 3 ; c++)
            {
                unsigned char p1 = img1.getPixel(x, y, c);
                unsigned char p2 = img2.getPixel(x, y, c);
                unsigned char avg = ((p1 + p2) / 2);
                merged.setPixel(x, y, c, avg);
            }
        }
    }
    return merged;
}
void load_images_4merge()
{
    cout << "Choose one of the following: \n";
    cout << "1. Use the already loaded image and load the second one.\n";
    cout << "2. Load 2 new images.\n";
    int op;
    cin >> op;
    string image2_name;
    if(op == 2)
    {
        load_image();
    }
    bool name = false;
    while(name == false)
    {
    cout << "Please Enter the second image's name: \n";
    cin >> image2_name;
    if(!check_name_exist(image2_name))
        cout << "Image's name is incorrect or the file doesn't exist, Please try again.\n";
    else
        name = true;
    }
    Image image2(image2_name);
    cout << "Both images are loaded succesfully.\n";
    if (image1.width != image2.width || image1.height != image2.height) 
    {
        image2 = resize(image2, image1.width, image1.height);
    }
    Image merged = merge(image1, image2);
    image1 = merged;
    cout << "Images merged successfully.\n";
    cout << "If saved as in the same file it will be saved in the first image's file.\n";
}

void infrared_image()
{
    for(int i = 0; i < image1.width; i++)
    {
        for(int j = 0; j < image1.height; j++)
        {
            image1(i,j,0) = 255;
            image1(i,j,1) = 255 - image1(i,j,1);
            image1(i,j,2) = 255 - image1(i,j,2);
        }
    }
    cout << "The image is now infrared.\n";
}
void black_and_white_building(Image image) 
{
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int result = (avg > 128) ? 255 : 0;
            for (int k = 0; k < image.channels; k++) 
            {
                image(i, j, k) = result;
            }
        }
    }
    image1 = image;
    cout << "Image is now black and white.\n";
}
Image Flipped_Horizontaly(Image image) 
{
    Image newimage(image.width, image.height);
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            for (int k = 0; k < image.channels; k++) 
            {
                newimage(i, j, k) = image(image.width - 1 - i, j, k);
            }
        }
    }
    return newimage;
}
Image Flipped_Vertical(Image image) 
{
    Image newimage(image.width, image.height);
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            for (int k = 0; k < image.channels; k++) 
            {
                newimage(i, j, k) = image(i , image.height-1-j , k);
            }
        }
    }
    return newimage;
}
void flip_image()
{
    cout << "Choose one of the following: \n";
    cout << "1. Flip the image vertically. \n";
    cout << "2. Flip the image horizontally. \n";
    int op;
    cin >> op;
    if(op == 1)
    {
        image1 = Flipped_Vertical(image1);
        cout << "Image flipped succesfully.\n";
    }
    else if(op == 2)
    {
        image1 = Flipped_Horizontaly(image1);
        cout << "Image flipped succesfully.\n";
    }
    else
    {
        cout << "Wrong number, Please try again.\n";
        flip_image();
    }
}
void gray_scale()
{
   for ( int i = 0 ; i < image1.width ; i++)
    {
        for ( int j = 0 ; j < image1.height ; j++)
        {
            int avg = image1(i,j,0) ; 
            avg += image1(i,j,1) ; 
            avg += image1(i,j,2) ; 
            avg = avg/3 ;  
            for ( int k = 0 ; k < 3 ; k++)
            {
                image1(i,j,k) = avg ; 
            }
        }
    }
    cout << "Conversion Done Succesfully.\n";
} 
void invert_image()
{
    for(int i = 0; i < image1.width; i++)
    {
        for(int j = 0; j < image1.height; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image1(i,j,k) = 255 - image1(i,j,k);
            }
        }
    }
    cout << "Image colors inverted succesfully.\n";
}
void rotate_image()
{
    cout << "Please choose the rotation amount: \n";
    cout << "1. Rotate the image by 90° clockwise\n";
    cout << "2. Rotate the image by 180° clockwise\n";
    cout << "3. Rotate the image by 270° clockwise\n";
    int op;
    cin >> op;
    while(op--)
    {
        Image image2(image1.height,image1.width);
        for(int i = 0; i < image1.width; i++)
        {
            for(int j = 0; j < image1.height; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    int img2_wdith = image1.height - 1 - j;
                    image2(img2_wdith,i,k) = image1(i,j,k);
                }
            }
        }
    image1 = image2;
    }
    cout << "Image succesfully rotated.\n";
}
void blur_image()
{
    Image image2(image1.width,image1.height);
    vector<vector<vector<long long>>> img(
    3, 
    vector<vector<long long>>(image1.width, vector<long long>(image1.height, 0))
);
    img[0][0][0] = image1(0,0,0);
    img[1][0][0] = image1(0,0,1);
    img[2][0][0] = image1(0,0,2);
    for(int k = 0; k < 3; k++)
    {
    for(int i = 1; i < image1.width; i++)
    {
        img[k][i][0] = img[k][i - 1][0] + image1(i,0,k);
    }
    for(int i = 1; i < image1.height; i++)
    {
        img[k][0][i] = img[k][0][i - 1] + image1(0,i,k);
    }
    for(int i = 1; i < image1.width; i++)
    {
        for(int j = 1; j < image1.height; j++)
        {
            img[k][i][j] = image1(i,j,k) + img[k][i-1][j] + img[k][i][j-1] - img[k][i-1][j-1];
        }
    }
    }
    for(int i = 0; i < image1.width; i++)
    {
        for(int j = 0; j < image1.height; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                int x1 = max(0,i - 25);
                int y1 = max(0,j - 25);
                int x2 = min(image1.width - 1, i + 25);
                int y2 = min(image1.height - 1, j + 25);
                int pixels_num = (x2 - x1 + 1) * (y2 - y1 + 1);
                long long total = img[k][x2][y2];
                if (x1 > 0)
                    total -= img[k][x1-1][y2];
                if (y1 > 0)
                    total -= img[k][x2][y1-1];
                if (x1 > 0 && y1 > 0)
                    total += img[k][x1-1][y1-1];
                image2(i,j,k) = total / pixels_num;
            }
        }
    }
    image1 = image2;
    cout << "Image blurred successfully. \n";
}
void Frame()
{
    cout << "Choose a frame type: \n";
    cout << "1. Simple frame. \n";
    cout << "2. Decorated frame. \n";
    int op;
    cin >> op;
        cout << "choose the color of the frame: \n";
        cout << "1. Red frame. \n";
        cout << "2. Blue frame. \n";
        cout << "3. Black frame. \n";
        cout << "4. Green frame. \n";
        cout << "5. White frame. \n";
        cout << "6. purple frame. \n";
        int color;
        cin >> color;
        int values[3];
        if(color == 1)
        {
            values[0] = 184;
            values[1] = 15;
            values[2] = 10;
        }
        if(color == 2)
        {
            values[0] = 15;
            values[1] = 82;
            values[2] = 186;
        }
        if(color == 3)
        {
            values[0] = 0;
            values[1] = 0;
            values[2] = 0;
        }
        if(color == 4)
        {
            values[0] = 0;
            values[1] = 255;
            values[2] = 0;
        }
        if(color == 5)
        {
            values[0] = 255;
            values[1] = 255;
            values[2] = 255;
        }
        if(color == 6)
        {
            values[0] = 128;
            values[1] = 0;
            values[2] = 128;
        }
        int frame = 100;
        Image image2(image1.width + 2 * frame,image1.height + 2* frame);
        for(int i = 0; i < image2.width; i++)
        {
            
            for(int j = 0; j <image2.height; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                image2(i,j,k) = values[k];
                }
            }
        }
        for(int i = 0;i < image1.width; i++)
        {
            for(int j = 0; j < image1.height; j++)
            {
                for(int k = 0 ; k < 3; k++)
                {
                    image2(i + frame,j + frame,k) = image1(i,j,k);
                }
            }
        }
        image1 = image2;
    if(op == 2)
    {
            int thickness = 5;
            int frame = 100;
            int spacing2 = -50;
            for(int i = frame; i < image1.width - frame; i++)
            {
                for(int j = frame; j < frame + thickness; j++)
                {
                    for(int k = 0; k < 3; k++)
                        image1(i,j,k) = 255;
                }
                for(int j = image1.height - frame; j > image1.height - frame - thickness; j--)
                {
                    for(int k = 0; k < 3; k++)
                        image1(i,j,k) = 255;
                }
            }
            for(int j = frame; j < image1.height - frame; j++)
            {
                for(int i = frame; i < frame + thickness; i++)
                {
                    for(int k = 0; k < 3; k++)
                        image1(i,j,k) = 255;
                }
                for(int i = image1.width - frame; i > image1.width - frame - thickness; i--)
                {
                    for(int k = 0; k < 3; k++)
                        image1(i,j,k) = 255;
                }
            }
            for (int i = frame - spacing2; i < image1.width - frame + spacing2; i++)
            {
                for (int j = frame - spacing2; j < frame - spacing2 + thickness; j++)
                {
                    for (int k = 0; k < 3; k++)
                        image1(i, j, k) = 255;
                }
                for (int j = image1.height - frame + spacing2 - thickness; j < image1.height - frame + spacing2; j++)
                {
                    for (int k = 0; k < 3; k++)
                        image1(i, j, k) = 255;
                }
            }

            for (int j = frame - spacing2; j < image1.height - frame + spacing2; j++)
            {
                for (int i = frame - spacing2; i < frame - spacing2 + thickness; i++)
                {
                    for (int k = 0; k < 3; k++)
                        image1(i, j, k) = 255;
                }
                for (int i = image1.width - frame + spacing2 - thickness; i < image1.width - frame + spacing2; i++)
                {
                    for (int k = 0; k < 3; k++)
                        image1(i, j, k) = 255;
                }
            }
    }
    cout << "Frame added successfully. \n";   
}
Image cropImage(const Image& img, int x, int y, int W, int H) {
    if (W <= 0 || H <= 0 || x < 0 || y < 0 || x + W > img.width || y + H > img.height) {
        cout << "Error ==> invalid crop area." << endl;
        return img;
    }
    Image cropped(W, H);
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            for (int k = 0; k < img.channels; k++) {
                cropped(i, j, k) = img(i + x, j + y, k);
            }
        }
    }
    return cropped;
}
void crop_image() {
    int x, y, W, H;
    cout << "Enter upper left corner (x , y): ";
    cin >> x >> y;
    cout << "Enter the dimensions of the area to cut (W , H): ";
    cin >> W >> H;
    Image cropped = cropImage(image1, x, y, W, H);
    if (cropped.width != image1.width || cropped.height != image1.height) {
        image1 = cropped;
        cout << "Image cropped successfully.\n";
    }
}
Image resizeImage(const Image& input_image, int new_width, int new_height) {
    Image resized_image(new_width, new_height);
    double width_ratio = (double)input_image.width / new_width;
    double height_ratio = (double)input_image.height / new_height;
    for (int j = 0; j < new_height; j++) {
        for (int i = 0; i < new_width; i++) {
            int original_i = i * width_ratio;
            int original_j = j * height_ratio;
            for (int k = 0; k < 3; k++) {
                unsigned char value = input_image.getPixel(original_i, original_j, k);
                resized_image.setPixel(i, j, k, value);
            }
        }
    }
    return resized_image;
}
void resize_image() {
    int new_width, new_height;
    cout << "Enter new width: ";
    cin >> new_width;
    cout << "Enter new height: ";
    cin >> new_height;
    image1 = resizeImage(image1, new_width, new_height);
    cout << "Image resized successfully.\n";
}
Image wanoFilter(const Image& image) {
    Image result(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int R = image(i, j, 0) + 30;
            int G = image(i, j, 1) + 30;
            int B = image(i, j, 2) - 30;
            if (R > 255)
            {
                R = 255;
            }
            if (G > 255)
            {
                G = 255;
            } 
            if (B > 255) 
            {
                B = 255;
            }
            if (B < 0)
            {
                B = 0;
            }
            result(i, j, 0) = R;
            result(i, j, 1) = G;
            result(i, j, 2) = B;
        }
    }
    return result;
}
void wano_filter() {
    image1 = wanoFilter(image1);
    cout << "Wano filter applied successfully.\n";
}
// void blur_image()
// {
//     Image image3(image1.width,image1.height);
//     cout << "choose the intensity of the blur effect ranging from 1 to 10: \n";
//     int z;
//     cin >> z;
//     z = ceil(z/2);
//     while(z--)
//     for(int i = 0; i < image1.width; i++)
//     {
//         for(int j = 0; j < image1.height; j++)
//         {
//                 int values[3] = {0,0,0};
//                 int pixels = 0;

//                 for(int x = i-6; x <= i+6; x++) {
//                     for(int y = j-6; y <= j+6; y++) {
//                         if(x < 0 || y < 0 || x >= image1.width || y >= image1.height) 
//                             continue;
//                         for(int k = 0; k < 3; k++) {
//                             values[k] += image1(x,y,k);
//                         }
//                         pixels++;
//                     }
//                 }

//                 for(int k = 0; k < 3; k++) {
//                     image3(i,j,k) = values[k] / pixels;
//                 }

//         }
//     }
//     image1 = image3;
//     cout << "Image successfully blured. \n";
// }
void save_image()
{
    cout << "Please choose one of the following: \n";
    cout <<"1. Save in the same file.\n";
    cout <<"2. Save in a new file.\n";
    int op;
    cin >> op;
    if(op == 2)
    {
        cout << "Enter the new file's name: \n";
        cin >> image_name;
    }
    if(!check_name(image_name))
    {
        cout << "Wrong extension, please try again\n";
        save_image();
    }
    else
    {
    image1.saveImage(image_name);
    cout << "Image saved succefully.\n";
    }
}
void menu()
{
    int operation = -1;
    while(operation == -1)
    {
    cout << "Please choose an operation from below: \n";
    cout << "1. Load a new image.\n";
    cout << "2. Grayscale Conversion Filter.\n";
    cout << "3. Black and White Filter.\n";
    cout << "4. Invert colors Filter.\n";
    cout << "5. Merge 2 Images.\n";
    cout << "6. Rotate Image.\n";
    cout << "7. Make the image infrared.\n";
    cout << "8. Flip the image vertically or horizontally.\n";
    cout << "9. Blur the image. \n";
    cout << "10. Add a frame.\n";
    cout << "11. Crop Image.\n";
    cout << "12. Resize Image.\n";
    cout << "13. Wano Filter.\n";
    cout << "14. Save image.\n";
    cout << "15. Exit.\n";
    cin >> operation;
    if (operation < 1 || operation > 15)
    {
        cout << "invalid operation number, Please try again.\n";
        operation = -1;
    }
    }
    if(operation == 1)
        load_image();
    if(operation == 2)
        gray_scale();
    if(operation == 3)
        black_and_white_building(image1);
    if(operation == 4)
        invert_image();
    if(operation == 5)
        load_images_4merge();
    if(operation == 6)
        rotate_image();
    if(operation == 7)
        infrared_image();
    if(operation == 8)
        flip_image();
    if(operation == 9)
        blur_image();
    if(operation == 10)
        Frame();
    if(operation == 11)
        crop_image();   
    if(operation == 12)
        resize_image();
    if(operation == 13)
        wano_filter();         
    if(operation == 14)
        save_image();
    if(operation == 15)
        working = 0;
}
int main()
{
    first_load();
    while (working)
    {
        int operation = -1;
        menu();
        if(working == 0)
        {
            cout << "See you soon.";
            break;
        }
    }
    return 0;
}