#include "helpers.h"
#include<math.h>
#include<stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
      // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        average = 0;
        for (int j = 0; j < width; j++)
        {
           average = (image[i][j].rgbtBlue +image[i][j].rgbtGreen +image[i][j].rgbtRed )/3;
           image[i][j].rgbtBlue = average;
           image[i][j].rgbtGreen = average;
           image[i][j].rgbtRed = average;
            // Update pixel values
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originImage[height][width] ;
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           originImage[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
           originImage[i][j].rgbtGreen =  image[i][width-j].rgbtGreen;
           originImage[i][j].rgbtRed =  image[i][width-j].rgbtRed;
            // Update pixel values
        }
    }
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           image[i][j].rgbtBlue = originImage[i][j].rgbtBlue;
           image[i][j].rgbtGreen =  originImage[i][j].rgbtGreen;
           image[i][j].rgbtRed =  originImage[i][j].rgbtRed;
            // Update pixel values
        }
    }
    // image = originImage;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int blur_box[9] = {1,1,1,1,1,1,1,1,1};
    RGBTRIPLE pixel ;
     RGBTRIPLE originImage[height][width] ;
      for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           originImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
           originImage[i][j].rgbtGreen =  image[i][j].rgbtGreen;
           originImage[i][j].rgbtRed =  image[i][j].rgbtRed;
            // Update pixel values
        }
    }
    
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           if (i!=0 &&j!=0 &&i!=height-1 &&j!=width-1  )
         {

            getKernalProduct(i,j,height,width,originImage,&pixel,blur_box);
            image[i][j].rgbtBlue = (pixel.rgbtBlue);
            image[i][j].rgbtGreen = (pixel.rgbtGreen);
            image[i][j].rgbtRed = (pixel.rgbtRed);

         }else
         {
             image[i][j].rgbtBlue = 0;
            image[i][j].rgbtGreen = 0;
            image[i][j].rgbtRed = 0;
         }
         
           
           
        }
    }
   
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
       grayscale(height,width,image);
    int rx,bx,gx,ry,by,gy = 0;
    int x_gradient[9] = {1,0,1,-2,0,2,-1,0,1};
    int y_gradient[9] = {-1,2,-1,0,0,0,1,2,1};
     RGBTRIPLE originImage[height][width] ;
      for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           originImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
           originImage[i][j].rgbtGreen =  image[i][j].rgbtGreen;
           originImage[i][j].rgbtRed =  image[i][j].rgbtRed;
            // Update pixel values
        }
    }
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           if (i!=0 &&j!=0 &&i!=height-1 &&j!=width-1  )
         {
            int b_box[9] = {originImage[i-1][j-1].rgbtBlue,originImage[i-1][j].rgbtBlue,originImage[i-1][j+1].rgbtBlue,
                        originImage[i][j-1].rgbtBlue,originImage[i][j].rgbtBlue,originImage[i][j+1].rgbtBlue,
                        originImage[i+1][j-1].rgbtBlue,originImage[i+1][j].rgbtBlue,originImage[i+1][j+1].rgbtBlue
                        };
            int g_box[9] = {originImage[i-1][j-1].rgbtGreen,originImage[i-1][j].rgbtGreen,originImage[i-1][j+1].rgbtGreen,
                        originImage[i][j-1].rgbtGreen,originImage[i][j].rgbtGreen,originImage[i][j+1].rgbtGreen,
                        originImage[i+1][j-1].rgbtGreen,originImage[i+1][j].rgbtGreen,originImage[i+1][j+1].rgbtGreen
                        };
            int r_box[9] = {originImage[i-1][j-1].rgbtRed,originImage[i-1][j].rgbtRed,originImage[i-1][j+1].rgbtRed,
                        originImage[i][j-1].rgbtRed,originImage[i][j].rgbtRed,originImage[i][j+1].rgbtRed,
                        originImage[i+1][j-1].rgbtRed,originImage[i+1][j].rgbtRed,originImage[i+1][j+1].rgbtRed
                        };


            bx = ((x_gradient[0]*b_box[0])+(x_gradient[1]*b_box[1])+(x_gradient[2]*b_box[2])+(x_gradient[3]*b_box[3])+(x_gradient[4]*b_box[4])+(x_gradient[5]*b_box[5])+(x_gradient[6]*b_box[6])+(x_gradient[7]*b_box[7])+(x_gradient[8]*b_box[8]));
            gx = ((x_gradient[0]*g_box[0])+(x_gradient[1]*g_box[1])+(x_gradient[2]*g_box[2])+(x_gradient[3]*g_box[3])+(x_gradient[4]*g_box[4])+(x_gradient[5]*g_box[5])+(x_gradient[6]*g_box[6])+(x_gradient[7]*g_box[7])+(x_gradient[8]*g_box[8]));
            rx = ((x_gradient[0]*r_box[0])+(x_gradient[1]*r_box[1])+(x_gradient[2]*r_box[2])+(x_gradient[3]*r_box[3])+(x_gradient[4]*r_box[4])+(x_gradient[5]*r_box[5])+(x_gradient[6]*r_box[6])+(x_gradient[7]*r_box[7])+(x_gradient[8]*r_box[8]));
            by = ((y_gradient[0]*b_box[0])+(y_gradient[1]*b_box[1])+(y_gradient[2]*b_box[2])+(y_gradient[3]*b_box[3])+(y_gradient[4]*b_box[4])+(y_gradient[5]*b_box[5])+(y_gradient[6]*b_box[6])+(y_gradient[7]*b_box[7])+(y_gradient[8]*b_box[8]));
            gy = ((y_gradient[0]*g_box[0])+(y_gradient[1]*g_box[1])+(y_gradient[2]*g_box[2])+(y_gradient[3]*g_box[3])+(y_gradient[4]*g_box[4])+(y_gradient[5]*g_box[5])+(y_gradient[6]*g_box[6])+(y_gradient[7]*g_box[7])+(y_gradient[8]*g_box[8]));
            ry = ((y_gradient[0]*r_box[0])+(y_gradient[1]*r_box[1])+(y_gradient[2]*r_box[2])+(y_gradient[3]*r_box[3])+(y_gradient[4]*r_box[4])+(y_gradient[5]*r_box[5])+(y_gradient[6]*r_box[6])+(y_gradient[7]*r_box[7])+(y_gradient[8]*r_box[8]));
                     
                    if (sqrt( (bx*bx)+(by*by))>=255)
                    {
                        image[i][j].rgbtBlue = 255;
                    }else if (sqrt( (bx*bx)+(by*by))<=0)
                    {
                        image[i][j].rgbtBlue = 0;
                    }else
                    {
                        
                    image[i][j].rgbtBlue =(int)sqrt( (bx*bx)+(by*by));
                    }
                    if (sqrt( (gx*gx)+(gy*gy))>=255)
                    {
                     image[i][j].rgbtGreen = 255;
                    }else if (sqrt( (gx*gx)+(gy*gy))<=0)
                    {
                     image[i][j].rgbtGreen = 0;
                    }else
                    {
                        image[i][j].rgbtGreen = (int)sqrt((gx*gx )+(gy*gy));                  
                    }
                    if ( sqrt( (rx*rx)+(ry*ry))>=255)
                    {
                       image[i][j].rgbtRed = 255;
                    }else if ( sqrt( (rx*rx)+(ry*ry))<=0)
                    {
                       image[i][j].rgbtRed = 0;
                    
                    }else{
                         image[i][j].rgbtRed =(int) sqrt((rx*rx)+(ry*ry));
                    }


           
            
           
         }else
         {
             image[i][j].rgbtBlue = 0;
            image[i][j].rgbtGreen = 0;
            image[i][j].rgbtRed = 0;
         }
         
           
           
        }
    }
   
    return;
}


// makes calculations on the pixel based on the chosen kernal
void getKernalProduct(int i, int j,int height, int width, RGBTRIPLE originImage[height][width],RGBTRIPLE *pixel , int kernal[9]){
//  9 by 9 kernal for every color

    int b_box[9] = {originImage[i-1][j-1].rgbtBlue,originImage[i-1][j].rgbtBlue,originImage[i-1][j+1].rgbtBlue,
                        originImage[i][j-1].rgbtBlue,originImage[i][j].rgbtBlue,originImage[i][j+1].rgbtBlue,
                        originImage[i+1][j-1].rgbtBlue,originImage[i+1][j].rgbtBlue,originImage[i+1][j+1].rgbtBlue
                        };
    int g_box[9] = {originImage[i-1][j-1].rgbtGreen,originImage[i-1][j].rgbtGreen,originImage[i-1][j+1].rgbtGreen,
                        originImage[i][j-1].rgbtGreen,originImage[i][j].rgbtGreen,originImage[i][j+1].rgbtGreen,
                        originImage[i+1][j-1].rgbtGreen,originImage[i+1][j].rgbtGreen,originImage[i+1][j+1].rgbtGreen
                        };
    int r_box[9] = {originImage[i-1][j-1].rgbtRed,originImage[i-1][j].rgbtRed,originImage[i-1][j+1].rgbtRed,
                        originImage[i][j-1].rgbtRed,originImage[i][j].rgbtRed,originImage[i][j+1].rgbtRed,
                        originImage[i+1][j-1].rgbtRed,originImage[i+1][j].rgbtRed,originImage[i+1][j+1].rgbtRed
                        };
    (*pixel).rgbtBlue = ((kernal[0]*b_box[0])+(kernal[1]*b_box[1])+(kernal[2]*b_box[2])+(kernal[3]*b_box[3])+(kernal[4]*b_box[4])+(kernal[5]*b_box[5])+(kernal[6]*b_box[6])+(kernal[7]*b_box[7])+(kernal[8]*b_box[8]))/9;
    (*pixel).rgbtGreen = ((kernal[0]*g_box[0])+(kernal[1]*g_box[1])+(kernal[2]*g_box[2])+(kernal[3]*g_box[3])+(kernal[4]*g_box[4])+(kernal[5]*g_box[5])+(kernal[6]*g_box[6])+(kernal[7]*g_box[7])+(kernal[8]*g_box[8]))/9;
    (*pixel).rgbtRed = ((kernal[0]*r_box[0])+(kernal[1]*r_box[1])+(kernal[2]*r_box[2])+(kernal[3]*r_box[3])+(kernal[4]*r_box[4])+(kernal[5]*r_box[5])+(kernal[6]*r_box[6])+(kernal[7]*r_box[7])+(kernal[8]*r_box[8]))/9;

            
return ;
}